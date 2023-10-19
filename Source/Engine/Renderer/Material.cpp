#include "Material.h"
#include "Program.h"
#include "Texture.h"
#include "Core/Core.h"

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

		// read the textures name
		std::vector<std::string> textures;
		READ_DATA(document, textures);
		for (auto texture : textures)
		{
			// get texture resource
			m_textures.push_back(GET_RESOURCE(Texture, texture));
		}

		READ_DATA(document, diffuse);
		READ_DATA(document, specular);
		READ_DATA(document, shiny);
		READ_DATA(document, tiling);
		READ_DATA(document, offset);



		return true;
	}

	void Material::Bind()
	{
		m_program->Use();

		m_program->SetUniform("material.diffuse", diffuse);
		m_program->SetUniform("material.tiling", tiling);
		m_program->SetUniform("material.offset", offset);
		m_program->SetUniform("material.specular", specular);
		m_program->SetUniform("material.shininess", shiny);



		for (size_t i = 0; i < m_textures.size(); i++)
		{
			m_textures[i]->setActive(GL_TEXTURE0 + (int)i);
			m_textures[i]->Bind();
		}
	}
	void Material::ProcessGui()
	{
		ImGui::Begin("Material");

		ImGui::ColorEdit4(" diffuse", &diffuse[0]);
		ImGui::ColorEdit3("specular", &specular[0]);
		ImGui::DragFloat("shiny", &shiny, 0.1f, 2.0f, 255.0f);
		ImGui::DragFloat2("tiling", &tiling[0], 0.1f);
		ImGui::DragFloat2("offset", &offset[0], 0.1f);
		
		ImGui::End();

		


		
	}
}