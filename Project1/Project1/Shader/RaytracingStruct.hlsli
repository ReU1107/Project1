
struct Payload
{
	float4 color;
	half traceCount;
};

struct ShadowPayload
{
	float shadowCoeff;	// �V���h�E�W��
};

struct CameraData
{
	float4x4 viewMatrix;			// �r���[�ϊ��s��
	float4x4 projectionMatrix;		// �v���W�F�N�V�����ϊ��s��
	float4x4 viewProjectionMatrix;	// �r���[�v���W�F�N�V�����ϊ��s��
	float4x4 projViewMatrix;
	float4 position;
};

struct SceneData
{
	uint lightCount;		// ���C�g�̐�
	float refraction;		// ��C���̋��ܗ�
};

struct LightData
{
	float3 color;		// �F
	float3 position;	// �ʒu
	float3 direction;	// ����
	float range;		// �͈�
	float angle;		// �A���O��

	uint type;
};

/*
�萔�o�b�t�@��float4���E������
���̂��߉��̂悤�ȍ\���ɂȂ��Ă���
*/
struct MaterialData
{
	float3 color;			// �P�̂̐F
	float opacity;			// �s�����x(0.0 �` 1.0)
	float3 diffuseCoeff;	// �g�U���ˌW��(r,g,b,a)
	float specularity;		// ���ʐ����x(0.0 �` 200.0)
	float3 ambientCoeff;	// �����ˌW��(r,g,b)
	float refraction;		// ���ܗ�
	float3 specularCoeff;	// ���ʔ��ˌW��(r,g,b)
	float dummy;
};

struct ProceduralInstance
{
	float3 min;
	float3 max;
};

struct Ray
{
	float3 origin;
	float3 direction;
};

struct Sphere
{
	float3 center;		// ���S���W
	float radius;		// ���a
};

// 
struct SphereAttribute
{
	float3 position;
	float3 normal;
	bool front;
};
