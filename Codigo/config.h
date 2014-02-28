#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform2.hpp> 
#include <glm/gtx/projection.hpp>




/* ****************************************************************************
 * CONFIGURACIÓN GENERAL DE LA ESCENA
 * ***************************************************************************/


const GLfloat AMBIENT_COLOR_R = 40.0f / 255.0;
const GLfloat AMBIENT_COLOR_G = 91.0f / 255.0;
const GLfloat AMBIENT_COLOR_B = 166.0f / 255.0;
const GLfloat AMBIENT_COLOR_ALPHA = 0.0f / 255.0;

const glm::vec3 LIGHT_INTENSITY = glm::vec3(0.8f, 0.8f, 1.0f);
const glm::vec4 LIGHT_POSITION = glm::vec4(10.0f, 0.0f, 4.0f, 1.0f);

const GLfloat FOG_MIN_DISTANCE = 0.0;
const GLfloat FOG_MAX_DISTANCE = 25.0;
const glm::vec3 FOG_COLOR = glm::vec3(40.0f / 255.0, 
									  91.0f / 255.0,
									  166.0f / 255.0);


#endif