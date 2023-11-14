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

		if (castShadow)
		{
			program->SetUniform("shadowVP", GetShadowMatrix());
		}
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

		ImGui::Checkbox("Cast Shadow", &castShadow);
		if (castShadow)
		{
			ImGui::DragFloat("Shadow Size", &shadowSize, 0.1f, 1, 60);
		}
	}

	glm::mat4 LightComponent::GetShadowMatrix()
	{
		glm::mat4 projection = glm::ortho(-shadowSize * 0.5f, shadowSize * 0.5f, -shadowSize * 0.5f, shadowSize * 0.5f, 0.1f, 50.0f);
		glm::mat4 view = glm::lookAt(m_owner->transform.position, m_owner->transform.position + m_owner->transform.Forward(), glm::vec3{ 0,1,0 });


		return projection * view;
	}

	void LightComponent::Read(const Twili::json_t& value)
	{
		std::string lightTypeName;
		READ_NAME_DATA(value, "lightType", lightTypeName);
		if (IsEqualIgnoreCase(lightTypeName, "point")) type = LightComponent::eType::Point;
		if (IsEqualIgnoreCase(lightTypeName, "directional")) type = LightComponent::eType::Directional;
		if (IsEqualIgnoreCase(lightTypeName, "spot")) type = LightComponent::eType::Spot;

		READ_DATA(value, color);
		READ_DATA(value, intensity);
		READ_DATA(value, range);
		READ_DATA(value, innerangle);
		READ_DATA(value, outerangle);
		READ_DATA(value, castShadow);


	}
}