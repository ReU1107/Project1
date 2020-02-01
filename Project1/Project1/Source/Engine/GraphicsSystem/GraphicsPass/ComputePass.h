#pragma once
#include "GraphicsPass.h"
#include <mutex>
#include <string>
#include <unordered_map>
#include "../../Utility/AsyncJob.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		class ComputePipeline;
		class Texture;

		// �񓯊��ɍs�������̃p�X
		class ComputePass : public GraphicsPass, public AsyncJob
		{
		private:
			using base = GraphicsPass;
			using TexturePtr = std::shared_ptr<Texture>;
			static std::unordered_map<std::wstring, ComputePass*> s_allComputePasses;
			static std::mutex s_computePassAccess;
		protected:
			ComputePipeline* m_pipeline;			// �p�C�v���C��
			TexturePtr m_resultTexture;

		public:
			// �R���X�g���N�^
			ComputePass();
			// �f�X�g���N�^
			virtual ~ComputePass();

			// �o�^
			static void Register(const std::wstring& name, ComputePass* pass);

			// �R���s���[�g�p�X�擾
			static ComputePass* Find(const std::wstring& name);

			// �p�X��񑗐M
			virtual void OnDispatch() = 0;
		};

	}
}