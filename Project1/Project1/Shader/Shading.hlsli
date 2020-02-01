#include "Light.hlsli"
#include "Material.hlsli"

float3 DirectionalFunction(float3 normal, float3 view, Light light, Material material)
{
	float3 color = float3(0.0f, 0.0f, 0.0f);
	// Diffuse(拡散反射)計算
	float d = saturate(dot(light.direction, normal));
	float luminous = 0.5f;
	float3 diffuse = (light.color * luminous * material.diffuseCoeff) * d;
	
	color.rgb += diffuse;
	
	// Specular(鏡面反射)計算
	float c = dot(reflect(normal, -light.direction), view);
	float3 specular = material.specularCoeff * pow(c, material.specularity);
	
	color.rgb += specular;

	return color;
}

float3 PointFunction(float3 position, float3 normal, float3 view, Light light, Material material)
{
	float3 color = float3(0.0f, 0.0f, 0.0f);
	float length = 0.0f; //length(float3(light.position - position));
	// 範囲外なら早期
	if (length < light.range)
	{
		return color;
	}

	return color;
}

float3 SpotFunction(float3 position, float3 normal, float3 view, Light light, Material material)
{
	float3 color = float3(0.0f, 0.0f, 0.0f);
	float length = 0.0f; //length(float3(light.position - position));
	// 範囲外なら早期
	if (length > light.range)
	{
		return color;
	}

	return color;
}

// 戻り値の値をベース色に加算してください
// フォンシェーディング
float3 PhongShading(float3 position, float3 normal, float3 view, Light light, Material material)
{
	float3 color = float3(0.0f, 0.0f, 0.0f);

	switch (light.type)
	{
	case DirectionalID:
		color = DirectionalFunction(normal, view, light, material);
		break;
	case PointID:
		color = PointFunction(position, normal, view, light, material);
		break;
	case SpotID:
		color = SpotFunction(position, normal, view, light, material);
		break;
	};

	return color;
}

// ブリンフォンシェーディング
float3 BlinePhongShading()
{
	float3 color = float3(0.0f, 0.0f, 0.0f);
	return color;
}

// 双方向反射率分布関数
void BidirectionalReflectanceDistributionFucntion()
{

}