#include <GL/glut.h>

// Declaración de las funciones
void init(void);
void display(void);
void reshape(int, int);
void dibujar_ejes();
void dibujar_patron();
void circunferencia_punto_medio(int, int, int);
void Arco(int, int, int);

// Algoritmo del punto medio para dibujar la circunferencia
void circunferencia_punto_medio(int h, int k, int R) {
    int x = 0;
    int y = R;
    int d = 1 - R;

    glBegin(GL_POINTS);
    // Dibuja el primer punto en la parte derecha de la circunferencia
    glVertex2f(x + h, y + k - R / 2);  // Primer punto

    while (x <= y) {
        // Dibuja la parte derecha de la circunferencia
        glVertex2f(x + h, y + k - R / 2); // Arriba derecha
        glVertex2f(x + h, -y + k - R / 2); // Abajo derecha
        glVertex2f(y + h, x + k - R / 2); // Arriba derecha más interior
        glVertex2f(y + h, -x + k - R / 2); // Abajo derecha más interior

        if (d < 0) {
            d += 2 * x + 3;
        }
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
    glEnd();
}

// Función que dibuja un arco utilizando la circunferencia de punto medio
void Arco(int h, int k, int R) {
    circunferencia_punto_medio(h, k, R);
}

// Función para dibujar los ejes y la cuadrícula
void dibujar_ejes() {
    glBegin(GL_LINES);

    // Eje X
    glVertex2f(0, 200);
    glVertex2f(400, 200);

    // Eje Y
    glVertex2f(200, 0);
    glVertex2f(200, 400);

    // Cuadrícula
    for (int i = 0; i <= 400; i += 100) {
        // Líneas horizontales
        glVertex2f(0, i);
        glVertex2f(400, i);
        // Líneas verticales
        glVertex2f(i, 0);
        glVertex2f(i, 400);
    }

    glEnd();
}

// Función para dibujar el patrón de arcos
void dibujar_patron() {
    int L = 100;  // Distancia entre centros de los arcos
    int R = 50;   // Radio de los arcos

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            int x = i * L;
            int y = j * L;

            // Dibujar el arco en cada celda, pegado a la izquierda
            Arco(x, y + 50, R);  // Ajustar el desplazamiento vertical si es necesario

        }
    }
}

// Función para inicializar las configuraciones de OpenGL
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Fondo blanco
    glShadeModel(GL_FLAT);
}

// Función de visualización que llama a los elementos a dibujar
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);  // Color azul para los ejes y cuadrícula
    dibujar_ejes();

    // Dibujar patrón de arcos
    glColor3f(0.0, 0.0, 0.0);  // Color negro para los arcos
    dibujar_patron();

    glFlush();
}

// Función que ajusta la ventana cuando cambia su tamaño
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);  // Ajustamos la proyección ortogonal
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Función principal
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Patrón de Arcos con Ejes");

    init();  // Inicializa configuraciones
    glutDisplayFunc(display);  // Llama a la función display
    glutReshapeFunc(reshape);  // Llama a la función reshape cuando se redimensiona
    glutMainLoop();  // Inicia el loop principal de eventos

    return 0;
}
