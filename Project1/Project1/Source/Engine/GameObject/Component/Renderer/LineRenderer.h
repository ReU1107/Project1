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
		Viewport,		// �r���[�|�[�g��Ԃɕ\��(2D)
		Local			// ���[�J����Ԃɕ\��(3D)���[���h���
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
			Vector2 start;	// �J�n�ʒu
			Vector2 end;	// �I���ʒu
			Color4 color;	// ���̐F
			float width;	// ���̕�
		};

		struct Information3D
		{
			Vector3 start;		// �J�n�ʒu
			Vector3 end;		// �I���ʒu
			Color4 startColor;	// ���̐F
			Color4 endColor;	// ���̐F
			float width;		// ���̕�
		};

		using Lines2D = std::vector<Information2D>;
		using Lines3D = std::vector<Information3D>;

	private:
		mutable Lines2D m_lines2D;				// �����z��
		mutable Lines3D m_lines3D;				// �����z��3D
		mutable Vertices2D m_vertices2D;		// 
		mutable Vertices3D m_vertices3D;		// 
		mutable Indices m_indices;

		VertexBufferPtr m_vertexBuffer;			// ���_�o�b�t�@
		IndexBufferPtr m_indexBuffer;			// �C���f�b�N�X�o�b�t�@
		uint32_t m_maxLineCount;				// �ő���i�[��
		mutable uint32_t m_lineCount;			// ���C����

		LineSpace m_space;						// 
		mutable bool m_isDirty;					// 

	public:
		// �R���X�g���N�^
		LineRenderer(LineSpace space = LineSpace::Local, const uint32_t maxLineCount = 512) noexcept;
		// �f�X�g���N�^
		virtual ~LineRenderer() noexcept;
		// ID�擾
		static const InstanceID ID() { return InstanceID::LineRenderer; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::LineRenderer; }
	public:
		// �����ǉ�
		void AddLine2D(const Vector2& start, const Vector2& end, const Color4& color = Color4::Blue, const float width = 50.0f);

		// �����ݒ�
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