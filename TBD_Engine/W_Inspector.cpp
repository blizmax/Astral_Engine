#include "Application.h"
#include "W_Inspector.h"
#include "Component_Transform.h"

W_Inspector::W_Inspector() : Window()
{
	App->LogInConsole("Created Inspector Window");
}

W_Inspector::~W_Inspector()
{
}


bool W_Inspector::Start()
{
	//selected_GO = selected_GO.
	return true;
}

bool W_Inspector::Draw()
{
	if (App->gui->inspector)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(7, 3));

		ImGui::Begin("Inspector");
		//Draw Inspector stuff
		if (selected_GO != nullptr && selected_GO->id != 0)
		{
			ImGui::InputText("Name", (char*)selected_GO->name.c_str(), 20, ImGuiInputTextFlags_EnterReturnsTrue);
			ImGui::Text("");
			active_bool = selected_GO->active;
			ImGui::Checkbox("Active", &active_bool);

			if (active_bool)
			{
				selected_GO->Enable();
			}
			else
			{
				selected_GO->Disable();
			}

			if (selected_GO->active)
			{
				if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_Leaf) && selected_GO->GetComponentTransform() != nullptr)
				{
					ComponentTransform* transform = selected_GO->GetComponentTransform();

					float3 position = transform->GetPosition();
					ImGui::Text("Position:");
					/*ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::Text("X1 %.3f   ", selected_GO->GetComponentTransform()->GetPosition().x);
					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::Text("Y1 %.3f   ", selected_GO->GetComponentTransform()->GetPosition().y);
					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::Text("Z1 %.3f   ", selected_GO->GetComponentTransform()->GetPosition().z);*/

					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::DragFloat("##X1", &position.x, 0.05f, -INFINITY, INFINITY);
					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::DragFloat("##Y1", &position.y, 0.05f, -INFINITY, INFINITY);
					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::DragFloat("##Z1", &position.z, 0.05f, -INFINITY, INFINITY);
					if (!transform->GetPosition().Equals(position))
						transform->SetPosition(position);

					ImGui::Text("");

					float3 rotation = transform->GetEulerRotation();
					ImGui::Text("Rotation:");
					/*ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::Text("X2 %.3f   ", selected_GO->GetComponentTransform()->GetQuaternionRotation().x);
					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::Text("Y2 %.3f   ", selected_GO->GetComponentTransform()->GetQuaternionRotation().y);
					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::Text("Z2 %.3f   ", selected_GO->GetComponentTransform()->GetQuaternionRotation().z);*/
																				   
					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::DragFloat("##X2", &rotation.x, 0.05f, -INFINITY, INFINITY);
					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::DragFloat("##Y2", &rotation.y, 0.05f, -INFINITY, INFINITY);
					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::DragFloat("##Z2", &rotation.z, 0.05f, -INFINITY, INFINITY);
					if (!transform->GetEulerRotation().Equals(rotation))
						transform->SetEulerRotation(rotation);
					ImGui::Text("");

					float3 sc = transform->GetScale();
					ImGui::Text("Scale:   ");
					/*ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::Text("X3 %.3f   ", selected_GO->GetComponentTransform()->GetScale().x);
					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::Text("Y3 %.3f   ", selected_GO->GetComponentTransform()->GetScale().y);
					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::Text("Z3 %.3f   ", selected_GO->GetComponentTransform()->GetScale().z);*/

					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::DragFloat("##X3", &sc.x, 0.05f, -INFINITY, INFINITY);
					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::DragFloat("##Y3", &sc.y, 0.05f, -INFINITY, INFINITY);
					ImGui::SameLine(); ImGui::PushItemWidth(50); ImGui::DragFloat("##Z3", &sc.z, 0.05f, -INFINITY, INFINITY);
					if (!transform->GetScale().Equals(sc))
						transform->SetScale(sc);
					
				}

				if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_Leaf) && selected_GO->GetComponentMesh() != nullptr)
				{
					ImGui::Text("Vertex:");
					ImGui::SameLine(); ImGui::Text("%d", selected_GO->GetComponentMesh()->num_vertex);
					ImGui::Text("Faces:");
					ImGui::SameLine(); ImGui::Text("%d", (selected_GO->GetComponentMesh()->num_vertex / 3));
					ImGui::Checkbox("Show normals", &selected_GO->GetComponentMesh()->draw_normals);
				}

				if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_Leaf) && selected_GO->GetComponentTexture() != nullptr)
				{
					ImGui::Checkbox("Checkers Texture", &selected_GO->GetComponentTexture()->Checers_texture);

					if (selected_GO->GetComponentTexture()->Checers_texture == false)
					{
						if (selected_GO->GetComponentTexture()->texture.id != 0)
						{
							ImGui::Text("");
							ImGui::Text("Texture path: %s", selected_GO->GetComponentTexture()->texture.path.c_str());
							ImGui::Text("");
							ImGui::Text("Texture Width: %u", selected_GO->GetComponentTexture()->texture.width);
							ImGui::Text("");
							ImGui::Text("Texture Height: %u", selected_GO->GetComponentTexture()->texture.height);
							ImGui::Text("");
							ImGui::Text("Texture preview:");
							ImGui::Image((ImTextureID*)selected_GO->GetComponentTexture()->texture.id, ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
						}
						else
						{
							ImGui::Text("");
							ImGui::Text("No texture applied");
						}

					}
					else if (selected_GO->GetComponentTexture()->Checers_texture == true)
					{
						ImGui::Text("");
						ImGui::Text("Texture path: %s", App->tex_loader->CheckersTexture.path.c_str());
						ImGui::Text("");
						ImGui::Text("Texture Width: %u", App->tex_loader->CheckersTexture.width);
						ImGui::Text("");
						ImGui::Text("Texture Height: %u", App->tex_loader->CheckersTexture.height);
						ImGui::Text("");
						ImGui::Text("Texture preview:");
						ImGui::Image((ImTextureID*)App->tex_loader->CheckersTexture.id, ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
					}

				}
			}
		}
			
		
		

		ImGui::End();
		ImGui::PopStyleVar();

	}
	
	return true;
}


