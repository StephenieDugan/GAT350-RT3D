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
		m_scene->Load("Scenes/scen_Framebuffer.json");
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

        // Set postprocess GUI
        ImGui::Begin("Post-Process");
        ImGui::SliderFloat("Blend", &blend, 0, 1);

        // Checkbox and controls for Invert
        bool effect = params & INVERT_MASK;
        if (ImGui::Checkbox("Invert", &effect))
        {
            (effect) ? params |= INVERT_MASK : params &= ~INVERT_MASK;
        };

        // Checkbox and controls for Grayscale
        effect = params & GRAYSCALE_MASK;
        if (ImGui::Checkbox("Grayscale", &effect))
        {
            (effect) ? params |= GRAYSCALE_MASK : params &= ~GRAYSCALE_MASK;
        };

        // Checkbox and controls for Color Tint
        effect = params & COLORTINT_MASK;
        if (ImGui::Checkbox("Color Tint", &effect))
        {
            (effect) ? params |= COLORTINT_MASK : params &= ~COLORTINT_MASK;
        }
        if (params & COLORTINT_MASK)
        {
            ImGui::ColorEdit3("Color Tint", glm::value_ptr(colorTint));
        }

        //// Checkbox and controls for Grain
        //effect = m_params & GRAIN_MASK;
        //if (ImGui::Checkbox("Grain", &effect))
        //{
        //    (effect) ? m_params |= GRAIN_MASK : m_params &= ~GRAIN_MASK;
        //}

        //// Checkbox and controls for Scanline
        //effect = m_params & SCANLINE_MASK;
        //if (ImGui::Checkbox("Scanline", &effect))
        //{
        //    (effect) ? m_params |= SCANLINE_MASK : m_params &= ~SCANLINE_MASK;
        //}

        //// Controls for Grain and Scanline parameters
        //if (m_params & GRAIN_MASK)
        //{
        //    ImGui::SliderFloat("Grain Intensity", &m_grainIntensity, 0.0f, 1.0f);
        //}

        //if (m_params & SCANLINE_MASK)
        //{
        //    ImGui::SliderFloat("Scanline Intensity", &m_scanlineIntensity, 0.0f, 1.0f);
        //}

        //// Checkbox and controls for Kernel Effect
        //effect = m_params & KERNEL_EFFECT_MASK;
        //if (ImGui::Checkbox("Kernel Effect", &effect))
        //{
        //    (effect) ? m_params |= KERNEL_EFFECT_MASK : m_params &= ~KERNEL_EFFECT_MASK;
        //}
        //if (m_params & KERNEL_EFFECT_MASK)
        //{
        //    ImGui::SliderFloat("Kernel Intensity", &m_kernelIntensity, 0.0f, 1.0f);
        //}
        ImGui::End();

		//set post process shader
		auto program = GET_RESOURCE(Program, "shaders/post_process.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("blend", blend);
			program->SetUniform("params", params);
		}

		ENGINE.GetSystem<Gui>()->EndFrame();
	}

	void World07::Draw(Renderer& renderer)
	{
		//**PASS 1 ***
		m_scene->GetActorByName("postprocess")->active = false;
		auto framebuffer = GET_RESOURCE(Framebuffer,"fb");
		renderer.SetViewport(framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();

		// Pre-render
		renderer.BeginFrame(glm::vec3{ 0,0,0 });
		m_scene->Draw(renderer);

		framebuffer->Unbind();

		//*** PASS 2 ***
		m_scene->GetActorByName("postprocess")->active = true;

		renderer.ResetViewport();
		renderer.BeginFrame();
		m_scene->GetActorByName("postprocess")->Draw(renderer);



		ENGINE.GetSystem<Gui>()->Draw();
		renderer.EndFrame();
	}
}
