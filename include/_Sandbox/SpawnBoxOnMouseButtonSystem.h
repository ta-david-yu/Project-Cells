#pragma once

#include "_Sandbox/SpawnBoxOnMouseButtonComponent.h"

#include "Core/EditorSystem.h"
#include "Core/Components.h"

#include "Input/InputManager.h"
#include "Graphics/WindowManager.h"
#include "Core/Entity.h"

namespace DYE::DYEditor
{
	DYE_SYSTEM("Spawn Box On Mouse Button System", DYE::DYEditor::SpawnBoxOnMouseButtonSystem)
	struct SpawnBoxOnMouseButtonSystem final : public SystemBase
	{
		ExecutionPhase GetPhase() const final
		{
			return ExecutionPhase::Update;
		}

		void Execute(World &world, DYE::DYEditor::ExecuteParameters params) final
		{
			if (!INPUT.GetMouseButtonDown(MouseButton::Left))
			{
				return;
			}

			auto tryGetFocusedWindowID = WindowManager::TryGetMouseFocusedWindowID();
			if (!tryGetFocusedWindowID.has_value())
			{
				return;
			}

			auto group = world.GetGroup<SpawnBoxOnMouseButtonComponent>(Get<CameraComponent, TransformComponent>);
			for (auto entity : group)
			{
				SpawnBoxOnMouseButtonComponent &spawnBoxOnMouseButtonComponent = group.get<SpawnBoxOnMouseButtonComponent>(entity);
				CameraComponent &cameraComponent = group.get<CameraComponent>(entity);
				TransformComponent &transformComponent = group.get<TransformComponent>(entity);

				if (cameraComponent.Properties.TargetType != RenderTargetType::Window)
				{
					continue;
				}

				WindowID targetWindowID = tryGetFocusedWindowID.value();
				auto tryGetWindowIndex = WindowManager::TryGetWindowIndexFromID(targetWindowID);
				if (!tryGetWindowIndex.has_value())
				{
					// The window is possibly not registered in the WindowManager (i.e. ImGui Window).
					continue;
				}

				if (cameraComponent.Properties.TargetWindowIndex != tryGetWindowIndex.value())
				{
					continue;
				}

				WindowBase *targetWindow = WindowManager::TryGetWindowFromID(targetWindowID);

				// Derive the world position that the mouse clicks at.
				Camera camera = cameraComponent.CreateCameraWithTransform(transformComponent);
				auto mousePosition = INPUT.GetMousePositionRelativeToWindow(targetWindowID);
				auto screenPosition = mousePosition;
				screenPosition.y = targetWindow->GetHeight() - screenPosition.y;

				auto worldPositionClicked = camera.ScreenToWorldPoint(screenPosition, 10);

				// Spawn a box sprite entity at the position.
				Entity newBoxEntity = world.CreateEntity("Box");
				newBoxEntity.AddComponent<SpriteRendererComponent>().Color = spawnBoxOnMouseButtonComponent.BoxColor;
				newBoxEntity.AddComponent<TransformComponent>().Position = worldPositionClicked;
			}
		}
	};
}