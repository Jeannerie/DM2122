#ifndef A01_H
#define A01_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Camera2.h"
class Assignment : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_LIGHTBALL,
		GEO_IBERG,
		GEO_IBERG2,
		GEO_SPHERE,
		GEO_SBALL,
		GEO_SPHERE2,
		GEO_TOOTH,
		GEO_WSPOTS,
		GEO_TAIL,
		GEO_HSPHERE,
		GEO_HSPHERE2,
		GEO_SNOSE,
		GEO_SHAND,
		GEO_EYESL,
		GEO_LPUPILS,
		GEO_CATCH,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_TOTAL,
	};
public:
	Assignment();
	~Assignment();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float translateX;
	float translateDirX;

	float translateY;
	float translateY2;
	float translateDirY;
	float translateDirY2;

	float translateZ;
	float translateDirZ;

	float rotateAngle;
	float rotateDir;

	float rotateAngle2;
	float rotateDir2;

	float rotateAngle3;
	float rotateDir3;

	float scaleAll;
	float scaleDir;
	
	float scaleAll2;
	float scaleDir2;

	float scaleAll3;
	float scaleDir3;

private:
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	
	
	Camera2 camera;
	MS modelStack, viewStack, projectionStack;
	Light light[1];
	void RenderMesh(Mesh* mesh, bool enableLight);
};

#endif