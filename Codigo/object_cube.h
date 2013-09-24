/*  
 *  CLASS CUBE
 */  


#ifndef OBJECT_CUBE_H
#define OBJECT_CUBE_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"





/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class Cube : public ObjectDibujable
{
private:

	GLfloat* cube_vertex_buffer;
	GLfloat* cube_normal_buffer;
	GLuint* cube_index_buffer;
	unsigned int cube_vertex_buffer_size;
	unsigned int cube_normal_buffer_size;
	unsigned int cube_index_buffer_size;

public:

	// Constructor
	Cube();

	// Destructor
	~Cube();

	// Crea un objeto.
	virtual void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
