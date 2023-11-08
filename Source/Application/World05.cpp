#include "World05.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "imgui/imgui.h"

#include <glm/glm/gtc/type_ptr.hpp>
#include<glm/glm/gtx/color_space.hpp>

namespace Twili
{
	int selectedModel = 0;

	bool World05::Initialize()
	{
		m_scene = std::make_unique<Scene>();
		m_scene->Load("scenes/scene.json");
		m_scene->Initialize();

		for (int i = 0; i < 2; i++) 
		{
			auto actor = CREATE_CLASS_BASE(Actor, "tree");
			actor->name = CreateUnique("tree");
			actor->transform.position = glm::vec3{ randomf(-10,10),0,randomf(-10,10) };
			actor->transform.scale = glm::vec3{ randomf(0.5f,0.3f),randomf(0.5f,0.3f),0 };

			actor->Initialize();
			m_scene->Add(std::move(actor));
		}
		return true;
	}

	void World05::Shutdown()
	{
	}

	void World05::Update(float dt)
	{
		ENGINE.GetSystem<Gui>()->BeginFrame();

		m_scene->Update(dt);
		m_scene->ProcessGui();

		auto actor = m_scene->GetActorByName<Actor>("actor1");
		if (actor)
		{
			// Use the actor if it's not null
			actor->transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
			actor->transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * dt : 0;
			actor->transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * -dt : 0;
			actor->transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * dt : 0;
		}
		
		auto material = actor->GetComponent<ModelComponent>()->material;

		material->ProcessGui();
		material->Bind();

		material = GET_RESOURCE(Material, "materials/refraction.mtrl");
		if (material)
		{
			ImGui::Begin("Refraction");
			ImGui::DragFloat("IOR", &m_refraction, 0.01f,1.0f,3.0f);
			auto program = material->GetProgram();
			program->Use();
			program->SetUniform("ior",m_refraction);

			ImGui::End();
		}

		m_time += dt;

		material->GetProgram()->SetUniform("material.shininess", shininess);

		ENGINE.GetSystem<Gui>()->EndFrame();
	}

	void World05::Draw(Renderer& renderer)
	{
		// Pre-render
		renderer.BeginFrame();

		// Render
		m_scene->Draw(renderer);

		ENGINE.GetSystem<Gui>()->Draw();
		renderer.EndFrame();
	}
}
