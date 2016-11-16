//  определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "game.h"
#include <iostream>

int RESOLUTION_WIDTH = 960;
int RESOLUTION_HEIGHT = 540;
float RATIO = (float)RESOLUTION_WIDTH / RESOLUTION_HEIGHT;
char* TITLE = "EvA";
float FRAMES_PER_SECOND;
float TIME_PER_FRAME;

Game * game;
FontHelper * fpsFont;

void calculateFrameRate()
{
	static float framesPerSecond = 0.0f;
	static float lastTime = 0.0f;
	float currentTime = GetTickCount() * 0.001f;
	++framesPerSecond;
	if (currentTime - lastTime > 1.0f)
	{
		lastTime = currentTime;
		FRAMES_PER_SECOND = framesPerSecond;
		framesPerSecond = 0;
	}
}

void printFrameRate()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glColor3f(1.0f, 1.0f, 1.0f);

	wchar_t buf[256];
	swprintf(buf, sizeof(buf), L"%f|%f", FRAMES_PER_SECOND, TIME_PER_FRAME);
	fpsFont->Print(10, 20, buf);

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glutPostRedisplay();
}

void idle()
{

#define LIMIT_OF_FPS
#ifdef LIMIT_OF_FPS
	static float previousClock = glutGet(GLUT_ELAPSED_TIME);
	static float clock = glutGet(GLUT_ELAPSED_TIME);
	static float deltaT;
	clock = glutGet(GLUT_ELAPSED_TIME);
	deltaT = clock - previousClock;

	if (deltaT < 15) return;                  // ОГРАНИЧЕНИЕ (каждые 15мс отрисовка 1го кадра)!!!

	TIME_PER_FRAME = deltaT;
	previousClock = clock;
#endif

	calculateFrameRate();	
	glutPostRedisplay();

}


void keyboardSpecial(int key, int x, int y)
{
	game->GetKeyboardHandler()->SpecialDown(key, x, y);
}

void keyboardSpecialUp(int key, int x, int y)
{
	game->GetKeyboardHandler()->SpecialUp(key, x, y);
}

void keyboard(unsigned char key, int x, int y)
{
	game->GetKeyboardHandler()->Up(key, x, y);
};

void keyboardUp(unsigned char key, int x, int y)
{
	game->GetKeyboardHandler()->Down(key, x, y);
};

void test()
{
	printFrameRate();
	game->Frame();
};

void display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0);
	test();                        /// кадр! ///
	glutSwapBuffers();
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
	glutInitWindowPosition(GLUT_SCREEN_WIDTH, GLUT_SCREEN_HEIGHT / 2);
	glutCreateWindow(TITLE);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(keyboardSpecial);
	glutSpecialUpFunc(keyboardSpecialUp);
	glutDisplayFunc(display);
	glewInit();

	game = new Game();
	fpsFont = new FontHelper("fonts/arial.ttf", 16, -0.2);

	glutMainLoop();
    return 0;
}

