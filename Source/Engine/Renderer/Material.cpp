#include "Material.h"
#include "Program.h"
#include "Texture.h"
#include "Core/Core.h"
//add something

namespace Twili
{
	bool Material::Create(std::string filename, ...)
	{
		// load program json document
		rapidjson::Document document;
		bool success = Json::Load(filename, document);
		if (!success)
		{
			INFO_LOG("Could not load program file (%s)." << filename);
			return false;
		}

		// read the program name
		std::string program;
		READ_DATA(document, program);
		// get program resource
		m_program = GET_RESOURCE(Program, program);

		// read the textures
		std::string albedoTextureName;
		if (READ_NAME_DATA(document, "albedoTexture", albedoTextureName))
		{
			params |= ALBEDO_TEXTURE_MASK;
			albedoTexture = GET_RESOURCE(Texture, albedoTextureName);
		}

		std::string specularTextureName;
		if (READ_NAME_DATA(document, "specularTexture", specularTextureName))
		{
			params |= SPECULAR_TEXTURE_MASK;
			specularTexture = GET_RESOURCE(Texture, specularTextureName);
		}

		std::string emissiveTextureName;
		if (READ_NAME_DATA(document, "emissiveTexture", emissiveTextureName))
		{
			params |= EMISSIVE_TEXTURE_MASK;
			emissiveTexture = GET_RESOURCE(Texture, emissiveTextureName);
		}

		std::string normalTextureName;
		if (READ_NAME_DATA(document, "normalTexture", normalTextureName))
		{
			params |= NORMAL_TEXTURE_MASK;
			normalTexture = GET_RESOURCE(Texture, normalTextureName);
		}

		std::string cubemapName;
		if (READ_NAME_DATA(document, "cubemap", cubemapName))
		{
			params |= CUBEMAP_TEXTURE_MASK;
			std::vector<std::string> cubemaps;
			READ_DATA(document, cubemaps);

			cubemapTexture = GET_RESOURCE(Texture, cubemapName);
		}

		READ_DATA(document, albedo);
		READ_DATA(document, specular);
		READ_DATA(document, emissive);
		READ_DATA(document, shiny);
		READ_DATA(document, tiling);
		READ_DATA(document, offset);

		return true;
	}
	void Material::Bind()
	{
		m_program->Use();

		m_program->SetUniform("material.params", params);
		m_program->SetUniform("material.albedo", albedo);
		m_program->SetUniform("material.specular", specular);
		m_program->SetUniform("material.emissive", emissive);
		m_program->SetUniform("material.tiling", tiling);
		m_program->SetUniform("material.offset", offset);
		m_program->SetUniform("material.shininess", shiny);

		if (albedoTexture)
		{
			albedoTexture->setActive(GL_TEXTURE0);
			albedoTexture->Bind();
		}
		if (specularTexture)
		{
			specularTexture->setActive(GL_TEXTURE1);
			specularTexture->Bind();
		}
		if (normalTexture)
		{
			normalTexture->setActive(GL_TEXTURE2);
			normalTexture->Bind();
		}
		if (emissiveTexture)
		{
			emissiveTexture->setActive(GL_TEXTURE3);
			emissiveTexture->Bind();
		}

	}
	void Material::ProcessGui()
	{
		ImGui::Begin("Material");

		ImGui::ColorEdit4("albedo", &albedo[0]);
		ImGui::ColorEdit4("emissive", &emissive[0]);
		ImGui::ColorEdit3("specular", &specular[0]);
		ImGui::DragFloat("shiny", &shiny, 0.1f, 2.0f, 255.0f);
		ImGui::DragFloat2("tiling", &tiling[0], 0.1f);
		ImGui::DragFloat2("offset", &offset[0], 0.1f);
		
		ImGui::End();

		


		
	}
}