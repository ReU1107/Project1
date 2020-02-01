#include "VMDClipFactory.h"
#include "VMDDataModel.h"
#include "../Engine/AnimationSystem/Include.h"
#include "../Engine/Math/Vector2.h"

using namespace Engine;
using namespace Engine::AnimationSystem;

static float VMDBezier(char ax, char ay, char bx, char by, char t)
{
	float result = 0.0f;
	float d = 0.0f;
	float c = (float)ay / ax;
	float b = -(float)(127 - by) / (float)(127 * (127 - bx)) + (float)3 / 127 - 2 * c / 127;
	float a = (-127 * b - c + 1) / (127 * 127);

	result = a * t * t * t + b * t * t + c * t + d;

	return result / 127;
}

void VMDClipFactory::CreateBodyMotion(std::vector<VMDBodyMotion>& motions)
{
	auto clip = Motion::Create<AnimationClip>(m_motionName);

	std::string targetName;
	std::vector<Vector2> controllPoint(8);

	const std::string Tx = "Tx";
	const std::string Ty = "Ty";
	const std::string Tz = "Tz";
	const std::string Qx = "Qx";
	const std::string Qy = "Qy";
	const std::string Qz = "Qz";
	const std::string Qw = "Qw";

	for (auto& body : motions)
	{

		// たまに\0で終わっていない文字列があるため
		body.boneName[14] = '\0';
		targetName = body.boneName;

		const float time = (float)body.frameIndex / 30.0f;
		const auto& position = body.position;
		const auto& rotation = body.rotataion;

		/*
		https://olyutorskii.wordpress.com/2013/05/21/newvmd/
		の提言より
		最初の16バイト≒ベジェ曲線のコントロールポイント4つ
		のみ使用したらいい
		旧バージョンでも最初の16バイトのコピーを行っているだけと
		書いてあるので2013年以前のものでも大丈夫なはず
		*/
		for (uint32_t i = 0; i < 8; ++i)
		{
			controllPoint[i].x = body.bezierControllPoint[i];
			controllPoint[i].y = body.bezierControllPoint[i + 4];
		}
		const auto& xIn = controllPoint.at(0);
		const auto& yIn = controllPoint.at(1);
		const auto& zIn = controllPoint.at(2);
		const auto& rIn = controllPoint.at(3);

		const auto& xOut = controllPoint.at(4);
		const auto& yOut = controllPoint.at(5);
		const auto& zOut = controllPoint.at(6);
		const auto& rOut = controllPoint.at(7);
		// 接線の傾き
		const float xInTangent = xIn.y / xIn.x;
		const float xOutTangent = (float)(127 - xOut.y) / (127 - xOut.x);

		const float yInTangent = yIn.y / yIn.x;
		const float yOutTangent = (float)(127 - yOut.y) / (127 - yOut.x);

		const float zInTangent = zIn.y / zIn.x;
		const float zOutTangent = (float)(127 - zOut.y) / (127 - zOut.x);

		const float rInTangent = rIn.y / rIn.x;
		const float rOutTangent = (float)(127 - rOut.y) / (127 - rOut.x);

		Keyframe xTranslate(time, position.x, xInTangent, 1.0f, xOutTangent, 1.0f);
		Keyframe yTranslate(time, position.y, yInTangent, 1.0f, yOutTangent, 1.0f);
		Keyframe zTranslate(time, position.z, zInTangent, 1.0f, zOutTangent, 1.0f);

		Keyframe xQuaternion(time, rotation.x, rInTangent, 1.0f, rOutTangent, 1.0f);
		Keyframe yQuaternion(time, rotation.y, rInTangent, 1.0f, rOutTangent, 1.0f);
		Keyframe zQuaternion(time, rotation.z, rInTangent, 1.0f, rOutTangent, 1.0f);
		Keyframe wQuaternion(time, rotation.w, rInTangent, 1.0f, rOutTangent, 1.0f);

		// targetNameのオブジェクトを動かすアニメーションがあるか
		AnimationProperty* translateProperty = clip->GetProperty(targetName + "T");
		if (!translateProperty)
		{
			translateProperty = new AnimationPropertyVector3();
			translateProperty->SetTargetPropertyName("keyPosePosition");
			translateProperty->SetTargetName(targetName);
			clip->AddProperty(targetName + "T", translateProperty);
		}

		translateProperty->GetCurve(0)->AddKeyframe(xTranslate);
		translateProperty->GetCurve(1)->AddKeyframe(yTranslate);
		translateProperty->GetCurve(2)->AddKeyframe(zTranslate);

		AnimationProperty* quaternionProperty = clip->GetProperty(targetName + "R");
		if (!quaternionProperty)
		{
			quaternionProperty = new AnimationPropertyQuaternion();
			quaternionProperty->SetTargetPropertyName("keyPoseRotation");
			quaternionProperty->SetTargetName(targetName);

			clip->AddProperty(targetName + "R", quaternionProperty);

		}

		quaternionProperty->GetCurve(0)->AddKeyframe(xQuaternion);
		quaternionProperty->GetCurve(1)->AddKeyframe(yQuaternion);
		quaternionProperty->GetCurve(2)->AddKeyframe(zQuaternion);
		quaternionProperty->GetCurve(3)->AddKeyframe(wQuaternion);

	}
	clip->Sort();
}

void VMDClipFactory::CreateMorphMotion(const std::vector<VMDMorphMotion>& motions)
{
	auto clip = Motion::Create<AnimationClip>(m_motionName + "Morph");

	std::string name;
	for (auto& morph : motions) 
	{
		/*
		100掛けている理由:
		値を％で表すことで分かりやすくするため
		*/
		name = morph.name;
		float time = (float)morph.frameIndex / 30.0f;
		Keyframe keyframe(time, (morph.weight * 100));

		AnimationProperty* weightProperty = clip->GetProperty(name + "W");
		if (!weightProperty)
		{
			weightProperty = new AnimationPropertyFloat();
			weightProperty->SetTargetPropertyName("weight");
			weightProperty->SetTargetName(name);
			clip->AddProperty(name + "W", weightProperty);
		}

		weightProperty->GetCurve(0)->AddKeyframe(keyframe);
	}

	clip->Sort();
}

void VMDClipFactory::CreateCameraMotion(const std::vector<VMDCameraMotion>& motions)
{
	for (auto& camera : motions)
	{

	}
}

void VMDClipFactory::CreateLightMotion(const std::vector<VMDLightMotion>& motions)
{
	for (auto& light : motions) 
	{

	}
}

void VMDClipFactory::CreateSelfShadowMotion(const std::vector<VMDSelfShadowMotion>& motions)
{
	for (auto& selfShadow : motions) 
	{

	}
}
