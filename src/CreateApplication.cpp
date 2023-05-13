#include "AppEntryPoint.h"
#include "Core/Application.h"
#include "DYEditorApplication.h"
#include "Configuration/ProjectConfig.h"

namespace DYE
{
	Application * CreateApplication()
	{
		DYEditor::ProjectConfig &runtimeConfig = DYEditor::GetRuntimeConfig();
		auto projectName = runtimeConfig.GetOrDefault<std::string>(DYEditor::RuntimeConfigKeys::ProjectName, "Sandbox");
		auto mainWindowWidth = runtimeConfig.GetOrDefault<int>(DYEditor::RuntimeConfigKeys::MainWindowWidth, 1600);
		auto mainWindowHeight = runtimeConfig.GetOrDefault<int>(DYEditor::RuntimeConfigKeys::MainWindowHeight, 900);

		return new DYEditor::DYEditorApplication
			{
				WindowProperties
					{
						projectName,
						(std::uint32_t) mainWindowWidth,
						(std::uint32_t) mainWindowHeight
					},
				60
			};
	}
}
