#pragma once
#include "Component.h"

namespace Twili
{
	class ScriptComponent : public Component
	{
	public:
		virtual void OnCollision(Actor* other) = 0;
	};
}