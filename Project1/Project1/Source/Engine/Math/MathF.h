#pragma once

namespace Engine
{

	struct MathF
	{

		// ����Ȃ�0�ɋ߂��l
		static constexpr float Epsilon = 0.00001f;
		// ��������
		static constexpr float Infinity = 3.402823466e+38f;
		// ���̖�������
		static constexpr float NegativeInfinity = -Infinity;
		// �~����
		static constexpr float PI = 3.14159265359f;
		// 
		static constexpr float PI2 = PI * 2.0f;
		// 
		static constexpr float PIDiv2 = PI / 2.0f;

		// ���W�A������x
		static constexpr float RadToDeg = 360.0f / (PI * 2);
		// �x���烉�W�A��
		static constexpr float DegToRad = (PI * 2) / 360.0f;

		// �قڃ[�����ۂ�
		inline static bool NearZero(float value);

		// �x���烉�W�A���ɕϊ�
		inline static float ConvertDegreeToRadian(float degree);

		// ���W�A������x�ɕϊ�
		inline static float ConvertRadianToDegree(float radian);

		// �񐔂��ǂ���
		inline static bool IsNotANumber(float value);

		// �傫������Ԃ�
		inline static float Max(float lhs, float rhs);

		// ����������Ԃ�
		inline static float Min(float lhs, float rhs);

		// �͈͐���
		inline static float Clamp(float source, float max, float min);

		// �u�����h�W��
		inline static float BlendCoefficient(float current, float left, float right);

		// �R�T�C��
		inline static float Cos(float angle);
		// �T�C��
		inline static float Sin(float angle);
		//�^���W�F���g
		inline static float Tan(float angle);

		// �A�[�N�R�T�C��
		inline static float ACos(float);
		// �A�[�N�T�C��
		inline static float ASin(float);
		// �A�[�N�^���W�F���g
		inline static float ATan(float);
		inline static float ATan2(float, float);
	};
}
// ����
#include "MathFImpl.h"