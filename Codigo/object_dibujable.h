/*  
 *  CLASS OBJECTDIBUJABLE
 */  


#ifndef OBJECT_DIBUJABLE_H
#define OBJECT_DIBUJABLE_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>





/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class ObjectDibujable
{
protected:

	GLuint programHandle;				// Program shader
	GLuint vertShader;					// Vertex shader
	GLuint fragShader;					// Fragment shader

	// Carga los shaders
	void loadShaderPrograms(std::string vertShaderFile, 
		std::string fragShaderFile);

public:

	// Constructor
	ObjectDibujable();

	// Destructor
	~ObjectDibujable();

	// Crea un objeto.
	void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix) = 0;
};

#endif
