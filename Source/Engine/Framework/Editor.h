#pragma once
namespace nc
{
	class Editor
	{
	public:
		void Update();
		void ProcessGUI(class Scene* scene);

	private:
		bool m_active = true;
		class Object* m_selected = nullptr;
	};
}