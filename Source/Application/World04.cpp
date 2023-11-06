#include "World04.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "imgui/imgui.h"

#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>
#define INTERLEAVE

namespace Twili
{
		
	bool World04::Initialize()
	{
		m_material = GET_RESOURCE(Material, "materials/squirrel.mtrl");
		m_model = std::make_shared<Model>();
		m_model->Load("models/ogre.obj");
		m_transform.position.y = -1;
		//m_model->Load("models/buddha.obj", glm::vec3{ 0 }, glm::vec3{ -90, 0, 0 });

		for (int i = 0; i < 3; i++)
		{
			m_lights.push_back(light_t
				{
					light_t::eType::POINT,
					glm::vec3{randomf(-5, 5), randomf(1, 8), 0},
					glm::vec3{0, -1, 0},
					glm::vec3{randomf(), 1, 1},
					0.4f, 6.0f, 10.0f, 30.0f
				});
		}

		return true;
	}

	void World04::Shutdown()
	{
	}

	void World04::Update(float dt)
	{
		ENGINE.GetSystem<Gui>()->BeginFrame();

		

		ImGui::Begin("Light");

		for (int i = 0; i < m_lights.size(); i++)
		{
			if (ImGui::TreeNode(("Light " + std::to_string(i)).c_str()))
			{
				ImGui::Combo(("Type" + std::to_string(i)).c_str(), (int*)(&m_lights[i].type), "Point\0Directional\0Spot\0");

				ImGui::DragFloat3(("Position" + std::to_string(i)).c_str(), glm::value_ptr(m_lights[i].position), 0.1f);
				ImGui::DragFloat3(("Direction" + std::to_string(i)).c_str(), glm::value_ptr(m_lights[i].direction), 0.1f);
				ImGui::ColorEdit3(("Color" + std::to_string(i)).c_str(), glm::value_ptr(m_lights[i].color));
				ImGui::DragFloat(("Intensity" + std::to_string(i)).c_str(), &m_lights[i].intesity, 0.1f, 0, 8);

				if (m_lights[i].type != light_t::eType::DIRECTIONAL)
				{
					ImGui::DragFloat(("Range##" + std::to_string(i)).c_str(), &m_lights[i].range, 0.1f, 0.1f, 50);
				}

				if (m_lights[i].type == light_t::eType::SPOT)
				{
					ImGui::DragFloat(("Inner Angle" + std::to_string(i)).c_str(), &m_lights[i].innerAngle, 1, 0, m_lights[i].outerAngle);
					ImGui::DragFloat(("Outer Angle" + std::to_string(i)).c_str(), &m_lights[i].outerAngle, 1, m_lights[i].innerAngle, 90);
				}

				ImGui::TreePop();
			}
		}

		if (ImGui::Button("Add Light"))
		{
			m_lights.push_back(light_t{ light_t::eType::POINT, glm::vec3{0, 0, 0}, glm::vec3{0, -1, 0}, glm::vec3{1, 1, 1}, 1.0f, 10.0f, 10.0f, 30.0f });
		}

		if (ImGui::Button("Remove Light") && !m_lights.empty())
		{
			m_lights.pop_back();
		}

		ImGui::ColorEdit3("Ambient Color", glm::value_ptr(ambientLight));
		ImGui::End();

		//***************** Testing model loading in GUI interface ********************************************************
		//

		const char* modelFilenames[] =
		{
			"Models/plane.obj",
			"Models/buddha.obj",
			"Models/squirrel.glb",
			"Models/quad.obj",
			"Models/sphere.obj",
			"Models/spot.obj",
			"Models/teapot.obj",
			"Models/torus.obj",
			"Models/ogre.obj",
			"Models/cube.obj",
			"Models/bunny.obj",
			"Models/hydra.obj"
		};

		ImGui::Begin("Models");

		static int selectedModelIndex = 0; // Store the index of the selected model

		const char* SelectedModelString = modelFilenames[selectedModelIndex];
		if (ImGui::BeginCombo("Select A Model:", SelectedModelString)) {
			for (int i = 0; i < _countof(modelFilenames); i++)
			{
				bool isSelected = (selectedModelIndex == i); // Check against the index
				if (ImGui::Selectable(modelFilenames[i], isSelected))
				{
					selectedModelIndex = i; // Update the selected index

					// Handle model selection change here
					m_model->Load(modelFilenames[i]);

					// Apply rotation to "buddha" and "bunny" models
					if (selectedModelIndex == 1) // "buddha.obj" index
					{
						m_model->Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
					}

					if (selectedModelIndex == 10) // "bunny.obj" index
					{
						m_model->Rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
					}
				}
				if (isSelected) { ImGui::SetItemDefaultFocus(); }
			}
			ImGui::EndCombo();
		}

		ImGui::End();

		//*********************** end test of model in gui ****************************************************************************

		// Set updated light and shininess uniform values in the shade

		m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
		m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * +dt : 0;
		m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * -dt : 0;
		m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * +dt : 0;

		m_time += dt;

		m_material->ProcessGui();
		m_material->Bind();

		for (int i = 0; i < 3; i++)
		{
			std::string name = "light[" + std::to_string(i) + "]";

			m_material->GetProgram()->SetUniform(name + ".type", m_lights[i].type);
			m_material->GetProgram()->SetUniform(name + ".position", m_lights[i].position);
			m_material->GetProgram()->SetUniform(name + ".direction", glm::normalize(m_lights[i].direction));
			m_material->GetProgram()->SetUniform(name + ".color", m_lights[i].color);
			m_material->GetProgram()->SetUniform(name + ".intesity", m_lights[i].intesity);
			m_material->GetProgram()->SetUniform(name + ".range", m_lights[i].range);
			m_material->GetProgram()->SetUniform(name + ".innerangle", glm::radians(m_lights[i].innerAngle));
			m_material->GetProgram()->SetUniform(name + ".outerangle", glm::radians(m_lights[i].outerAngle));

		}

		m_material->GetProgram()->SetUniform("material.shininess", shiny);

		// Model matrix
		m_material->GetProgram()->SetUniform("model", m_transform.GetMatrix());

		// View matrix
		glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
		m_material->GetProgram()->SetUniform("view", view);

		// Projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(70.0f), ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), 0.01f, 100.0f);
		m_material->GetProgram()->SetUniform("projection", projection);

		ENGINE.GetSystem<Gui>()->EndFrame();
	}

	void World04::Draw(Renderer& renderer)
	{
		// Pre-render
		renderer.BeginFrame();
		m_material->Bind();
		// Render
		m_model->Draw(GL_TRIANGLES);

		ENGINE.GetSystem<Gui>()->Draw();
		renderer.EndFrame();
	}
}
