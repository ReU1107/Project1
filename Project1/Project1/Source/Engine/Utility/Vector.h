#pragma once
#include <cstdint>
#include <cassert>

namespace Engine 
{
	/*
	���[�u�����ł��Ȃ�
	�R�s�[������̂ł͂Ȃ�
	����Ă���ϒ��z��I�u�W�F�N�g
	�̎��̂̎Q�Ƃ�Ⴂ���g��ύX���Ă�������
	*/

	template<class T>
	class Vector
	{
	private:
		T* m_array;			// �f�[�^�z��
		uint32_t m_maxSize;	// �ő�e��
		uint32_t m_index;	// �i�[�ςݔԍ�
	public:
		// �R���X�g���N�^
		Vector(size_t size = 8);
		// �R�s�[�R���X�g���N�^(�Ȃ�)
		Vector(const Vector<T>& other) = delete;
		// ������Z�q(�Ȃ�)
		Vector& operator=(const Vector<T>& other) = delete;
		// ���[�u�R���X�g���N�^
		Vector(Vector<T>&& other);

		// �f�X�g���N�^
		~Vector();

	public:
		// []operator���Z�q�I�[�o�[���[�h
		inline T operator[](uint32_t index);

		// �C���f�b�N�X�Ԗڂ̔z��ɃA�N�Z�X
		inline T At(uint32_t index);

		// �ő�T�C�Y�ύX
		inline void Resize(uint32_t size);

		// �����ɒǉ�
		inline void PushBack(T value);

		// �z��̐擪�A�h���X�擾
		inline T* GetArray() const;

		// �T�C�Y
		inline uint32_t GetSize() const;

		inline void Clear();

	};

	template<class T>
	inline Vector<T>::Vector(size_t size)
		: m_array(nullptr)
		, m_maxSize(size)
		, m_index(0)
	{
		m_array = new T[size];
	}

	template<class T>
	inline Vector<T>::Vector(Vector<T>&& other)
		: m_array(other.m_array)
		, m_maxSize(other.m_maxSize)
		, m_index(other.m_index)
	{
		other.m_array = nullptr;
		other.m_maxSize = 0;
		other.m_index = 0;
	}

	template<class T>
	inline Vector<T>::~Vector()
	{
		delete[] m_array;
	}

	template<class T>
	inline T Vector<T>::operator[](uint32_t index)
	{
		assert(!(index > m_maxSize) && "�z��O���w���Ă��܂�");
		return m_array[index];
	}

	template<class T>
	inline T Vector<T>::At(uint32_t index)
	{
		assert(!(index > m_maxSize) && "�z��O���w���Ă��܂�");
		return m_array[index];
	}

	template<class T>
	inline void Vector<T>::Resize(uint32_t size)
	{
		m_maxSize = size;
		T* tmpArray = new T[size];
		// ���݂̈ʒu�܂ł̒l��S�ăR�s�[����
		for (size_t i = 0; i < m_index; i++) {
			tmpArray[i] = m_array[i];
		}
		delete[] m_array;
		m_array = tmpArray;
	}

	template<class T>
	inline void Vector<T>::PushBack(T value)
	{
		// �i�[�\���𒴂��Ă���ꍇ�T�C�Y�̑傫����{�ɕύX����
		if (m_index + 1 > m_maxSize)
			Resize(m_maxSize * 2);

		m_array[m_index++] = value;
	}

	template<class T>
	inline T* Vector<T>::GetArray() const
	{
		return m_array;
	}

	template<class T>
	inline uint32_t Vector<T>::GetSize() const
	{
		return m_index;
	}

	template<class T>
	inline void Vector<T>::Clear()
	{
		delete[] m_array;
	}

}