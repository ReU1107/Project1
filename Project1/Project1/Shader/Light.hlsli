
// ���s
struct DirectionalLight
{
	float3 direction;	// ����
};

// �_
struct PointLight
{
	float3 position;	// �ʒu
	float range;		// �͈�
};

// �X�|�b�g
struct SpotLight
{
	float3 position;	// �ʒu
	float3 direction;	// ����
	float range;		// �͈�
	float angle;		// �A���O��
};

// ���Ȕ��s
struct EmissiveLight
{

};

#define DirectionalID 0
#define PointID 1
#define SpotID 2

/*
SpotLight��I��ł��闝�R
�S�Ă̋��ʃp�����[�^�������Ă���
�z��Ŏ����ߍő�o�C�g���ɍ��킹�Ȃ��Ă͂����Ȃ�����
*/
struct Light
{
	float3 color;			// �F
	float3 position;	// �ʒu
	float3 direction;	// ����
	float range;		// �͈�
	float angle;		// �A���O��

	uint type;
};
