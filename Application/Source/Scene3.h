#ifndef SCENE_3_H
#define SCENE_3_H

#include "Scene.h"

class Scene3 : public Scene
{
public:
	Scene3();
	~Scene3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float rotateAngle;
	float rotateAngle2;
	float rotateAngle3;
	float translateX;
	float translateX2;
	float scaleAll;
	float scaleAll2;
	float scaleAll3;
	float rotateDir;
	float rotateDir2;
	float rotateDir3;
	float translateDir;
	float translateDir2;
	float scaleDir;
	float scaleDir2;
	float scaleDir3;


	enum UNIFORM_TYPE
	{
		U_MVP = 0 ,
		U_TOTAL,
	};

	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2,
		GEO_TRIANGLE_3,
		GEO_TRIANGLE_4,
		GEO_TRIANGLE_5,
		GEO_TRIANGLE_6,
		NUM_GEOMETRY,

	};

private:
	unsigned m_parameters[U_TOTAL];
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
};

#endif