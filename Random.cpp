#include "Random.h"

#include <boost/random.hpp>
#include <ctime>

namespace {
	boost::random::mt19937 gRandomEngine(time(NULL));
}

namespace core {
	namespace random {
		int getInt(int min, int max) {
			boost::random::uniform_int_distribution<int> dist(min, max);
			return dist(gRandomEngine);
		}

		float getFloat(float min, float max) {
			boost::random::uniform_real_distribution<float> dist(min, max);
			return dist(gRandomEngine);
		}

		double getDouble(double min, double max) {
			boost::random::uniform_real_distribution<double> dist(min, max);
			return dist(gRandomEngine);
		}
	}
}