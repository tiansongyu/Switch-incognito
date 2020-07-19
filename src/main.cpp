// Copyright (C) 2020 averne
//
// This file is part of Turnips.
//
// Turnips is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Turnips is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Turnips.  If not, see <http://www.gnu.org/licenses/>.

#include <cstdio>
#include <cstdint>
#include <utility>
#include <switch.h>
#include <math.h>
#include <imgui.h>
#include <filesystem>
#include <string>
#include <fstream>

#include "json.hpp"
#include "incognito.h"
#include "gui.hpp"

#include "Lang.hpp"

#include "theme.hpp"
#include "delete_function.hpp"

extern "C" void userAppInit()
{
        setsysInitialize();
        plInitialize(PlServiceType_User);
        romfsInit();
#ifdef DEBUG
        socketInitializeDefault();
        nxlinkStdio();
#endif
}

extern "C" void userAppExit()
{
        setsysExit();
        plExit();
        romfsExit();
#ifdef DEBUG
        socketExit();
#endif
}
using json = nlohmann::json;
int main(int argc, char **argv)
{
        json j = nullptr;
        std::string path = "romfs:/theme.json";

        if (!std::filesystem::exists(path))
                return false;
        std::ifstream in(path);
        j = json::parse(in);
        auto color_theme = j["current_theme"];
        //gui绘制
        printf("Starting gui\n");
        if (!gui::init())
                printf("Failed to init\n");
        ///这里可以选择黑暗和光亮的主题
        //auto color_theme = ColorSetId_Dark;

        if (color_theme == ColorSetId_Light)
                th::apply_theme(th::Theme::Light);
        else
                th::apply_theme(th::Theme::Dark);
        Lang::setLanguage(Language::Chinese);
        ///////////////////////
        int e = 0;
        while (gui::loop())
        {

                auto &[width, height] = im::GetIO().DisplaySize;
                im::SetNextWindowFocus();
                im::Begin(Lang::stringtochar("main_title"_lang), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
                im::SetWindowPos({0.23f * width, 0.16f * height});
                im::SetWindowSize({0.55f * width, 0.73f * height});

                ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
                if (ImGui::BeginTabBar(Lang::stringtochar("bar_1"_lang), tab_bar_flags))
                {
                        if (ImGui::BeginTabItem(Lang::stringtochar("bar_1"_lang)))
                        {
                                delete_tian::display_delete();
                                ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem(Lang::stringtochar("bar_2"_lang)))
                        {
                               ImGui::RadioButton("中文", &e, Language::Chinese);
                                ImGui::RadioButton("English", &e, Language::English);
                               switch(e)
                                {
                                        case Language::Chinese:
                                                Lang::setLanguage(Chinese);
                                                break;
                                        case Language::English:
                                                Lang::setLanguage(English);
                                                break;
                                        default:
                                                break;
                                }
                                ImGui::EndTabItem();
                        }

                        ImGui::EndTabBar();
                }

                im::End();
                gui::render();
        }

        gui::exit();

        return 0;
}