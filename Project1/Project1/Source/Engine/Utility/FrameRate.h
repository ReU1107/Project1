#pragma once
#include <cstdint>
#include <chrono>

namespace Engine 
{

	enum class FPS : uint8_t
	{
		Thirty,	// 30フレームレート
		Sixty,	// 60フレームレート
	};

	// フレームレート30
	static const uint32_t FramePerSecond30 = 30;
	static const uint32_t FPS30 = FramePerSecond30;
	// (1000/30) = 33.33
	static const auto FPSChrono30 = std::chrono::milliseconds(33);
	// 30フレームレートの差分
	static const float DeltaTime30 = 1.0f / 30.0f;

	// フレームレート60
	static const uint32_t FramePerSecond60 = 60;
	static const uint32_t FPS60 = FramePerSecond60;

	// 1フレームレートで使える時間 1秒(1/60) = 1000ミリ秒(1000/60) = 16.66
	static const auto FPSChrono60 = std::chrono::milliseconds(16);
	// 60フレームレートの差分
	static const float DeltaTime60 = 1.0f / 60.0f;

	//// フレームレートに変換(秒)
	//static float ConvertSecondToFrameRate(float s) { return s * fps; }
	//// フレームレートに変換(分)
	//static float ConvertMinuteToFrameRate(float m) { return ConvertSecondToFrameRate(m * 60); }
	//// フレームレートに変換(時)
	//static float ConvertHourToFrameRate(float h) { return ConvertMinuteToFrameRate(h * 60); }
	
}