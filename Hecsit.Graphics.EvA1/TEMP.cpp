#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "plug/glut.h"

// ���� �������� ������
float angle = 0.0;
// ���������� ������� ����������� �������� ������
float lx = 0.0f, lz = -1.0f;
// XZ ������� ������
float x = 0.0f, z = 5.0f;
//����� ������� ������. ���������� ���������������� �������� ����������
//����� ������� �� ������
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;
//���� ���� ���������
float red = 1.0f, blue = 0.5f, green = 0.5f;
//������ ���������
float scale = 1.0f;
//����� �� ���������
void *font = GLUT_STROKE_ROMAN;
//������ � ������ ����
int h, w;

// ���������� ��� ���������� ������ � �������
int frame;
long time, timebase;
char s[60];
char currentMode[80];

// ��� ������ ��������� ��������� ���������
// ��� �������� ������
char gameModeString[40] = "640x480";

void init();

void changeSize(int ww, int hh) {
	h = hh;
	w = ww;
	// �������������� ������� �� ����
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	// ���������� ������� ��������
	glMatrixMode(GL_PROJECTION);
	// �������� �������
	glLoadIdentity();
	// ���������� ��������� ��������
	glViewport(0, 0, w, h);
	// ���������� ���������� �����������
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// ��������� � ������� ��������
	glMatrixMode(GL_MODELVIEW);
}

void drawSnowMan()
{
	glScalef(scale, scale, scale);
	glColor3f(1.0f, 1.0f, 1.0f);
	// ���� ���������
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);
	// ������ ���������
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);
	// ����� ���������
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();
	// ��� ���������
	glColor3f(red, green, blue);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
	glColor3f(1.0f, 1.0f, 1.0f);
}

void renderBitmapString(
	float x,
	float y,
	float z,
	void *font,
	char *string) {

	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void renderStrokeFontString(
	float x,
	float y,
	float z,
	void *font,
	char *string) {

	char *c;
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(0.002f, 0.002f, 0.002f);
	for (c = string; *c != '\0'; c++) {
		glutStrokeCharacter(font, *c);
	}
	glPopMatrix();
}

void restorePerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	//������������ ���������� ������� ��������
	glPopMatrix();
	//��������� � ����� ������
	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection() {
	//������� ����� ��������
	glMatrixMode(GL_PROJECTION);
	//��������� ���������� �������, ������� ��������
	//��������� ������������� ��������
	glPushMatrix();
	//�������� �������
	glLoadIdentity();
	//������������� 2D ������������� ��������
	gluOrtho2D(0, w, h, 0);
	//�������� ����� ������ ������
	glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void renderScene(void) {
	if (deltaMove)
		computePos(deltaMove);

	//�������� ����� ����� � �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �������� �������������
	glLoadIdentity();
	// ���������� ������
	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);

	// �������� "�����"
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	// �������� 64 ���������
	char number[4];
	for (int i = -4; i < 4; i++)
		for (int j = -4; j < 4; j++) {
			glPushMatrix();
			glTranslatef(i*10.0f, 0.0f, j * 10.0f);
			drawSnowMan();
			sprintf(number, "%d", (i + 3) * 8 + (j + 4));
			renderStrokeFontString(0.0f, 0.5f, 0.0f, (void *)font, number);
			glPopMatrix();
		}
	// ��� ��� ���������� ������ � �������
	frame++;

	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s, "Informatika.TNU - FPS:%4.2f",
			frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}

	setOrthographicProjection();
	void *font = GLUT_BITMAP_8_BY_13;
	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(30, 15, 0, font, (char *)"GLUT lib @ Iformatika TNU");
	renderBitmapString(30, 30, 0, font, s);
	renderBitmapString(30, 45, 0, font, (char *)"F1 - Game Mode  640x480 32 bits");
	renderBitmapString(30, 60, 0, font, (char *)"F2 - Game Mode  960x540 32 bits");
	renderBitmapString(30, 75, 0, font, (char *)"F3 - Game Mode 1280x720 32 bits");
	renderBitmapString(30, 90, 0, font, (char *)"F4 - Game Mode 1366x768 32 bits");
	renderBitmapString(30, 105, 0, font, (char *)"F5 - Game Mode 1650x1050 32 bits");
	renderBitmapString(30, 120, 0, font, (char *)"F6 - Window Mode");
	renderBitmapString(30, 135, 0, font, (char *)"Esc - Quit");
	renderBitmapString(30, 150, 0, font, currentMode);
	glPopMatrix();

	restorePerspectiveProjection();

	glutSwapBuffers();
}

// -----------------------------------	//
//            ����������				//
// -----------------------------------	//

void processNormalKeys(unsigned char key, int xx, int yy) {

	switch (key) {
	case 27:
		if (glutGameModeGet(GLUT_GAME_MODE_ACTIVE) != 0)
			glutLeaveGameMode();
		exit(0);
		break;
	}
}

void pressKey(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_UP: deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	case GLUT_KEY_F1:
		// ���������� ���������� � ����
		glutGameModeString("640x480:32");
		// �������� ������������� �����
		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
			glutEnterGameMode();
			sprintf(gameModeString, "640x480:32");
			// ����������� �������� �������
			// � ������������� OpenGL
			init();
		}
		else
			glutGameModeString(gameModeString);
		break;
	case GLUT_KEY_F2:
		// ���������� ���������� � ����
		glutGameModeString("960x540:32");
		// �������� ������������� �����
		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
			glutEnterGameMode();
			sprintf(gameModeString, "960x540:32");
			// ����������� �������� �������
			// � ������������� OpenGL
			init();
		}
		else
			glutGameModeString(gameModeString);
		break;
	case GLUT_KEY_F3:
		// ���������� ���������� � ����
		glutGameModeString("1280x720:32");
		// �������� ������������� �����
		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
			glutEnterGameMode();
			sprintf(gameModeString, "1280x720:32");
			// ����������� �������� �������
			// � ������������� OpenGL
			init();
		}
		else
			glutGameModeString(gameModeString);
		break;
	case GLUT_KEY_F4:
		// ���������� ���������� � ����
		glutGameModeString("1366x768:32");
		// �������� ������������� �����
		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
			glutEnterGameMode();
			sprintf(gameModeString, "1366x768:32");
			// ����������� �������� �������
			// � ������������� OpenGL
			init();
		}
		else
			glutGameModeString(gameModeString);
		break;
	case GLUT_KEY_F5:
		// ���������� ���������� � ����
		glutGameModeString("1680x1050");
		// �������� ������������� �����
		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
			glutEnterGameMode();
			sprintf(gameModeString, "1680x1050");
			// ����������� �������� �������
			// � ������������� OpenGL
			init();
		}
		else
			glutGameModeString(gameModeString);
		break;
	case GLUT_KEY_F6:
		//��������� � ���� �� ���������
		w = 800; h = 600;
		if (glutGameModeGet(GLUT_GAME_MODE_ACTIVE) != 0) {
			glutLeaveGameMode();
			//init();
		}
		break;
	}
	if (glutGameModeGet(GLUT_GAME_MODE_ACTIVE) == 0)
		sprintf(currentMode, "Window MODE");
	else
		sprintf(currentMode,
			"Mode: Game Mode %dx%d at %d hertz, %d bpp",
			glutGameModeGet(GLUT_GAME_MODE_WIDTH),
			glutGameModeGet(GLUT_GAME_MODE_HEIGHT),
			glutGameModeGet(GLUT_GAME_MODE_REFRESH_RATE),
			glutGameModeGet(GLUT_GAME_MODE_PIXEL_DEPTH));
}

void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	}
}

// -----------------------------------	//
//            ������� ����				//
// -----------------------------------	//

void mouseMove(int x, int y)
{
	// ������ ����� ����� ������ �� �������
	if (xOrigin >= 0)
	{
		// �������� deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;
		// �������� ����������� ������
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y)
{
	// ������ ������ ��������, ���� ����� ������ ���� ������
	if (button == GLUT_LEFT_BUTTON)
	{
		// ����� ������ ��������
		if (state == GLUT_UP)
		{
			angle += deltaAngle;
			xOrigin = -1;
		}
		else
		{// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}

void init() {

	// ����������� �������
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL �������������
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

// ------------------------------------	//
//             main()			//
// -----------------------------------	//

int main(int argc, char **argv) {

	// ������������� GLUT � �������� ����
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("���� 13");

	// ����������� �������
	init();

	// ������� ����
	glutMainLoop();

	return 1;
}