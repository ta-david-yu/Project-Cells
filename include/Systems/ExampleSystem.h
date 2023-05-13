#pragma once

#include "Core/EditorSystem.h"
#include "Util/Logger.h"

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
}
