/*  
 *  CLASS CANGREJOPATA
 */  


#ifndef OBJECT_CANGREJO_PATA_MUSLO_H
#define OBJECT_CANGREJO_PATA_MUSLO_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"


// Objetos
#include "object_spiralSphere.h"






/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class CangrejoPataMuslo : public ObjectDibujable
{
private:

	GLfloat* muslo_vertex_buffer;
	GLfloat* muslo_normal_buffer;
	GLuint* muslo_index_buffer;
	unsigned int muslo_vertex_buffer_size;
	unsigned int muslo_normal_buffer_size;
	unsigned int muslo_index_buffer_size;

	// Objetos
	SpiralSphere spiralSphere;			// Esfera

public:

	// Constructor
	CangrejoPataMuslo();

	// Destructor
	~CangrejoPataMuslo();

	// Crea un objeto
	virtual void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, GLuint &programHandle);
};

#endif
