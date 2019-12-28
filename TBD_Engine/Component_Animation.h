#ifndef __COMPONENT_ANIM_H__
#define __COMPONENT_ANIM_H__

#include "Component.h"
#include <vector>
#include <map>
#include "ResourceAnimation.h"

class ComponentMesh;
class ComponentBone;

struct Animation
{
	Animation(std::string name, uint start, uint end, bool loop, bool Default) : name(name), start(start), end(end), loop(loop), Default(Default) {};

	std::string name;
	uint start;
	uint end;
	bool loop = false;
	bool Default = false;
};

class ComponentAnimation : public Component
{
	struct Link //Stores a bone(gameobject) with his corresponding channel of the animation
	{
		Link(GameObject* gameObject, Channel* channel) : gameObject(gameObject), channel(channel) {};
		GameObject* gameObject;
		Channel* channel;
	};

public:
	ComponentAnimation(GameObject* gameObject);
	~ComponentAnimation();

	void Update(float dt);
	float GetDuration() { return res_anim->duration / res_anim->ticksPerSecond; }

	Animation* GetDefaultAnimation();

public:

	std::vector<Animation*> animations;

	Animation* prev_anim = nullptr;
	Animation* playing_animation = nullptr;;

	ResourceAnimation* res_anim = nullptr;

private:

	Animation* CreateAnimation(std::string name, uint start, uint end, bool loop, bool Default = false);
	void DoLink();
	void DoBoneLink();
	void UpdateJointsTransform();

	void UpdateMesh(GameObject* go);
	void GetAllBones(GameObject* go, std::map<uint, ComponentMesh*>& meshes, std::vector<ComponentBone*>& bones);

	bool HasSkeleton(std::vector<GameObject*> GO);

private:
	std::vector<Link> links;
	bool linked_channels = false;
	bool linked_bones = false;
	bool created_buffer = false;
	bool has_skeleton = false;

	float time = 0;
};

#endif // __COMPONENT_ANIM_H__