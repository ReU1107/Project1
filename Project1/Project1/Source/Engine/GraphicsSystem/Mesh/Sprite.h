#pragma once
#include <array>
#include <vector>
#include "..//..//Math/Vector2.h"

namespace Engine
{
	struct Rect;
	namespace GraphicsSystem
	{
		class VertexBuffer;
		class Texture;

		class Sprite
		{
		private:
			using VertexBuffers = std::array<VertexBuffer*, 2>;
			using Positions = std::vector<Vector2>;
			using Texcoords = std::vector<Vector2>;
			using SpritePtr = std::shared_ptr<Sprite>;
		private:
			VertexBuffers m_vertexBuffers;	// 頂点バッファ配列
			Positions m_positions;			// 位置座標	
			Texcoords m_texcoords;			// 
			Texture* m_texture;				// テクスチャ
		public:
			// コンストラクタ
			Sprite();
			// デストラクタ
			~Sprite();

			static Sprite* Create(Texture* texture, const Rect& rect);

			static Sprite* Create(const Rect& rect);

			VertexBuffers& GetVertexBuffers() { return m_vertexBuffers; }

		};
	}
}