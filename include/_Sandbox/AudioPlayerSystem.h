#pragma once

#include "Core/EditorSystem.h"
#include "Audio/AudioSource.h"
#include "Audio/AudioClip.h"
#include "ImGui/ImGuiUtil.h"

namespace DYE::DYEditor
{
	DYE_SYSTEM("Audio Player System", DYE::DYEditor::AudioPlayerSystem)
	class AudioPlayerSystem final : public SystemBase
	{
	public:
		ExecutionPhase GetPhase() const override
		{
			return ExecutionPhase::ImGui;
		}

		void InitializeLoad(World &world, DYE::DYEditor::InitializeLoadParameters parameters) override
		{
			if (parameters.LoadType == InitializeLoadType::AfterLoadScene ||
				parameters.LoadType == InitializeLoadType::BeforeEnterEditMode)
			{
				m_MusicSource1.Stop();
				m_MusicSource2.Stop();
				m_SoundSource.Stop();
			}
		}

		void Execute(World &world, DYE::DYEditor::ExecuteParameters params) override
		{
			ImGui::Begin("Runtime Audio Player Window");

			ImGui::PushID(1);
			{
				std::filesystem::path musicClipPath1 =
					m_MusicSource1.GetClip() != nullptr ? m_MusicSource1.GetClip()->GetPath() : "";
				if (ImGuiUtil::DrawAssetPathStringControl("Music 1", musicClipPath1, {".mp3", ".wav", ".ogg"}))
				{
					m_MusicSource1.SetClip(
						AudioClip::Create(musicClipPath1, AudioClipProperties {.LoadType = AudioLoadType::Streaming}));
				}
				float volume = m_MusicSource1.GetVolume();
				if (ImGui::SliderFloat("Volume", &volume, 0, 1))
				{
					m_MusicSource1.SetVolume(volume);
				}
				if (ImGui::Button("Play"))
				{
					m_MusicSource1.Play();
				}
				ImGui::SameLine();
				if (ImGui::Button("Stop"))
				{
					m_MusicSource1.Stop();
				}
			}
			ImGui::PopID();

			ImGui::Separator();

			ImGui::PushID(2);
			{
				std::filesystem::path musicClipPath2 =
					m_MusicSource2.GetClip() != nullptr ? m_MusicSource2.GetClip()->GetPath() : "";
				if (ImGuiUtil::DrawAssetPathStringControl("Music 2", musicClipPath2, {".mp3", ".wav", ".ogg"}))
				{
					m_MusicSource2.SetClip(
						AudioClip::Create(musicClipPath2, AudioClipProperties {.LoadType = AudioLoadType::Streaming}));
				}
				float volume = m_MusicSource2.GetVolume();
				if (ImGui::SliderFloat("Volume", &volume, 0, 1))
				{
					m_MusicSource2.SetVolume(volume);
				}

				if (ImGui::Button("Play"))
				{
					m_MusicSource2.Play();
				}
				ImGui::SameLine();
				if (ImGui::Button("Stop"))
				{
					m_MusicSource2.Stop();
				}
			}
			ImGui::PopID();

			ImGui::Separator();

			ImGui::PushID(3);
			{
				std::filesystem::path soundClipPath =
					m_SoundSource.GetClip() != nullptr ? m_SoundSource.GetClip()->GetPath() : "";
				if (ImGuiUtil::DrawAssetPathStringControl("Sound", soundClipPath, {".mp3", ".wav", ".ogg"}))
				{
					m_SoundSource.SetClip(AudioClip::Create(soundClipPath,
															AudioClipProperties {.LoadType = AudioLoadType::DecompressOnLoad}));
				}
				float volume = m_SoundSource.GetVolume();
				if (ImGui::SliderFloat("Volume", &volume, 0, 1))
				{
					m_SoundSource.SetVolume(volume);
				}
				if (ImGui::Button("Play"))
				{
					m_SoundSource.Play();
				}
				ImGui::SameLine();
				if (ImGui::Button("Stop"))
				{
					m_SoundSource.Stop();
				}
			}
			ImGui::PopID();

			ImGui::End();
		}

	private:
		AudioSource m_MusicSource1;
		AudioSource m_MusicSource2;
		AudioSource m_SoundSource;
	};
}