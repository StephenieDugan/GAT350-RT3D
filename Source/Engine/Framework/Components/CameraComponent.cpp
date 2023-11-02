#include "CameraComponent.h"
#include "Framework/Actor.h"
#include "Framework/Engine.h"

namespace Twili
{
	CLASS_DEFINITION(CameraComponent)

	bool CameraComponent::Initialize()
	{
		// get aspect from window if not set
		if (aspect == 0)
		{
			aspect = (float) ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight();
		}

		return true;
	}

	void CameraComponent::Update(float dt)
	{
		// View matrix
		view = glm::lookAt(this->m_owner->transform.position, this->m_owner->transform.position + this->m_owner->transform.Forward(), m_owner->transform.Up());
		
		// Projection matrix
		projection = glm::perspective(glm::radians(fov), aspect, 0.01f, 100.0f);
	}

	void CameraComponent::SetPerspective(float fov, float aspect, float near, float far)
	{
		this->fov = fov;
		this->aspect = aspect;
		this->near = near;
		this->far = far;
		
		// Projection matrix
		projection = glm::perspective(glm::radians(fov), aspect, 0.01f, 100.0f);
	}

	void CameraComponent::SetLookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
	{
		// View matrix
		view = glm::lookAt(eye, center, up);
	}

	void CameraComponent::SetProgram(res_t<Program> program)
	{
		program->SetUniform("view", view);
		
		program->SetUniform("projection", projection);
	}

	void CameraComponent::ProcessGui()
	{
		ImGui::DragFloat("fov", &fov, 0.1f);
		ImGui::DragFloat("aspect", &aspect, 0.1f);
		ImGui::DragFloat("near", &near, 0.1f);
		ImGui::DragFloat("far", &far, 0.1f);
	}

	void CameraComponent::Read(const json_t& value)
	{
		// READ_DATA of fov, aspect, near and far values
		READ_DATA(value, fov);
		READ_DATA(value, aspect);
		READ_DATA(value, near);
		READ_DATA(value, far);

	}
}