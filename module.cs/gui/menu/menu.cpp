#include "Menu.h"

#include "../../structs/hooks/hooks.h"
#include "variables.h"

static const char* items[]("Flash", "Recoil" ,"Scope");
static const char* itemsFlags[]("Flashed", "Scoped","Money");
static int selectedItem = 0;
static std::string previwValue;
static std::string previewValueFlags;
static void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

namespace menu
{
	void theme()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4* colors = style.Colors;

		/// 0 = FLAT APPEARENCE
		/// 1 = MORE "3D" LOOK
		int is3D = 1;

		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
		colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.77f);
		colors[ImGuiCol_Separator] = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

		style.PopupRounding = 3;

		style.WindowPadding = ImVec2(4, 4);
		style.FramePadding = ImVec2(6, 4);
		style.ItemSpacing = ImVec2(6, 2);
		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style.ScrollbarSize = 18;

		style.WindowBorderSize = 1;
		style.ChildBorderSize = 1;
		style.PopupBorderSize = 1;
		style.FrameBorderSize = is3D;

		style.WindowRounding = 3;
		style.ChildRounding = 3;
		style.FrameRounding = 3;
		style.ScrollbarRounding = 2;
		style.GrabRounding = 3;

#ifdef IMGUI_HAS_DOCK 
		style.TabBorderSize = is3D;
		style.TabRounding = 3;

		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
		colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
#endif
	}

	bool initialize() noexcept
	{
		auto& io{ ImGui::GetIO() };
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
		theme();
		return true;
	}

	void render() noexcept
	{
		ImGuiWindowFlags Flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
		auto& style = ImGui::GetStyle();
		const auto& io = ImGui::GetIO();
		static int tabs = 1;
		if (!is_open)
		{
			return;
		}
		ImGui::Begin("module.cs [DEBUG]", nullptr, Flags);
		if (ImGui::Button("aim", ImVec2(100, 20))) { tabs = 1; }
		ImGui::SameLine(0, 4);
		if (ImGui::Button("esp", ImVec2(100, 20))) { tabs = 2; }
		ImGui::SameLine(0, 4);
		if (ImGui::Button("misc", ImVec2(100, 20))) { tabs = 3; }
		ImGui::SameLine(0, 4);
		if (ImGui::Button("config", ImVec2(100, 20))) { tabs = 4; }
		switch (tabs)
		{
		case 1:
			break;
		case 2:
			ImGui::Text("basic");
			ImGui::Checkbox("enable player esp", &vars::esp::playerEsp);
			ImGui::Checkbox("player name", &vars::esp::name);
			ImGui::Checkbox("player healthbar", &vars::esp::healthbar);
			if (vars::esp::healthbar) {
				ImGui::Checkbox("show text", &vars::esp::showtext);
			}
			ImGui::Checkbox("Flags", &vars::esp::flags);
			if (vars::esp::flags) {
				if (ImGui::BeginCombo("Player Conds", previewValueFlags.c_str()))
				{
					previewValueFlags = "";
					std::vector<std::string> vec;
					for (size_t i = 0; i < IM_ARRAYSIZE(itemsFlags); i++)
					{
						ImGui::Selectable(itemsFlags[i], &vars::esp::flagsSelect[i], ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
						if (vars::esp::flagsSelect[i])
							vec.push_back(itemsFlags[i]);

					}
					for (size_t i = 0; i < vec.size(); i++)
					{
						if (vec.size() == 1)
							previewValueFlags += vec.at(i);
						else if (!(i == vec.size()))
							previewValueFlags += vec.at(i) + ",";
						else
							previewValueFlags += vec.at(i);
					}


					ImGui::EndCombo();
				}
			}


			ImGui::Checkbox("player box", &vars::esp::box);
			ImGui::Separator();
			ImGui::Text("glow");
			ImGui::Checkbox("apply player glow", &vars::esp::glow);
			ImGui::Separator();
			ImGui::Text("colors");
			ImGui::ColorEdit3("entity glow color", vars::esp::glowRGB);
			break;
		case 3:
			ImGui::Text("movement");
			ImGui::Checkbox("auto bhop", &vars::misc::bhop);
			ImGui::Separator();
			ImGui::Text("misc");
			ImGui::Checkbox("force radar", &vars::misc::radarhack);
			ImGui::Checkbox("watermark", &vars::misc::watermark);
			ImGui::Separator();
			ImGui::Text("removals");
			if (ImGui::BeginCombo("Items",previwValue.c_str()))
			{
				previwValue = "";
				std::vector<std::string> vec;
				for (size_t i = 0; i < IM_ARRAYSIZE(items); i++)
				{
					ImGui::Selectable(items[i], &vars::misc::removalsSelect[i], ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
					if (vars::misc::removalsSelect[i])
						vec.push_back(items[i]);
				
				}
				for (size_t i = 0; i < vec.size(); i++)
				{
					if (vec.size() == 1)
						previwValue += vec.at(i);
					else if (!(i == vec.size()))
						previwValue += vec.at(i) + ",";
					else
						previwValue += vec.at(i);
				}


				ImGui::EndCombo();
			}
			ImGui::Separator();
			ImGui::TextColored(ImVec4(0, 255, 0, 255), __TIMESTAMP__);
			break;
		case 4:
			break;
		}

		ImGui::End();
	}
}