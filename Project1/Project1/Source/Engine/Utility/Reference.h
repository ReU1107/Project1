#pragma once
#include <cstdint>

namespace Engine 
{
	/*
	AddRef Additional ReferenceCount
	DirectX�Ɠ����悤�ɖ��O��t����
	*/
	// �Q�ƃJ�E���g
	class Reference
	{
	private:
		uint32_t m_refCount;	// �Q�ƃJ�E���g
	public:
		// �R���X�g���N�^
		Reference() noexcept;
		// ���z�f�X�g���N�^
		virtual ~Reference() noexcept {}
	public:

		// �Q�ƃJ�E���g����
		uint32_t AddRef();

		// ���
		uint32_t Release();
	};
}
