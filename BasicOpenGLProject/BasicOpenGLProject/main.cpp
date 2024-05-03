#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <math.h>

using namespace std;


//=================================================================================================
// CALLBACKS
//=================================================================================================

//-----------------------------------------------------------------------------
// CALLBACK DOCUMENTATION
// https://www.opengl.org/resources/libraries/glut/spec3/node45.html
// http://freeglut.sourceforge.net/docs/api.php#WindowCallback
//-----------------------------------------------------------------------------

int point = 0;
bool ended = false;
float movement = 0.3f;
float playerPlace = 0.05f;
float rockPlace = 0.0f;
float goldPlace = 0.0f;
bool rock = false;
bool gold = true;

void idle_func()
{
	//uncomment below to repeatedly draw new frames
	//glutPostRedisplay();
}

void timer(int) {
	glutPostRedisplay();
	
	glutTimerFunc(1000, timer, 0);
}

void reshape_func( int width, int height )
{
	glViewport( 0, 0, width, height );
	glutPostRedisplay();
}

void textBox(float x, float y, string String) {
	glRasterPos2i(x, y);
	for (int i = 0; i < String.size(); i++)
	{
		glScaled(0.2, 0.2, 1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);
	}
}

void keyboard_func( unsigned char key, int x, int y )
{
	switch( key )
	{
		

		case 'a':
		{
				playerPlace -= movement;
		break;

		}

		case 'd':
		{
				playerPlace += movement;
			break;
		}

		// Exit on escape key press
		case '\x1B':
		{
			exit( EXIT_SUCCESS );
			break;
		}
	}

	glutPostRedisplay();
}

void start() {

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
}

//i got an idea for a square class

void player() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex2f(playerPlace, -0.85f);
		glVertex2f(playerPlace-.10f, -0.85f);
		glVertex2f(playerPlace-.10f, -0.95f);
		glVertex2f(playerPlace, -0.95f);
	glEnd();
}


float random() {
	int randX = rand() % 100;
	float x = 0.0f;
	if (randX < 20)
		x = -movement*2;
	else if (randX >= 20 && randX < 39)
		x = -movement;
	else if (randX >= 60 && randX < 79)
		x = movement;
	else if (randX >= 80)
		x = movement*2;
	return x;
}
//

void downwardRock() {
	if (!ended) {
		if (playerPlace == rockPlace && rock) {
			ended = true;
		}
		else
			point++;
		rock = false;

	}
}

void downwardGold() {
	if (!ended) {
		if (playerPlace == goldPlace && gold) {
			point += 2;
		}
		else
			point++;
		gold = false;

	}
}

void spawnRock() {
	if (!ended) {
		rock = true;

		float x = random();
		glColor3f(0.5f, 0.5f, 0.5f);
		glBegin(GL_QUADS);
		glVertex2f(0.05f + x, 0.95f);
		glVertex2f(-0.05f + x, 0.95f);
		glVertex2f(-0.05f + x, 0.85f);
		glVertex2f(0.05f + x, 0.85f);
		glEnd();
		rockPlace = 0.05f + x;

	}
}

void spawnGold() {
	if (!ended){
		gold = true;

		glColor3f(1.0f, 1.0f, 0.0f);
		float x = random();
		glBegin(GL_QUADS);
		glVertex2f(0.05f + x, 0.95f);
		glVertex2f(-0.05f + x, 0.95f);
		glVertex2f(-0.05f + x, 0.85f);
		glVertex2f(0.05f + x, 0.85f);
		glEnd();
		goldPlace = 0.05f + x;
	}
	
}

void static gameOver() {
	if (ended) {
		glColor3f(0.0f, 0.0f, 0.0f);
		string help = std::to_string(point);
		glColor3f(1.0f, 1.0f, 1.0f);
		textBox(-0.0f, -0.0f, "Final Score: " + help);
	}
	
}






//=================================================================================================
// RENDERING
//=================================================================================================

void display_func( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	


	player();

	glColor3f(0.5f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex2f(-0.7f, 1.0f);
		glVertex2f(-1.0f, 1.0f);
		glVertex2f(-1.0f, -1.0f);
		glVertex2f(-0.7f, -1.0f);
	glEnd();

	glColor3f(0.5f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex2f(0.7f, 1.0f);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);
		glVertex2f(0.7f, -1.0f);
	glEnd();

	

	int x = rand()%100;

	if (x <= 80) {
		spawnRock();
		
	}
	else {
		spawnGold();
	}


	downwardRock();
	downwardGold();
	gameOver();
	

	glutSwapBuffers();
}



//=================================================================================================
// INIT
//=================================================================================================

void init( void )
{
	// Print some info
	std::cout << "Vendor:         " << glGetString( GL_VENDOR   ) << "\n";
	std::cout << "Renderer:       " << glGetString( GL_RENDERER ) << "\n";
	std::cout << "OpenGL Version: " << glGetString( GL_VERSION  ) << "\n\n";

	// Set the background color
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	std::cout << "Finished initializing...\n\n";
}

//=================================================================================================
// MAIN
//=================================================================================================

int main( int argc, char** argv )
{
	glutInit( &argc, argv );

	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( 800, 600 );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

	glutCreateWindow( "Falling Rocks: Try Not to Die" );

	glutDisplayFunc( display_func );
	glutIdleFunc( idle_func );
	glutReshapeFunc( reshape_func );
	glutKeyboardFunc( keyboard_func );
	glutTimerFunc(0, timer, 0);

	init();

	glutMainLoop();

	return EXIT_SUCCESS;
}
