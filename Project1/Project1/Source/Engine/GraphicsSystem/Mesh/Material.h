#pragma once

#include "..//..//Math/Color3.h"
#include "..//..//Math/Color4.h"
#include <vector>
#include <iostream>
#include "../../Object.h"

namespace Engine
{
	// �O���錾
	//struct GameContext;
	namespace GraphicsSystem
	{
		class Shader;
		class Texture;
		class ConstantBuffer;

		// �e�N�X�`�������@
		enum class BlendType
		{
			Addition,		// ���Z
			Multiplication	// ��Z
		};

		struct MaterialData
		{
			Color3 color;			// 
			float opacity;			// �s�����x(0.0 �` 1.0)
			Color3 diffuseCoeff;	// �g�U���ˌW��(r,g,b,a)
			float specularity;		// ���ʐ����x(0.0 �` 200.0)
			Color3 ambientCoeff;	// �����ˌW��(r,g,b)
			float refraction;		// ���ܗ�
			Color3 specularCoeff;	// ���ʔ��ˌW��(r,g,b)
			float dummy;
		};

		class Material final : public Object
		{
		private:
			using base = Object;
			using TexturePtr = std::shared_ptr<Texture>;
			using Textures = std::vector<TexturePtr>;
		private:

			TexturePtr m_decalTexture;				// �f�J�[���e�N�X�`��(���C���e�N�X�`��)

			ConstantBuffer* m_constantBuffer;		// �萔�o�b�t�@
			MaterialData m_data;

		public:
			// �R���X�g���N�^
			Material(const std::string& name = "");
			// �f�X�g���N�^
			virtual ~Material();
		public:
			// �C���X�^���XID
			static const InstanceID ID() { return InstanceID::Material; }
			// �C���X�^���XID�擾
			virtual InstanceID GetInstanceID() const { return InstanceID::Material; }

		public:
			// ����
			//Material* Clone();
			// �萔�o�b�t�@�쐬
			void CreateConstantBuffer();
		public:
			// ��{�F�ǉ�
			void SetColor(const Color3& color);

			// �����ˌW���ݒ�
			void SetAmbientCoeff(const Color3& coeff);

			// ���ʔ��ˌW���ݒ�
			void SetSpecularCoeff(const Color3& coeff);

			// �g�U���ˌW���ݒ�
			void SetDiffuseCoeff(const Color3& coeff);

			// ���ʐ����x�ݒ�
			void SetSpecularity(float specularity);

			// �s�����x�ݒ�
			void SetOpacity(float opacity);

			// ���ܗ��ݒ�
			void SetRefraction(float refraction);

			// �f�J�[���e�N�X�`���ݒ�
			void SetDecalTexture(TexturePtr texture);

		public:

			// �f�J�[���e�N�X�`���擾
			TexturePtr GetDecalTexture() const;

			// �萔�o�b�t�@�擾
			ConstantBuffer* GetConstantBuffer() const;

			// �A���r�G���g�W���擾
			const Color3& GetAmbientCoeff() const;
			// �f�B�t���[�Y�W���擾
			const Color3& GetDiffuseCoeff() const;
			// �X�y�L�����[�W���擾
			const Color3& GetSpecularCoeff() const;
			// �X�y�L�����[�擾
			float GetSpecularity() const;
			// �I�p�V�e�B�擾
			float GetOpacity() const;
		};
	}
}

using MaterialPtr = std::shared_ptr<Engine::GraphicsSystem::Material>;