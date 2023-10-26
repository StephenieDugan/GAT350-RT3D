#pragma once

#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"

#include <vector>
#include <glm/glm/glm.hpp> 


namespace Twili
{
   

    class World05 : public World
    { 
    public:
        bool Initialize() override;
        void Shutdown() override;
        void Update(float dt) override;
        void Draw(Renderer& renderer) override;

    private:
        float m_time;
        float m_speed = 5;
        float shiny = 2.0f;

        glm::vec3 ambientLight{ 0.2 };    // Light position
    };
}
