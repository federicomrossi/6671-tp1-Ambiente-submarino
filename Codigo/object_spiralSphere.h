/*  
 *  CLASS SPIRALSPHERE
 */


#ifndef OBJECT_SPIRAL_SPHERE_H
#define OBJECT_SPIRAL_SPHERE_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"




/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class SpiralSphere : public ObjectDibujable
{
private:

	GLfloat* sphere_vertex_buffer;
	GLuint* sphere_index_buffer;
	std::vector<float> vertex_buffer;
	std::vector<unsigned int> index_buffer;

public:

	// Constructor
	SpiralSphere();

	// Destructor
	~SpiralSphere();

	// Crea un objeto.
	// PRE: 'radius' es el radio de la esfera; 'loops' ...; 'segmentsPerLoop' .... [Completar documentacion]
	void create(const float radius, const unsigned int loops, const unsigned int segmentsPerLoop);

	// Renderiza el cubo (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	void render(glm::mat4 model_matrix, glm::mat4 &view_matrix);
};

#endif
