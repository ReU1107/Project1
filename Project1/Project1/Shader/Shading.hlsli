#include "Light.hlsli"
#include "Material.hlsli"

float3 DirectionalFunction(float3 normal, float3 view, Light light, Material material)
{
	float3 color = float3(0.0f, 0.0f, 0.0f);
	// Diffuse(�g�U����)�v�Z
	float d = saturate(dot(light.direction, normal));
	float luminous = 0.5f;
	float3 diffuse = (light.color * luminous * material.diffuseCoeff) * d;
	
	color.rgb += diffuse;
	
	// Specular(���ʔ���)�v�Z
	float c = dot(reflect(normal, -light.direction), view);
	float3 specular = material.specularCoeff * pow(c, material.specularity);
	
	color.rgb += specular;

	return color;
}

float3 PointFunction(float3 position, float3 normal, float3 view, Light light, Material material)
{
	float3 color = float3(0.0f, 0.0f, 0.0f);
	float length = 0.0f; //length(float3(light.position - position));
	// �͈͊O�Ȃ瑁��
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
	// �͈͊O�Ȃ瑁��
	if (length > light.range)
	{
		return color;
	}

	return color;
}

// �߂�l�̒l���x�[�X�F�ɉ��Z���Ă�������
// �t�H���V�F�[�f�B���O
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

// �u�����t�H���V�F�[�f�B���O
float3 BlinePhongShading()
{
	float3 color = float3(0.0f, 0.0f, 0.0f);
	return color;
}

// �o�������˗����z�֐�
void BidirectionalReflectanceDistributionFucntion()
{

}