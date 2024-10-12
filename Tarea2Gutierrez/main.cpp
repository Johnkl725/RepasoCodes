#include <GL/glut.h> 
#include <stdlib.h>

GLfloat anguloCuboX = 0.0f;
GLfloat anguloCuboY = 0.0f;
GLfloat anguloEsfera = 0.0f;
GLfloat desp = 0.0f;
GLfloat escala = 1.0f;

GLint ancho, alto;
int hazPerspectiva = 0;

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (hazPerspectiva)
		gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 20.0f);
	else
		glOrtho(-4, 4, -4, 4, -4, 4);

	glMatrixMode(GL_MODELVIEW);

	ancho = width;
	alto = height;
}

void drawCube(void)
{
	glScalef(escala, escala, escala);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);  //cara frontal 
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);  //cara trasera 
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);  //cara lateral izq 
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);  //cara lateral dcha 
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);  //cara arriba 
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);  //cara abajo 
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(desp, 0.0f, 0.0f);
	glRotatef(anguloCuboX, 1.0f, 0.0f, 0.0f);
	glRotatef(anguloCuboY, 0.0f, 1.0f, 0.0f);
	drawCube();

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(anguloEsfera, 0.0f, 1.0f, 0.0f);
	glTranslatef(3.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireSphere(0.5f, 18, 18);

	glFlush();
	glutSwapBuffers();
}

void init()
{
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	ancho = 400;
	alto = 400;
}

void idle()
{
	display();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':
		anguloCuboX -= 0.1f;
		anguloCuboY -= 0.1f;
		reshape(ancho, alto);
		break;
	case 'P':
		anguloCuboX += 0.1f;
		anguloCuboY += 0.1f;
		reshape(ancho, alto);
		break;

	case 'o':
		hazPerspectiva = 0;
		reshape(ancho, alto);
		desp -= 0.5f;
		break;
	case 'O':
		hazPerspectiva = 0;
		reshape(ancho, alto);
		desp += 0.5f;
		break;

	case 'r':
		anguloCuboY -= 5.0f;
		break;
	case 'R':
		anguloCuboY += 5.0f;
		break;

	case 's':
		escala -= 0.1f;
		break;
	case 'S':
		escala += 0.1f;
		break;

	case 27:   // escape 
		exit(0);
		break;
	}
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		desp -= 0.1f;
		break;
	case GLUT_KEY_RIGHT:
		desp += 0.1f;
		break;
	case GLUT_KEY_UP:
		anguloCuboX -= 5.0f;
		break;
	case GLUT_KEY_DOWN:
		anguloCuboX += 5.0f;
		break;
	}
	reshape(ancho, alto);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(300, 400);
	glutInitWindowSize(ancho, alto);
	glutCreateWindow("Cubo 1");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}
