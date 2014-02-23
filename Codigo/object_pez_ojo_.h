/*  
 *  CLASS PEZ_OJO
 */  


#ifndef OBJECT_PEZ_OJO_H
#define OBJECT_PEZ_OJO_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"

// Objetos
#include "object_spiralSphere.h"



/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class PezOjo : public ObjectDibujable
{
private:

	// Objetos
	SpiralSphere spiralSphere;		// Esfera
	
public:

	// Constructor
	PezOjo();

	// Destructor
	~PezOjo();

	// Crea un objeto
	virtual void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
