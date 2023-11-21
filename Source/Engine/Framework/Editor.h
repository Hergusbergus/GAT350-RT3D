#pragma once
namespace nc
{
	class Editor
	{
	public:
		void ProcessGUI(class Scene* scene);

	private:
		class Object* m_selected = nullptr;
	};
}