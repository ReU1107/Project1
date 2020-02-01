#pragma once

#define DeclareIUnknownInterfaces() \
private: \
	int m_referenceCount = 1; \
public: \
virtual size_t AddRef() override { return ++m_referenceCount;} \
virtual size_t Release() override \
{ \
	if (--m_referenceCount <= 0) \
	{ \
		delete this; \
		return 0; \
	} \
	return m_referenceCount; \
} \
virtual bool QueryInterface(const _GUID& guid, void** object) override;



namespace Engine {


		class __declspec(uuid("B4FB7711-C2D1-4231-BA21-2125CBFC1D16")) IUnknown
		{
		public:
			// 参照カウントインクリメント
			virtual size_t AddRef() = 0;

			// 参照カウントデクリメント
			virtual size_t Release() = 0;

			// クエリー
			virtual bool QueryInterface(const _GUID& guid, void** object) = 0;
		};

	

}