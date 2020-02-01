#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		enum class LogicOperation : uint8_t
		{
			Clear,			// �N���A
			Set,			// �ݒ�
			Copy,			// �R�s�[
			InvertedCopy,	// ���]�R�s�[
			None,			// �Ȃɂ����Ȃ�
			Inverted,		// ���]
			And,			// �_��AND���Z�q
			NotAnd,			// �_��NAND���Z�q
			Or,				// �_��OR���Z�q
			NotOr,			// �_��NOR���Z�q
			ExclusiveOr,	// �_��XOR���Z�q
			Equivalent,		// �_������
			AndReverse,		// 
			AndInverted,	// 
			OrReverse,		//
			OrInverted,		// 
		};
	}
}