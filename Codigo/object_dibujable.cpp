/*  
 *  CLASS OBJECTDIBUJABLE
 */  


#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform2.hpp> 
#include <glm/gtx/projection.hpp>

#include "object_dibujable.h"





/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
ObjectDibujable::ObjectDibujable() { }


// Destructor
ObjectDibujable::~ObjectDibujable() { }
	

// Crea un objeto.
void ObjectDibujable::create() { }


// Carga los shaders
void ObjectDibujable::loadShaderPrograms(std::string vertShaderFile, 
	std::string fragShaderFile)
{
	// ********************************************
	// Compiling the shader programms
	// ********************************************

	// Do your GLEW experiments here:
	if (GLEW_ARB_shading_language_100) 
	{ 
		std::cout << "GLEW_ARB_shading_language_100" << std::endl;
		const GLubyte* sVersion = glGetString(GL_SHADING_LANGUAGE_VERSION_ARB);
		
		if (glGetError() != GL_INVALID_ENUM)
		{
			std::string version((char*)sVersion);
			std::cout << version.c_str() << std::endl;
		}

		// Load vertex Shader
		this->vertShader = glCreateShader (GL_VERTEX_SHADER);
		
		if (0 == this->vertShader)
			std::cout << "Error creating vertex shader" << std::endl;

		std::ifstream v_shader_file(vertShaderFile.c_str(), std::ifstream::in);
		std::string v_str((std::istreambuf_iterator<char>(v_shader_file)), 
			std::istreambuf_iterator<char>());
		const char* vs_code_array[] = {v_str.c_str()};

		glShaderSource(this->vertShader, 1, vs_code_array, NULL);

		// Compilar el shader
		glCompileShader(this->vertShader);

		// Verificar resultado de la compilacion
		GLint vs_compilation_result;
		glGetShaderiv(this->vertShader, GL_COMPILE_STATUS, 
			&vs_compilation_result);

		if(GL_FALSE == vs_compilation_result)
		{
			std::cout << "Vertex shader compilation failed!\n" << std::endl;
			GLint logLen;
			glGetShaderiv( this->vertShader, GL_INFO_LOG_LENGTH, &logLen );
			
			if(logLen > 0)
			{
				char * log = (char *) malloc(logLen);
				GLsizei written;
				glGetShaderInfoLog(vertShader, logLen, &written, log);
				std::cout << "Shader log: " << log << std::endl;
				free(log);
			}
		}

		 // Load fragment Shader
		this->fragShader = glCreateShader (GL_FRAGMENT_SHADER);

		if(0 == this->fragShader)
			std::cout << "Error creating fragment shader" << std::endl;

		std::ifstream f_shader_file(fragShaderFile.c_str(), std::ifstream::in);
		std::string f_str((std::istreambuf_iterator<char>(f_shader_file)),
			std::istreambuf_iterator<char>());
		const char* fs_code_array[] = {f_str.c_str()};

		glShaderSource(this->fragShader, 1, fs_code_array, NULL);

		// Compilar el shader
		glCompileShader(this->fragShader);

		// verificar resultado de la compilacion
		GLint fs_compilation_result;
		glGetShaderiv( this->fragShader, GL_COMPILE_STATUS, 
			&fs_compilation_result );

		if(GL_FALSE == fs_compilation_result)
		{
			std::cout << "Fragment shader compilation failed!\n" << std::endl;
			GLint logLen;
			glGetShaderiv( this->fragShader, GL_INFO_LOG_LENGTH, &logLen );
			
			if(logLen > 0)
			{
				char * log = (char *)malloc(logLen);
				GLsizei written;
				glGetShaderInfoLog( this->fragShader, logLen, &written, log);
				std::cout << "Shader log: " << log << std::endl;
				free(log);
			}
		}
	
	// *******************************************


	// *******************************************
	// Linking the shader programms
	// *******************************************

		this->programHandle = glCreateProgram();
		
		if (0 == this->programHandle)
			std::cout << "Error creating program object" << std::endl;
		else
		{
			glAttachShader(this->programHandle, this->vertShader);
			glAttachShader(this->programHandle, this->fragShader);
			glLinkProgram(this->programHandle);

			GLint status;
			glGetProgramiv( this->programHandle, GL_LINK_STATUS, &status );
			
			if(GL_FALSE == status)
			{
				std::cout << "Failed to link shader program!\n" << std::endl;
				GLint logLen;
				glGetProgramiv(this->programHandle, GL_INFO_LOG_LENGTH, 
					&logLen);
				
				if(logLen > 0)
				{
					char * log = (char *) malloc(logLen);
					GLsizei written;
					glGetProgramInfoLog(programHandle, logLen, &written, log);
					std::cout << "Program log: \n%s" << std::endl;
					free(log);
				}
			}
			else
				glUseProgram(this->programHandle);
		}
	}
}


// Cambia el color del objeto
// PRE: 'r', 'g' y 'b' corresponden al color en RGB.
void ObjectDibujable::changeObjectColor(float r, float g, float b)
{
	glm::vec3 diffuse_reflectivity = glm::vec3(r, g, b);

	GLuint location_diffuse_reflectivity = glGetUniformLocation(
		this->programHandle, "Kd");

	if(location_diffuse_reflectivity >= 0) 
		glUniform3fv(location_diffuse_reflectivity, 1, 
			&diffuse_reflectivity[0]); 
}
