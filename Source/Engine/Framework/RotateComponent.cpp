#include "RotateComponent.h"
#include "Framework/Actor.h"
namespace Twili 
{
	CLASS_DEFINITION(RotateComponent)

	bool RotateComponent::Initialize()
	{
		return true;
	}

	void RotateComponent::Update(float dt)
	{
		m_owner->transform.euler = euler * dt;
	}

	void RotateComponent::ProcessGui()
	{
		ImGui::DragFloat3("Rotate", glm::value_ptr(euler));
	}
}