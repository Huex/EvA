#include "game.h"
#include <iostream>
#include<OpenGL/glew.h>
#include<OpenGL/glut.h>
#include "font.h"
#include <windows.h>

int RESOLUTION_HEIGHT;
int RESOLUTION_WIDTH;
float RATIO;
char* TITLE = "EvA";
float FRAMES_PER_SECOND;
float TIME_PER_FRAME;

Game * game;

void reshape(int width, int height)
{	

	RESOLUTION_WIDTH = width;
	RESOLUTION_HEIGHT = height;
	float ratio = RESOLUTION_WIDTH * 1.0 / RESOLUTION_HEIGHT;
	if(ratio >=4.0/3)
	{
		glViewport(0, RESOLUTION_HEIGHT / 2 - RESOLUTION_WIDTH / 2, RESOLUTION_WIDTH, RESOLUTION_WIDTH);
	}
	if (ratio < 4.0/3)
	{
		glViewport(RESOLUTION_WIDTH / 2 - RESOLUTION_HEIGHT / 2, 0, RESOLUTION_HEIGHT, RESOLUTION_HEIGHT);
	}
}

void calculateFPS()
{
	static int frame;
	static long time, timebase;
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		FRAMES_PER_SECOND = frame*1000.0 / (time - timebase);
		timebase = time;
		frame = 0;
	}
}

void idle()
{
// ОГРАНИЧЕНИЕ (каждые 15мс или дольше отрисовка одного кадра)!!!
	static float deltaT;
	static float frameTime = 0.0f;  // Время последнего кадра
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
	// Интервал времени, прошедшего с прошлого кадра
	deltaT = currentTime - frameTime;
	frameTime = currentTime;
	if (deltaT >= 15)
	{
		TIME_PER_FRAME = deltaT;
		glutPostRedisplay();
	}
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
	game->GetKeyboardHandler()->Down(key, x, y);
};

void keyboardUp(unsigned char key, int x, int y)
{
	game->GetKeyboardHandler()->Up(key, x, y);
};

void test()
{
	
	game->Frame();

	char FPS[256];
	sprintf(FPS, "FPS:%4.2f", FRAMES_PER_SECOND);
	FontHelper::Render(-0.85,0.48, GLUT_BITMAP_HELVETICA_18, FPS);

};

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	calculateFPS();

	test();                        /// кадр! ///

	glutSwapBuffers();
};

void Init()
{
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(keyboardSpecial);
	glutSpecialUpFunc(keyboardSpecialUp);
	glutDisplayFunc(display);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
};

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 640);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(TITLE);
	glewInit();

	Init();
	
	game = new Game();

	glutMainLoop();

    return 0;
}

