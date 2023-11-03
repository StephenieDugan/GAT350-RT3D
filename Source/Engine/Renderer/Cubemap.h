#pragma once
#include "Renderer/Texture.h"
#include <vector>

namespace Twili
{
	class Cubemap : public Texture
	{
	public:
		bool Create(std::string filename, ...) override;
		bool Load(const std::vector<std::string>& filenames);

	};
}