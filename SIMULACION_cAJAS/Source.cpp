//Parcial Simulación 1er Corte Vanessa Escobar Mora Natalia Gomez Malaver Santiago Forero Zapata
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "GL/freeglut.h"
#include "GL/glut.h"
#include <ctime> 
using namespace std;
unsigned t0, t1;
long double P[3], Pf[3], V[3], A[3], tf, t, Kx[4], Ky[4], Kxa[4], Kya[4], Kxv[4], Kyv[4], h, N;
CONST double C = 1.32;
CONST double GRAVEDAD = 9.8;
CONST double EULER = 2.71828182845904523536;
int ancho = 1300, alto = 800, i, op;
void pintaPixel(float x, float y) {
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}
void Iniciar() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ancho / 200, ancho / 200, -alto / 200, alto / 200, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}
void graficas() {
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.0, 2.0);
	glVertex2f(0.0, 4.0);
	glEnd();
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	pintaPixel(t - 5.5, (P[0] * 0.02) + 2.5);
	glColor3f(1.0, 0.0, 0.0);
	pintaPixel(t - 4, V[0]* 0.02 + 1.5);
	glColor3f(0.0, 1.0, 0.0);
	pintaPixel(t - 2, (A[0] * 0.02) + 4.25);
	glColor3f(0.0, 0.0, 1.0);
	pintaPixel(t + 1, P[1] + 3.5);
	glColor3f(1.0, 0.0, 0.0);
	pintaPixel(t + 3, (V[1] * 0.02) + 3.5);
	glColor3f(0.0, 1.0, 0.0);
	pintaPixel(t + 5, (A[1] * 0.02) + 4.5);
	glPopMatrix();
}
void esfera() {
	glPushMatrix();
	glColor3f(0.58, 1, 0.94);
	glBegin(GL_QUADS);
	glVertex2i(6, 2); glVertex2i(-6, 2);
	glVertex2i(-6, -6); glVertex2i(6, -5);
	glEnd();
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);	
	glRotatef(-20.0, 0.0, 0.0, 1.0);	
	glTranslated(-2.0 + (P[0] * 0.01), 1.0+(tan(0.0174533)* (P[0] * -0.01)), 0.0);
	glScalef(2.0, 1.0, 1.0);
	glutSolidCube(0.40);
	glPopMatrix();
	glEnd();
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glTranslated(2.5, -0.0+ (P[0] * (-0.01)), 0.0);
	glScalef(1.0, 2.0, 1.0);
	glutSolidCube( 0.40);
	glPopMatrix();
	glEnd();
	glutSwapBuffers();
}
void Iniciar_Sistema() {
	t = 0.0;
	tf = 10;
	N = 200;
	h = (tf - t) / N;
	i = 0;
	P[0] = 0.0; P[1] = 0.0; P[2] = 0.0;
	
	V[0] = 0.0; V[1] = 0.0; V[2] = 0.0;
	A[0] = 5.33; A[1] = 0.0; A[2] =0.0;
}
void Calcular_MetodoEuler() {
	P[0] = P[0] + (h * V[0]);
	V[0] = V[0] + (h * A[0]);
	A[0] = A[0];
	P[1] = P[1] + (h * V[1]);
	V[1] = V[1] + (h * A[1]);
	A[1] = 0;
	P[2] = P[2] + (h * V[2]);
	V[2] = V[2] + (h * A[2]);
	A[2] = 0;
}

void Aumentar_Tiempo() {
	i = i + 1;
	t = t + h;
}
void Metodo_Euler()
{
	while (i <= N) {
		cout << "Tiempo : " << t << endl;
		cout << "P,V,A en X: " << fixed << P[0] << "m " << V[0] << "m/s " << A[0] << "m/s^2" << endl;
		cout << "P,V,A en Y: " << fixed << P[1] << "m " << V[1] << "m/s " << A[1] << "m/s^2" << endl;
		//Ciclo Simulación
		graficas();
		esfera();
		Aumentar_Tiempo();
		Calcular_MetodoEuler();
	}
	
}

int main(int argc, char** argv) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowPosition(10, 20);
		glutInitWindowSize(ancho, alto);
		glutCreateWindow("Metodo Runge Kutta");
		Iniciar();
		Iniciar_Sistema();
		glutDisplayFunc(Metodo_Euler);
		glutIdleFunc(Metodo_Euler);
		glutMainLoop();
	
		return 0;
}
