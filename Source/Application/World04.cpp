#include "World04.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "imgui/imgui.h"

#include <glm/glm/gtc/type_ptr.hpp>

#define INTERLEAVE

namespace Twili
{
		
	bool World04::Initialize()
	{
		auto material = GET_RESOURCE(Material, "materials/grid.mtrl");
		m_model = std::make_shared<Model>();
		m_model->SetMaterial(material);
		m_model->Load("models/buddha.obj", glm::vec3{0}, glm::vec3{90,0,0});

		ambientLight = glm::vec3(0.2f, 0.2f, 0.2f);
		diffuseLight = glm::vec3(1.0f, 1.0f, 1.0f);
		lightPosition = glm::vec3(0.0f, 8.0f, 0.0f);

		return true;
	}

	void World04::Shutdown()
	{
	}

	void World04::Update(float dt)
	{
		
		ENGINE.GetSystem<Gui>()->BeginFrame();

		ImGui::Begin("Transform");
		ImGui::DragFloat3("Position", &m_transform.position[0], 0.1f);
		ImGui::DragFloat3("Rotation", &m_transform.rotation[0]);
		ImGui::DragFloat3("Scale", &m_transform.scale[0], 0.1f);
		ImGui::End();
	
		// GUI for Light Controls
		ImGui::Begin("Light");
		ImGui::DragFloat3("Position", glm::value_ptr(lightPosition), 0.1f);
		ImGui::ColorEdit3("Diffuse Light", glm::value_ptr(diffuseLight));
		ImGui::ColorEdit3("Ambient Light", glm::value_ptr(ambientLight));
		ImGui::End();

		// Set updated light uniform values in the shader
		auto material = m_model->GetMaterial();

		// Call ProcessGui on the Material object
		material->ProcessGui();
		material->Bind();

		material->GetProgram()->SetUniform("light.position", lightPosition);
		material->GetProgram()->SetUniform("light.color", diffuseLight);
		material->GetProgram()->SetUniform("ambientLight", ambientLight);

		m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
		m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * +dt : 0;
		m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * -dt : 0;
		m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * +dt : 0;

		m_time += dt;

		// Model matrix
		material->GetProgram()->SetUniform("model", m_transform.GetMatrix());

		// View matrix
		glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
		material->GetProgram()->SetUniform("view", view);

		// Projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float) ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), 0.01f, 100.0f);
		material->GetProgram()->SetUniform("projection", projection);

		ENGINE.GetSystem<Gui>()->EndFrame();
	}

	void World04::Draw(Renderer& renderer)
	{
		// Pre-render
		renderer.BeginFrame();

		// Render
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		m_model->Draw(GL_TRIANGLES);

		ENGINE.GetSystem<Gui>()->Draw();

		// Post-render
		renderer.EndFrame();
	}
}
