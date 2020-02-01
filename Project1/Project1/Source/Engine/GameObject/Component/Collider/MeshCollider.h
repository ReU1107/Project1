#pragma once
#include "Collider.h"
#include <DirectXMath.h>
namespace Engine 
{

	// ���b�V���R���C�_�[(�Փˑ��u)(���U�����|���g�[�v)
	class MeshCollider final : public Collider
	{
	private:
		using base = Collider;
	private:
		DirectX::XMFLOAT3 m_localCenter;	// ���S���W(���[�J��)
		DirectX::XMFLOAT3 m_localSize;		// �T�C�Y(���[�J��)
	public:
		// �R���X�g���N�^
		MeshCollider() noexcept;
		// �f�X�g���N�^
		~MeshCollider() noexcept;

	};
}