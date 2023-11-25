#pragma once
#include <string>
namespace Twili
{
	class Editor
	{
		enum eType
		{
			All,
			Texture,
			Model,
			Material,
			Shader,
			Depth,
			Fantasie
		};
		public:
			void Update();
			void ProcessGui(class Scene* scene);

		private:
		bool m_active = true;
		class Object* m_selected = nullptr;
		eType m_selectedType = eType::All;
	};
}


