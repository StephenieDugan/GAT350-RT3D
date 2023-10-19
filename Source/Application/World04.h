#pragma once

#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"

#include <vector>
#include <glm/glm/glm.hpp> // Include the necessary glm header for glm types

namespace Twili
{
    class World04 : public World
    {
    public:
        bool Initialize() override;
        void Shutdown() override;
        void Update(float dt) override;
        void Draw(Renderer& renderer) override;

    private:
        float m_time;
        float m_speed = 5;

        Transform m_transform;
        res_t<Model> m_model;

        bool m_guiInitialized = false;

        glm::vec3 ambientLight;    // Ambient light color
        glm::vec3 diffuseLight;    // Diffuse light color
        glm::vec3 lightPosition;   // Light position
    };
}
