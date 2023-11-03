#include "LightComponent.h"
#include "Framework/Actor.h"
#include "Core/Json.h"

namespace Twili
{
	CLASS_DEFINITION(LightComponent)

	bool LightComponent::Initialize()
	{
		return true;
	}

	void LightComponent::Update(float dt)
	{
	}

	void LightComponent::SetProgram(const res_t<Program> program, const std::string& name)
	{
		program->SetUniform(name + ".type", type);
		program->SetUniform(name + ".position", m_owner->transform.position);
		program->SetUniform(name + ".direction", m_owner->transform.Forward());
		program->SetUniform(name + ".color", color);
		program->SetUniform(name + ".intensity", intensity);
		program->SetUniform(name + ".range", range);
		program->SetUniform(name + ".innerAngle", glm::radians(innerangle));
		program->SetUniform(name + ".outerAngle", glm::radians(outerangle));
	}

	void LightComponent::ProcessGui()
	{
		const char* types[] = { "Point", "Directional", "Spot" };
		ImGui::Combo("Type", (int*)(&type), types, 3);

		if (type == Spot)
		{
			ImGui::DragFloat("Inner Angle", &innerangle, 1, 0, outerangle);
			ImGui::DragFloat("Outer Angle", &outerangle, 1, innerangle, 90);
		}

		ImGui::ColorEdit3("Color", glm::value_ptr(color));
		ImGui::DragFloat("Intensity", &intensity, 0.1f, 0, 10);
		if (type != Directional) ImGui::DragFloat("Range", &range, 0.1f, 0.1f, 50);


	}

	void LightComponent::Read(const Twili::json_t& value)
	{
		READ_DATA(value, intensity);
		READ_DATA(value, range);
		READ_DATA(value, innerangle);
		READ_DATA(value, outerangle);
	}
}