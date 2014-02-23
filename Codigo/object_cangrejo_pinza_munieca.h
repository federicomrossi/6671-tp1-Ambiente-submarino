/*  
 *  CLASS CANGREJO_PINZA_MUNIECA
 */


#ifndef OBJECT_CANGREJO_PINZA_MUNIECA_H
#define OBJECT_CANGREJO_PINZA_MUNIECA_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"




/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class CangrejoPinzaMunieca : public ObjectDibujable
{
private:

	GLfloat* sphere_vertex_buffer;
	GLuint* sphere_index_buffer;
	GLfloat* sphere_tangent_buffer;
	GLfloat* sphere_texture_buffer;
	std::vector<float> vertex_buffer;
	std::vector<unsigned int> index_buffer;
	std::vector<float> tangent_buffer;
	std::vector<float> texture_buffer;

public:

	// Constructor
	CangrejoPinzaMunieca();

	// Destructor
	~CangrejoPinzaMunieca();

	// Crea un objeto.
	// PRE: 'radius' es el radio de la esfera; 'loops' ...; 'segmentsPerLoop' .
	// ... [Completar documentacion]
	void create(const float radius, const unsigned int loops, 
		const unsigned int segmentsPerLoop);

	// Renderiza el cubo (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
