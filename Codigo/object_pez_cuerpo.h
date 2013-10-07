/*  
 *  CLASS PEZ_CUERPO
 */  


#ifndef OBJECT_PEZ_CUERPO_H
#define OBJECT_PEZ_CUERPO_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"

// Objetos
#include "object_spiralSphere.h"



/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class PezCuerpo : public ObjectDibujable
{
private:

	// Objetos
	SpiralSphere spiralSphere;		// Esfera

public:

	// Constructor
	PezCuerpo();

	// Destructor
	~PezCuerpo();

	// Crea un objeto
	virtual void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
