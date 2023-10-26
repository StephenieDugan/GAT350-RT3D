#pragma once

#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"

#include <vector>
#include <glm/glm/glm.hpp> 


namespace Twili
{
    struct light_t
    {
        enum eType {
            POINT,
            DIRECTIONAL,
            SPOT
        };
        eType type;
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 color;
        float range;
        float intesity;
        float innerAngle;
        float outerAngle;
    };

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
        float shiny = 2.0f;

        Transform m_transform;
        res_t<Model> m_model;

        bool m_guiInitialized = false;

        //light_t m_light;
        std::vector<light_t> m_lights;
        int m_selected = 0;
        glm::vec3 ambientLight{ 0.2 };    // Light position
    };
}
