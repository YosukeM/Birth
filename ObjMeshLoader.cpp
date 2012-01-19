#include "ObjMeshLoader.h"

#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/home/phoenix.hpp>

#include "Vector2d.h"
#include "Vector3d.h"

#include "IFileReader.h"

using namespace rsc;
using namespace meshloader;

namespace {
	const u32 UNDETERMINED = 0xFFFFFFFF;

	class ObjFile {
	public:
		class Index {
		public:
			u32 vertex, texcoord, normal;
			Index() : vertex(UNDETERMINED), texcoord(UNDETERMINED), normal(UNDETERMINED) {}
		};

		class Face {
		public:
			Index i1, i2, i3;
		};

		class Group {
		public:
			core::string material;
			core::vector<Face> faceList;
		};

		core::string materialFile;

		core::vector<float3d> vertexList;
		core::vector<float3d> normalList;
		core::vector<float2d> texCoordList;

		core::vector<Group> groups;
	};

}

using namespace boost::spirit;

BOOST_FUSION_ADAPT_STRUCT(
	float3d,
	(float, x)
	(float, y)
	(float, z)
);

BOOST_FUSION_ADAPT_STRUCT(
	float2d,
	(float, x)
	(float, y)
);

BOOST_FUSION_ADAPT_STRUCT(
	ObjFile,
	(core::string, materialFile)
	(core::vector<float3d>, vertexList)
	(core::vector<float3d>, normalList)
	(core::vector<float2d>, texCoordList)
	(core::vector<ObjFile::Group>, groups)
);

BOOST_FUSION_ADAPT_STRUCT(
	ObjFile::Group,
	(core::string, material)
	(core::vector<ObjFile::Face>, faceList)
);

BOOST_FUSION_ADAPT_STRUCT(
	ObjFile::Index,
	(u32, vertex)
	(u32, texcoord)
	(u32, normal)
);

BOOST_FUSION_ADAPT_STRUCT(
	ObjFile::Face,
	(ObjFile::Index, i1)
	(ObjFile::Index, i2)
	(ObjFile::Index, i3)
);

namespace {
	template <typename Iterator>
	class ObjParser : public qi::grammar<Iterator, ObjFile()>
	{
		qi::rule<Iterator, float3d()> float3d_;
		qi::rule<Iterator, float2d()> float2d_;
		qi::rule<Iterator, ObjFile::Index()> index_def;

		qi::rule<Iterator, float3d()> vert_line;
		qi::rule<Iterator, float3d()> normal_line;
		qi::rule<Iterator, float2d()> texcoord_line;
		qi::rule<Iterator, core::string()> group_line;
		qi::rule<Iterator, core::string()> usemtl_line;
		qi::rule<Iterator, core::string()> mtllib_line;
		qi::rule<Iterator, ObjFile::Face()> face_line;
		qi::rule<Iterator> surface_line;
		qi::rule<Iterator> comment_line;

		qi::rule<Iterator, ObjFile::Group()> group;

		qi::rule<Iterator, ObjFile()> start;

	public:
		ObjParser()
			: ObjParser::base_type(start)
		{
			using namespace qi;
			namespace phx = boost::phoenix;

			float3d_ %= float_ >> ' ' >> float_ >> ' ' >> float_;
			float2d_ %= float_ >> ' ' >> float_;
			index_def = eps[_val = phx::construct<ObjFile::Index>()]
					>> uint_[phx::at_c<0>(_val) = qi::_1 - 1]
					>> -('/' >> -(uint_[phx::at_c<1>(_val) = qi::_1 - 1])
						>> -('/' >> uint_[phx::at_c<2>(_val) = qi::_1 - 1])
					);

			vert_line %= "v " >> float3d_ >> eol;
			normal_line %= "vn " >> float3d_ >> eol;
			texcoord_line %= "vt " >> float2d_ >> eol;

			group_line %= "g " >> +(char_ - eol) >> eol;

			face_line %= "f " >> index_def >> ' ' >> index_def >> ' ' >> index_def >> eol;
			surface_line = "s " >> *(char_ - eol) >> eol;

			usemtl_line %= "usemtl " >> +(char_ - eol) >> eol;
			mtllib_line %= "mtllib " >> +(char_ - eol) >> eol;

			comment_line = '#' >> *(char_ - eol) >> eol | eol;

			group = eps[_val = phx::construct<ObjFile::Group>()]
					>> (
						usemtl_line[phx::at_c<0>(_val) = qi::_1]
						| face_line[phx::push_back(phx::at_c<1>(_val), qi::_1)]
					)
					>> *(
						face_line[phx::push_back(phx::at_c<1>(_val), qi::_1)]
						| comment_line
					);

			start = eps[_val = phx::construct<ObjFile>()]
					>> *(
						group_line
						| surface_line
						| vert_line[phx::push_back(phx::at_c<1>(_val), qi::_1)]
						| normal_line[phx::push_back(phx::at_c<2>(_val), qi::_1)]
						| texcoord_line[phx::push_back(phx::at_c<3>(_val), qi::_1)]
						| mtllib_line[phx::at_c<0>(_val) = qi::_1]
						| group[phx::push_back(phx::at_c<4>(_val), qi::_1)]
						| comment_line
					);
		}
	};

	template <typename Vert>
	Vert createVertex(const ObjFile::Index& i, const ObjFile& file) {
		Vert v;
		v.position = file.vertexList[i.vertex];
		if (file.normalList.size() > i.normal) v.setNormal(file.normalList[i.normal]);
		if (file.texCoordList.size() > i.texcoord) v.setTexCoord(file.texCoordList[i.texcoord]);
		return v;
	}

	template <typename Vert>
	void addMeshbuffer(core::vector<Mesh::meshbuffer_type>& mbs, ObjFile& file, ObjFile::Group& group) {
		ogl::Meshbuffer<Vert>* meshbuf = new ogl::Meshbuffer<Vert>();
		core::vector<Vert> verts;
		core::vector<u32> indices;
		foreach (const ObjFile::Face& face, group.faceList) {
			verts.push_back(createVertex<Vert>(face.i1, file));
			verts.push_back(createVertex<Vert>(face.i2, file));
			verts.push_back(createVertex<Vert>(face.i3, file));
			indices.push_back(indices.size());
			indices.push_back(indices.size());
			indices.push_back(indices.size());
		}
		meshbuf->generate(verts, indices);
		mbs.push_back(meshbuf);
	}

}

bool ObjMeshLoader::isAvailableExtension(const core::string& ext) const {
	return ext == "obj";
}

void ObjMeshLoader::load(core::shared_ptr<fs::IFileReader> reader, core::vector<Mesh::meshbuffer_type>& mbs) {
	core::string source;
	reader->getAllAsString(source);

	ObjFile value;
	ObjParser<core::string::iterator> parser;
	qi::parse(source.begin(), source.end(), parser, value);

	foreach (ObjFile::Group& group, value.groups) {
		if (!group.faceList.size()) continue;
		if (group.faceList[0].i1.texcoord != UNDETERMINED) {
			if (group.faceList[0].i1.normal != UNDETERMINED) {
				addMeshbuffer<ogl::Vertex3dTN>(mbs, value, group);
			} else {
				addMeshbuffer<ogl::Vertex3dT>(mbs, value, group);
			}
		} else {
			if (group.faceList[0].i1.normal != UNDETERMINED) {
				addMeshbuffer<ogl::Vertex3dN>(mbs, value, group);
			} else {
				addMeshbuffer<ogl::Vertex3d>(mbs, value, group);
			}
		}
	}
}
