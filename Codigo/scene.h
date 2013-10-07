/*  
 *  CLASS SCENE
 */  


#ifndef SCENE_H
#define SCENE_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>

// Objetos
#include "object_eje_coordenado.h"
#include "object_grid.h"
#include "object_superficie.h"
#include "object_cangrejo.h"
#include "object_pez.h"
#include "object_roca.h"
#include "object_planta_acuatica.h"
#include "object_TEST.h"





/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class Scene
{
private:

	glm::mat4 view_matrix;				// Camera view position
	glm::vec3 cameraTarget;

	// View parameters
	glm::vec3 position;
	glm::vec3 right;
	int xpos, ypos;						// Mouse position
	float horizontalAngle;				// Horizontal angle
	float verticalAngle;				// Vertical angle
	float initialFoV;					// Initial Field of View
	float speed;						// Speed of movement
	float mouseSpeed;					// Mouse speed


	// Camera
	GLfloat cameraPositionX;
	GLfloat cameraPositionY;
	GLfloat cameraPositionZ;
	GLfloat cameraTargetX;
	GLfloat cameraTargetY;
	GLfloat cameraTargetZ;

	// Objetos
	// (Definir atributos relacionados con objetos AQUI)

	EjeCoordenado ejeCoordenado;
	Grid grid;
	Superficie superficie;
	Cangrejo cangrejo;
	Pez pez;
	Roca roca;
	PlantaAcuatica plantaAcuatica;

	// TEMPORAL
	GLfloat grado;
	Test test;
	// FIN TEMPORAL

public:

	// Constructor
	Scene();

	// Destructor
	~Scene();

	// Inicializa la escena.
	void initialize(); 

	// Renderiza la escena.
	// POST: previo a realizar el primer renderizado debe invocarse al método
	// initialize().
	void render(GLuint height, GLuint width);

	// Redimensiona la escena.
	void resize(int width, int height);

	// Establece la posicion de la camara de la escena.
	void setCameraPosition();

	// Devuelve la posicion de la camara de la escena.
	void getCameraPosition();

	// Manejador del evento de tecla presionada.
	void onKeyDown(int nKey, char cAscii);

	// Manejador del evento de movimiento de la rueda del mouse.
	void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y);

	// Manejador del evento de movimiento del mouse.
	void OnMouseMove(int x, int y);
};

#endif
