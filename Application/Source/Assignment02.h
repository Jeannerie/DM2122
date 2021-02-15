#ifndef SCENE_ASSIGNMENTTWO_H
#define SCENE_ASSIGNMENTTWO_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Camera3.h"
class AssignmentTwo : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_GRASS,
		GEO_CIRCLE,
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
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_MODELDMAN,
		GEO_MODELDBOARD,
		GEO_MODELDART,
		GEO_MODELCHAIR,
		GEO_MODELWINE,
		GEO_MODELSHOE,
		GEO_TENT,
		GEO_LIGHTBALL,
		GEO_TEXT,
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
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TOTAL,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
	};
public:
	AssignmentTwo();
	~AssignmentTwo();

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

	bool sphealAppear;
	bool tentEntered;

private:
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	
	float FPS;


	Camera3 camera;
	MS modelStack, viewStack, projectionStack;
	Light light[2];

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	void RenderMesh(Mesh* mesh, bool enableLight);

	void RenderSkybox();

};

#endif