#pragma once

// バイトサイズを一定にする
template<class T,class U>
inline T Alignment(T base, U alignment)
{
	return ((base + alignment - 1) / alignment) * alignment;
}

// 引数未使用の警告対策
template<class T>
inline void UnusedArgment(T t)
{
	(t);
}

#define SafeRelease(object) \
do{object->Release(); object = nullptr;}while(0)
/*
↑のマクロをテンプレート関数にできない理由
template<class T>
inline void SafeRelease(T object)
{
	object->Release();
	object = nullptr;
}
Release関数を呼ぶところまではいいが
関数の引数のアドレスにnullptrを入れたところで何の意味もないため
マクロ関数ならコンパイル時に文字列をソースコードとして扱う為
その場のポインタにnullptrを入れアクセス不可になるためマクロでしかできない
ダブルポインタで受け取りnullptrを入れるということは可能だけど
テンプレートの理解が間違ってたらすいません
*/

#ifdef UNICODE
static const wchar_t* ErrorMessage = L"エラーが発生しました";
#else
static const char* ErrorMessage = "エラーが発生しました";
#endif // UNICODE
