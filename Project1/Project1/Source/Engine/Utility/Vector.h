#pragma once
#include <cstdint>
#include <cassert>

namespace Engine 
{
	/*
	ムーブしかできない
	コピーをするのではなく
	作られている可変長配列オブジェクト
	の実体の参照を貰い中身を変更してください
	*/

	template<class T>
	class Vector
	{
	private:
		T* m_array;			// データ配列
		uint32_t m_maxSize;	// 最大容量
		uint32_t m_index;	// 格納済み番号
	public:
		// コンストラクタ
		Vector(size_t size = 8);
		// コピーコンストラクタ(なし)
		Vector(const Vector<T>& other) = delete;
		// 代入演算子(なし)
		Vector& operator=(const Vector<T>& other) = delete;
		// ムーブコンストラクタ
		Vector(Vector<T>&& other);

		// デストラクタ
		~Vector();

	public:
		// []operator演算子オーバーロード
		inline T operator[](uint32_t index);

		// インデックス番目の配列にアクセス
		inline T At(uint32_t index);

		// 最大サイズ変更
		inline void Resize(uint32_t size);

		// 末尾に追加
		inline void PushBack(T value);

		// 配列の先頭アドレス取得
		inline T* GetArray() const;

		// サイズ
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
		assert(!(index > m_maxSize) && "配列外を指しています");
		return m_array[index];
	}

	template<class T>
	inline T Vector<T>::At(uint32_t index)
	{
		assert(!(index > m_maxSize) && "配列外を指しています");
		return m_array[index];
	}

	template<class T>
	inline void Vector<T>::Resize(uint32_t size)
	{
		m_maxSize = size;
		T* tmpArray = new T[size];
		// 現在の位置までの値を全てコピーする
		for (size_t i = 0; i < m_index; i++) {
			tmpArray[i] = m_array[i];
		}
		delete[] m_array;
		m_array = tmpArray;
	}

	template<class T>
	inline void Vector<T>::PushBack(T value)
	{
		// 格納可能数を超えている場合サイズの大きさを倍に変更する
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