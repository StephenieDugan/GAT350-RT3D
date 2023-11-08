#pragma once
#include "Component.h"

namespace Twili
{
	class RotateComponent : public Component
	{
	public:
		CLASS_DECLARATION(RotateComponent)

		bool Initialize() override;
		void Update(float dt) override;

		void ProcessGui();

	public:
		float sensitivity = 0.2f;
		float speed = 3;
		float yaw = 0;
		float pitch = 0;
	};
}

