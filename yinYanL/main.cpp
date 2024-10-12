#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
void ejes(void);
void inicio(void);
void display(void);
void myreshape(int, int);
void abasico(int, int, int, int);
void ingresoDatos(void);
int px0 = 0, py0 = 0, px1 = 50, py1 = 20;
void recta_punto_medio(int, int, int, int);
void circunferencia_punto_medio(int, int, int, int);
void circunferencia_punto_medio2(int);

void reflectar_cuadrante(float x, float y, int tipo) {

    switch (tipo)
    {
    case 1:
        glVertex2f(x, y);
        glVertex2f(-x, y);
        break;
    case 2:
        glVertex2f(-y, x);
        glVertex2f(-y, -x);
        break;
    case 3:
        glVertex2f(-x, -y);
        glVertex2f(x, -y);
        break;
    case 4:
        glVertex2f(y, -x);
        glVertex2f(y, x);
        break;
    }
}

void reflectar_octante(float x, float y, int tipo) {

    switch (tipo)
    {
    case 1:
        glVertex2f(x, y);

        break;
    case 2:
        glVertex2f(-x, y);
        break;
    case 3:
        glVertex2f(-y, x);

        break;
    case 4:
        glVertex2f(-y, -x);
        break;
    case 5:
        glVertex2f(-x, -y);

        break;
    case 6:
        glVertex2f(x, -y);
        break;
    case 7:
        glVertex2f(y, -x);

        break;
    case 8:
        glVertex2f(y, x);
        break;
    }

}

void yinyang_puntomedio() {
    /*
     circunferencia_punto_medio(0, 0, 100 , 5);
     glColor3f(1, 0, 0);
     circunferencia_punto_medio(0, 50, 50, 1);
     glColor3f(0, 1, 0);
     circunferencia_punto_medio(0, 50, 50, 4);
     glColor3f(0, 0, 1);
     circunferencia_punto_medio(0, 50, 10, 5);
     glColor3f(0, 0, 1);

     circunferencia_punto_medio(0, -50, 10, 5);
     glColor3f(0, 1, 0);
     circunferencia_punto_medio(0, -50, 50, 2);
     glColor3f(0, 1, 0);
     circunferencia_punto_medio(0, -50, 50, 3);
     glColor3f(0, 0, 1);
     */

    circunferencia_punto_medio(0, 0, 100, 5);
    glColor3f(0, 0, 0);


    circunferencia_punto_medio(50, 0, 50, 1);
    glColor3f(0, 1, 0);
    circunferencia_punto_medio(50, 0, 50, 2);
    glColor3f(0, 0, 1);
    circunferencia_punto_medio(50, 0, 10, 5);
    glColor3f(0, 0, 1);

    circunferencia_punto_medio(-50, 0, 10, 5);
    glColor3f(0, 1, 0);
    circunferencia_punto_medio(-50, 0, 50, 4);
    glColor3f(0, 1, 0);
    circunferencia_punto_medio(-50, 0, 50, 3);
    glColor3f(0, 0, 1);







}
/*
void figura4(int R) {
    // Dibuja la circunferencia circunscrita


    // Cálculo del radio de las circunferencias pequeñas
    glColor3f(1.0, 0.0, 0.0);
    circunferencia_punto_medio(0, 0, sqrt(3) * R / 3,5);
    //circunferencia contenidas
    circunferencia_punto_medio(0, 2 * (R / (2 * (sqrt(3) + 1))) / sqrt(3), R / (2 * (sqrt(3) + 1)));
    circunferencia_punto_medio(-R / (2 * (sqrt(3) + 1)), -(R / (2 * (sqrt(3) + 1)) / sqrt(3)), R / (2 * (sqrt(3) + 1)));
    circunferencia_punto_medio(R / (2 * (sqrt(3) + 1)), -(R / (2 * (sqrt(3) + 1)) / sqrt(3)), R / (2 * (sqrt(3) + 1)));

    glColor3f(0.0, 0.0, 1.0);
    recta_punto_medio(-R / 2, -sqrt(3) * R / 6, R / 2, -sqrt(3) * R / 6);
    recta_punto_medio(R / 2, -sqrt(3) * R / 6, 0, sqrt(3) * R / 3);
    recta_punto_medio(0, sqrt(3) * R / 3, -R / 2, -sqrt(3) * R / 6);
}*/

int main(int argc, char** argv)
{
    //ingresoDatos();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Algoritmos de primitivas graficas");

    inicio();
    glutDisplayFunc(display);
    glutReshapeFunc(myreshape);
    glutMainLoop();
    return 0;
}

void ejes(void)
{
    float e = 195;
    glBegin(GL_LINES);
    glVertex2f(-e, 0);
    glVertex2f(e, 0);
    glVertex2f(0, -e);
    glVertex2f(0, e);
    glEnd();
}
void recta_punto_medio(int x0, int y0, int x1, int y1) {
    // Reflexión si la pendiente es mayor que 1
    glColor3f(0, 0, 1);
    bool steep = abs(y1 - y0) > abs(x1 - x0);

    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    // Asegurarse de dibujar de izquierda a derecha
    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    int d = 2 * dy - dx;
    int dE = 2 * dy;
    int dNE = 2 * (dy - dx);
    int y = y0;
    int y_step = (y0 < y1) ? 1 : -1;

    glBegin(GL_POINTS);
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            glVertex2f(y, x); // Reflexión inversa: Intercambia x e y para dibujar correctamente
        }
        else {
            glVertex2f(x, y);
        }

        if (d <= 0) {
            d += dE;
        }
        else {
            d += dNE;
            y += y_step;
        }
    }
    glEnd();
}

void circunferencia_punto_medio(int h, int k, int R, int cuadrante)
{
    {
        // discretizacion valida en el II octante
        int x = 0;
        int y = R, d = 1 - R;
        glBegin(GL_POINTS);
        switch (cuadrante) {
        case 1:
            //1er octante
            glVertex2f(y + h, x + k);
            //2da octante
            glVertex2f(x + h, y + k);
            break;
        case 2:
            //3er octante
            glVertex2f(-x + h, y + k);
            //4to octante
            glVertex2f(-y + h, x + k);
            break;
        case 3:
            //5to octante
            glVertex2f(-y + h, -x + k);
            //6to octante
            glVertex2f(-x + h, -y + k);
            break;
        case 4:
            //7mo octante
            glVertex2f(x + h, -y + k);
            //8vo octante
            glVertex2f(y + h, -x + k);
            break;
        case 5:
            glVertex2f(x + h, y + k);
            glVertex2f(-x + h, y + k);
            glVertex2f(-y + h, x + k);
            glVertex2f(-y + h, -x + k);
            glVertex2f(-x + h, -y + k);
            glVertex2f(x + h, -y + k);
            glVertex2f(y + h, -x + k);
            glVertex2f(y + h, x + k);
            glVertex2f(y + h, x + k);
        }



        while (x < y) {
            if (d < 0)
                d += 2 * x + 3;
            else {
                d += 2 * (x - y) + 5;
                y--;
            }
            x++;
            switch (cuadrante) {
            case 1:
                //1er octante
                glVertex2f(y + h, x + k);
                //2da octante
                glVertex2f(x + h, y + k);
                break;
            case 2:
                //3er octante
                glVertex2f(-x + h, y + k);
                //4to octante
                glVertex2f(-y + h, x + k);
                break;
            case 3:
                //5to octante
                glVertex2f(-y + h, -x + k);
                //6to octante
                glVertex2f(-x + h, -y + k);
                break;
            case 4:
                //7mo octante
                glVertex2f(x + h, -y + k);
                //8vo octante
                glVertex2f(y + h, -x + k);
                break;
            case 5:
                glVertex2f(x + h, y + k);
                glVertex2f(-x + h, y + k);
                glVertex2f(-y + h, x + k);
                glVertex2f(-y + h, -x + k);
                glVertex2f(-x + h, -y + k);
                glVertex2f(x + h, -y + k);
                glVertex2f(y + h, -x + k);
                glVertex2f(y + h, x + k);
                glVertex2f(y + h, x + k);
            }
        }
        glEnd();
    }

}


void circunferencia_punto_medio2(int R)
{
    {
        // discretizacion valida en el II octante
        int x = 0;
        int y = R, d = 1 - R;
        glBegin(GL_POINTS);
        //2da octante
        glVertex2f(x, y);
        //3er octante
        glVertex2f(-x, y);
        //4to octante
        glVertex2f(-y, x);
        //5to otcante
        glVertex2f(-y, -x);
        //6to octante
        glVertex2f(-x, -y);
        //7mo octante
        glVertex2f(x, -y);

        //8vo octante
        glVertex2f(y, -x);
        //1er octante
        glVertex2f(y, x);
        while (x < y) {
            if (d < 0)
                d += 2 * x + 3;
            else {
                d += 2 * (x - y) + 5;
                y--;
            }
            x++;
            // aplico reflexiones para reprod las coord en los 7 octantes restantes
            //2da octante
            glVertex2f(x, y);
            //3er octante
            glVertex2f(-x, y);
            //4to octante
            glVertex2f(-y, x);
            //5to octante
            glVertex2f(-y, -x);
            //6to octante
            glVertex2f(-x, -y);
            //7mo octante
            glVertex2f(x, -y);

            //8vo octante
            glVertex2f(y, -x);
            //1er octante
            glVertex2f(y, x);
        }
        glEnd();
    }

}

void inicio(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  //parametros: rojo, amarillo y azul, el cuarto es el parametro      alpha
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();     // salva el estado actual de la matriz
    glColor3f(0, 0, 1);    // Azul
    glPointSize(2);     // Fije el grosor de pixel = 2

    glColor3f(0, 0, 0);
    ejes();
    glColor3f(0, 1, 0);
    yinyang_puntomedio();
    glPopMatrix();         // recupera el estado del matriz
    glFlush();
}

void myreshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200.0, 200.0, -200.0, 200, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void abasico(int x0, int y0, int x1, int y1)
{
    int x;
    float dx, dy, m, b, y;
    dx = x1 - x0;
    dy = y1 - y0;
    m = dy / dx;
    b = y0 - m * x0;
    y = y0;
    glBegin(GL_POINTS);
    for (x = x0; x <= x1; x++)
    {
        y = m * x + b;
        cout << x << "  " << y << "  " << (int)ceil(y - 0.5) << "\n";
        glVertex2f(x, (int)ceil(y - 0.5));
    }
    glEnd();
}

// opcional
void ingresoDatos(void)
{
    // lo que Ud desee
    cout << "\n leer px0="; cin >> px0;
    cout << "\n leer py0="; cin >> py0;
    cout << "\n leer px1="; cin >> px1;
    cout << "\n leer py1="; cin >> py1;
}