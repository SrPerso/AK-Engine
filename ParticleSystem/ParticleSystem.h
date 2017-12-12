#ifndef _PS_PARTICLE_SYSTEM_
#define _PS_PARTICLE_SYSTEM_

#include <vector>
#include "../MathGeo/MathGeoLib.h"
#include "GlobalDefines.h"

struct SystemState //going to global state to set on particles latter
{
	float3 force = float3(0.0f, -9.81f, 0.0f);

};

struct TextureData // it is like resource texture, contains all the data of the texture.
{
	 void Set(unsigned int ID, unsigned int width, unsigned int heigth);

	 int textureID = 0;
	 int textureW = 0;
	 int textureH = 0;

};

struct PTransformation
{
	float3 Position;
	Quat Rotation;
	float3 Scale;
};

class Particle;
class Emiter;

class ParticleSystem
{
	friend class Particle;
public:
	ParticleSystem();
	~ParticleSystem();
	

private:
	std::vector<Particle*> particleVec;
	Emiter* emiter;

public:

	float3 cameraPos = float3::zero;
	TextureData tData;
};




#endif // !_PS_PARTICLE_SYSTEM_
