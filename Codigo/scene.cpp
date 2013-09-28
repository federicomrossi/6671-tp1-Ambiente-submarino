/*  
 *  CLASS SCENE
 */


#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform2.hpp> 
#include <glm/gtx/projection.hpp>

#include "scene.h"





/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
Scene::Scene()
{
	// The position of your camera, in world space
	glm::vec3 cameraPosition = glm::vec3(8.0, 0.0, 3.0);
	// Where you want to look at, in world space
	glm::vec3 cameraTarget = glm::vec3 (0.0, 0.0, 0.0);
	// Probably glm::vec3(0,1,0), but (0,,0) would make you looking 
	// upside-down, which can be great too
	glm::vec3 upVector = glm::vec3 (0.0, 0.0, 1.0);

	// View (camera) Matrix
	this->view_matrix = glm::lookAt(
		cameraPosition,
		cameraTarget,
		upVector
	);
}


// Destructor
Scene::~Scene() { }


// Inicializa la escena.
void Scene::initialize()
{
	this->grado = 0.0f;
	this->ejeCoordenado.create(2);
	// this->grid.create(10);
	// this->cangrejo.create();

	// Establecemos un color inicial para la escena
	glClearColor(0.3f, 0.3f, 0.4f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}


// Renderiza la escena.
// POST: previo a realizar el primer renderizado debe invocarse al método
// initialize().
void Scene::render(GLuint height, GLuint width)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Matriz de projeccion
	glm::mat4 projection_matrix = glm::mat4 (1.0f);
	
	// PERSPECTIVA INFINITA
	projection_matrix = glm::infinitePerspective(
		30.0f,
		(float)width / (float)height,
		0.1f
	);

	// // PERSPECTIVA
	// projection_matrix = glm::perspective(
		
	// 	// The horizontal Field of View, in degrees : the amount of "zoom". 
	// 	// Think "camera lens". Usually between 90° (extra wide) and 30° 
	// 	// (quite zoomed in)
	// 	30.0f,
	
	// 	// Aspect Ratio. Depends on the size of your window. Notice that 
	// 	// 4/3 == 800/600 == 1280/960.
	// 	4.0f / 3.0f,

	// 	// Near clipping plane. Keep as big as possible, or you'll get 
	// 	// precision issues.
	// 	0.1f,

	// 	// Far clipping plane. Keep as little as possible.
	// 	100.0f
	// );


	///////////////////////////////////////////////////////////////////////////
	// OBJETOS DE LA ESCENA
	///////////////////////////////////////////////////////////////////////////
	
	// Dibujamos el eje coordenado
	glm::mat4 model_matrix_eje_coordenado = glm::mat4 (1.0f);
	model_matrix_eje_coordenado = glm::rotate(model_matrix_eje_coordenado,
		this->grado, glm::vec3(0.0, 0.0, 1.0));
	this->ejeCoordenado.render(model_matrix_eje_coordenado, this->view_matrix, 
		projection_matrix);

	// Drawing Grid
	glm::mat4 model_matrix_grid = glm::mat4(1.0f);

	// Cambiamos el color de la grilla
	this->grid.changeObjectColor(0.5, 0.5, 0.5);
	this->grid.render(model_matrix_grid, this->view_matrix, projection_matrix);

	// // Dibujamos cangrejo
	// glm::mat4 model_matrix_cangrejo = glm::mat4(1.0f);

	// // Cambiamos el color de la grilla
	// this->cangrejo.changeObjectColor(0.796, 0.65, 0.6);
	// this->cangrejo.render(model_matrix_cangrejo, this->view_matrix, 
	// 	projection_matrix);


	
	///////////////////////////////////////////////////////////////////////////

	glutSwapBuffers();
}


// Redimensiona la escena.
void Scene::resize(int width, int height)
{
	glViewport(0, 0, (GLsizei) width, (GLsizei) height); 
}


// Establece la posicion de la camara de la escena.
void Scene::setCameraPosition()
{

}


// Devuelve la posicion de la camara de la escena.
void Scene::getCameraPosition()
{

}


// Manejador del evento de tecla presionada.
void Scene::onKeyDown(int nKey, char cAscii)
{
	if(cAscii == '+') 
		this->grado--;
	else if(cAscii == '-') 
		this->grado++;
}
