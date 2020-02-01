#pragma once

namespace Engine
{
	namespace GraphicsSystem
	{
		class IAccelerationStructure;
		enum class ASType
		{
			Top,
			Bottom,
		};

		class AccelerationStructure
		{
		protected:
			IAccelerationStructure* m_interface;
			ASType m_type;
		public:
			// コンストラクタ
			AccelerationStructure();
			// デストラクタ
			virtual ~AccelerationStructure();

		public:
			IAccelerationStructure* GetInterface() const;

			virtual void Create() = 0;

			virtual void Recreate() = 0;
		};

	}
}