#pragma once
#include <cstdint>

namespace Engine 
{

	namespace AudioSystem
	{

		// �ǂݍ��ݕ��@
		enum class AudioClipLoadType : uint8_t
		{
			DecompressOnLoad,	// �𓀏�Ԃňꊇ�Ń������Ɋi�[
			CompressedInMemory,	// ���k���
			Streaming,			// �X�g���[�~���O
		};

	}

}