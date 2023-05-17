#pragma once

#include "Core/EditorSystem.h"

#include "Core/Entity.h"
#include "Util/Logger.h"
#include "Input/InputManager.h"
#include "ImGui/ImGuiUtil.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Graphics/DebugDraw.h"
#include "Graphics/WindowManager.h"
#include "Graphics/RenderCommand.h"

namespace DYE::DYEditor::Template
{
	DYE_SYSTEM("Example System", DYE::DYEditor::Template::ExampleSystem)
	struct ExampleSystem final : public SystemBase
	{
		ExecutionPhase GetPhase() const override { return ExecutionPhase::Update; }
		void Execute(DYE::DYEditor::World &world, DYE::DYEditor::ExecuteParameters params) override
		{
			DYE_LOG("Example System Update!");
		}
	};

	DYE_SYSTEM("Mouse Position In Camera Space System", DYE::DYEditor::Template::MousePositionInCameraSpaceImGuiSystem)
	struct MousePositionInCameraSpaceImGuiSystem final : public SystemBase
	{
		glm::vec4 Colors[3] = { {1, 0, 0, 1}, {0.2f, 1, 0.2f, 1}, {0, 0, 1, 1} };

		ExecutionPhase GetPhase() const final
		{
			return ExecutionPhase::Update;
		}

		void Execute(World &world, DYE::DYEditor::ExecuteParameters params) final
		{
			int index = 0;
			auto view = world.GetView<CameraComponent, TransformComponent>();
			for (auto [entity, cameraComponent, transformComponent] : view.each())
			{
				auto color = Colors[index % 3];

				Camera camera;
				camera.Properties = cameraComponent.Properties;
				camera.Position = transformComponent.Position;
				camera.Rotation = transformComponent.Rotation;

				glm::vec2 mousePosition {0, 0};
				glm::vec2 screenPosition {0, 0};
				WindowBase *targetWindow = WindowManager::TryGetWindowAt(camera.Properties.TargetWindowIndex);
				if (targetWindow != nullptr)
				{
					WindowID windowID = targetWindow->GetWindowID();
					mousePosition = INPUT.GetMousePositionRelativeToWindow(windowID);
					screenPosition = mousePosition;
					screenPosition.y = targetWindow->GetHeight() - screenPosition.y;
				}

				glm::vec3 worldPoint = camera.ScreenToWorldPoint(screenPosition, 10);

				RenderCommand::GetInstance().SetLinePrimitiveWidth(3);
				DebugDraw::Sphere(worldPoint, 0.2f, color);

				index++;
			}
		}

		void DrawInspector(World &world) final
		{
			if (!ImGui::Begin("Camera Space Debugger"))
			{
				ImGui::End();
				return;
			}

			auto globalMousePosition = INPUT.GetGlobalMousePosition();
			ImGui::Text("Global Mouse Position: %d, %d", globalMousePosition.x, globalMousePosition.y);
			auto pFocusedWindow = WindowManager::TryGetMouseFocusedWindow();
			ImGui::Text("Focused Window: %s", pFocusedWindow != nullptr? pFocusedWindow->GetTitle().c_str() : "null");
			ImGui::Separator();

			int index = 0;
			auto view = world.GetView<CameraComponent, TransformComponent>();
			for (auto [entity, cameraComponent, transformComponent] : view.each())
			{
				auto color = Colors[index % 3];

				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(color.r, color.g, color.b, color.a));

				Entity wrappedEntity = world.WrapIdentifierIntoEntity(entity);

				Camera camera;
				camera.Properties = cameraComponent.Properties;
				camera.Position = transformComponent.Position;
				camera.Rotation = transformComponent.Rotation;

				glm::vec2 mousePosition {0, 0};
				glm::vec2 screenPosition {0, 0};
				if (pFocusedWindow != nullptr)
				{
					std::uint32_t focusedWindowIndex = WindowManager::TryGetWindowIndexFromID(pFocusedWindow->GetWindowID()).value();
					if (focusedWindowIndex == camera.Properties.TargetWindowIndex)
					{
						mousePosition = INPUT.GetMousePositionRelativeToFocusedWindow();
						screenPosition = mousePosition;
						screenPosition.y = pFocusedWindow->GetHeight() - screenPosition.y;
					}
				}

				glm::vec3 worldPoint = camera.ScreenToWorldPoint(screenPosition, 10);

				ImGui::Text("Camera '%s'", wrappedEntity.TryGetName().value().c_str());
				ImGui::Text("Mouse: %f, %f", mousePosition.x, mousePosition.y);
				ImGui::Text("Screen: %f, %f", screenPosition.x, screenPosition.y);
				ImGui::Text("World: %f, %f, %f", worldPoint.x, worldPoint.y, worldPoint.z);
				ImGui::Separator();

				ImGui::PopStyleColor();
				index++;
			}

			ImGui::End();
		}
	};
}
