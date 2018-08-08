#include <windows.h>
#include <GL/glut.h>
#include "2DPoint.h"

extern int m_LButtonDown, m_MButtonDown, m_RButtonDown;
extern TwoDPoint m_LDownPos, m_MDownPos, m_RDownPos;
extern double m_xRotate, m_yRotate;
extern double m_transX, m_transY, m_transZ;
extern int win_id;

// my variables
extern double m_shearX;
extern double m_shearY;
extern double m_shearZ;
extern bool upY, downY, leftX, rightX;
extern double m_shear;

void mouseFunc(int button, int state, int x, int y )
  {
     switch( button )
     {
        case GLUT_LEFT_BUTTON:
      
           switch( state )
           {
              case GLUT_DOWN:
				m_LButtonDown = TRUE;
				m_LDownPos.x = x;
				m_LDownPos.y = y;
                break;
              case GLUT_UP:
				m_LButtonDown = FALSE;
                break;
           }
           break;

		case GLUT_RIGHT_BUTTON:
      
           switch( state )
           {
              case GLUT_DOWN:
				m_RButtonDown = TRUE;
				m_RDownPos.x = x;
				m_RDownPos.y = y;
                break;
              case GLUT_UP:
				m_RButtonDown = FALSE;
                break;
           }
           break;

		case GLUT_MIDDLE_BUTTON:

		   switch(state)
		   {
		   case GLUT_DOWN:
			   m_MButtonDown = TRUE;
			   m_MDownPos.x = x;
			   m_MDownPos.y = y;
			   break;
		   case GLUT_UP:
			   m_MButtonDown = FALSE;
			   break;
		   }
		   break;
		

		default:
			break;

     } //End of switch
  }

void mouseMotionFunc(int x, int y)
{
     /* find out what action to perform */
	if (m_LButtonDown)
	{
		m_yRotate -= (m_LDownPos.x - (double)x)/2.0;
		m_xRotate -= (m_LDownPos.y - (double)y)/2.0;
			
		m_LDownPos.x = x;
		m_LDownPos.y = y;
		
		
	}

	if (m_RButtonDown)
	{
 		m_transX -= (m_RDownPos.x - (double)x)/10.0f; 	
		m_transY += (m_RDownPos.y - (double)y)/10.0f;

		m_RDownPos.x = x;
		m_RDownPos.y = y;

		
	}

		if (m_MButtonDown)
	{
 		m_transZ -= (m_MDownPos.y - (double)y)/10.0f; 	

		m_MDownPos.x = x;
		m_MDownPos.y = y;

		
	}

  glutSetWindow(win_id);
  glutPostRedisplay();
 
}
// new function for scaling
void arrowKey(int key, int x, int y){
	switch (key){
	case GLUT_KEY_UP:
		m_shearY++;
		upY = true;
		downY = false;
		rightX = false;
		leftX = false;
		break;
	case GLUT_KEY_DOWN:
		m_shearY--;
		upY = false;
		downY = true;
		rightX = false;
		leftX = false;
		break;
	case GLUT_KEY_LEFT:
		m_shearX--;
		upY = false;
		downY = false;
		rightX = false;
		leftX = true;
		break;
	case GLUT_KEY_RIGHT:
		m_shearX++;
		upY = false;
		downY = false;
		rightX = true;
		leftX = false;
		break;
	default:
		break;


	}
	glutPostRedisplay();
}

void keyboard(unsigned char Key, int x, int y)
{

  switch(Key)
  {
  case 'd':  // included for shear
	  m_shear++;
	  break;
  case 'c':
	  m_shear--;
	  break;
		case 27: 
		case 'q':
			exit(0); break;

		default:
			break;
  };
  
  glutPostRedisplay();

}