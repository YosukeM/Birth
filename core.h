#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/scoped_ptr.hpp>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <boost/variant.hpp>
#include <boost/circular_buffer.hpp>
#include <array>
#include <functional>
#include <tuple>

namespace core {
	using boost::shared_ptr;
	using boost::scoped_ptr;
	using boost::make_shared;
	using boost::shared_dynamic_cast;
	using boost::shared_static_cast;

	using std::string;
	using std::vector;
	using std::list;
	using std::deque;
	using std::map;
	using std::set;
	using std::unordered_map;
	using std::unordered_set;
	using boost::circular_buffer;
	using std::array;

	using std::tuple;
	using boost::variant;

	using std::function;
}
