#ifndef __ModuleSceneEditor_H__
#define __ModuleSceneEditor_H__

#include "Module.h"
#include "Primitive.h"
#include "MathGeo\Geometry\AABB.h"
#include <list>

class GameObject;
class Mesh;

class ModuleSceneEditor : public Module
{
public:
	ModuleSceneEditor(Application* app, bool startEnabled = true);
	~ModuleSceneEditor();

	bool Init(JSON_Object* data = nullptr);
	bool Start();
	bool CleanUp(JSON_Object* data = nullptr);

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	void Draw();
	void SetToWireframe(bool wframe);
	bool GetWireframe()const;

	//Add Primitive
	void AddCube(vec3 size, vec3 pos = vec3(0,0,0));
	void AddCube1(vec3 size, vec3 pos = vec3(0, 0, 0));
	void AddCube2(vec3 size, vec3 pos = vec3(0, 0, 0));
	void AddCylinder(float radius, float height, vec3 pos = vec3(0, 0, 0));
	void AddSphere(float radius, vec3 pos = vec3(0, 0, 0));
	void AddPlane(float x, float y, float z, float d, vec3 pos = vec3(0, 0, 0));
	void AddPlaneNoGrid(float x, float y, float z, float d, vec3 pos = vec3(0, 0, 0));
	void AddCapsule(float radius, float height, vec3 pos = vec3(0, 0, 0));

	GameObject* CreateNewGameObject(const char* path);

private:
	//For now ----
	std::list<Primitive*> sceneObjects;
	std::list<Mesh*> sceneMeshes;

	GameObject* root;

	bool wframe;
};

#endif