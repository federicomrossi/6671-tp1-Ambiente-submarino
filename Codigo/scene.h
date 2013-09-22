/*  
 *  CLASS SCENE
 */  


#ifndef SCENE_H
#define SCENE_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>

// Objetos
#include "object_grid.h"
#include "object_cube.h"
#include "object_spiralSphere.h"





/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class Scene
{
private:

    glm::mat4 view_matrix;				// Camera view position

    // BORRAR
	GLuint programHandle;
	GLuint vertShader;
	GLuint fragShader;
	// END BORRAR

	// Objetos
	Grid grid;						// Grilla
	Cube cube;						// Cubo
	SpiralSphere spiralSphere;		// Esfera

	// Modo de movimiento
	int modoMovimiento;

	// TEMPORALES (Nota: cada objeto debe ser separado en clases individuales 
	// y no dejarlos definidos aquí)
	GLfloat gradoHombro;			// Hombro
	GLfloat gradoCodo;				// Codo
	GLfloat gradoBrazo;				// Brazo
	GLfloat gradoAntebrazo;			// Muñeca
	GLfloat gradoMunieca;			// Muñeca
	GLfloat gradoMano;				// Mano

	void dibujarHombro(glm::mat4 m, glm::mat4 &projection_matrix);
	void dibujarBrazo(glm::mat4 m, glm::mat4 &projection_matrix);
	void dibujarCodo(glm::mat4 m, glm::mat4 &projection_matrix);
	void dibujarAntebrazo(glm::mat4 m, glm::mat4 &projection_matrix);
	void dibujarMunieca(glm::mat4 m, glm::mat4 &projection_matrix);
	void dibujarMano(glm::mat4 m, glm::mat4 &projection_matrix);
	// FIN TEMPORALES

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
};

#endif
