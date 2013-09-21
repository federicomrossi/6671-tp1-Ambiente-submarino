/*  
 *  CLASS GRID
 */  


#ifndef OBJECT_GRID_H
#define OBJECT_GRID_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"




/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class Grid : public ObjectDibujable
{
private:

	GLfloat* grid_vertex_buffer;
	unsigned int grid_vertex_buffer_size;
	GLuint* grid_index_buffer;
	unsigned int grid_index_buffer_size;

public:

	// Constructor
	Grid();

	// Destructor
	~Grid();

	// Crea un objeto grilla
	// PRE: 'size' es el tamanio de la grilla
	virtual void create(int size);

	// Renderiza el cubo (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix);
};

#endif
