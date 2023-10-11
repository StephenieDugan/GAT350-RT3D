#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Vector2.h"
#include "Renderer/Program.h"
#include <vector>

namespace Twili
{
	class World03 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_speed = 5;
		float m_time = 0;

		Transform m_transform;

		GLuint vao;
		res_t<Program> m_program;
	};
}