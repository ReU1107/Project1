#include "LineRenderer.h"
#include "../../../GraphicsSystem/HardwareBuffer/VertexBuffer.h"
#include "../../../GraphicsSystem/HardwareBuffer/IndexBuffer.h"
#include "../../../../Resolution.h"

namespace Engine 
{
	using namespace GraphicsSystem;

	LineRenderer::LineRenderer(LineSpace space, const uint32_t maxLineCount) noexcept
		: base("LineRenderer")
		, m_vertexBuffer(nullptr)
		, m_indexBuffer(nullptr)
		, m_maxLineCount(maxLineCount)
		, m_lineCount(0)
		, m_space(space)
		, m_isDirty(false)
	{
		m_vertexBuffer = new VertexBuffer();

		if (space == LineSpace::Local)
		{
			m_lines3D.reserve(m_maxLineCount);
			m_vertexBuffer->SetStride(sizeof(LineVertex3D));
			m_vertices3D.resize(m_maxLineCount * 6);
		}
		else
		{
			// vector領域確保
			m_lines2D.reserve(m_maxLineCount);
			m_vertexBuffer->SetStride(sizeof(LineVertex2D));
			m_vertices2D.resize(m_maxLineCount * 6);
		}

		m_vertexBuffer->SetCount(m_maxLineCount * 6);
		m_vertexBuffer->Dynamic();
		m_vertexBuffer->Create();

		m_indexBuffer = new IndexBuffer();
		m_indexBuffer->SetCount(m_maxLineCount * 6);
		m_indexBuffer->Dynamic();
		m_indexBuffer->Create();
		m_indices.resize(m_maxLineCount * 6);
	}

	LineRenderer::~LineRenderer() noexcept
	{
		delete m_vertexBuffer;
	}

	void LineRenderer::AddLine2D(const Vector2& start, const Vector2& end, const Color4& color, const float width)
	{
		if (m_space != LineSpace::Viewport)
		{
			assert(!"このラインレンダラーは3D用です");
		}
		// 領域外アクセス防止
		if (m_lines2D.size() + 1 > m_maxLineCount)
		{
			assert(!"格納数を超えています");
		}

		Information2D line;
		line.start = start;
		line.end = end;
		line.color = color;
		line.width = width;

		m_lines2D.push_back(line);
		m_lineCount++;
		m_isDirty = true;
	}

	void LineRenderer::AddLine3D(const Vector3& start, const Vector3& end, const Color4& color, const float width)
	{
		if (m_space != LineSpace::Local)
		{
			assert(!"このラインレンダラーは2D用です");
		}
		// 領域外アクセス防止
		if (m_lines3D.size() + 1 > m_maxLineCount)
		{
			assert(!"格納数を超えています");
		}

		Information3D line;
		line.start = start;
		line.end = end;
		line.startColor = color;
		line.endColor = color;
		line.width = width;

		m_lines3D.push_back(line);
		m_lineCount++;
		m_isDirty = true;
	}

	void LineRenderer::AddLine3D(const Vector3& start, const Vector3& end, const Color4& startColor, const Color4& endColor, const float width)
	{
		if (m_space != LineSpace::Local)
		{
			assert(!"このラインレンダラーは2D用です");
		}
		// 領域外アクセス防止
		if (m_lines3D.size() + 1 > m_maxLineCount)
		{
			assert(!"格納数を超えています");
		}

		Information3D line;
		line.start = start;
		line.end = end;
		line.startColor = startColor;
		line.endColor = endColor;
		line.width = width;

		m_lines3D.push_back(line);
		m_lineCount++;
		m_isDirty = true;
	}

	LineRenderer::VertexBufferPtr LineRenderer::GetVertexBuffer() const
	{
		if (m_space == LineSpace::Viewport)
		{
			Update2D();
		}
		else
		{
			Update3D();
		}
		
		return m_vertexBuffer;
	}

	LineRenderer::IndexBufferPtr LineRenderer::GetIndexBuffer() const
	{
		if (m_space == LineSpace::Viewport)
		{
			Update2D();
		}
		else
		{
			Update3D();
		}
		return m_indexBuffer;
	}

	uint32_t LineRenderer::GetUseIndexCount() const
	{
		return m_lineCount * 6;
	}

	void LineRenderer::Clear()
	{
		m_lines3D.clear();
		m_lineCount = 0;
	}

	void LineRenderer::Update2D() const
	{
		if (m_isDirty)
		{
			uint32_t start = 0;
			for (const auto& line : m_lines2D)
			{
				// 開始位置から終了位置へ向かうベクトル
				Vector2 vector;
				vector.x = line.end.x - line.start.x;
				vector.y = line.end.y - line.start.y;

				// ベクトルの長さ
				const float length = sqrt((line.start.x * line.start.x) + (line.end.y * line.end.y));
				if (length < 0.5f)
					continue;

				// 幅の長さに変更
				vector.x *= (line.width / 2) / (length);
				vector.y *= (line.width / 2) / (length);

				auto& destination = m_vertices2D[start];

				// 開始位置(-90度回転)
				destination.position.x = line.start.x + vector.y;
				destination.position.y = line.start.y - vector.x;
				destination.position.x = (destination.position.x / ResolutionWidth) * 2 - 1;
				destination.position.y = 1 - (destination.position.y / ResolutionHeight) * 2;
				destination.color = line.color;
				start++;

				destination = m_vertices2D[start];

				// 終了位置(-90度回転)
				destination.position.x = line.end.x + vector.y;
				destination.position.y = line.end.y - vector.x;
				destination.color = line.color;
				destination.position.x = (destination.position.x / ResolutionWidth) * 2 - 1;
				destination.position.y = 1 - (destination.position.y / ResolutionHeight) * 2;
				start++;

				destination = m_vertices2D[start];

				// 開始位置(90度回転)
				destination.position.x = line.start.x - vector.y;
				destination.position.y = line.start.y + vector.x;
				destination.color = line.color;
				destination.position.x = (destination.position.x / ResolutionWidth) * 2 - 1;
				destination.position.y = 1 - (destination.position.y / ResolutionHeight) * 2;
				start++;

				destination = m_vertices2D[start];

				// 終了位置(90度回転)
				destination.position.x = line.end.x - vector.y;
				destination.position.y = line.end.y + vector.x;
				destination.color = line.color;
				destination.position.x = (destination.position.x / ResolutionWidth) * 2 - 1;
				destination.position.y = 1 - (destination.position.y / ResolutionHeight) * 2;
				start++;

			}

			// 情報クリア
			m_lines2D.clear();
			m_lineCount = 0;

			m_isDirty = false;
		}
	}

	void LineRenderer::Update3D() const
	{
		if (m_isDirty)
		{
			uint32_t index = 0;
			for (const auto& line : m_lines3D)
			{
				// 開始位置から終了位置へ向かうベクトル
				Vector3 vector = line.end - line.start;
				// ベクトルの長さ
				const float length = sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
				if (length < 0.5f)
					continue;

				// 幅の長さに変更
				vector *= (line.width / 2) / (length);

				// ベクトルの回転を参照

				// 開始位置(-90度回転)
				m_vertices3D[index].position.x = line.start.x + vector.z;
				m_vertices3D[index].position.y = line.start.y - vector.y;
				m_vertices3D[index].position.z = line.start.z + vector.x;
				m_vertices3D[index].color = line.startColor;
				m_indices[index] = index;
				index++;

				// 終了位置(-90度回転)
				m_vertices3D[index].position.x = line.end.x + vector.z;
				m_vertices3D[index].position.y = line.end.y - vector.y;
				m_vertices3D[index].position.z = line.end.z + vector.x;
				m_vertices3D[index].color = line.endColor;
				m_indices[index] = index;
				index++;

				// 開始位置(90度回転)
				m_vertices3D[index].position.x = line.start.x + vector.z;
				m_vertices3D[index].position.y = line.start.y + vector.y;
				m_vertices3D[index].position.z = line.start.z - vector.x;
				m_vertices3D[index].color = line.startColor;
				m_indices[index] = index;
				index++;

				// 開始位置(90度回転)
				m_vertices3D[index].position.x = line.start.x + vector.z;
				m_vertices3D[index].position.y = line.start.y + vector.y;
				m_vertices3D[index].position.z = line.start.z - vector.x;
				m_vertices3D[index].color = line.startColor;
				m_indices[index] = index;
				index++;

				// 終了位置(-90度回転)
				m_vertices3D[index].position.x = line.end.x + vector.z;
				m_vertices3D[index].position.y = line.end.y - vector.y;
				m_vertices3D[index].position.z = line.end.z + vector.x;
				m_vertices3D[index].color = line.endColor;
				m_indices[index] = index;
				index++;

				// 終了位置(90度回転)
				m_vertices3D[index].position.x = line.end.x + vector.z;
				m_vertices3D[index].position.y = line.end.y + vector.y;
				m_vertices3D[index].position.z = line.end.z - vector.x;
				m_vertices3D[index].color = line.endColor;
				m_indices[index] = index;
				index++;

			}

			m_vertexBuffer->Update(m_vertices3D.data());

			m_indexBuffer->Update(m_indices.data());

			// 情報クリア
			m_lines3D.clear();
			m_lineCount = 0;

			m_isDirty = false;
		}
	}

}
