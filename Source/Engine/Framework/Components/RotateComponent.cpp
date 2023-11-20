#include "RotateComponent.h"
#include <Core/Math/MathUtils.h>
namespace nc
{
	CLASS_DEFINITION(RotateComponent);

	bool RotateComponent::Initialize()
	{
		return false;
	}
	void RotateComponent::Update(float dt)
	{
		glm::quat rotation = EulerToQuaternion(euler * dt);
		//m_owner->transform.rotation = m_owner->transform.rotation * rotation;
	}
	void RotateComponent::ProcessGUI()
	{
	}
	void RotateComponent::SetProgram(const res_t<Program> program)
	{
	}

	void RotateComponent::Read(const json_t& value)
	{
		READ_DATA(value, euler);
	}
}