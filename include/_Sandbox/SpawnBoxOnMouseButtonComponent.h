#pragma once

#include "Core/EditorComponent.h"
#include "Core/EditorProperty.h"

namespace DYE::DYEditor
{
	DYE_COMPONENT("Spawn Box On Mouse Button", DYE::DYEditor::SpawnBoxOnMouseButtonComponent)
	struct SpawnBoxOnMouseButtonComponent
	{
		DYE_PROPERTY()
		DYE::Color4 BoxColor = {1, 1, 1, 1};
	};
}