#pragma once
#include <cstdint>
#include <chrono>

namespace Engine 
{

	enum class FPS : uint8_t
	{
		Thirty,	// 30�t���[�����[�g
		Sixty,	// 60�t���[�����[�g
	};

	// �t���[�����[�g30
	static const uint32_t FramePerSecond30 = 30;
	static const uint32_t FPS30 = FramePerSecond30;
	// (1000/30) = 33.33
	static const auto FPSChrono30 = std::chrono::milliseconds(33);
	// 30�t���[�����[�g�̍���
	static const float DeltaTime30 = 1.0f / 30.0f;

	// �t���[�����[�g60
	static const uint32_t FramePerSecond60 = 60;
	static const uint32_t FPS60 = FramePerSecond60;

	// 1�t���[�����[�g�Ŏg���鎞�� 1�b(1/60) = 1000�~���b(1000/60) = 16.66
	static const auto FPSChrono60 = std::chrono::milliseconds(16);
	// 60�t���[�����[�g�̍���
	static const float DeltaTime60 = 1.0f / 60.0f;

	//// �t���[�����[�g�ɕϊ�(�b)
	//static float ConvertSecondToFrameRate(float s) { return s * fps; }
	//// �t���[�����[�g�ɕϊ�(��)
	//static float ConvertMinuteToFrameRate(float m) { return ConvertSecondToFrameRate(m * 60); }
	//// �t���[�����[�g�ɕϊ�(��)
	//static float ConvertHourToFrameRate(float h) { return ConvertMinuteToFrameRate(h * 60); }
	
}