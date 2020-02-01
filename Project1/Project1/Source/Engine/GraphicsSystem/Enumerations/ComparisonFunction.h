#pragma once
#include <cstdint>

namespace Engine
{
	namespace GraphicsSystem
	{
		// ”äŠrŠÖ”
		enum class ComparisonFunction : uint8_t
		{
			Never,			// ‘S‚Ä•s‡Ši
			Less,			// ¬‚«‚¢‚È‚ç‡Ši
			Equal,			// “™‚µ‚¢‚È‚ç‡Ši
			LessEqual,		// ˆÈ‰º‚È‚ç‡Ši
			Greater,		// ‘å‚«‚¢‚È‚ç‡Ši
			NotEqual,		// “™‚µ‚­‚È‚¢‚È‚ç‡Ši
			GreaterEqual,	// ˆÈã‚È‚ç‡Ši
			Always,			// ‘S‚Ä‡Ši
		};
	}
}