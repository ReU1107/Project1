#pragma once

// �o�C�g�T�C�Y�����ɂ���
template<class T,class U>
inline T Alignment(T base, U alignment)
{
	return ((base + alignment - 1) / alignment) * alignment;
}

// �������g�p�̌x���΍�
template<class T>
inline void UnusedArgment(T t)
{
	(t);
}

#define SafeRelease(object) \
do{object->Release(); object = nullptr;}while(0)
/*
���̃}�N�����e���v���[�g�֐��ɂł��Ȃ����R
template<class T>
inline void SafeRelease(T object)
{
	object->Release();
	object = nullptr;
}
Release�֐����ĂԂƂ���܂ł͂�����
�֐��̈����̃A�h���X��nullptr����ꂽ�Ƃ���ŉ��̈Ӗ����Ȃ�����
�}�N���֐��Ȃ�R���p�C�����ɕ�������\�[�X�R�[�h�Ƃ��Ĉ�����
���̏�̃|�C���^��nullptr�����A�N�Z�X�s�ɂȂ邽�߃}�N���ł����ł��Ȃ�
�_�u���|�C���^�Ŏ󂯎��nullptr������Ƃ������Ƃ͉\������
�e���v���[�g�̗������Ԉ���Ă��炷���܂���
*/

#ifdef UNICODE
static const wchar_t* ErrorMessage = L"�G���[���������܂���";
#else
static const char* ErrorMessage = "�G���[���������܂���";
#endif // UNICODE
