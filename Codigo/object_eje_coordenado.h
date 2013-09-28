/*  
 *  CLASS EJECOORDENADO
 */  


#ifndef OBJECT_EJE_COORDENADO_H
#define OBJECT_EJE_COORDENADO_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"


// Objetos
#include "object_spiralSphere.h"
#include "object_cube.h"




/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class EjeCoordenado : public ObjectDibujable
{
private:

	int size;

	// Objetos
	SpiralSphere sphere;
	Cube cube;

public:

	// Constructor
	EjeCoordenado();

	// Destructor
	~EjeCoordenado();

	// Crea un objeto
	virtual void create(int size);

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
