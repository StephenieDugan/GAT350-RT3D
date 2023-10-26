#pragma once
#include "Component.h"
#include "Renderer/Program.h"

namespace Twili
{
	class LightComponent : public Component
	{
	public:
		CLASS_DECLARATION(LightComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void SetProgram(const res_t<Program> program, const std::string& name);

		void ProcessGui() override;

	public:
		enum eType
		{
			POINT,
			DIRECTIONAL,
			SPOT
		};

		eType type = eType::POINT;
		glm::vec3 color{ 1 };
		float intensity = 1;
		float range = 20;
		float innerAngle = 20;
		float outerAngle = 30;
	};
}
