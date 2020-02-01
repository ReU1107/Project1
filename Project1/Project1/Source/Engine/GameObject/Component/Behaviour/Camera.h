#pragma once
#include <vector>
#include "Behaviour.h"
#include "../../../Math/Color4.h"
#include "../../../Math/Matrix4x4.h"
#include "Enumerations/CameraEvent.h"
#include "Enumerations/DepthTextureMode.h"
#include <iostream>

namespace Engine
{

	// 前方宣言
	namespace GraphicsSystem
	{
		class RenderTexture;
		class ConstantBuffer;
	}

	// 投影法
	enum class ProjectionType : uint8_t
	{
		Orthographic,	// 平行投影法
		Perspective		// 透視投影法
	};

	class Camera final : public Behaviour, public std::enable_shared_from_this<Camera>
	{
	private:
		using base = Behaviour;
		using CameraPtr = std::shared_ptr<Camera>;
		using ConstantBufferPtr = GraphicsSystem::ConstantBuffer*;
		using Cameras = std::vector<CameraPtr>;
	public:
		static Cameras allCameras;			// 全てのカメラ
		static uint32_t allCamerasCount;	// 全てのカメラ数
		static CameraPtr main;				// メインカメラ
		static CameraPtr current;			// 現在有効になっているカメラ
		
	private:
		ConstantBufferPtr m_constantBuffer;
		mutable Matrix4x4 m_projectionMatrix;			// 射影変換行列

		Color4 m_backGroundColor;						// テクスチャのクリア色

		float m_fovAngle;								// 視野角filed of view(単位:ラジアン)
		float m_width;									// 幅
		float m_height;									// 高さ
		float m_aspect;									// アスペクト比(幅/高さ)
		float m_nearClipPlane;							// 最近面
		float m_farClipPlane;							// 最遠面

		DepthTextureMode m_depthTextureMode;
		ProjectionType m_projectionType;				// 投影方法
		mutable bool m_projectionIsDirty;				// ダーティーフラグ(プロジェクション変換行列)
		bool m_isActive;								// カメラが有効か

	public:
		// コンストラクタ
		Camera() noexcept;
		// デストラクタ
		virtual ~Camera() noexcept;

	public:
		// インスタンスID
		static const InstanceID ID() { return InstanceID::Camera; }
		// インスタンスID取得
		virtual InstanceID GetInstanceID() const override { return InstanceID::Camera; }

	public:
		ConstantBufferPtr GetConstantBuffer() const;

		// 視野角設定(単位:ラジアン)
		void SetFovAngle(float fovAngle);

		// アスペクト比設定
		void SetAspect(float aspect);

		// 最近面の位置設定
		void SetNearClipPlane(float nearClipPlane);

		// 最遠面の位置設定
		void SetFarClipPlane(float farClipPlane);

		// 投影法設定
		void SetProjectionType(ProjectionType projectionType);

		// 状態設定
		void SetActive(bool isActive);

		// 背景色設定
		void SetBackGroundColor(const Color4& color);
		void SetBackGroundColor(float color);

		// ビュー変換行列取得
		const Matrix4x4& GetViewMatrix() const;
		// 射影変換行列取得
		const Matrix4x4& GetProjectionMatrix() const;

		// 投影法が透視か
		bool IsPerspective() const;

		// 稼働しているか
		bool IsActive() const;
		// コマンドバッファ取得
		//std::vector<CommandBuffer*>& GetCommandBuffer(CameraEvent evt);
		// コマンドバッファ実行
		//void ExecuteCommandBuffer(CameraEvent evt);
	};

	template<>
	inline std::shared_ptr<Camera> Component::Create()
	{
		auto camera = std::make_shared<Camera>();
		if (!Camera::main)
			Camera::main = camera;
		Camera::allCameras.push_back(camera);

		return camera;
	}
}