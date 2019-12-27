#include "Component_Animation.h"
#include "Application.h"
#include "W_Game.h"
#include "GameObject.h"

float Animation::GetDuration()
{
	return ((float)end - (float)start) / ticksPerSecond;
}

ComponentAnimation::ComponentAnimation(GameObject* gameobj) : Component(Component::ComponentType::Animation, gameobj)
{

}

ComponentAnimation::~ComponentAnimation()
{

}

void ComponentAnimation::Update(float dt)
{
	if (linked_channels == false)
		DoLink();

	if (!App->gui->game_window->in_editor)
		UpdateJointsTransform(dt);
	else
		time = 0;

	UpdateMesh(my_GO);
}

void ComponentAnimation::DoLink()
{
	if (res_anim != nullptr)
	{
		std::vector<GameObject*> childs;
		my_GO->GetAllChilds(childs);

		for (int i = 0; i < res_anim->numChannels; i++)
		{
			for (int j = 0; j < childs.size(); j++)
			{
				// We link them if the GO is a bone and their names are equal
				if (childs[j]->GetComponentBone() != nullptr && childs[j]->name.compare(res_anim->channels[i].name) == 0) 
				{
					links.push_back(Link(childs[j], &res_anim->channels[i]));
					break;
				}
			}
		}

		linked_channels = true;
	}
	else
	{
		App->LogInConsole("ERROR: Can't link channels, Resource_Animation is nullptr");
	}
}

void ComponentAnimation::UpdateJointsTransform(float dt)
{
	for (int i = 0; i < links.size(); i++)
	{
		ComponentTransform* trans = links[i].gameObject->GetComponentTransform();
		float duration_sec = res_anim->duration / res_anim->ticksPerSecond;

		if (App->time->GetGameTime() > duration_sec)
		{
			time = App->time->GetGameTime() - duration_sec * loop_times;
		}
		else
		{
			time = App->time->GetGameTime();
		}
		uint Frame = time * res_anim->ticksPerSecond;

		if (Frame == res_anim->duration)
		{
			loop_times++;
		}
		
		float3 position = trans->GetPosition();
		if (links[i].channel->PosHasKey())
		{
			
			std::map<double, float3>::iterator pos = links[i].channel->PositionKeys.find(Frame);
			if (pos != links[i].channel->PositionKeys.end())
				position = pos->second;

		}
		trans->SetPosition(position);

		Quat rotation = trans->GetQuaternionRotation();
		if (links[i].channel->RotHasKey())
		{
			std::map<double, Quat>::iterator rot = links[i].channel->RotationKeys.find(Frame);
			if (rot != links[i].channel->RotationKeys.end())
				rotation = rot->second;

		}
		trans->SetQuatRotation(rotation);

		float3 scale = trans->GetScale();
		if (links[i].channel->ScaleHasKey())
		{
			std::map<double, float3>::iterator sca = links[i].channel->ScaleKeys.find(Frame);
			if (sca != links[i].channel->ScaleKeys.end())
				scale = sca->second;

		}
		trans->SetScale(scale);
		
		

	}
}

void ComponentAnimation::UpdateMesh(GameObject* go)
{
	ComponentMesh* tmp = go->GetComponentMesh();

	if (tmp != nullptr)
	{
		tmp->AttachSkeleton(go);
		tmp->UpdateMesh();
	}
	for (int i = 0; i < go->children.size(); i++)
	{
		UpdateMesh(go->children[i]);
	}
}
