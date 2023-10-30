#include "World05.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "imgui/imgui.h"

#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>
#define INTERLEAVE

#include <iostream>
#include "Core/StringUtils.h"

namespace Twili
{
		
	bool World05::Initialize()
	{
		m_scene = std::make_unique<Scene>();
		m_scene->Load("Scenes/scene.json");
		m_scene->Initialize();

		{
			auto actor = CREATE_CLASS(Actor);
			actor->name = "camera1";
			actor->transform.position = glm::vec3{ 0, 0, 3 };
			actor->transform.rotation = glm::vec3{ 0, 180, 0 };

			auto cameraComponent = CREATE_CLASS(CameraComponent);
			cameraComponent->SetPerspective(70.0f, ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), 0.1f, 100.0f);
			actor->AddComponent(std::move(cameraComponent));

			m_scene->Add(std::move(actor));
		}

		{
			auto actor = CREATE_CLASS(Actor);
			actor->name = "light1";
			actor->transform.position = glm::vec3{ 3, 3, 3 };
			auto lightComponent = CREATE_CLASS(LightComponent);
			lightComponent->type = LightComponent::eType::POINT;
			lightComponent->color = glm::rgbColor(glm::vec3{ randomf() * 360, 1, 1 });
			lightComponent->intensity = 1;
			lightComponent->range = 20;
			lightComponent->innerAngle = 10.0f;
			lightComponent->outerAngle = 30.0f;
			actor->AddComponent(std::move(lightComponent));
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
		// Set updated light and shininess uniform values in the shader

		actor->transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
		actor->transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * +dt : 0;
		actor->transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * -dt : 0;
		actor->transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * +dt : 0;

		m_time += dt;

		auto material = actor->GetComponent<ModelComponent>()->model->GetMaterial();

		material->ProcessGui();
		material->Bind();

		//material->GetProgram()->SetUniform("material.shininess", shiny);
		
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

	int main() {
		std::string input = "Hello";

		// Testing ToUpper function
		std::string upper = StringUtils::ToUpper(input);
		std::cout << "ToUpper: " << upper << std::endl;

		// Testing ToLower function
		std::string lower = StringUtils::ToLower(input);
		std::cout << "ToLower: " << lower << std::endl;

		// Testing IsEqualIgnoreCase function
		std::string str1 = "Hello";
		std::string str2 = "HELLO";
		bool isEqual = StringUtils::IsEqualIgnoreCase(str1, str2);
		std::cout << "IsEqualIgnoreCase: " << isEqual << std::endl;

		// Testing CreateUnique function
		std::string uniqueStr1 = StringUtils::CreateUnique(input);
		std::string uniqueStr2 = StringUtils::CreateUnique(input);
		std::cout << "Unique Strings: " << uniqueStr1 << ", " << uniqueStr2 << std::endl;

		return 0;
	}

}
