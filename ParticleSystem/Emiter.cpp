#include "Emiter.h"
#include "../MathGeo/MathGeoLib.h"
#include "../imgui-1.51/imgui.h"
#include "GlobalDefines.h"

Emiter::Emiter()
{
	type = E_SEMISPHERE;
	DefaultEmiterData();
}

Emiter::~Emiter()
{

}

void Emiter::DefaultEmiterData()
/* -DefaultEmiterData- Used to put default sizes of the shapes ( you can change it from GlobalDefines) */
{
	switch (type)
	{
	case E_SPHERE:

		shape.sphere.r = PS_DEFAULT_SIZE_SPHERE*0.5f;
		break;

	case E_SEMISPHERE:
		shape.semiSphere.r = PS_DEFAULT_SIZE_SEMISPHERE*0.5f;
		break;

	case E_CIRCLE:
		shape.circle.r = PS_DEFAULT_SIZE_CIRCLE*0.5f;
		break;
	}

}

void Emiter::DrawEmiter()
{
	if (!active)
		return;

	switch (type)
	{
	case E_SPHERE:	
		shape.sphere.Transform(pSystem->transformation->rotation);
		shape.sphere.pos = pSystem->transformation->position;

		DrawSphere(shape.sphere);
		break;

	case E_SEMISPHERE:

		shape.semiSphere.Transform(pSystem->transformation->rotation);
		shape.semiSphere.pos = pSystem->transformation->position;

		DrawSemiSphere(shape.semiSphere);
		break;

	case E_CIRCLE:

		shape.circle.pos = pSystem->transformation->position;

		DrawCircle(shape.circle);
		break;

	}
	
}

void Emiter::DrawEmiterEditor()
{
	/* Enable Disable Draw*/

	ImGui::SliderFloat("Emiting time", (float*)&data.timeToEmite, -1, 100);


	if (data.timeToEmite < 0)// in the case that the Emiting time is null the emiter will emite all time
		data.loop = true;
	
	ImGui::Checkbox("Loop", &data.loop);

	ImGui::SliderFloat("Particle Emittion rate", &data.particleRate, 0.02, 4);

	if (data.particleRate < 0)
		data.particleRate = 0;

	ImGui::SliderFloat("Particle time life", &data.timePLife, -1,40);
	ImGui::DragFloat("variance of the Particle time life", &data.modTimePlife, 0.1f);

	ImGui::DragFloat("Start Speed", &data.speed, 2.f);
	ImGui::DragFloat("variance of the Start speed", &data.modSpeed, 0.1f);

	/* Select the shape*/
	if (ImGui::Combo("Shape", (int*)&type, "Sphere\0SemiSphere\0Circle")) DefaultEmiterData();

	switch (type)
	{
	case E_SPHERE:
		ImGui::SliderFloat("Radio", (float*)&shape.sphere.r, 0.25, 20);
		break;

	case E_SEMISPHERE:
		ImGui::SliderFloat("Radio", (float*)&shape.semiSphere.r, 0.25, 20);
		break;

	case E_CIRCLE:
		ImGui::SliderFloat("Radio", (float*)&shape.circle.r, 0.25, 20);
		break;
	}
}

void Emiter::DrawSphere(const Sphere & sphere)
{

	glLineWidth(2.0f);
	glColor3f(PS_DEBUG_COLOR_LINES);

	float totalRad = CIRCLEDEGREES / CIRCLEPERFECTION;
	totalRad *= DEGTORAD;

	//X
	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < CIRCLEPERFECTION; i++)
	{
		glVertex3f(cos(totalRad * i) *  sphere.r + sphere.pos.x, 0.0f + sphere.pos.y, sin(totalRad * i) *  sphere.r + sphere.pos.z);
	}		
	glEnd();

	//Y
	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < CIRCLEPERFECTION; i++)
	{
		glVertex3f(cos(totalRad * i) *  sphere.r + sphere.pos.x, sin(totalRad * i) *  sphere.r + sphere.pos.y, 0.0f + sphere.pos.z);
	}	
	glEnd();

	//Z
	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < CIRCLEPERFECTION; i++)
	{
		glVertex3f(0.0f + sphere.pos.x, sin(totalRad * i) *  sphere.r + sphere.pos.y, cos(totalRad * i) *  sphere.r + sphere.pos.z);
	}	
	glEnd();


	glLineWidth(1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);

}


void Emiter::DrawSemiSphere(const Sphere & sphere)
{

	glLineWidth(2.0f);
	glColor3f(PS_DEBUG_COLOR_LINES);

	
	float totalRad = CIRCLEDEGREES / CIRCLEPERFECTION;
	totalRad *= DEGTORAD;

	//X
	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < CIRCLEPERFECTION; i++)
	{
		glVertex3f(cos(totalRad * i) *  sphere.r + sphere.pos.x, 0.0f + sphere.pos.y, sin(totalRad * i) *  sphere.r + sphere.pos.z);
	}	
	glEnd();

	//Y
	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i <= CIRCLEPERFECTION * 0.5f; i++)
	{
		glVertex3f(cos(totalRad * i) *  sphere.r + sphere.pos.x, sin(totalRad * i) *  sphere.r + sphere.pos.y, 0.0f + sphere.pos.z);
	}	
	glEnd();

	//Z
	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i <= CIRCLEPERFECTION * 0.5f; i++)
	{
		glVertex3f(0.0f + sphere.pos.x, sin(totalRad * i) *  sphere.r + sphere.pos.y, cos(totalRad * i) *  sphere.r + sphere.pos.z);
	}
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(1.0f);

}

void Emiter::DrawCircle(const Circle & circle)
{

	glLineWidth(2.0f);
	glColor3f(PS_DEBUG_COLOR_LINES);


	float totalRad = CIRCLEDEGREES / CIRCLEPERFECTION;
	totalRad *= DEGTORAD;

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < CIRCLEPERFECTION; i++)
	{
		glVertex3f(cos(totalRad * i) *  circle.r + circle.pos.x, 0.0f + circle.pos.y, sin(totalRad * i) *  circle.r+ circle.pos.z);
	}
	glEnd();

	glLineWidth(1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
}

EmiterData::EmiterData()
{
	
}
