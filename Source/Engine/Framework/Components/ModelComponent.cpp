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
			//ADD_RESOURCE(modelName, model);
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


		std::string cullfacename;
		READ_NAME_DATA(value, "cullface", cullfacename);
		if (IsEqualIgnoreCase(cullfacename, "front")) cullface = GL_FRONT;
		if (IsEqualIgnoreCase(cullfacename, "back")) cullface = GL_BACK;
		if (IsEqualIgnoreCase(cullfacename, "front_and_back")) cullface = GL_FRONT_AND_BACK;

		READ_DATA(value, enableDepth);


	}

}
