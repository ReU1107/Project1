#pragma once

namespace Engine
{
	namespace GraphicsSystem
	{
		class ResourceDescriptor;
		// �O���t�B�b�N�X�Ɋ֘A����p�X
		class GraphicsPass
		{
		protected:
			ResourceDescriptor* m_shaderResourceDescriptor;	// CBV,SRV,UAV�o�^��
			bool m_isActive;

		public:
			// �R���X�g���N�^
			GraphicsPass();
			// �f�X�g���N�^
			virtual ~GraphicsPass();

			// 
			void Active(bool active = true);

			// 
			bool IsActive() const { return m_isActive; }

			// ����������
			virtual void OnInitialize() = 0;

		};
	}
}