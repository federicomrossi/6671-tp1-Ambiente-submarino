/*  
 *  CLASS PEZ_ALETA_DORSAL
 */  


#ifndef OBJECT_PEZ_ALETA_DORSAL_H
#define OBJECT_PEZ_ALETA_DORSAL_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"






/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class PezAletaDorsal : public ObjectDibujable
{
private:

	// Buffers
	GLfloat* object_vertex_buffer;
	GLfloat* object_normal_buffer;
	GLfloat* object_texture_buffer;
	GLuint* object_index_buffer;
	unsigned int object_vertex_buffer_size;
	unsigned int object_normal_buffer_size;
	unsigned int object_texture_buffer_size;
	unsigned int object_index_buffer_size;

	// Caracteristicas del objeto
	int CANT_PUNTOS;
	int ESTIRAMIENTO;				// Niveles que posee el objeto de
									// estiramiento
	float ESPACIADO_ESTIRAMIENTO;	// Espacio entre cada nivel de altura del
									// estiramiento del objeto.
	
public:

	// Constructor
	PezAletaDorsal();

	// Destructor
	~PezAletaDorsal();

	// Crea un objeto
	virtual void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
