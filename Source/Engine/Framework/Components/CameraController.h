#pragma once
#include "Component.h"

namespace Twili
{
	class CameraController : public Component
	{
	public:
		CLASS_DECLARATION(CameraController)

		bool Initialize() override;
		void Update(float dt) override;

	public:
		float sensitivity = 0.2f;
		float speed = 3;
		float yaw = 0;
		float pitch = 0;
	};
}