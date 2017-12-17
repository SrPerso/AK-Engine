#ifndef _PS_PARTICLE_SYSTEM_
#define _PS_PARTICLE_SYSTEM_

#include "../Application.h"
#include <vector>
#include "../MathGeo/MathGeoLib.h"
#include "GlobalDefines.h"
#include "../ModuleTextures.h"






// -------------------------------------- [STATE]
struct SystemState //going to global state to set on particles latter
{	
	float size1 = 1.f;
	float size2 = 1.f;
	float gravity = 1;
	float gravityVariation = 0.0f;
	float rotation = 0.f;
	float rotation2 = 0.f;
	float speed = 0.5f;
	float4 color = float4::one; 
	float4 color2 = float4::one;
};
// -------------------------------------- [TEXTURE]
struct TextureData // it is like resource texture, contains all the data of the texture.
{	
	uint textureID = App->textures->ImportImage("../Game/Assets/Baker_house.png");
	float4 color = float4::one;
};

struct PTransformation
{
	float3 position;
	Quat rotation;
	float3 scale;
};

// -------------------------------------- [PARTICLE SYSTEM]
class Particle;
class Emiter;
struct ParticleMesh;


class ParticleSystem
{
	friend class Particle;	

public:
	ParticleSystem();
	~ParticleSystem();
	
	bool PreUpdate(float dt);
	bool Update(float dt);
	bool PostUpdate(float dt);

	// Events in time 
	void Stop(); // used to kill the particle system process
	void Play();// used to play the particle system
	void Pause();// Stops the particles


	//	Save & load------------------------
	/* used to calls to load and save the particle system*/

	void Load(std::vector<float> vectEmiter, std::vector<float>initPart, std::vector<float>finalPart);
	void Save(std::vector<float>& vectEmiter, std::vector<float> & initPart, std::vector<float> &finalPart);
	std::vector<float> SaveEmiter();
	std::vector<float> SaveEndState();
	std::vector<float> SaveInitialState();
	//UI -------------------------------
	
	//Draws --- /*Draws the editor and the particles*/
	void DrawParticleSystemEditor(); // basic 
	void Draw();	
	void DrawBasicEditor();
	
	//Show/unshow Window ---
	void openCloseWindowPS(bool state);
	bool isOpenCloseWindowPS();
	void changeOpenCloseWindowPS();
	
	void SetTransform(float3 Position, Quat rotation, float3 scale);

	ParticleMesh * GetMesh() const;

	void SetPlaneMesh();
	void SetActive();
	void SetDesactive();
	void CreateParticle();


private:
	ParticleMesh* particleMesh;
	std::vector<Particle*> particleVec;
	Emiter* emiter;
	SystemState initialState;
	SystemState finalState;
	bool windowShow = true;

private: //times   // time variables with _
	float time_ToCreateNParticle = 0.f;
	ParticleSystem_State ps_state= PS_STOP;

	float ps_dt = 0.f; //particlesystem dt
	float control = 0.f;
	bool active = true;

public:	
	int size = 0;
	PTransformation* transformation; 
	TextureData tData;
	float3 cameraPos = float3::zero;
	
};

#endif // !_PS_PARTICLE_SYSTEM_
