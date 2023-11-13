#include "World07.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "imgui/imgui.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include<glm/glm/gtx/color_space.hpp>

namespace Twili
{
	

	bool World07::Initialize()
	{
		m_scene = std::make_unique<Scene>();
		m_scene->Load("Scenes/scene_shadow.json");
		m_scene->Initialize();

		auto texture = std::make_shared<Texture>();
		texture->CreateTexture(2048, 2048);
		ADD_RESOURCE("fb_texture", texture);

		auto frameBuffer = std::make_shared<Framebuffer>();
		frameBuffer->CreateFramebuffer(texture);
		ADD_RESOURCE("fb", frameBuffer);

		auto material = GET_RESOURCE(Material, "Materials/post_process.mtrl");
		if (material)
		{
			material->albedoTexture = texture;
		}

		return true;
	}

	void World07::Shutdown()
	{
	}

    void World07::Update(float dt) {
        m_time += dt;

        ENGINE.GetSystem<Gui>()->BeginFrame();

        m_scene->Update(dt);
        m_scene->ProcessGui();

		ENGINE.GetSystem<Gui>()->EndFrame();

	}

	void World07::Draw(Renderer& renderer)
	{
		//**PASS 1 ***
		/*
		m_scene->GetActorByName("postprocess")->active = false;
		auto framebuffer = GET_RESOURCE(Framebuffer,"fb");
		renderer.SetViewport(framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();

		// Pre-render
		renderer.BeginFrame(glm::vec3{ 0,0,0 });
		m_scene->Draw(renderer);

		framebuffer->Unbind();
*/
		//*** PASS 2 ***

		renderer.ResetViewport();
		renderer.BeginFrame();
		m_scene->Draw(renderer);



		ENGINE.GetSystem<Gui>()->Draw();
		renderer.EndFrame();
	}
}
