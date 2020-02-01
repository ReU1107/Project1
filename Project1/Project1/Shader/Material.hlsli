
struct Material
{
	float3 color;			// 
	float opacity;			// •s“§–¾“x(0.0 ` 1.0)
	float3 diffuseCoeff;	// ŠgU”½ËŒW”(r,g,b,a)
	float specularity;		// ‹¾–Ê«‹­“x(0.0 ` 200.0)
	float3 ambientCoeff;	// ŠÂ‹«”½ËŒW”(r,g,b)
	float refraction;		// ‹üÜ—¦
	float3 specularCoeff;	// ‹¾–Ê”½ËŒW”(r,g,b)
	float dummy;
};