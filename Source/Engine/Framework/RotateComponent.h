#pragma once
#include "Components/Component.h"

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
		glm::vec3 euler{ 0 };

	};
}

