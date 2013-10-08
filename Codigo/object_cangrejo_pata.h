/*  
 *  CLASS CANGREJOPATA
 */  


#ifndef OBJECT_CANGREJO_PATA_H
#define OBJECT_CANGREJO_PATA_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"

#include "object_eje_coordenado.h"
#include "object_spiralSphere.h"



/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class CangrejoPata : public ObjectDibujable
{
private:

	GLfloat* pata_vertex_buffer;
	GLfloat* pata_normal_buffer;
	GLuint* pata_index_buffer;
	unsigned int pata_vertex_buffer_size;
	unsigned int pata_normal_buffer_size;
	unsigned int pata_index_buffer_size;

	// Objetos
	EjeCoordenado ejeCoordenado;		// Eje coordenado del objeto
	SpiralSphere spiralSphere;

public:

	// Constructor
	CangrejoPata();

	// Destructor
	~CangrejoPata();

	// Crea un objeto
	virtual void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
