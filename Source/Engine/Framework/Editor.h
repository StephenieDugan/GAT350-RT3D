#pragma once

namespace Twili
{
class Editor
{
    enum class ResourceType
    {
        ALL,
        TEXTURE,
        MODEL,
        MATERIAL,
        SHADER
    };
public:
	void Update();
	void ProcessGui(class Scene* scene);

    Editor::ResourceType GetResourceType(Resource* resource);

private:
	bool m_active = true;
	class Object* m_selected = nullptr;
    ResourceType m_selectedResourceType = ResourceType::ALL;
};
}


