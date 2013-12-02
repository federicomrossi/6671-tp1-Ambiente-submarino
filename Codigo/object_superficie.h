/*  
 *  CLASS SUPERFICIE
 */  


#ifndef OBJECT_SUPERFICIE_H
#define OBJECT_SUPERFICIE_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"

// Objetos
#include "object_eje_coordenado.h"


// DEBUG
#include "object_vector.h"
// END DEBUG
 


/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class Superficie : public ObjectDibujable
{
private:

	// Buffers
	GLfloat* object_vertex_buffer;
	GLfloat* object_normal_buffer;
	GLuint* object_index_buffer;
	unsigned int object_vertex_buffer_size;
	unsigned int object_normal_buffer_size;
	unsigned int object_index_buffer_size;

	// Caracteristicas del objeto
	int CANT_PUNTOS;
	int ESTIRAMIENTO;		// Niveles que posee el objeto de estiramiento

	// Objetos
	EjeCoordenado ejeCoordenado;		// Eje coordenado del objeto

	// DEBUG
	Vector vector;
	// END DEBUG
	
public:

	// Constructor
	Superficie();

	// Destructor
	~Superficie();

	// Crea un objeto
	virtual void create(int ancho);

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
