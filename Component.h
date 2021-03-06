#pragma once

#include <string>

class GameObject;
class Configuration;

enum ComponentType
{
	Component_Transform,
	Component_Mesh,
	Component_Material,
	Component_Camera,
	Component_Particles
};
enum TimeState
{
	C_PLAYING, 
	C_STOP,
	C_PAUSED
};

enum Event_Engine;

class Component
{
public:
	Component(ComponentType type, bool startActive = true);
	virtual ~Component();

	virtual void Enable();
	virtual void Update(float dt);
	virtual void Disable();
	virtual void OnEditor();

	//time manager ---
	virtual void OnPause();
	virtual void OnPlay();
	virtual void OnStop();
	//---
	virtual void OnEvent(Event_Engine);

	virtual void OnSave(Configuration& data)const;
	virtual void OnLoad(Configuration& data);

	bool IsActive()const;
	void SetName(const char* name);
	const char* GetName()const;
	void SetGameObject(GameObject* GO);
	GameObject* GetGameObject()const;
	virtual void AddResource(int UID);
	ComponentType GetType() const;

	bool wantsToDie = false;

protected:
	GameObject* myGO = nullptr;
	std::string name;
	bool active = true;
	ComponentType type;

	TimeState state= C_PAUSED;
};
