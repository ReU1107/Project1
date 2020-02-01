#pragma once
#include "Behaviour.h"

namespace Engine 
{
	// ����Đ����u(���m�����r�w�C�r�A)���m����:�Đ�����
	class MonoBehaviour : public Behaviour
	{
	private:
		using base = Behaviour;
		using MonoBehaviourPtr = std::shared_ptr<MonoBehaviour>;
	public:
		// �R���X�g���N�^
		MonoBehaviour(const std::string& name = "MonoBehaviour") noexcept;
		// ���z�f�X�g���N�^
		virtual ~MonoBehaviour() noexcept;
	public:
		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::MonoBehaviour; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::MonoBehaviour; }
	public:
		// ����J�n�ɂ�肽������
		virtual void OnStart() {}

		// �ʃI�u�W�F�N�g�Ɉˑ�����\���̂��鏈��
		virtual void OnAwake() {}

		// �{�`���ɂ�肽������
		virtual void OnPostRender() {}

		// �{�`��O�ɂ�肽������
		virtual void OnPreRender() {}

		// �X�V����
		virtual void OnUpdate(float deltaTime);
		// �X�V����(�A�j���[�V�����K�p��)
		virtual void OnLateUpdate(float deltaTime);
		// �X�V����(��莞��)
		virtual void OnFixedUpdate(float deltaTime);
	};

}