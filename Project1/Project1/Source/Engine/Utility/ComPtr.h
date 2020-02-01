#pragma once
#include <cstdint>

namespace Engine 
{

	/*
	Component Object Model �p
	�}�C�N���\�t�g���ŗp�ӂ���Ă���
	�������炵�����O��Ԃɓ����Ă��܂�
	*/

	template<class Interface>
	class ComponentPtr
	{
	private:
		Interface* m_ptr;		// �|�C���^
		uint64_t m_refCount;	// �Q�ƃJ�E���g
	public:
		ComponentPtr();
		~ComponentPtr();

	public:
		uint64_t AddRef();

		uint64_t Release();

	};

}