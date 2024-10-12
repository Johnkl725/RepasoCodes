#include <GL/glut.h>
#include <cmath>
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void LINEA(int x0, int y0, int x1, int y1) {
    // Si el punto inicial est� a la derecha, intercambiar los puntos
    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;  // Direcci�n del incremento de x
    int sy = (y0 < y1) ? 1 : -1;  // Direcci�n del incremento de y
    int err = dx - dy;

    glBegin(GL_LINES);  // Dibuja l�neas
    while (true) {
        glVertex2i(x0, y0);  // Dibuja el punto actual

        if (x0 == x1 && y0 == y1) break;  // Salimos si hemos alcanzado el punto final

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
    glEnd();
    glFlush();
}

void calcularVertices(int N, float radio, int x[], int y[]) {
    float angulo = 2 * M_PI / N;  // �ngulo entre v�rtices
    for (int i = 0; i < N; i++) {
        x[i] = (int)(radio * cos(i * angulo));  // Coordenada x
        y[i] = (int)(radio * sin(i * angulo));  // Coordenada y
    }
}

void dibujarPoligonoEstrellado(int N, int salto, int x[], int y[]) {
    glColor3f(0.5, 0.0, 0.5);  // Color p�rpura
    for (int i = 0; i < N; i++) {
        int next = (i + salto) % N;  // Salta v�rtices para formar la estrella
        LINEA(x[i], y[i], x[next], y[next]);
    }
}

void dibujarEjes() {
    glColor3f(0.0, 0.0, 0.0);  // Color negro para los ejes
    LINEA(-250, 0, 250, 0);  // Eje horizontal
    LINEA(0, -250, 0, 250);  // Eje vertical
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibuja los ejes
    dibujarEjes();

    int N = 9;  // N�mero de lados del pol�gono (hept�gono)
    int salto = 2;  // Salto de v�rtices para la estrella
    float radio = 150.0;
    int x[100], y[100];

    calcularVertices(N, radio, x, y);  // Calcula los v�rtices del pol�gono
    dibujarPoligonoEstrellado(N, salto, x, y);  // Dibuja el pol�gono estrellado

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Fondo blanco
    glColor3f(1.0, 0.0, 0.0);          // Color negro para las l�neas
    gluOrtho2D(-250.0, 250.0, -250.0, 250.0); // Configurar la proyecci�n ortogonal 2D
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Pol�gono Estrellado con Ejes");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
