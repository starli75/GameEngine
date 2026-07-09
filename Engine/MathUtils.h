#pragma once

namespace nu::math
{
	constexpr float Pie = 3.14159265359f;
	constexpr float TwoPie = Pie * 2;
	constexpr float HalfPie = Pie / 2;

	template<typename T>
	T Min(T a, T b) {
		return (a < b) ? a : b;
	}

	template<typename T>
	T Max(T a, T b) {
		return (a > b) ? a : b;
	}

	template<typename T>
	T Wrap(T min, T max, T value) {
		if (value > max) value = min;
		if (value < min) value = max;

		return value;
	}

	template <typename T>
	T Clamp(T min, T max, T value) {


		if (value > max) value = max;
		if (value < min) value = min;

		return value;
	}
}