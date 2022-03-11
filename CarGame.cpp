//CAR GAME
//Code by Rhean Keith


#include "include\freeglut.h"	// OpenGL toolkit - in the local shared folder
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <stdio.h>
#include <math.h>
#include <random>
#include <time.h>

//collision boxes
struct collisionBox2D
{
	float carX, carY, carW, carH;
	float boundX, boundY, boundW, boundH;
	float ob1x, ob1y, ob2x, ob2y, ob3x, ob3y, ob4x, ob4y, ob5x, ob5y;
	float ob1w, ob1h, ob2w, ob2h, ob3w, ob3h, ob4w, ob4h, ob5w, ob5h;
	float exitX, exitY, exitW, exitH;
};

struct collisionBox2D boundary;
struct collisionBox2D exitPoint;
struct collisionBox2D car;

struct collisionBox2D obstacle1;
struct collisionBox2D obstacle2;
struct collisionBox2D obstacle3;
struct collisionBox2D obstacle4;
struct collisionBox2D obstacle5;


//set up some constants
#define X_CENTRE 0.0      /* centre point of square */
#define Y_CENTRE 0.0
#define LENGTH   1.0      /* lengths of sides of square */
#define StartX_CENTRE -0.6	  /* centre point of the start point */
#define StartY_CENTRE -0.90
#define ExitX_CENTRE 0.6	  /* centre point of the exit point */
#define ExitY_CENTRE 0.90
//#define CarX_CENTRE -0.6		 /* centre point of the car */
//#define CarY_CENTRE -0.70

GLfloat red = 1.0, green = 1.0, blue = 1.0;

//moving the car
GLfloat carX = 0, carY = 0;
GLfloat x = 0, y = 0;

//grid for exitPoint
GLfloat eX = 0, eY = 0;
GLfloat eW = 0, eH = 0;

//movement for obstacles
GLfloat ob1x = 0, ob1y = 0, ob2x = 0, ob2y = 0, ob3x = 0, ob3y = 0, ob4x = 0, ob4y = 0, ob5x = 0, ob5y = 0;
GLfloat obX = 0, obY = 0;

//int variables for games
int score = 50;
int speed = 4;


using namespace std;


//calling draw functions at top
void drawBoundary(GLfloat length, GLfloat x, GLfloat y);
void drawStart(GLfloat length);
void drawExit(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
void drawCar(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
//functions to draw the 5 different obstacles
void drawObstacle1(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
void drawObstacle2(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
void drawObstacle3(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
void drawObstacle4(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
void drawObstacle5(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h);


/* reshape callback function
executed when window is moved or resized */
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	/* uses orthographic (parallel) projection
	use xmin = -1, xmax = 1
	ymin = -1, ymax = 1
	znear = -1, zfar = 1 - not relevant here (2D) */
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

//function for drawing boundary
void drawBoundary(GLfloat length, GLfloat x, GLfloat y)
{
	//changing thickness of the line
	glLineWidth(1.0);

	//drawn using line loop
	glBegin(GL_LINE_LOOP);

	//drawing of the boundary
	glVertex2f(X_CENTRE - LENGTH / 1.1, Y_CENTRE - LENGTH / 1.1);
	glVertex2f(X_CENTRE - LENGTH / 1.1, Y_CENTRE + LENGTH / 1.1);
	glVertex2f(X_CENTRE + LENGTH / 1.1, Y_CENTRE + LENGTH / 1.1);
	glVertex2f(X_CENTRE + LENGTH / 1.1, Y_CENTRE - LENGTH / 1.1);

	glEnd();

	//executes the drawing
	glFlush();
}

//function for drawing starting point
 void drawStart(GLfloat length)
{
	//changing thickness of the line
	glLineWidth(1.0);

	//drawn using line loop
	glBegin(GL_POLYGON);

	//drawing of the starting point
	glVertex2f(StartX_CENTRE - length / 4, StartY_CENTRE - length / 30);
	glVertex2f(StartX_CENTRE - length / 4, StartY_CENTRE + length / 30);
	glVertex2f(StartX_CENTRE + length / 4, StartY_CENTRE + length / 30);
	glVertex2f(StartX_CENTRE + length / 4, StartY_CENTRE - length / 30);

	glEnd();

	//executes the drawing
	glFlush();
}

 //function for drawing exit point
 void drawExit(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
 {
	 //changing thickness of the line
	 glLineWidth(1.0);

	 //drawn using line loop
	 glBegin(GL_POLYGON);

	 //drawing of the exit point
	 glVertex2f(ExitX_CENTRE - length / 4, ExitY_CENTRE - length / 30);
	 glVertex2f(ExitX_CENTRE - length / 4, ExitY_CENTRE + length / 30);
	 glVertex2f(ExitX_CENTRE + length / 4, ExitY_CENTRE + length / 30);
	 glVertex2f(ExitX_CENTRE + length / 4, ExitY_CENTRE - length / 30);

	 glEnd();

	 //executes the drawing
	 glFlush();
 }

 //function for drawing the car
 void drawCar(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
 {

	 //changing thickness of the line
	 glLineWidth(1.0);

	 //drawn using line loop
	 glBegin(GL_POLYGON);

	 //drawing of the car
	 glVertex2f(x - length / 8, y - length / 8);
	 glVertex2f(x - length / 8, y + length / 8);
	 glVertex2f(x + length / 8, y + length / 8);
	 glVertex2f(x + length / 8, y - length / 8);

	 glEnd();

	 //executes the drawing
	 glFlush();
 }

 //function for level reset that randomizes obstacles
 void resetLevel()
 {
	 //if car reaches exit point, spawn it back to starting point
	 srand(static_cast <unsigned> (time(0)));
	 float randY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 0.85);
	 float randY2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 0.85);
	 float randY3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 0.85);
	 float randY4 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 0.85);
	 float randY5 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 0.85);

	 //exit point spawn
	 exitPoint.exitX = eX + 0.6;
	 exitPoint.exitY = eY + 0.9;

	 //car spawn
	 car.carX = x - 0.6;
	 car.carY = y - 0.85;
	 //obstacle spawns
	 obstacle1.ob1x = obX - 0.7;
	 obstacle1.ob1y = randY;
	 obstacle2.ob2x = obX - 0.3;
	 obstacle2.ob2y = randY2;
	 obstacle3.ob3x = obX + 0.2;
	 obstacle3.ob3y = randY3;
	 obstacle4.ob4x = obX + 0.4;
	 obstacle4.ob4y = randY4;
	 obstacle5.ob5x = obX + 0.4;
	 obstacle5.ob5y = randY5;

 }

 bool checkAABBcollision()
 {
	 //obstacle 1
	 if (car.carX < obstacle1.ob1x + obstacle1.ob1w && car.carX + car.carW > obstacle1.ob1x && car.carY < obstacle1.ob1y + obstacle1.ob1h && car.carY + car.carH > obstacle1.ob1y)
	 {
		 return true;
	 }
	 //obstacle 2
	 else if (car.carX < obstacle2.ob2x + obstacle2.ob2w && car.carX + car.carW > obstacle2.ob2x && car.carY < obstacle2.ob2y + obstacle2.ob2h && car.carY + car.carH > obstacle2.ob2y)
	 {
		 return true;
	 }
	 //obstacle 3
	 else if (car.carX < obstacle3.ob3x + obstacle3.ob3w && car.carX + car.carW > obstacle3.ob3x && car.carY < obstacle3.ob3y + obstacle3.ob3h && car.carY + car.carH > obstacle3.ob3y)
	 {
		 return true;
	 }
	 //obstacle 4
	 else if (car.carX < obstacle4.ob4x + obstacle4.ob4w && car.carX + car.carW > obstacle4.ob4x && car.carY < obstacle4.ob4y + obstacle4.ob4h && car.carY + car.carH > obstacle4.ob4y)
	 {
		 return true;
	 }
	 //obstacle 5
	 else if (car.carX < obstacle5.ob5x + obstacle5.ob5w && car.carX + car.carW > obstacle5.ob5x && car.carY < obstacle5.ob5y + obstacle5.ob5h && car.carY + car.carH > obstacle5.ob5y)
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }

 }

 //collision for obstacles
 bool obstacleCollision()
 {
	 if (checkAABBcollision()==true)
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }
 }

 //keyboard movement for carGame
 void keyboard(unsigned char key, int x, int y)
 {
	 switch (key)
	 {
	 case 'w':
		 //if statement
		 if (car.carY > 0.85)
		 {
			 car.carY += 0;
			 glutPostRedisplay();
		 }
		 //else if that resets level when reaching exit
		 else if (car.carX < exitPoint.exitX + exitPoint.exitW && car.carX + exitPoint.exitW > exitPoint.exitX && car.carY < exitPoint.exitY + exitPoint.exitH && car.carY + car.carH > exitPoint.exitY)
		 {
			 resetLevel();
			 glutPostRedisplay();
		 }
		 //checks if car collides with obstacle
		 else if (checkAABBcollision()==true)
		 {
			 car.carY += 0;
			 glutPostRedisplay();
		 }
		 else
		 {
			 car.carY += 0.05;
			 glutPostRedisplay();
		 }
		 break;
	 case 'a':
		 //if
		 if (car.carX < -0.74)
		 {
			 car.carX -= 0;
			 glutPostRedisplay();
		 }
		 //else if that resets level when reaching exit
		 /*else if (car.carX < exitPoint.exitX + exitPoint.exitW && car.carX + exitPoint.exitW > exitPoint.exitX && car.carY < exitPoint.exitY + exitPoint.exitH && car.carY + car.carH > exitPoint.exitY)
		 {
			 resetLevel();
		 }
		 */
		 /*checks if car collides with obstacle
		 else if (checkAABBcollision() == true)
		 {
			 car.carX -= 0;
			 glutPostRedisplay();
		 }
		 */
		 else
		 {
			 car.carX -= 0.05;
			 glutPostRedisplay();
		 }
		 break;
	 case 's':
		 //if
		 if (car.carY < -0.85)
		 {
			 car.carY -= 0;
			 glutPostRedisplay();
		 }
		 //else if that resets level when reaching exit
		 /*else if (car.carX < exitPoint.exitX + exitPoint.exitW && car.carX + exitPoint.exitW > exitPoint.exitX && car.carY < exitPoint.exitY + exitPoint.exitH && car.carY + car.carH > exitPoint.exitY)
		 {
			 resetLevel();
		 }
		 */
		 /*checks if car collides with obstacle
		 else if (checkAABBcollision() == true)
		 {
			 car.carY -= 0;
			 glutPostRedisplay();
		 }
		 */
		 else
		 {
			 car.carY -= 0.05;
			 glutPostRedisplay();
		 }
		 break;
	 case 'd':
		 //if
		 if (car.carX > 0.74)
		 {
			 car.carX += 0;
			 glutPostRedisplay();
		 }
		 /*else if (car.carX < exitPoint.exitX + exitPoint.exitW && car.carX + exitPoint.exitW > exitPoint.exitX && car.carY < exitPoint.exitY + exitPoint.exitH && car.carY + car.carH > exitPoint.exitY)
		 {
			 resetLevel();
		 }
		 */
		 /*checks if car collides with obstacle
		 else if (checkAABBcollision() == true)
		 {
			 car.carX += 0;
			 glutPostRedisplay();
		 }
		 */
		 else
		 {
			 car.carX += 0.05;
			 glutPostRedisplay();
		 }
		 break;
	 }
	 glutPostRedisplay();
 }
 
 //function for drawing the obstacle
 void drawObstacle1(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
 {
	 //changing thickness of the line
	 glLineWidth(1.0);

	 //drawn using quads
	 glBegin(GL_QUADS);

	 //drawing obstacle 1
	 glVertex2f(x - length / 7, y - length / 7);
	 glVertex2f(x - length / 7, y + length / 7);
	 glVertex2f(x + length / 7, y + length / 7);
	 glVertex2f(x + length / 7, y - length / 7);

	 glEnd();

	 //executes the drawing
	 glFlush();


 }

 //function for drawing the 2nd obstacle
 void drawObstacle2(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
 {
	 //changing thickness of the line
	 glLineWidth(1.0);

	 //drawn using polygon
	 glBegin(GL_QUADS);

	 //drawing obstacle 1
	 glVertex2f(x - length / 7, y - length / 7);
	 glVertex2f(x - length / 7, y + length / 7);
	 glVertex2f(x + length / 7, y + length / 7);
	 glVertex2f(x + length / 7, y - length / 7);

	 glEnd();

	 //executes the drawing
	 glFlush();


 }

 //function for drawing the 3rd obstacle
 void drawObstacle3(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
 {
	 //changing thickness of the line
	 glLineWidth(1.0);

	 //drawn using polygon
	 glBegin(GL_QUADS);

	 //drawing obstacle 1
	 glVertex2f(x - length / 7, y - length / 7);
	 glVertex2f(x - length / 7, y + length / 7);
	 glVertex2f(x + length / 7, y + length / 7);
	 glVertex2f(x + length / 7, y - length / 7);

	 glEnd();

	 //executes the drawing
	 glFlush();


 }

 //function for drawing the 4th obstacle
 void drawObstacle4(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
 {
	 //changing thickness of the line
	 glLineWidth(1.0);

	 //drawn using polygon
	 glBegin(GL_QUADS);

	 //drawing obstacle 1
	 glVertex2f(x - length / 7, y - length / 7);
	 glVertex2f(x - length / 7, y + length / 7);
	 glVertex2f(x + length / 7, y + length / 7);
	 glVertex2f(x + length / 7, y - length / 7);

	 glEnd();

	 //executes the drawing
	 glFlush();


 }

 //function for drawing the 5th obstacle
 void drawObstacle5(GLfloat length, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
 {
	 //changing thickness of the line
	 glLineWidth(1.0);

	 //drawn using polygon
	 glBegin(GL_QUADS);

	 //drawing obstacle 5
	 glVertex2f(x - length / 7, y - length / 7);
	 glVertex2f(x - length / 7, y + length / 7);
	 glVertex2f(x + length / 7, y + length / 7);
	 glVertex2f(x + length / 7, y - length / 7);

	 glEnd();

	 //executes the drawing
	 glFlush();


 }


/* display callback function
called whenever contents of window need to be re-displayed */
//this is the all important drawing method - all drawing code goes in here
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);   /* clear window */
	glColor3f(red, green, blue);        /* white drawing objects */
   
    //calling boundary to draw
	drawBoundary(1.0, boundary.boundX, boundary.boundY);
	//calling start point to draw
	glColor3f(1.0, 0.0, 0.0);
	drawStart(0.6);
	//calling exit point to draw
	glColor3f(0.0, 1.0, 0.0);
	drawExit(0.6, exitPoint.exitX, exitPoint.exitY, exitPoint.exitW, exitPoint.exitH);
	//calling car to draw
	glColor3f(1.0, 1.0, 1.0);
	drawCar(0.6, car.carX, car.carY, car.carW, car.carH);
	//calling obstacles to draw
	glColor3f(0.0, 0.0, 1.0);
	drawObstacle1(0.6, obstacle1.ob1x, obstacle1.ob1y, obstacle1.ob1w, obstacle1.ob1h);
	//obstacle 2
	glColor3f(0.0, 1.0, 1.0);
	drawObstacle2(0.6, obstacle2.ob2x, obstacle2.ob2y, obstacle2.ob2w, obstacle2.ob2h);
	//obstacle 3
	glColor3f(1.0, 0.0, 1.0);
	drawObstacle3(0.6, obstacle3.ob3x, obstacle3.ob3y, obstacle3.ob3w, obstacle3.ob3h);
	//obstacle 4
	glColor3f(1.0, 0.0, 0.0);
	drawObstacle4(0.6, obstacle4.ob4x, obstacle4.ob4y, obstacle4.ob4w, obstacle4.ob4h);
	//obstacle 5
	glColor3f(0.0, 1.0, 0.0);
	drawObstacle5(0.6, obstacle5.ob5x, obstacle5.ob5y, obstacle5.ob5w, obstacle5.ob5h);


	glFlush();  /* execute drawing commands in buffer */
}

/* graphics initialisation */
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);   /* window will be cleared to black */
}

//rename this to main(...) and change example 2 to run this main function
int main(int argc, char** argv)
{
	//spawning obstacles at random positions
	srand(static_cast <unsigned> (time(0)));
	float randY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/0.85);
	float randY2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/0.85);
	float randY3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/0.85);
	float randY4 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/0.85);
	float randY5 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/0.85);

	//exit point spawn
	exitPoint.exitX = eX + 0.6;
	exitPoint.exitY = eY + 0.9;
	exitPoint.exitW = eW + 0.2;
	exitPoint.exitH = eH + 0.2;

	//car spawn
	car.carX = x - 0.6;
	car.carY = y - 0.85;
	car.carW = 0.2;
	car.carH = 0.2;

	//obstacle 1 spawns
	obstacle1.ob1x = obX - 0.7;
	obstacle1.ob1y = randY;
	obstacle1.ob1w = 0.2;
	obstacle1.ob1h = 0.2;
	//obstacle 2 spawns
	obstacle2.ob2x = obX - 0.3;
	obstacle2.ob2y = randY2;
	obstacle2.ob2w = 0.2;
	obstacle2.ob2h = 0.2;
	//obstacle 3 spawns
	obstacle3.ob3x = obX + 0.2;
	obstacle3.ob3y = randY3;
	obstacle3.ob3w = 0.2;
	obstacle3.ob3h = 0.2;
	//obstacle 4 spawns
	obstacle4.ob4x = obX + 0.4;
	obstacle4.ob4y = randY4;
	obstacle4.ob4w = 0.2;
	obstacle4.ob4h = 0.2;
	//obstacle 5 spawns
	obstacle5.ob5x = obX + 0.4;
	obstacle5.ob5y = randY5;
	obstacle5.ob5w = 0.2;
	obstacle5.ob5h = 0.2;


	/* window management code ... */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	/* 500 pixels, height = 500 pixels */
	glutInitWindowSize(600, 600);
	/* window upper left corner at (100, 100) */
	glutInitWindowPosition(100, 100);
	/* title of window */
	glutCreateWindow("Car Game");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	/* calling for keyboard input */
	glutKeyboardFunc(keyboard);
	
	cout << "WELCOME TO CAR GAME \n" << endl;
	cout << "-MADE BY RHEAN KEITH- \n" << endl;
	cout << "W - MOVE UP \n" << endl;
	cout << "A - MOVE LEFT \n" << endl;
	cout << "S - MOVE DOWN \n" << endl;
	cout << "D - MOVE RIGHT \n" << endl;
	cout << "SCORE \n" << endl;
	cout << score << endl;

	glutMainLoop();
	return 0;

}
