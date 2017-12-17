#pragma once
#include "Component.h"
#include "MathGeo/Math/float3.h"

#include <string>
#include <vector>

class Configuration;
enum Event_Engine;

class GameObject
{
public:
	GameObject(GameObject* parent = nullptr, bool isStatic = true);
	~GameObject();

	void Update(float dt);
	void PostUpdate();
	void AddChild(GameObject* child);
	void DeleteChilds();
	void AddComponent(Component* component);
	void SetName(const char* name);

	//Time controls!
	void Play();
	void Pause();
	void Stop();
	//-----


	const char* GetName() const;
	int GetUID()const;

	void UpdateChildsTransform();
	void OnEditor();
	void ShowProperties();
	void RecursiveDraw();

	void OnEvent(Event_Engine);

	//Used from root when there's no quadtree acceleration
	void CollectAllIntersectionsAABB(std::vector<GameObject*>& intersections, LineSegment& line);
	bool Intersects(LineSegment& line)const;
	void CollectTriIntersections(LineSegment& line, float& distance, float3& hitPoint);

	void OnSerialize(Configuration& dataToSave)const;
	void OnDeserialize(Configuration& dataToLoad);
	void InsertSelfAndChilds();

	void OnStaticChange();

	Component* FindComponent(ComponentType type) const;
	GameObject* GetParent() const;
	GameObject* FindByUID(int toFind);

	std::vector<GameObject*> GetChilds() const;
	std::vector<Component*> GetComponents() const;

	bool selected = false;
	bool isStatic;

protected:
	int uid;

	GameObject* parent;

	bool addingMesh = false;
	bool addingMaterial = false;
	bool addingParticlesystem = false;
	bool wantsToDie = false;

	std::string name;
	std::vector<Component*> components;
	std::vector<GameObject*> childs;
};