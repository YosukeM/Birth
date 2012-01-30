#include "Application.h"

#include "rscMesh.h"
#include "oglMeshbuffer.h"

#include "Error.h"

#include "Sequence.h"
#include "TitleSequence.h"
#include "GameSequence.h"

#include <GL/glfw.h>
#include <boost/lexical_cast.hpp>

namespace {
	// �\����ʑS�̂𕢂��悤�ȕ��ʂ��쐬
	void createPlane(ogl::Meshbuffer<ogl::Vertex3dT, u16>& mesh) {
		std::vector<ogl::Vertex3dT> verts;
		ogl::Vertex3dT vert;
		vert.position = float3d(-1.0f, 1.0f, 0.0f);
		vert.texCoord = float2d(0.0f, 1.0f);
		verts.push_back(vert);
		vert.position = float3d(-1.0f, -1.0f, 0.0f);
		vert.texCoord = float2d(0.0f, 0.0f);
		verts.push_back(vert);
		vert.position = float3d(1.0f, -1.0f, 0.0f);
		vert.texCoord = float2d(1.0f, 0.0f);
		verts.push_back(vert);
		vert.position = float3d(1.0f, 1.0f, 0.0f);
		vert.texCoord = float2d(1.0f, 1.0f);
		verts.push_back(vert);

		std::vector<u16> indices;
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(3);

		mesh.generate(verts, indices, ogl::Meshbuffer<ogl::Vertex3dT, u16>::EDM_QUADS);
	}
}

Application::Application()
{
	// Extensions���m�F
	_checkExtensions();

	// ���ׂĂ�Sequence�����[�h����
	using namespace core;
	_seqs.push_back(shared_static_cast<Sequence>(make_shared<TitleSequence>()));
	_seqs.push_back(shared_static_cast<Sequence>(make_shared<GameSequence>()));
	_seq = _seqs[1];
}

Application::~Application() {

}

void Application::_checkExtensions() {
	core::vector<core::string> errors;

	// Extension�̗L���𒲂ׂ�
	if (!GLEW_EXT_framebuffer_object) errors.push_back("Framebuffer object is not supported");
	if (!GLEW_EXT_texture_rectangle) errors.push_back("Texture rectangle is not supported");

	// OpenGL�̃o�[�W�����𒲂ׂ�
	// �o�[�W�����̏����Ɋւ���K�i���Ȃ��̂ŁA�p�[�X�̎d���͓K���ł���B
	try {
		core::string version(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		if (version.size() > 3) {
			double v = boost::lexical_cast<double>(version.substr(0, 3));
			if (v < 2.0) errors.push_back(core::string("Your OpenGL version is ") + version + ", require 2.0 or greater");
		}
	} catch (...) {
	}

	// �G���[���������瓊����
	if (errors.size()) {
		core::string message;
		foreach (const core::string& str, errors) {
			message += str + "\n";
		}
		throw Error(message);
	}
}

void Application::update(f32 delta_time) {
	if (delta_time > 1.0f) delta_time = 1.0f;

	// �ŏ��t���[�����[�g��60�Ƃ���B
	f32 internal_frames_num = std::ceil(delta_time / (1.0f / 60.0f));
	f32 small_dt = delta_time / internal_frames_num;

	// Sequence��update
	core::shared_ptr<Sequence> next_seq;
	for (u32 counter = u32(internal_frames_num); counter > 0; --counter) {
		next_seq = _seq->update(small_dt);
		if (next_seq) {
			_seq = next_seq;
			next_seq.reset();
		}
	}

	// �`��
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_seq->draw();
}

void Application::onResize(const uint2d& viewport_size) {
	_seq->onResize(viewport_size);
}

bool Application::onClose() {
	return true;
}
