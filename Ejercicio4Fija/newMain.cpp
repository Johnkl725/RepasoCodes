#include "GL/glut.h"
#include <iostream>
#include <cmath>
#ifndef M_PI  
#define M_PI 3.14159265358979323846  
#endif  
int L = 0, r = 20, R = 40;  // Variable global para almacenar el lado del triángulo
int x_0, y_0;  // Coordenadas del centro del triángulo
char atributo = 'r';  // Color por defecto para pintar (rojo en este caso)

// Función para pintar un punto con un color específico
void pintar(int x, int y, char atributo) {
    // Selección del color según el atributo
    switch (atributo) {
    case 'r':  // Rojo
        glColor3f(1.0, 0.0, 0.0);
        break;
    case 'g':  // Verde
        glColor3f(0.0, 1.0, 0.0);
        break;
    case 'b':  // Azul
        glColor3f(0.0, 0.0, 1.0);
        break;
    default:   // Negro (por defecto si no se especifica color)
        glColor3f(0.0, 0.0, 0.0);
        break;
    }
    // Dibuja un punto en las coordenadas especificadas
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Implementación del algoritmo de punto medio para dibujar circunferencias
void circunferencia_punto_medio(int h, int k, int R) {
    int x = 0;
    int y = R;
    int d = 1 - R;  // Valor inicial de la variable de decisión 'd'

    glBegin(GL_POINTS);

    // Dibuja los puntos iniciales en las 8 simetrías de la circunferencia
    glVertex2f(x + h, y + k);
    glVertex2f(-x + h, y + k);
    glVertex2f(x + h, -y + k);
    glVertex2f(-x + h, -y + k);
    glVertex2f(y + h, x + k);
    glVertex2f(-y + h, x + k);
    glVertex2f(y + h, -x + k);
    glVertex2f(-y + h, -x + k);

    // Mientras x sea menor que y, continúa dibujando puntos
    while (x < y) {
        if (d < 0) {
            d += 2 * x + 3;
        }
        else {
            d += 2 * (x - y) + 5;
            y--;  // Decrementa y cuando d cambia
        }
        x++;
        pintar(x + h, y + k, atributo);  // Dibuja los puntos correspondientes en las 8 simetrías de la circunferencia
        // Dibuja los puntos correspondientes en las 8 simetrías de la circunferencia
        pintar(-x + h, y + k, atributo);
        pintar(x + h, -y + k, atributo);
        pintar(-x + h, -y + k, atributo);
        pintar(y + h, x + k, atributo);
        pintar(-y + h, x + k, atributo);
        pintar(y + h, -x + k, atributo);
        pintar(-y + h, -x + k, atributo);
        glVertex2f(x + h, y + k);
        glVertex2f(-x + h, y + k);
        glVertex2f(x + h, -y + k);
        glVertex2f(-x + h, -y + k);
        glVertex2f(y + h, x + k);
        glVertex2f(-y + h, x + k);
        glVertex2f(y + h, -x + k);
        glVertex2f(-y + h, -x + k);

    }
    glEnd();
    glFlush();
}

void LINEA(int x0, int y0, int x1, int y1) { //Esta funcion me servirá para poder construir el triangulo equilatero
    // Si el punto inicial está a la derecha, intercambiar los puntos
    if (x0 > x1) {
        std::swap(x0, x1); // Intercambia los valores de x0 y x1
        std::swap(y0, y1); // Intercambia los valores de y0 y y1
    }

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;  // Dirección del incremento de x
    int sy = (y0 < y1) ? 1 : -1;  // Dirección del incremento de y
    int err = dx - dy;

    glBegin(GL_LINES);  // Dibuja líneas
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

void triangulo_equilatero(int x0, int y0, int R) {
    // Ángulos para los tres vértices del triángulo (120° de diferencia entre cada vértice)
    float angulo1 = 0;                 // Primer vértice (ángulo 0°)
    float angulo2 = 2 * M_PI / 3;      // Segundo vértice (120°)
    float angulo3 = 4 * M_PI / 3;      // Tercer vértice (240°)

    // Cálculo de las coordenadas de los tres vértices
    int x1 = x0 + R * cos(angulo1);
    int y1 = y0 + R * sin(angulo1);
    int x2 = x0 + R * cos(angulo2);
    int y2 = y0 + R * sin(angulo2);
    int x3 = x0 + R * cos(angulo3);
    int y3 = y0 + R * sin(angulo3);

    glColor3f(0, 0, 1); // Color azul para el triángulo
    LINEA(x1, y1, x2, y2);  // Línea entre los vértices 1 y 2
    LINEA(x2, y2, x3, y3);  // Línea entre los vértices 2 y 3
    LINEA(x3, y3, x1, y1);  // Línea entre los vértices 3 y 1
}


// Función para dibujar los ejes X y Y
void ejes(void) {
    float e = 100.0;  // Define la extensión de los ejes
    glBegin(GL_LINES);
    glVertex2f(-e, 0);  // Eje X hacia la izquierda
    glVertex2f(e, 0);   // Eje X hacia la derecha
    glVertex2f(0, -e);  // Eje Y hacia abajo
    glVertex2f(0, e);   // Eje Y hacia arriba
    glEnd();
}

// Función principal de dibujo, se llama cada vez que se necesita actualizar la pantalla
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);  // Limpia la pantalla
    glPushMatrix();
    glPointSize(4);  // Tamaño de los puntos
    glColor3f(0.0, 0.0, 1.0);  // Color azul con el que se pinta los ejes y da por defecto un color
    ejes();  // Dibuja los ejes

    // Dibuja el círculo grande
    atributo = 'b';  // Color azul para el círculo grande
    int R_grande = L;  // Radio del círculo grande
    circunferencia_punto_medio(x_0, y_0, R_grande);

    // Dibuja el triángulo equilátero inscrito en el círculo grande
    triangulo_equilatero(x_0, y_0, R_grande);

    // Dibuja las circunferencias pequeñas dentro del triángulo
    atributo = 'r';  // Color rojo para las circunferencias
    float altura = (sqrt(3) / 2) * L;
    int r_pequeno = L / 6;
    circunferencia_punto_medio(x_0 - L / 4, y_0 - altura / 6, r_pequeno);
    circunferencia_punto_medio(x_0 + L / 4, y_0 - altura / 6, r_pequeno);
    circunferencia_punto_medio(x_0, y_0 + altura / 3, r_pequeno);

    glPopMatrix();
    glFlush();  // Fuerza a que se ejecute el dibujo
}

// Función que define cómo se adapta la ventana cuando se redimensiona
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);  // Ajusta el viewport al nuevo tamaño
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define el espacio de coordenadas a mostrar en la ventana
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Función de inicialización, define el color de fondo y otros ajustes iniciales
void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Define el color de fondo blanco
    glShadeModel(GL_FLAT);  // Modelo de sombreado plano
}

// Función principal, donde inicia el programa
int main(int argc, char** argv) {
    std::cout << "Ingrese las coordenadas del centro (x0 y0): ";
    std::cin >> x_0 >> y_0;  // Entrada del usuario para definir el centro de la circunferencia
    std::cout << "Ingrese el valor de L (lado del triángulo): ";
    std::cin >> L;  // Entrada del usuario para definir el lado del triángulo

    glutInit(&argc, argv);  // Inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Modo de visualización
    glutInitWindowSize(500, 500);  // Tamaño de la ventana
    glutCreateWindow("Triángulo Equilátero y Circunferencias");  // Crea la ventana con un título
    init();  // Llama a la función de inicialización
    glutDisplayFunc(display);  // Define la función de dibujo
    glutReshapeFunc(reshape);  // Define la función de redimensionamiento
    glutMainLoop();  // Inicia el loop principal de GLUT
    return 0;  // Fin del programa
}
