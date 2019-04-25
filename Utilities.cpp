//Blake Lockley - 44587643

#include <math.h>
#ifdef _WIN32
#include <GL/glut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

//This code was found on the following site and provieds a more efficent
//	appraoch to drawing circles as expensive trig functions are only called
//	once as opposed to n times:
//	http://slabode.exofire.net/circle_draw.shtml
void drawCircle(float cx, float cy, float r, int num_segments)
{
  float theta = 2 * M_PI / float(num_segments);
  float tangetial_factor = tanf(theta);//calculate the tangential factor
  float radial_factor = cosf(theta);//calculate the radial factor
  float x = r;//we start at angle = 0
  float y = 0;

  glBegin(GL_POLYGON);
  for(int ii = 0; ii < num_segments; ii++)
  {
  glVertex2f(x + cx, y + cy);//output vertex

  //calculate the tangential vector
  //remember, the radial vector is (x, y)
  //to get the tangential vector we flip those coordinates and negate one of them
  float tx = -y;
  float ty = x;

  //add the tangential vector
  x += tx * tangetial_factor;
  y += ty * tangetial_factor;

  //correct using the radial factor
  x *= radial_factor;
  y *= radial_factor;
  }
  glEnd();
}
