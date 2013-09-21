//*****************************************************************************
// Application Class
//
//(c) 2003-2006 by Martin Christen. All Rights reserved.
//******************************************************************************/

#include "glApplication.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstring>
#include <string>


using namespace cwc;

std::list<glApplication*> glApplication::_gAppInstances;

//-----------------------------------------------------------------------------

glApplication::glApplication(void)
{
   _gAppInstances.push_back(this);
   
   int argc = 1;

   std::string str = "CWCApp";
   char *argv = new char[str.length() + 1];
   strcpy(argv, str.c_str());
   
   glutInit(&argc, &argv);

   delete [] argv;
}

//-----------------------------------------------------------------------------

glApplication::~glApplication(void)
{
   // remove this instance from application list
   std::list<glApplication*>::iterator i = _gAppInstances.begin();
   
   while (i!=_gAppInstances.end())
   {
      if (*i == this)
      {
         _gAppInstances.erase(i);
         return;
      } 
      
      i++;   
   }
}

//-----------------------------------------------------------------------------

void glApplication::run(void)
{
   OnInit();
   MainLoop();
   OnExit();
}

//-----------------------------------------------------------------------------

bool glApplication::MainLoop()
{
   glutMainLoop();
   return true;
}

//-----------------------------------------------------------------------------
