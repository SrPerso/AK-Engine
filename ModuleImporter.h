#ifndef __ModuleImporter_H__
#define __ModuleImporter_H__

#include "Globals.h"
#include "Module.h"

class aiMesh;
class aiMaterial;
class aiNode;

class GameObject;

class ComponentMesh;
class ComponentMaterial;
class ComponentTransform;

class ModuleImporter : public Module
{
public:
	ModuleImporter(Application* app, bool start_enabled = true);
	~ModuleImporter();

	bool Init(JSON_Object* data = nullptr);

	bool CleanUp(JSON_Object* data = nullptr);

	GameObject* LoadGameObject(const char* fullPath);

	ComponentMesh* LoadMesh(aiMesh* newMesh);
	ComponentMaterial* LoadMaterial(aiMaterial* newMaterial);
	ComponentTransform* LoadTransform(aiNode* node);
};

#endif //__ModuleImporter_H__