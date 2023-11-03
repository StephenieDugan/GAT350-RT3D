#pragma once
#include "Component.h"

namespace Twili
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
		
	};
}
