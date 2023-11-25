#include "Editor.h"
#include "Scene.h"
#include "Components/CameraComponent.h"

namespace Twili
{
	void Editor::Update()
	{
		if (ImGui::IsKeyPressed(ImGuiKey_GraveAccent))
		{
			m_active = !m_active;
		}
	}
	void Editor::ProcessGui(Scene* scene)
	{
		if (!m_active) return;

		// Show filter dropdown
		ImGui::Begin("Resources");

		ImGui::Text("Filter by Resource Type:");
		const char* resourceTypes[] = { "All", "texture", "model", "material", "shader" };
		ImGui::Combo("##ResourceTypeCombo", (int*)&m_selectedType, resourceTypes, IM_ARRAYSIZE(resourceTypes));


		// Show resources based on the selected type
		auto resources = GET_RESOURCES(Resource);
		for (auto& resource : resources)
		{
			// Check if the resource type matches the selected type
			if (m_selectedType == "All") 
			{
				if (ImGui::Selectable(resource->name.c_str(), resource.get() == m_selected))
				{
					m_selected = resource.get();
				}
			}
			else if (m_selectedType == "texture")
			{
				std::cout << "Class Nmae: " << resource->GetClassName() << std::endl;
				if (resource->GetClassName() == "Texture")
				{
					if (ImGui::Selectable(resource->name.c_str(), resource.get() == m_selected))
					{
						m_selected = resource.get();
					}
				}
			}
			
		}

		ImGui::End();

		//show scene

		ImGui::Begin("Scene");
		scene->ProcessGui();
		ImGui::Separator();

		//show actors
		ImGui::BeginChild("Actors");
		//actor cobtrols 
		if (ImGui::BeginPopupContextWindow())
		{
			auto cameras = scene->GetComponents<CameraComponent>();
			auto camera = (!cameras.empty()) ? cameras[0] : nullptr;

			if(ImGui::MenuItem("Create Empty"))
			{
				auto actor = CREATE_CLASS(Actor);
				actor->name = CreateUnique(actor->GetClassName());
				actor->Initialize();
				m_selected = actor.get();
				scene->Add(std::move(actor));

			}
			if(ImGui::MenuItem("Sphere"))
			{
				auto actor = CREATE_CLASS_BASE(Actor,"Sphere");
				actor->name = CreateUnique(actor->name);
				if (camera)
				{
					actor->transform.position = camera->m_owner->transform.position * camera->m_owner->transform.Forward() * 3.0f;
				}
				actor->Initialize();
				m_selected = actor.get();
				scene->Add(std::move(actor));
			}
			if(ImGui::MenuItem("Cube"))
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Cube");
				actor->name = CreateUnique(actor->name);
				actor->Initialize();
				m_selected = actor.get();
				scene->Add(std::move(actor));
			}
			if(ImGui::MenuItem("Camera"))
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Camera");
				actor->name = CreateUnique(actor->name);
				
				actor->Initialize();
				m_selected = actor.get();
				scene->Add(std::move(actor));
			}
			if(ImGui::MenuItem("Light"))
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Light");
				actor->name = CreateUnique(actor->name);
				actor->Initialize();
				m_selected = actor.get();
				scene->Add(std::move(actor));
			}

			ImGui::EndPopup();
		}

		for (auto& actor : scene->m_actors)
		{
			if (ImGui::Selectable(actor->name.c_str(), actor.get() == m_selected))
			{
				m_selected = actor.get();
			}
		}
		ImGui::EndChild();
		ImGui::End();

		//show inspector
		ImGui::Begin("Inspector");
		if (m_selected)
		{
			m_selected->ProcessGui();
			//delete selected actor
			if (ImGui::IsKeyPressed(ImGuiKey_Delete))
			{
				auto actor = dynamic_cast<Actor*>(m_selected);
				if (actor)
				{
					scene->Remove(actor);
					m_selected = nullptr;
				}
			}
		}
		
		ImGui::End();
	}
}