
struct Material
{
	float3 color;			// 
	float opacity;			// �s�����x(0.0 �` 1.0)
	float3 diffuseCoeff;	// �g�U���ˌW��(r,g,b,a)
	float specularity;		// ���ʐ����x(0.0 �` 200.0)
	float3 ambientCoeff;	// �����ˌW��(r,g,b)
	float refraction;		// ���ܗ�
	float3 specularCoeff;	// ���ʔ��ˌW��(r,g,b)
	float dummy;
};