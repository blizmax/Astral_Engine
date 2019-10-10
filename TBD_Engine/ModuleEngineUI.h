#ifndef __MODULEENGINEUI_H__
#define __MODULEENGINEUI_H__

#include "Module.h"
#include "ImGui/imgui.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"

class ModuleEngineUI : public Module
{
public:

	ModuleEngineUI(Application* app, bool start_enabled = true);
	~ModuleEngineUI();

	bool Init();
	bool Start();
	bool Draw();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	void CreateMainMenuToolbar();
	
private:
	//bool show_demo_window = true;
	ImGuiIO* io = nullptr;
	bool p_open = true;
	bool demo_cpp = false;
	bool about_window = false;

	//Store the windows here and iterate them in Start, Draw, Pre/Post Update 
	std::list<Module*> windows;

};

#endif
