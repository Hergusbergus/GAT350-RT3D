#pragma once
#include "Component.h"
#include "Renderer/Program.h"

namespace nc
{
	class RotateComponent : public Component
	{
	public:
		CLASS_DECLARATION(RotateComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void ProcessGUI() override;

		void SetProgram(const res_t<Program> program);

	public:
		glm::vec3 euler{ 0 };
	};
}
