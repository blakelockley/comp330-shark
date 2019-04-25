//Blake Lockley - 44587643

#include <iostream>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#endif

#include "World.h"
#include "Menu.h"

#define WIDTH  1000.0f
#define HEIGHT 750.0f

#define ESC 27
#define SPC 32
#define MENU_QUIT 1
#define MENU_ADD_DRUM 2
#define MENU_ADD_ENEMY 3
#define MENU_RESET 4

int previousTime = 0;
bool paused = false;
World world(Frame(WIDTH / 2.0f, HEIGHT / 2.0f, WIDTH, HEIGHT));

void menuHandler(int value) {
  switch (value) {
    case MENU_QUIT:
      exit(0);
      break;

    case MENU_ADD_DRUM:
      world.addDrum();
      break;

    case MENU_ADD_ENEMY:
      world.addEnemy();
      break;

    case MENU_RESET:
      world = World(world.getFrame());
      paused = false;
      break;

    default:
      break;
  }
}

void skinMenuHandler(int value) {
  world.getShip().setSkin(Skin(value));
}

void menuStatus(int status, int x, int y) {
  if (status == GLUT_MENU_IN_USE)
  	paused = true;
  else if (status == GLUT_MENU_NOT_IN_USE) {
  	paused = false;
  }
}

void update(void) {
  int currentTime = glutGet(GLUT_ELAPSED_TIME);

  if (world.getShip().isDead())
    paused = true;

  if (!paused)
  	world.update(currentTime - previousTime);

  previousTime = currentTime;
  glutPostRedisplay();
}

void render(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);

  world.render();

  glutSwapBuffers();
}

void reshape(int width, int height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0f, width, height, 0.0f);
  glViewport(0.0f, 0.0f, width, height);
  world.updateFrame(Frame(width / 2.0f, height / 2.0f, width, height));
}

void keyboardPressed(unsigned char key, int mouse_x, int mouse_y) {
  if (key == ESC)
  	menuHandler(MENU_QUIT);
  if (key == SPC)
  	paused = !paused;
  if (key == 'a')
  	menuHandler(MENU_ADD_DRUM);
  if (key == 'e')
    menuHandler(MENU_ADD_ENEMY);
  if (key == 'r')
    menuHandler(MENU_RESET);
}

void mousePressed(int button, int state, int x, int y) {
  world.getShip().setShooting(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
}

void mouseMotion(int x, int y) {
  world.getShip().move(Point(x, y));
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);

  //create window
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow("Blake Lockley - 44587643");

  //callbacks
  glutDisplayFunc(render);
  glutReshapeFunc(reshape);
  glutIdleFunc(update);
  glutKeyboardFunc(keyboardPressed);
  glutMouseFunc(mousePressed);
  glutPassiveMotionFunc(mouseMotion);
  glutMotionFunc(mouseMotion);
  glutMenuStatusFunc(menuStatus);

  glClearColor(0.1f, 0.2f, 1.0f, 1.0f);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  int skinMenu = glutCreateMenu(skinMenuHandler);
  glutAddMenuEntry("Ship", ship);
  glutAddMenuEntry("Shark", shark);

  int menu = glutCreateMenu(menuHandler);
  glutSetMenu(menu);
  glutAddMenuEntry("Quit (esc)", MENU_QUIT);
  glutAddMenuEntry("Add Drum (a)", MENU_ADD_DRUM);
  glutAddMenuEntry("Add Enemy (e)", MENU_ADD_ENEMY);
  glutAddMenuEntry("Reset (r)", MENU_RESET);
  glutAddSubMenu("Change Skin", skinMenu);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  srand(time(NULL));

  glutMainLoop();
  
  return 1;
}
