#include "ComputePass.h"
#include <cassert>
#include "ComputePipeline.h"

namespace Engine
{
	namespace GraphicsSystem
	{
		std::unordered_map<std::wstring, ComputePass*> ComputePass::s_allComputePasses;
		std::mutex ComputePass::s_computePassAccess;

		ComputePass::ComputePass()
			: base()
			, AsyncJob()
			, m_pipeline(nullptr)
			, m_resultTexture(nullptr)
		{
		}

		ComputePass::~ComputePass()
		{
			delete m_pipeline;
		}

		void ComputePass::Register(const std::wstring& name, ComputePass* pass)
		{
			std::lock_guard<std::mutex> lock(s_computePassAccess);
			const auto& it = s_allComputePasses.find(name);
			if (it != s_allComputePasses.cend())
			{
				assert(L"同じ名前のコンピュートパスが登録されています");
			}
			s_allComputePasses.insert({ name,pass });
		}

		ComputePass* ComputePass::Find(const std::wstring& name)
		{
			std::lock_guard<std::mutex> lock(s_computePassAccess);
			const auto& it = s_allComputePasses.find(name);
			if (it == s_allComputePasses.cend())
			{
				return nullptr;
			}

			return (*it).second;
		}

	}
}