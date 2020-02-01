#pragma once
#include <cassert>
namespace Engine 
{
	/*
	�ێ����Ă���N���X�̓q�[�v�̈��
	�m�ۂ��Ă���A�h���X�͐ÓI�̈�Ɋm��
	*/
	// Base�N���X���V���O���g���Ƃ��ĕێ�
	template<class Base>
	class SingletonHolder final
	{
	private:
		static Base* s_instance;		// �C���X�^���X

	public:
		// �R���X�g���N�^
		SingletonHolder() = delete;
		// �f�X�g���N�^
		~SingletonHolder() {};
		// ���[�u�R���X�g���N�^
		SingletonHolder(SingletonHolder&&) = delete;
		// �R�s�[�R���X�g���N�^
		SingletonHolder(const SingletonHolder&) = delete;
		// ������Z�q
		SingletonHolder& operator=(const SingletonHolder&) = delete;

	public:
		// �V�X�e���N��
		static void Startup()
		{
			assert(!s_instance);
			// Base�̃R���X�g���N�^
			s_instance = new Base();
		}

		// �V�X�e���I��
		static void Shutdown()
		{
			assert(s_instance);
			delete s_instance;
			s_instance = nullptr;
		}
		// �C���X�^���X�擾
		static Base* GetPtr() { assert(s_instance); return s_instance; }

		static Base& Get() { assert(s_instance); return *s_instance; }

	};

	template<class Base>
	typename Base* SingletonHolder<Base>::s_instance = nullptr;
}
/*
typename��
�e���v���[�g��Base���N���X�^�ł���ƃR���p�C���[�ɖ����I�Ɏ����Ă���
���ꂪ�Ȃ���Base�����������炸�G���[�ɂȂ�
*/

// https://mickey24.hatenablog.com/entry/20110103/1294065116