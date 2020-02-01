#include "Sprite.h"
#include "..//Texture/Texture.h"
#include "..//..//Math/Rect.h"
#include "..//HardwareBuffer/VertexBuffer.h"

//https://madaopnob.wixsite.com/files
namespace Engine
{
	namespace GraphicsSystem
	{
		Sprite::Sprite()
			: m_vertexBuffers()
			, m_texture(nullptr)
		{
		}

		Sprite::~Sprite()
		{
		}

		Sprite* Sprite::Create(Texture* texture, const Rect& rect)
		{
			const float left = rect.left;
			const float right = rect.right;
			const float top = rect.top;
			const float bottom = rect.bottom;
			Positions positions(4);
			
			positions[0] = { left,top };
			positions[1] = { right,top };
			positions[2] = { left,bottom };
			positions[3] = { right,bottom };
			
			VertexBuffer* vertexBuffer = new VertexBuffer();
			vertexBuffer->SetStride(sizeof(Vector2));
			vertexBuffer->SetCount(4);
			vertexBuffer->Create(positions.data());

			Sprite* sprite = new Sprite();
			sprite->m_texture = texture;
			sprite->m_positions = std::move(positions);
			sprite->m_vertexBuffers[0] = vertexBuffer;

			return sprite;
		}

		Sprite* Sprite::Create(const Rect& rect)
		{
			const float left = rect.left;
			const float right = rect.right;
			const float top = rect.top;
			const float bottom = rect.bottom;
			Positions positions(4);

			positions[0] = { left,top };
			positions[1] = { right,top };
			positions[2] = { left,bottom };
			positions[3] = { right,bottom };

			Texcoords texcoords(4);
			texcoords[0] = { Vector2(0.0f,0.0f) };
			texcoords[1] = { Vector2(1.0f,0.0f) };
			texcoords[2] = { Vector2(0.0f,1.0f) };
			texcoords[3] = { Vector2(1.0f,1.0f) };

			VertexBuffer* vertexBuffers[2] = {};
			for (uint32_t i = 0; i < 2; ++i)
			{
				vertexBuffers[i] = new VertexBuffer();
				vertexBuffers[i]->SetStride(sizeof(Vector2));
				vertexBuffers[i]->SetCount(4);
			}

			vertexBuffers[0]->Create(positions.data());
			vertexBuffers[1]->Create(texcoords.data());

			Sprite* sprite = new Sprite();
			sprite->m_positions = std::move(positions);
			sprite->m_texcoords = std::move(texcoords);
			sprite->m_vertexBuffers[0] = vertexBuffers[0];
			sprite->m_vertexBuffers[1] = vertexBuffers[1];

			return sprite;
		}
	}
}