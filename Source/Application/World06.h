#pragma once

#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"

#include <vector>

namespace Twili
{
    class World06 : public World
    {
       
    public:
        bool Initialize() override;
        void Shutdown() override;
        void Update(float dt) override;
        void Draw(Renderer& renderer) override;

    private:
        float m_time;
        float m_speed = 5;

        float m_refraction = 3;

        glm::vec3 m_ambientColor{ 0.2f };

        bool m_guiInitialized = false;

        float shininess = 32.0f;  // Shininess property

    };
}
