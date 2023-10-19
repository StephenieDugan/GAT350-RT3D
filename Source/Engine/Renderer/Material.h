#pragma once
#include "Framework/Resource/Resource.h"
#include "GUI.h"
#include <glm/glm/glm.hpp>
#include <vector>
#include <memory>

namespace Twili
{
	class Texture;
	class Program;

	class Material : public Resource
	{
	public:
		virtual bool Create(std::string filename, ...) override;

		void Bind();

		res_t<Program> GetProgram() { return m_program; }

		void ProcessGui();

	public:
		glm::vec3 diffuse{ 1 };
		glm::vec3 specular{ 1 };
		float shiny = 2;
		/*glm::vec4 lcolor;
		glm::vec4 dcolor;
		glm::vec3 position;*/
		glm::vec2 tiling{ 1,1 };
		glm::vec2 offset{ 0,0 };


	private:
		res_t<Program> m_program;
		std::vector<res_t<Texture>> m_textures;
	};
}