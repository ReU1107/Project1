RWTexture2D<float4> outputTexture : register(u0);

//struct SceneData
//{
//	float3 cameraPosition;			// �J�����̈ʒu
//	float4x4 ProjectionViewMatrix;	// �v���W�F�N�V�����r���[�ϊ��s��
//};
//
//ConstantBuffer<SceneData> sceneBuffer : register(b0);

float GetSphereDistance(float3 position, float sphereRange)
{
	return length(position) - sphereRange;
}

float3 GetSphereNormal(float3 position, float sphereRange)
{
	// �Փ˂����ꏊ�ɋ߂��ꏊ�̌X���𒲂ׂ邻�ꂪ�@���ɂȂ�
	float offset = 0.001f;
	return float3
		(
			GetSphereDistance(position + offset, sphereRange) - GetSphereDistance(position - offset, sphereRange),
			GetSphereDistance(position + offset, sphereRange) - GetSphereDistance(position - offset, sphereRange),
			GetSphereDistance(position + offset, sphereRange) - GetSphereDistance(position - offset, sphereRange)
		);
}

// �n�b�V���֐�(�T�^�I�炵��)
// https://www.shadertoy.com/view/4djSRW
float Hash(float2 p)
{
	return frac(sin(dot(p, float2(12.9898, 78.233))) * 43758.5453);
}

// �m�C�Y�֐�
// https://www.shadertoy.com/view/4dS3Wd
float Noise(float2 p)
{
	float2 i = floor(p);
	float2 f = frac(p);

	// �i�q��
	float a = Hash(i + float2(0.0, 0.0));
	float b = Hash(i + float2(1.0, 0.0));
	float c = Hash(i + float2(0.0, 1.0));
	float d = Hash(i + float2(1.0, 1.0));

	float2 u = f * f * (3.0 - 2.0 * f);
	return lerp(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

float Noise2(float3 x)
{
	float3 p = floor(x);
	float3 f = frac(x);

	f = f * f * (3.0 - 2.0 * f);

	float a = 1.0f;
	float b = 1.0f;

	float n = p.x + p.y * a + (a * 2) * p.z;

	float res = lerp(
		lerp(
			lerp(Hash(n + 0.0), Hash(n + 1.0), f.x),
			lerp(Hash(n + a), Hash(n + a + b), f.x), f.y),
		lerp(
			lerp(Hash(n + a * 2), Hash(n + a * 2 + b), f.x),
			lerp(Hash(n + a * 3), Hash(n + a * 3 + b), f.x), f.y),
		f.z);
	return res;
}


// �񐮐��u���E���^��
// https://thebookofshaders.com/13/?lan=jp
float FractalBrownianMotion(float3 p)
{
	float value = 0.0f;
	uint octaves = 3;		// �I�N�^�[�u�𑝂₷�Ƃ��ߍׂ����Ȃ�
	float amplitude = 0.5f;	// �U��

	for (uint i = 0; i < octaves; ++i)
	{
		value += amplitude * Noise2(p);
		p *= 2;
		amplitude *= 0.5f;
	}
	return value;
}

// ����̖��x�֐�
float SphereDensity(float3 position)
{
	return 0.1 - length(position) * 0.05 + FractalBrownianMotion(position * 0.3);
}

[numthreads(32, 24, 1)]
void main(uint3 threadID : SV_DispatchThreadID)
{
	uint3 texcoord = threadID;

	uint3 launchIndex = texcoord;
	uint3 launchDim = uint3(1280, 960, 1);

	float2 crd = float2(launchIndex.xy);
	float2 dims = float2(launchDim.xy);

	float2 d = ((crd / dims) * 2.f - 1.f);
	float aspectRatio = dims.x / dims.y;

	//// -1�`1�ɂ���
	//float2 clipSpacePos = texcoord.xy / float2(1280, 960) * float2(2, -2) + float2(-1, 1);
	//// �e�N�X�`�������郏�[���h���W
	//float4 worldPos = mul(sceneBuffer.ProjectionViewMatrix, float4(clipSpacePos, 1, 1));

	// �J��������e�N�X�`���̍��W�Ɍ����Ẵx�N�g��
	//float3 direction = worldPos.xyz - sceneBuffer.cameraPosition;
	//float3 position = sceneBuffer.cameraPosition;
	float3 position = float3(0, 0, -20);
	float3 direction = normalize(float3(d.x * aspectRatio, -d.y, 1));
	
	uint marchingCount = 50;
	float cloudMinDepth = 2000.0f;
	float cloudMaxDepth = 5000.0f;
	float step = cloudMaxDepth / marchingCount;
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);

	//for (float distance = 0.0f; distance < 5000.0f; distance += step)
	//{
	//	position += direction * distance;
	//	//if (distance > cloudMinDepth&& distance < cloudMaxDepth)
	//	{
	//		float a = FractalBrownianMotion(position*0.0000001);
	//		color += (1).xxxx * (a);
	//	}
	//}

	float maxDepth = 40.0f;

	float stepDistance = maxDepth / marchingCount;

	float density = 0.0f;// ���x
	float absorption = 100.0f;	// �z����
	float transparency = 1.0f;
	float opacity = 50.f;
	// ���C�}�[�`���O�J�n
	for (uint i = 0; i < marchingCount; ++i)
	{
		density = SphereDensity(position);
		//density = FractalBrownianMotion(position* 0.0025);
		//color += (1).xxxx * density;
		// ���x���}�C�i�X�Ȃ�Փ˂��Ă��Ȃ�
		if (density > 0.0f)
		{
			float tmp = density / float(marchingCount);
			transparency *= 1.0 - (tmp * absorption);
			if (transparency < 0.01f)
			{
				break;
			}
			float k = opacity * tmp * transparency;
			float3 cloudColor = lerp(float3(1.0, 1.0, 1.0), float3(0.0f, 0.0f, 0.0f), transparency);

			color += (1).xxxx * k;
			//color += float4(cloudColor, 1) * k;
			//color += float4(cloudColor, 1) * k;
			//color += float4(cloudColor, 1) * k;
		}

		position += direction * stepDistance;

	}

	outputTexture[texcoord.xy] = color;

}