#ifndef _PS_EMITER_
#define _PS_EMITER_

#include "GlobalDefines.h"
#include "ParticleSystem.h"

#include "../Glew/include/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

//-------------------------------[ENUMS, SHAPES, UNIONS]

enum Etype //type of the emiter
{
	E_SPHERE,
	E_SEMISPHERE,
	E_CIRCLE
};

union Shape
{
	Shape(){}

	Sphere sphere;
	Sphere semiSphere;
	Circle circle;
}; 

//-------------------------------[DATA]

struct EmiterData

	//contains all data of the Emiter
{
	EmiterData(); //init transform
public:
	//emitor --------
	float timeToEmite = 20.f; // if the timeToEmite == 0.0f then never ends to emite == bool loop = true
	bool loop = true;

	float particleRate = 1.f; // quantity of particles droped in a sec

						  //Particles --------
	float timePLife = 2.f;
	float modTimePlife = 0.f; // intervale of time life of the particle

	float speed = 0.f; // speed to drop the particles
	float modSpeed = 0.f; // intervale of speed to drop particles
public:
	float emiterTime = 0.f; // time to emite in emiter
};


//-------------------------------[EMITER]
class Emiter 	//shapes // sphere, cube, cone, semiphere
{
	friend class ParticleSystem;
public:

	Emiter();
	~Emiter();	

	/* -DefaultEmiterData- Used to put default sizes of the shapes ( you can change it from GlobalDefines) */
	void DefaultEmiterData();

	//---[Draws]

	/*-DrawEmiter- Draws the emiter on the scene*/
	void DrawEmiter();

	/*-DrawEmiterEditor- Draws the emiter on the editor*/
	void DrawEmiterEditor();

	/* Draw shapes functiones.... E_SPHERE,E_BOX,	E_SEMISPHERE, E_CONE, E_SQUARE,	E_CIRCLE */

	void DrawSphere(const Sphere&sphere);
	void DrawSemiSphere(const Sphere&sphere);
	void DrawCircle(const Circle& circle);

	EmiterData data;
private:
	bool active = true; //can be draw the shape or not
	
	ParticleSystem* pSystem;
	Etype type = E_SPHERE;
	Shape shape; 
	
};


#endif // !_PS_EMITER
