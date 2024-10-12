#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define M_PI 3.14159265358979323846
void init(void);
void display(void);
void reshape(int, int);
void figuraCaracol(GLfloat, float, float, float);
void figuraRosal(GLfloat, float, float, float);
void figuraCardioide(GLfloat, float, float, float);
void circulos(GLfloat, float, float, float);
void mallaPolar(GLfloat, float, float, float);
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 500);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Fondo blanco
    glShadeModel(GL_FLAT);
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20.0, 20.0, -10.0, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void display(void)
{
    GLfloat ang = 0.0f, radio = 8.0f, x = 0.0f, y = 0.0f;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    mallaPolar(ang, radio, x, y);
    figuraCardioide(ang, radio, x, y);


    glPopMatrix();
    glFlush();
}
void circulos(GLfloat ang, float radio, float x, float y) {
    glColor3f(1, 0, 0);
    int i;
    for (i = 1; i <= radio; i++) {
        glBegin(GL_LINE_LOOP);
        for (ang = 0.0f; ang < 2 * M_PI; ang += 2 * M_PI / 20) {
            x = (float)i * cos(ang);
            y = (float)i * sin(ang);
            glVertex2f(x, y);
        }
        glEnd();
    }
}
void mallaPolar(GLfloat ang, float radio, float x, float y) {
    int i, N = 50;
    circulos(ang, radio, x, y);
    glBegin(GL_LINES);
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2 * M_PI / N) {
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(0, 0);
        glVertex2f(x, y);
    }
    glEnd();
}
void figuraCaracol(GLfloat ang, float radio, float x, float y) {
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2 * M_PI / 60)
    {
        radio = 2 + 4 * sin(ang);
        //radio = 3 * cos(2*ang);
        //radio = 3 - 3 * sin(ang);
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
}
void figuraRosal(GLfloat ang, float radio, float x, float y) {
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2 * M_PI / 60)
    {
        radio = 3 * cos(2 * ang);
        //radio = 3 - 3 * sin(ang);
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
}
void figuraCardioide(GLfloat ang, float radio, float x, float y) {
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2 * M_PI / 60)
    {
        radio = 3 - 3 * sin(ang);
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
}