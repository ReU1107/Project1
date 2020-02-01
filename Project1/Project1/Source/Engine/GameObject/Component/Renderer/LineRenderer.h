#pragma once
#include "Renderer.h"
#include "../../../Math/Include.h"

namespace Engine 
{
	namespace GraphicsSystem
	{
		class VertexBuffer;
		class IndexBuffer;
	}

	enum class LineSpace : uint8_t
	{
		None,
		Viewport,		// ビューポート空間に表示(2D)
		Local			// ローカル空間に表示(3D)ワールド空間
	};

	struct LineVertex2D
	{
		Vector2 position;
		Color4 color;
	};
	struct LineVertex3D
	{
		Vector3 position;
		Color4 color;
	};

	class LineRenderer final : public Renderer
	{
	private:
		using base = Renderer;
		using VertexBufferPtr = GraphicsSystem::VertexBuffer*;
		using IndexBufferPtr = GraphicsSystem::IndexBuffer*;
		using Vertices2D = std::vector<LineVertex2D>;
		using Vertices3D = std::vector<LineVertex3D>;
		using Indices = std::vector<uint32_t>;

		struct Information2D
		{
			Vector2 start;	// 開始位置
			Vector2 end;	// 終了位置
			Color4 color;	// 線の色
			float width;	// 線の幅
		};

		struct Information3D
		{
			Vector3 start;		// 開始位置
			Vector3 end;		// 終了位置
			Color4 startColor;	// 線の色
			Color4 endColor;	// 線の色
			float width;		// 線の幅
		};

		using Lines2D = std::vector<Information2D>;
		using Lines3D = std::vector<Information3D>;

	private:
		mutable Lines2D m_lines2D;				// 線情報配列
		mutable Lines3D m_lines3D;				// 線情報配列3D
		mutable Vertices2D m_vertices2D;		// 
		mutable Vertices3D m_vertices3D;		// 
		mutable Indices m_indices;

		VertexBufferPtr m_vertexBuffer;			// 頂点バッファ
		IndexBufferPtr m_indexBuffer;			// インデックスバッファ
		uint32_t m_maxLineCount;				// 最大線格納数
		mutable uint32_t m_lineCount;			// ライン数

		LineSpace m_space;						// 
		mutable bool m_isDirty;					// 

	public:
		// コンストラクタ
		LineRenderer(LineSpace space = LineSpace::Local, const uint32_t maxLineCount = 512) noexcept;
		// デストラクタ
		virtual ~LineRenderer() noexcept;
		// ID取得
		static const InstanceID ID() { return InstanceID::LineRenderer; }

		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::LineRenderer; }
	public:
		// 線情報追加
		void AddLine2D(const Vector2& start, const Vector2& end, const Color4& color = Color4::Blue, const float width = 50.0f);

		// 線情報設定
		void AddLine3D(const Vector3& start, const Vector3& end, const Color4& color, const float width = 2.0f);
		void AddLine3D(const Vector3& start, const Vector3& end, const Color4& startColor, const Color4& endColor, const float width = 2.0f);

		VertexBufferPtr GetVertexBuffer() const;

		IndexBufferPtr GetIndexBuffer() const;

		uint32_t GetUseIndexCount() const;

		void Clear();

	private:
		void Update2D() const;

		void Update3D() const;
	};

}

using LineRendererPtr = std::shared_ptr<Engine::LineRenderer>;