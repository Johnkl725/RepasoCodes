#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <iostream>

// Declarar las variables globales
int R;  // Variable global para almacenar el radio de la circunferencia
int x_0, y_0;  // Coordenadas del centro de la circunferencia
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
	glColor3f(0.0, 0.0, 1.0);  // Color azul para los puntos (por defecto)
    ejes();  // Dibuja los ejes
    // Dibuja la circunferencia en la ubicación especificada por el usuario
    circunferencia_punto_medio(x_0, y_0, R);
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
    std::cout << "Ingrese el radio de la circunferencia: ";
    std::cin >> R;  // Entrada del usuario para definir el radio de la circunferencia

    std::cout << "Ingrese las coordenadas del centro (x0 y0): ";
    std::cin >> x_0 >> y_0;  // Entrada del usuario para definir el centro de la circunferencia

    std::cout << "Ingrese el color (r para rojo, g para verde, b para azul): ";
    std::cin >> atributo;  // Entrada del usuario para definir el color

    glutInit(&argc, argv);  // Inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Modo de visualización
    glutInitWindowSize(500, 500);  // Tamaño de la ventana
    glutCreateWindow("Circunferencia - Punto Medio");  // Crea la ventana con un título
    init();  // Llama a la función de inicialización
    glutDisplayFunc(display);  // Define la función de dibujo
    glutReshapeFunc(reshape);  // Define la función de redimensionamiento
    glutMainLoop();  // Inicia el loop principal de GLUT
    return 0;  // Fin del programa
}

