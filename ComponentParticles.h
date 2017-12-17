#pragma once

#include "Component.h"

#include "MathGeo\MathGeoLib.h"
#include "ParticleSystem\ParticleSystem.h"
#include "ComponentCamera.h"
#include "ModuleCamera3D.h"


#define MAXTIMEEXPLODING 0.5f


enum PartType
{
	FIREWORK,
	EXPLOSION,
	NORMAL
};
class ComponentParticles : public Component
{
public:
	ComponentParticles();
	ComponentParticles(PartType type );
	~ComponentParticles();

	void PreUpdate(float dt);
	void Update(float dt) override;

	void OnPlay() override;
	void OnPause() override;
	void OnStop() override;

	void OnEditor()override;

	void OnSave(Configuration& data) const override;
	void OnLoad(Configuration& data) override;

private:
	ParticleSystem * particleSystem = nullptr;
	
	//this must work on API

private:
	PartType partType;
	float timer = 45.0f;
	float timeAlive = 0.f;
	//---------------------------------------------------------------
};