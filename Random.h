#pragma once

namespace core {
	namespace random {
		int getInt(int min = 0, int max = 32766);
		float getFloat(float min = 0.0f, float max = 1.0f);
		double getDouble(double min = 0.0f, double max = 1.0f);
	};
}