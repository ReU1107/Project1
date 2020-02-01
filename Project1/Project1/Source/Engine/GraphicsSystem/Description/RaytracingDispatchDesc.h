#pragma once
#include <cstdint>

namespace Engine
{

	namespace GraphicsSystem 
	{

		class IResource;

		struct RaytracingDispatchDesc
		{
			IResource* rayGenerate;		// ÉåÉCê∂ê¨
			IResource* missTable;		// 
			IResource* hitGroupTable;	// 

			uint32_t rayGenerateSize;	// ÉåÉCê∂ê¨óp
			
			uint32_t missStride;		// 
			uint32_t missSize;			// 

			uint32_t hitGroupStride;	// 
			uint32_t hitGroupSize;		// 

			uint32_t width;				// 
			uint32_t height;			// 
			uint32_t depth;				// 
		};

	}

}