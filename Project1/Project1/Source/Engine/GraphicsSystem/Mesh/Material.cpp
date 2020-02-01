#include "Material.h"
#include "..//Texture/Texture.h"
#include "..//HardwareBuffer//ConstantBuffer.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		Material::Material(const std::string& name)
			: base(name)
			, m_decalTexture(nullptr)
			, m_constantBuffer(nullptr)
			, m_data()
		{
		}

		Material::~Material()
		{
			delete m_constantBuffer;
		}

		void Material::CreateConstantBuffer()
		{
			m_constantBuffer = new ConstantBuffer();
			m_constantBuffer->SetCount(1);
			m_constantBuffer->SetStride(sizeof(m_data));
			m_constantBuffer->Create(&m_data);
		}

		void Material::SetDecalTexture(TexturePtr texture)
		{
			m_decalTexture = texture;
		}

		void Material::SetColor(const Color3& color)
		{
			m_data.color = color;
		}

		void Material::SetAmbientCoeff(const Color3& coeff)
		{
			m_data.ambientCoeff = coeff;
		}

		void Material::SetSpecularCoeff(const Color3& coeff)
		{
			m_data.specularCoeff = coeff;
		}

		void Material::SetDiffuseCoeff(const Color3& coeff)
		{
			m_data.diffuseCoeff = coeff;
		}

		void Material::SetSpecularity(float specularity)
		{
			m_data.specularity = specularity;
		}

		void Material::SetOpacity(float opacity)
		{
			m_data.opacity = opacity;
		}

		void Material::SetRefraction(float refraction)
		{
			m_data.refraction = refraction;
		}

		Material::TexturePtr Material::GetDecalTexture() const
		{
			return m_decalTexture;
		}

		ConstantBuffer* Material::GetConstantBuffer() const
		{
			return m_constantBuffer;
		}

		const Color3& Material::GetAmbientCoeff() const
		{
			return m_data.ambientCoeff;
		}

		const Color3& Material::GetDiffuseCoeff() const
		{
			return m_data.diffuseCoeff;
		}

		const Color3& Material::GetSpecularCoeff() const
		{
			return m_data.specularCoeff;
		}

		float Material::GetSpecularity() const
		{
			return m_data.specularity;
		}

		float Material::GetOpacity() const
		{
			return m_data.opacity;
		}
	}
}