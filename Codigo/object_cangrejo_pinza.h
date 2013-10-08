/*  
 *  CLASS CANGREJO_PINZA
 */  


#ifndef OBJECT_CANGREJO_PINZA_H
#define OBJECT_CANGREJO_PINZA_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"

#include "object_eje_coordenado.h"
#include "object_spiralSphere.h"
#include "object_cube.h"



/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class CangrejoPinza : public ObjectDibujable
{
private:

	GLfloat* pinza_vertex_buffer;
	GLfloat* pinza_normal_buffer;
	GLuint* pinza_index_buffer;
	unsigned int pinza_vertex_buffer_size;
	unsigned int pinza_normal_buffer_size;
	unsigned int pinza_index_buffer_size;

	// Objetos
	EjeCoordenado ejeCoordenado;		// Eje coordenado del objeto
	SpiralSphere spiralSphere;
	Cube cube;

public:

	// Constructor
	CangrejoPinza();

	// Destructor
	~CangrejoPinza();

	// Crea un objeto
	virtual void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
