#include <GL/glut.h>
#include <math.h>
#include <iostream>

int currentAlgorithm = 0;
int px0, py0, px1, py1;  // Variables para almacenar los puntos ingresados

void pintar(int x0, int y0, int x1, int y1, char color) {
    if (color == 'r') {
        glColor3f(1.0, 0.0, 0.0);  // Rojo
    }
    else if (color == 'g') {
        glColor3f(0.0, 1.0, 0.0);  // Verde
    }

    glBegin(GL_LINES);  // Dibuja una línea entre dos puntos
    glVertex2i(x0, y0);
    glVertex2i(x1, y1);
    glEnd();
    glFlush();
}

void ingresoDatos(void) {
    std::cout << "\n leer px0="; std::cin >> px0;
    std::cout << "\n leer py0="; std::cin >> py0;
    std::cout << "\n leer px1="; std::cin >> px1;
    std::cout << "\n leer py1="; std::cin >> py1;
}

void recta_simple(int x0, int y0, int x1, int y1) {
    pintar(x0, y0, x1, y1, 'r');  // Dibuja la línea entre dos puntos
}

void recta_dda(int x0, int y0, int x1, int y1) {
    int x;
    float dx, dy, m, y;
    dx = x1 - x0;
    dy = y1 - y0;
    m = dy / dx;
    y = y0;
    glBegin(GL_LINE_STRIP);  // Usa GL_LINE_STRIP para conectar puntos
    for (x = x0; x <= x1; x++) {
        glVertex2i(x, round(y));
        y += m;
    }
    glEnd();
    glFlush();
}

void recta_punto_medio(int x0, int y0, int x1, int y1) {
    int dx, dy, dE, dNE, d, x, y;
    dx = x1 - x0;
    dy = y1 - y0;
    d = 2 * dy - dx;
    dE = 2 * dy;
    dNE = 2 * (dy - dx);
    x = x0;
    y = y0;

    glBegin(GL_LINE_STRIP);  // Conectar los puntos secuencialmente
    glVertex2i(x, y);
    while (x < x1) {
        if (d <= 0) {
            d += dE;
            x++;
        }
        else {
            d += dNE;
            x++;
            y++;
        }
        glVertex2i(x, y);
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    if (currentAlgorithm == 1) {
        recta_simple(px0, py0, px1, py1);  // Algoritmo 1 con puntos ingresados
    }
    else if (currentAlgorithm == 2) {
        recta_dda(px0, py0, px1, py1);     // Algoritmo 2 con puntos ingresados
    }
    else if (currentAlgorithm == 3) {
        recta_punto_medio(px0, py0, px1, py1); // Algoritmo 3 con puntos ingresados
    }

    glPopMatrix();
    glFlush();
}

void GoMenu(int value) {
    currentAlgorithm = value;
    glutPostRedisplay();
}

void createMenu() {
    int algorithmMenu = glutCreateMenu(GoMenu);
    glutAddMenuEntry("Algoritmo basico", 1);
    glutAddMenuEntry("DDA", 2);
    glutAddMenuEntry("Algoritmo de punto medio", 3);

    glutCreateMenu(GoMenu);
    glutAddSubMenu("Algorithms", algorithmMenu);
    glutAddMenuEntry("Exit", 4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    ingresoDatos();  // Llamada al inicio

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Menu jerarquico");

    createMenu();
    glutDisplayFunc(display);

    glClearColor(1.0, 1.0, 1.0, 1.0);  // Fondo blanco
    glLineWidth(2.0);                  // Grosor de la línea

    gluOrtho2D(-20.0, 20.0, -20.0, 20.0);  // Configurar proyección ortogonal 2D // Configurar proyección ortogonal 2D

    glutMainLoop();

    return 0;
}
