/*  
 *  CLASS SCENE
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

#include "scene.h"





/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
Scene::Scene()
{
	// Inicializamos atributos de movimiento
	this->modoMovimiento = 1;

	this->gradoHombro = 0.0f;
	this->gradoBrazo = 45.0f;
	this->gradoCodo = 0.0f;
	this->gradoAntebrazo = 45.0f;
	this->gradoMano = 45.0f;

	// View (camera) Matrix
	this->view_matrix = glm::lookAt(glm::vec3 ( 8.0, 0.0, 5.0 ),
									glm::vec3 ( 0.0, 0.0, 0.0 ),
									glm::vec3 ( 0.0, 0.0, 1.0 ));
}


// Destructor
Scene::~Scene() { }


// Inicializa la escena.
void Scene::initialize()
{
	this->grid.create(10);							// Grilla
	this->spiralSphere.create(1.0, 32, 32);			// Esfera
	this->cube.create();							// Cubo    

	glClearColor(0.3f, 0.3f, 0.4f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);


	// // ********************************************
	// // Compiling the shader programms
	// //*********************************************

	// // Do your GLEW experiments here:
	// if (GLEW_ARB_shading_language_100) 
	// { 
	// 	std::cout << "GLEW_ARB_shading_language_100" << std::endl;
	// 	// int major, minor, revision;
	// 	const GLubyte* sVersion = glGetString(GL_SHADING_LANGUAGE_VERSION_ARB);
	// 	if (glGetError() != GL_INVALID_ENUM)
	// 	{
	// 	    std::string version((char*)sVersion);
	// 	    std::cout << version.c_str() << std::endl;
	// 	}
	// 	// else
	// 	// {
	// 	//     major = 1; minor = 0; revision=51;
	// 	// }

	// 	// Load vertex Shader
	// 	this->vertShader = glCreateShader (GL_VERTEX_SHADER);
	// 	if ( 0 == this->vertShader )
	// 	{
	// 		std::cout << "Error creating vertex shader" << std::endl;
	// 	}

	// 	std::ifstream v_shader_file("DiffuseShadingVShader.vert", std::ifstream::in);
	// 	std::string v_str((std::istreambuf_iterator<char>(v_shader_file)), std::istreambuf_iterator<char>());
	// 	const char* vs_code_array[] = {v_str.c_str()};

	// 	glShaderSource( this->vertShader, 1, vs_code_array, NULL);

	// 	// Compilar el shader
	// 	glCompileShader( this->vertShader );

	// 	// verificar resultado de la compilacion
	// 	GLint vs_compilation_result;
	// 	glGetShaderiv( this->vertShader, GL_COMPILE_STATUS, &vs_compilation_result );
	// 	if( GL_FALSE == vs_compilation_result )
	// 	{
	// 	    std::cout << "Vertex shader compilation failed!\n" << std::endl;
	// 	    GLint logLen;
	// 	    glGetShaderiv( this->vertShader, GL_INFO_LOG_LENGTH, &logLen );
	// 	    if( logLen > 0 )
	// 	    {
	// 	        char * log = (char *)malloc(logLen);
	// 	        GLsizei written;
	// 	        glGetShaderInfoLog(vertShader, logLen, &written, log);
	// 	        std::cout << "Shader log: " << log << std::endl;
	// 	        free(log);
	// 	    }
	// 	}

	// 	 // Load fragment Shader
	// 	this->fragShader = glCreateShader (GL_FRAGMENT_SHADER);
	// 	if ( 0 == this->fragShader )
	// 	{
	// 	    std::cout << "Error creating fragment shader" << std::endl;
	// 	}

	// 	std::ifstream f_shader_file("DiffuseShadingFShader.frag", std::ifstream::in);
	// 	std::string f_str((std::istreambuf_iterator<char>(f_shader_file)), std::istreambuf_iterator<char>());
	// 	const char* fs_code_array[] = {f_str.c_str()};

	// 	glShaderSource( this->fragShader, 1, fs_code_array, NULL);

	// 	// Compilar el shader
	// 	glCompileShader( this->fragShader );

	// 	// verificar resultado de la compilacion
	// 	GLint fs_compilation_result;
	// 	glGetShaderiv( this->fragShader, GL_COMPILE_STATUS, &fs_compilation_result );
	// 	if( GL_FALSE == fs_compilation_result )
	// 	{
	// 	    std::cout << "Fragment shader compilation failed!\n" << std::endl;
	// 	    GLint logLen;
	// 	    glGetShaderiv( this->fragShader, GL_INFO_LOG_LENGTH, &logLen );
	// 	    if( logLen > 0 )
	// 	    {
	// 	        char * log = (char *)malloc(logLen);
	// 	        GLsizei written;
	// 	        glGetShaderInfoLog( this->fragShader, logLen, &written, log);
	// 	        std::cout << "Shader log: " << log << std::endl;
	// 	        free(log);
	// 	    }
	// 	}
	// // *******************************************

	// // *******************************************
	// // Linking the shader programms
	// // *******************************************
	//     this->programHandle = glCreateProgram();
	//     if ( 0 == this->programHandle )
	//     {
	//         std::cout << "Error creating program object" << std::endl;
	//     }
	//     else
	//     {
	//         glAttachShader( this->programHandle, this->vertShader );
	//         glAttachShader( this->programHandle, this->fragShader );

	//         glLinkProgram( this->programHandle );

	//         GLint status;
	//         glGetProgramiv( this->programHandle, GL_LINK_STATUS, &status );
	//         if( GL_FALSE == status )
	//         {
	//             std::cout << "Failed to link shader program!\n" << std::endl;
	//             GLint logLen;
	//             glGetProgramiv( this->programHandle, GL_INFO_LOG_LENGTH, &logLen);
	//             if( logLen > 0 )
	//             {
	//                 char * log = (char *)malloc(logLen);
	//                 GLsizei written;
	//                 glGetProgramInfoLog(programHandle, logLen, &written, log);
	//                 std::cout << "Program log: \n%s" << std::endl;
	//                 free(log);
	//             }
	//         }
	//         else
	//         {
	//             glUseProgram( this->programHandle );
	//         }
	//     }
	// }
}


// Renderiza la escena.
// POST: previo a realizar el primer renderizado debe invocarse al método
// initialize().
void Scene::render(GLuint height, GLuint width)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//////////////////////////////////////
	// View and Projection Matrices Setting
	//

	// Projection Matrix
	glm::mat4 projection_matrix = glm::mat4 ( 1.0f );
	projection_matrix = glm::infinitePerspective( 52.0f , (float)width / (float)height, 0.1f);




	glUseProgram(this->programHandle);

	// Bind View Matrix
	GLuint location_view_matrix = glGetUniformLocation( this->programHandle, "ViewMatrix"); 
	if( location_view_matrix >= 0 ) 
	{ 
		glUniformMatrix4fv( location_view_matrix, 1, GL_FALSE, &view_matrix[0][0]); 
	}

	// Bind View MAtrix
	GLuint location_projection_matrix = glGetUniformLocation( this->programHandle, "ProjectionMatrix"); 
	if( location_projection_matrix >= 0 ) 
	{ 
		glUniformMatrix4fv( location_projection_matrix, 1, GL_FALSE, &projection_matrix[0][0]); 
	}
	//
	///////////////////////////////////////////


	//////////////////////////////////////
	// Bind Light Settings
	glm::vec4 light_position = glm::vec4( 8.0f, 8.0f, 2.0f, 1.0f );
	glm::vec3 light_intensity = glm::vec3( 1.0f, 1.0f, 1.0f );
	   
	GLuint location_light_position = glGetUniformLocation( this->programHandle, "LightPosition"); 
	if( location_light_position >= 0 ) 
	{ 
	    glUniform4fv( location_light_position, 1, &light_position[0]); 
	}

	GLuint location_light_intensity = glGetUniformLocation( this->programHandle, "Ld"); 
	if( location_light_intensity >= 0 ) 
	{ 
		glUniform3fv( location_light_intensity, 1, &light_intensity[0]); 
	}
	//
	///////////////////////////////////////////


	// Drawing Grid
	changeObjectColor(0.5, 0.5, 0.5);
	glm::mat4 model_matrix_grid = glm::mat4 ( 1.0f );
	this->grid.render(model_matrix_grid, this->view_matrix);

	// ARM
	glm::mat4 model_matrix = glm::mat4 ( 1.0f );
	changeObjectColor(0.796, 0.65, 0.6);

	// Rotacion del HOMBRO
	model_matrix = glm::rotate (model_matrix, this->gradoHombro, glm::vec3(0.0, 0.0, 1.0));

	this->dibujarHombro(model_matrix);

	glutSwapBuffers();
}


// Redimensiona la escena.
void Scene::resize(int width, int height)
{
	glViewport (0, 0, (GLsizei) width, (GLsizei) height); 
}


// Establece la posicion de la camara de la escena.
void Scene::setCameraPosition()
{

}


// Devuelve la posicion de la camara de la escena.
void Scene::getCameraPosition()
{

}


// Manejador del evento de tecla presionada.
void Scene::onKeyDown(int nKey, char cAscii)
{
	if(cAscii == '6') 
	{
		if(this->modoMovimiento == 1)
			this->gradoHombro += 1.0f;
		else if(this->modoMovimiento == 2)
			this->gradoCodo += 1.0f;
		else if(this->modoMovimiento == 3)
			this->gradoMunieca += 3.0f;
	}
	else if(cAscii == '4')
	{
		if(this->modoMovimiento == 1)
			this->gradoHombro -= 1.0f;
		else if(this->modoMovimiento == 2)
			this->gradoCodo -= 1.0f;
		else if(this->modoMovimiento == 3)
			this->gradoMunieca -= 3.0f;
	}
	else if(cAscii == '2')
	{	
		if(this->modoMovimiento == 1)
			this->gradoBrazo += 1;
		else if(this->modoMovimiento == 2)
			this->gradoAntebrazo += 1;
	}
	else if(cAscii == '8')
	{
		if(this->modoMovimiento == 1)
			this->gradoBrazo -= 1;
		else if(this->modoMovimiento == 2)
			this->gradoAntebrazo -= 1;
	}
	// Abrir pinzas
	else if(cAscii == '+')
	{
		this->gradoMano += 1;
	}
	// Cerrar pinzas
	else if(cAscii == '-')
	{
		this->gradoMano -= 1;
	}

		
	// Selección de movimiento del HOMBRO
	else if(cAscii == 'a' || cAscii == 'A')
		this->modoMovimiento = 1;
	// Selección de movimiento del CODO
	else if(cAscii == 's' || cAscii == 'S')
		this->modoMovimiento = 2;
	// Selección de movimiento del MUÑECA
	else if(cAscii == 'd' || cAscii == 'D')
		this->modoMovimiento = 3;
}






// METODOS PRIVADOS
// ################


void Scene::dibujarHombro(glm::mat4 m)
{
	// Renderizamos esfera que representa el hombro
	glm::mat4 mHombro = glm::mat4 ( 1.0f );
	mHombro = glm::rotate (m, this->gradoBrazo, glm::vec3(1.0, 0.0, 0.0));
	this->spiralSphere.render(mHombro, this->view_matrix);

	// Posicionamos el inicio del brazo
	glm::mat4 mBrazo = glm::mat4 ( 1.0f );
	mBrazo = glm::translate(mHombro , glm::vec3(0.0, 0.0, 0.5) );

	// Dibujamos brazo
	this->dibujarBrazo(mBrazo);
}


void Scene::dibujarBrazo(glm::mat4 m)
{
	// Transformamos para posicionar y formar el brazo
	glm::mat4 mBrazo = glm::mat4 ( 1.0f );
	mBrazo = glm::scale(m, glm::vec3 (0.6f, 0.6f, 3.0f) );
	mBrazo = glm::translate(mBrazo , glm::vec3(0.0, 0.0, 0.5) );

	// Renderizamos el brazo
	this->cube.render(mBrazo, this->view_matrix);

	// Posicionamos el codo respecto del brazo
	glm::mat4 mCodo = glm::mat4 ( 1.0f );
	mCodo = glm::translate(m, glm::vec3(0.0, 0.0, 3.0) );

	// Dibujamos codo
	this->dibujarCodo(mCodo);
}


void Scene::dibujarCodo(glm::mat4 m)
{
	// Renderizamos esfera que representa el codo
	glm::mat4 mCodo = glm::mat4 ( 1.0f );
	mCodo = glm::rotate (m, this->gradoCodo, glm::vec3(0.0, 0.0, 1.0));
	mCodo = glm::scale(mCodo, glm::vec3(0.5f, 0.5f, 0.5));
	this->spiralSphere.render(mCodo, this->view_matrix);

	// Posicionamos el inicio del antebrazo
	glm::mat4 mAntebrazo = glm::mat4 ( 1.0f );
	mAntebrazo = glm::rotate (m, this->gradoCodo, glm::vec3(0.0, 0.0, 1.0));
	mAntebrazo = glm::rotate (mAntebrazo, this->gradoAntebrazo, glm::vec3(1.0, 0.0, 0.0));
	// mAntebrazo = glm::translate(mAntebrazo, glm::vec3(0.0, 0.0, 0.5) );

	// Dibujamos antebrazo
	this->dibujarAntebrazo(mAntebrazo);
}


void Scene::dibujarAntebrazo(glm::mat4 m)
{
	// Transformamos para posicionar y formar el brazo
	glm::mat4 mAntebrazo = glm::mat4 ( 1.0f );
	mAntebrazo = glm::scale(m, glm::vec3 (0.4f, 0.4f, 1.5f) );
	mAntebrazo = glm::translate(mAntebrazo , glm::vec3(0.0, 0.0, 0.5) );

	this->cube.render(mAntebrazo, this->view_matrix);

	// Posicionamos la muñeca respecto del antebrazo
	glm::mat4 mMunieca = glm::mat4 ( 1.0f );
	mMunieca = glm::rotate (m, this->gradoMunieca, glm::vec3( 0.0, 0.0, 1.0));
	mMunieca = glm::translate(mMunieca, glm::vec3(0.0, 0.0, 1.5) );

	// Dibujamos muñeca
	this->dibujarMunieca(mMunieca);
}


void Scene::dibujarMunieca(glm::mat4 m)
{
	// Renderizamos esfera que representa la muñeca
	glm::mat4 mMunieca = glm::mat4 ( 1.0f );
	mMunieca = glm::scale(m, glm::vec3(0.3f, 0.3f, 0.3));
	
	this->spiralSphere.render(mMunieca, this->view_matrix);

	// Dibujamos mano
    this->dibujarMano(m);
}


void Scene::dibujarMano(glm::mat4 m)
{
	// Transformamos para posicionar y formar
	glm::mat4 mGarraDerecha = glm::mat4 ( 1.0f );
	mGarraDerecha = glm::rotate(m, (-1) * this->gradoMano, glm::vec3( 1.0, 0.0, 0.0));
	mGarraDerecha = glm::scale(mGarraDerecha, glm::vec3 (0.3f, 0.1f, 0.7f) );
	mGarraDerecha = glm::translate(mGarraDerecha , glm::vec3(0.0, 0.0, 0.5) );
	this->cube.render(mGarraDerecha, this->view_matrix);

	// Transformamos para posicionar y formar
	glm::mat4 mGarraIzquierda = glm::mat4 ( 1.0f );
	mGarraIzquierda = glm::rotate(m, this->gradoMano, glm::vec3( 1.0, 0.0, 0.0));
	mGarraIzquierda = glm::scale(mGarraIzquierda, glm::vec3 (0.3f, 0.1f, 0.7f) );
	mGarraIzquierda = glm::translate(mGarraIzquierda , glm::vec3(0.0, 0.0, 0.5) );
	this->cube.render(mGarraIzquierda, this->view_matrix);
}


void Scene::changeObjectColor(float r, float g, float b)
{
	glm::vec3 diffuse_reflectivity = glm::vec3( r, g, b );

	GLuint location_diffuse_reflectivity = glGetUniformLocation( this->programHandle, "Kd"); 
	if( location_diffuse_reflectivity >= 0 ) 
		glUniform3fv( location_diffuse_reflectivity, 1, &diffuse_reflectivity[0]); 
}
