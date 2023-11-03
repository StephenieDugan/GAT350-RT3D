#include "ModelComponent.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"
#include <Core/StringUtils.h>

namespace Twili
{
	CLASS_DEFINITION(ModelComponent)

	bool ModelComponent::Initialize()
	{
		if (!modelName.empty())
		{
			model = std::make_shared<Model>();
			model->Load(modelName);
		}
		if (model && !materialName.empty())
		{
			model->SetMaterial(GET_RESOURCE(Material, materialName));
		}
		return true;
	}

	void ModelComponent::Update(float dt)
	{
	}

	void ModelComponent::Draw(Renderer& renderer)
	{
		auto material = model->GetMaterial();
		material->Bind();
		material->GetProgram()->SetUniform("model", m_owner->transform.GetMatrix());

		glDepthMask(enableDepth);
		glCullFace(cullface);

		model->Draw();
	}

	void ModelComponent::Read(const json_t& value)
	{
		READ_DATA(value, modelName);
		READ_DATA(value, materialName);

		std::string cullfaceName;
		READ_NAME_DATA(value, "cullface", cullfaceName);
		if (IsEqualIgnoreCase(cullfaceName, "front")) cullface = GL_FRONT;
		if (IsEqualIgnoreCase(cullfaceName, "back")) cullface = GL_BACK;
		if (IsEqualIgnoreCase(cullfaceName, "front_and_back")) cullface = GL_FRONT_AND_BACK;

		READ_DATA(value, enableDepth);

	}
}
