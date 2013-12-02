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
	GLuint texture_id;					// ID de la textura	

	// Carga los shaders
	void loadShaderPrograms(std::string vertShaderFile, 
		std::string fragShaderFile);

	// Carga e inicia las texturas
	void loadAndInitTexture(const char* filename);

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
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix,
		glm::mat4 &projection_matrix) = 0;

	// Cambia el color del objeto
	// PRE: 'r', 'g' y 'b' corresponden al color en RGB, es decir, a un valor
	// entre 0 y 255.
	void changeObjectColor(int r, int g, int b);
};

#endif
