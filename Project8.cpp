#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <stdlib.h> // standard definitions
#include <stdio.h> // standard I/O

float tubestart = -4.0f;
float tubespeed = 0.02f;

float tube1x = tubestart;
float tube2x = tubestart;
float tube3x = tubestart;
float tube4x = tubestart;
float tube5x = tubestart;

float tube1y = float(rand() % 101) / 20.0 + 1.5;
float tube2y = float(rand() % 101) / 20.0 + 1.5;
float tube3y = float(rand() % 101) / 20.0 + 1.5;
float tube4y = float(rand() % 101) / 20.0 + 1.5;
float tube5y = float(rand() % 101) / 20.0 + 1.5;

float playerpos = 5.0f;
bool flap = false;
bool alive = true;
bool scoreprinted = true;
int score = -2;

int frame = 0;
int timenotflapped = 0;
int flapheight = 0;

void draw() {
  glBegin(GL_QUADS);
  //floor
  glColor3f(0,0.6,0);
    glVertex3f(-15,-10,0);
    glVertex3f(-15,10,0);
    glVertex3f(15,10,0);
    glVertex3f(15,-10,0);

  //ceiling
  glColor3f(0.9,0.9,0.9);
    glVertex3f(-15,-10,10);
    glVertex3f(-15,10,10);
    glVertex3f(15,10,10);
    glVertex3f(15,-10,10);

    //back wall
  glColor3f(0.47, 0.8, 0.88);
    glVertex3f(-15,0,0);
    glVertex3f(-15,0,10);
    glVertex3f(15,0,10);
    glVertex3f(15,0,0);



  glEnd();
}

void drawCircle(float x, float y, float z, float radius)
{
	float twicePi = 2.0f * M_PI;
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(x, y, z);
		for (int i = 0; i <= 16; i++)
		{
			glVertex3f(
				x + (radius * cos(i *  twicePi / 16)),
			    y + (radius * sin(i * twicePi / 16)),
				z
			);
		}
	glEnd();
}

void drawCylinder(float x, float y, float z, float radiusbot, float radiustop, float height)
{
	float twicePi = 2.0f * M_PI;
	glBegin(GL_QUADS);
		for (int i = 0; i <= 16; i++)
		{
			glVertex3f(
				x + (radiusbot * cos(i *  twicePi / 16)),
			    y + (radiusbot * sin(i * twicePi / 16)),
				z
			);
			glVertex3f(
				x + (radiustop * cos(i *  twicePi / 16)),
			    y + (radiustop * sin(i * twicePi / 16)),
				z + height
			);
			glVertex3f(
				x + (radiustop * cos((i+1) *  twicePi / 16)),
			    y + (radiustop * sin((i+1) * twicePi / 16)),
				z + height
			);
			glVertex3f(
				x + (radiusbot * cos((i+1) *  twicePi / 16)),
			    y + (radiusbot * sin((i+1) * twicePi / 16)),
				z
			);
		}
	glEnd();
}

void drawTube(float tubex, float tubey)
{
  glColor3f(0.1, 0.46, 0.17);
  // bottom tube
  drawCylinder(tubex-0.5, 1.6, 0, 0.45, 0.45, tubey-0.2);
  drawCylinder(tubex-0.5, 1.6, tubey-0.2, 0.5, 0.5, 0.2);
  drawCircle(tubex-0.5, 1.6, tubey, 0.5);
  glColor3f(0,0,0);
  drawCircle(tubex-0.5, 1.6, tubey, 0.4);

  // top tube
  glColor3f(0.1, 0.46, 0.17);
  drawCylinder(tubex-0.5, 1.6, tubey+2.2, 0.45, 0.45, 10);
  drawCylinder(tubex-0.5, 1.6, tubey+2, 0.5, 0.5, 0.2);
  drawCircle(tubex-0.5, 1.6, tubey+2, 0.5);
  glColor3f(0,0,0);
  drawCircle(tubex-0.5, 1.6, tubey+2, 0.4);

}

void drawPlayer(float z)
{
  // body
  glColor3f(0.91, 0.43, 0.2);
  glBegin(GL_QUADS);
    glVertex3f(1.6, 2, z);
    glVertex3f(0.8,2,z);
    glVertex3f(0.8,2,z+0.8);
    glVertex3f(1.6,2,z+0.8);

    glVertex3f(1.6, 1.2, z);
    glVertex3f(0.8,1.2,z);
    glVertex3f(0.8,1.2,z+0.8);
    glVertex3f(1.6,1.2,z+0.8);

    glVertex3f(1.6, 1.2, z);
    glVertex3f(1.6,2,z);
    glVertex3f(1.6,2,z+0.8);
    glVertex3f(1.6,1.2,z+0.8);

    glVertex3f(0.8, 1.2, z);
    glVertex3f(0.8,2,z);
    glVertex3f(0.8,2,z+0.8);
    glVertex3f(0.8,1.2,z+0.8);

    glVertex3f(1.6, 1.2, z+0.8);
    glVertex3f(1.6,2,z+0.8);
    glVertex3f(0.8,2,z+0.8);
    glVertex3f(0.8,1.2,z+0.8);

    glVertex3f(1.6, 1.2, z);
    glVertex3f(1.6,2,z);
    glVertex3f(0.8,2,z);
    glVertex3f(0.8,1.2,z);

    // wings
    glColor3f(1,1,1);
    glVertex3f(1,2,z+0.3);
    glVertex3f(1.4,2,z+0.3);
    glVertex3f(1.4,2.4,z+0.3);
    glVertex3f(1.1,2.4,z+0.3);


    // eye
    glVertex3f(0.9, 2, z+0.4);
    glVertex3f(0.9, 2, z+0.7);
    glVertex3f(1.2, 2, z+0.7);
    glVertex3f(1.2, 2, z+0.4);

    glColor3f(0,0,0);
    glVertex3f(0.92, 2, z+0.42);
    glVertex3f(0.92, 2, z+0.6);
    glVertex3f(1.1, 2, z+0.6);
    glVertex3f(1.1, 2, z+0.42);
  glEnd();

  // beak
  glBegin(GL_TRIANGLES);
    glColor3f(0.91, 0.77, 0.2);
    glVertex3f(0.8,1.6,z+0.3);
    glVertex3f(0.8,1.6,z+0.6);
    glVertex3f(0.4,1.6,z+0.3);
  glEnd();
}

void gameover()
{
  glColor3f(0,0,0);
  glBegin(GL_QUADS);
    glVertex3f(-5,2.5,6);
    glVertex3f(5,2.5,6);
    glVertex3f(5,2.5,8);
    glVertex3f(-5,2.5,8);

    glColor3f(1,1,0.1);
    glVertex3f(-0.8,2.5,6.2);
    glVertex3f(0.8,2.5,6.2);
    glVertex3f(0.8,2.5,7.8);
    glVertex3f(-0.8,2.5,7.8);

    glColor3f(0,0,0);
    glVertex3f(-0.6,2.5,6.4);
    glVertex3f(-0.4,2.5,6.4);
    glVertex3f(-0.4,2.5,6.6);
    glVertex3f(-0.6,2.5,6.6);

    glVertex3f(0.6,2.5,6.4);
    glVertex3f(0.4,2.5,6.4);
    glVertex3f(0.4,2.5,6.6);
    glVertex3f(0.6,2.5,6.6);

    glVertex3f(-0.4,2.5,6.6);
    glVertex3f(-0.4,2.5,6.8);
    glVertex3f(0.4,2.5,6.8);
    glVertex3f(0.4,2.5,6.6);

    glVertex3f(0.4,2.5,7.4);
    glVertex3f(0.4,2.5,7);
    glVertex3f(0.2,2.5,7);
    glVertex3f(0.2,2.5,7.4);

    glVertex3f(-0.4,2.5,7.4);
    glVertex3f(-0.4,2.5,7);
    glVertex3f(-0.2,2.5,7);
    glVertex3f(-0.2,2.5,7.4);

  glEnd();

}


void processNormalKeys(unsigned char keypress, int x1, int y1)
{
  if (keypress == 'f') {
    if (timenotflapped > 6)
    {
      flap = true;
      flapheight = 6;
      timenotflapped = 0;
    }
  }
}


void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  draw();

  if (alive)
  {
    tube1x += tubespeed;

    if (frame > 200)
    {
      tube2x += tubespeed;
    }
    if (frame > 400)
    {
      tube3x += tubespeed;
    }
    if (frame > 600)
    {
      tube4x += tubespeed;
    }
    if (frame > 800)
    {
      tube5x += tubespeed;
    }

    if (tube1x > 16.0)
    {
      tube1x = tubestart;
      tube1y = float(rand() % 101) / 20.0 + 1.5;
    }
    if (tube2x > 16.0)
    {
      tube2x = tubestart;
      tube2y = float(rand() % 101) / 20.0 + 1.5;
    }
    if (tube3x > 16.0)
    {
      tube3x = tubestart;
      tube3y = float(rand() % 101) / 20.0 + 1.5;
    }
    if (tube4x > 16.0)
    {
      tube4x = tubestart;
      tube4y = float(rand() % 101) / 20.0 + 1.5;
    }
    if (tube5x > 16.0)
    {
      tube5x = tubestart;
      tube5y = float(rand() % 101) / 20.0 + 1.5;
    }

    timenotflapped++;
    playerpos -= 0.00002 * timenotflapped * timenotflapped;

    if (flap && flapheight > 0)
    {
      playerpos += 0.006 * flapheight * flapheight;
      flapheight--;
    }
    if (frame % 200 == 0)
    {
      score++;
    }
    frame++;
  }

  if (tube1x > 0.8 && tube1x < 2.6 && (tube1y > playerpos || playerpos > tube1y + 1.2))
  {
    alive = false;
  }
  if (tube2x > 0.8 && tube2x < 2.6 && (tube2y > playerpos || playerpos > tube2y + 1.2))
  {
    alive = false;
  }
  if (tube3x > 0.8 && tube3x < 2.6 && (tube3y > playerpos || playerpos > tube3y + 1.2))
  {
    alive = false;
  }
  if (tube4x > 0.8 && tube4x < 2.6 && (tube4y > playerpos || playerpos > tube4y + 1.2))
  {
    alive = false;
  }
  if (tube5x > 0.8 && tube5x < 2.6 && (tube5y > playerpos || playerpos > tube5y + 1.2))
  {
    alive = false;
  }
  if (playerpos < 1)
  {
    alive = false;
  }
  if (playerpos > 8.2)
  {
    alive = false;
  }


  drawTube(tube1x, tube1y);
  drawTube(tube2x, tube2y);
  drawTube(tube3x, tube3y);
  drawTube(tube4x, tube4y);
  drawTube(tube5x, tube5y);
  drawPlayer(playerpos);
  if (!alive)
  {
    gameover();
    if (scoreprinted)
    {
      printf("------------------------------------\nYour score was: ");
      printf("%d", score);
      printf("\n------------------------------------");
      scoreprinted = false;
    }
  }

  glFlush();
  glutSwapBuffers();
}


void timer(int v) {
  glLoadIdentity();
  gluLookAt(0,10,5,
    0,0,5,
    0,0,1
  );
  glutPostRedisplay();
  glutTimerFunc(1000/60.0, timer, v);
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 800);
  glutCreateWindow("Project 8 - Flappy Bird");
  printf("------------------------------------\n");
  printf("Project 8 - Flappy Bird\n");
  printf("Rylan Casanova and Dylan Olthoff\n\n");
  printf("Instructions: Avoid the Obstacles\n");
  printf("Controls: Press 'f' to flap\n");
  printf("------------------------------------\n");
  glutReshapeFunc(reshape);
  glutKeyboardFunc(processNormalKeys);
  glutTimerFunc(100, timer, 0);
  glutDisplayFunc(display);
  glutMainLoop();
}