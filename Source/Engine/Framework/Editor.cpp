#include "Editor.h"
#include "Scene.h"
#include "Components/CameraComponent.h"

namespace nc
{
	void Editor::Update()
	{
		if (ImGui::IsKeyPressed(ImGuiKey_GraveAccent))
		{
			m_active = !m_active;
		}
	}

	void Editor::ProcessGUI(Scene* scene)
	{
		if (!m_active) return;

		// Define categories
		std::vector<std::pair<std::string, std::vector<std::string>>> categories = {
			{"Textures", {".png"}},
			{"Models", {".obj"}},
			{"Materials", {".mtrl"}},
			{"Shaders", {".prog", ".vert", ".frag"}}
		};

		// Map to store resources for each category
		std::map<std::string, std::vector<Resource*>> categorizedResources;

		// Categorize resources
		auto resources = GET_RESOURCES(Resource);
		for (auto& resource : resources)
		{
			for (const auto& category : categories)
			{
				for (const auto& extension : category.second)
				{
					if (resource->name.length() >= extension.length() &&
						resource->name.compare(resource->name.length() - extension.length(), extension.length(), extension) == 0)
					{
						categorizedResources[category.first].emplace_back(resource.get());
						break;
					}
				}
			}
		}

		// show resources
		// Show categorized resources
		ImGui::Begin("Resources");
		for (const auto& category : categories)
		{
			if (ImGui::TreeNode(category.first.c_str()))
			{
				for (auto& resource : categorizedResources[category.first])
				{
					if (ImGui::Selectable(resource->name.c_str(), resource == m_selected))
					{
						m_selected = resource;
					}
				}
				ImGui::TreePop();
			}
		}
		ImGui::End();

		// show scene
		ImGui::Begin("Scene");
		scene->ProcessGUI();
		ImGui::Separator();

		// show actors
		ImGui::BeginChild("Actors");
		// actor controls
		if (ImGui::BeginPopupContextWindow())
		{
			auto cameras = scene->GetComponents<CameraComponent>();
			auto camera = (!cameras.empty()) ? cameras[0] : nullptr;

			if (ImGui::MenuItem("Create Empty"))
			{
				auto actor = CREATE_CLASS(Actor);
				actor->name = CreateUnique(actor->name);
				actor->Initialize();
				m_selected = actor.get();
				scene->Add(std::move(actor));
			}
			if (ImGui::MenuItem("Sphere"))
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Sphere");
				actor->name = CreateUnique(actor->GetClassName());
				if (camera)
				{
					actor->transform.position = camera->m_owner->transform.position;
				}
				actor->Initialize();
				m_selected = actor.get();
				scene->Add(std::move(actor));
			}
			if (ImGui::MenuItem("Cube"))
			{

			}
			if (ImGui::MenuItem("Camera"))
			{

			}
			if (ImGui::MenuItem("Light"))
			{

			}

			ImGui::EndPopup();
		}

		for (auto& actor : scene->m_actors)
		{
			if (ImGui::Selectable(actor->name.c_str(), actor.get() == m_selected))
			{
				m_selected = actor.get();
			}
		}
		ImGui::EndChild();
		ImGui::End();

		ImGui::Begin("Inspector");
		if (m_selected)
		{
			m_selected->ProcessGUI();

			// delete selected actor
			if (ImGui::IsKeyPressed(ImGuiKey_Delete))
			{
				auto actor = dynamic_cast<Actor*>(m_selected);
				if (actor)
				{
					scene->Remove(actor);
					m_selected = nullptr;
				}
			}
		}
		ImGui::End();
	}
}

