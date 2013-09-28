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
// #include "object_cangrejo_pata_muslo.h"





/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class Scene
{
private:

	glm::mat4 view_matrix;				// Camera view position

	// Objetos
	// (Definir atributos relacionados con objetos AQUI)

	// TEMPORAL
	EjeCoordenado ejeCoordenado;
	Grid grid;
	// CangrejoPataMuslo cangrejo;
	GLfloat grado;
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
};

#endif
