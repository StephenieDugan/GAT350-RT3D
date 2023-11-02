#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace Twili
{
	class ModelComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(ModelComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
		
	public:
		std::string modelName;
		std::string materialName;
		bool enableDepth{ true };
		GLint cullface{ GL_BACK };
		res_t<Model> model;
	};
}