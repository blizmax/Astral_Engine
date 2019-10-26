#include "Application.h"
#include "W_Hierarchy.h"

W_Hierarchy::W_Hierarchy() : Window()
{
	App->LogInConsole("Created Hierarchy Window");
}

W_Hierarchy::~W_Hierarchy()
{
}

bool W_Hierarchy::Start()
{
	return true;
}

bool W_Hierarchy::Draw()
{
	static int selection_mask = 0x02;

	TreeNode_Clicked = -1;

	if (App->gui->hierarchy)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

		ImGui::Begin("Hierarchy");
		//Draw Hierarchy stuff
		for (std::vector<GameObject*>::iterator iterator = App->scene_intro->GO_list.begin(); iterator != App->scene_intro->GO_list.end(); iterator++)
		{

			ImGuiTreeNodeFlags flag = ((selection_mask & (1 << (*iterator)->id)) ? ImGuiTreeNodeFlags_Selected : 0);
		
			flag |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
	
			if((*iterator)->active == true)
				ImGui::TreeNodeEx((void*)(intptr_t)(*iterator)->id, flag, (*iterator)->name.c_str());
			else
				ImGui::TreeNodeEx((void*)(intptr_t)(*iterator)->id, flag, (*iterator)->unactive_name.c_str());


			if (ImGui::IsItemClicked())
			{
				TreeNode_Clicked = (*iterator)->id;
				App->gui->ins_window->selected_GO = (*iterator);
			}
			
		}

		if (TreeNode_Clicked != -1) // show selected node
		{
			selection_mask = (1 << TreeNode_Clicked);
		}
		else if (TreeNode_Clicked == -1 && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow)) 
		{
			App->gui->ins_window->selected_GO = nullptr; 
			selection_mask = (1 << -1);
		}

		ImGui::End();
		ImGui::PopStyleVar();

	}
	
	return true;
}


