#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 255.0, 255.0, 0.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define COR		 0.0, 1.0, 1.0, 0.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 0.0
#define DARK_BROWN 0.239, 0.109, 0.003
#define BROWN	 0.55, 0.27, 0.075
#define LIGHT_BROWN 0.784, 0.639, 0.517
#define PI		 3.14159

#include "RgbImage.h"

//================================================================================
//===========================================================Variaveis e constantes

GLfloat zoom = 3;

GLfloat esp = 0.08;
GLfloat altG = 1;
GLfloat tam1 = 0.5;

GLfloat altP = altG / 2;
GLfloat altP1 = altG / 10;
GLfloat altP2 = altG * 0.35;
GLfloat altV = altG * 0.05;

GLfloat tam3 = tam1 / 10;
GLfloat tam2 = tam1 / 2;
GLfloat tamPR = tam1 * 0.3;
GLfloat tamP = tam1 * 0.16;

GLfloat posV = tam3;


GLfloat angG = 0.0;
GLfloat angP = 0.0;

GLfloat Matriz[4][4];				// para obter a posição Px, Py
GLfloat Px, Py;						// posição final da extremidade

GLboolean GAberto = false;
GLboolean PAberto = false;
GLboolean VAberto = false;



static GLfloat vertices[] = {

	//----------- PORTA GRANDE ------------
	// EsquerdaG
		-esp,  -altG,  tam1,	// 0 
		-esp,   altG,  tam1,	// 1 
		-esp,   altG, -tam1,	// 2 
		-esp,  -altG, -tam1,	// 3 

	// DireitaG
		 esp,  -altG,  tam1,	// 4 
		 esp,   altG,  tam1,	// 5 
		 esp,   altG, -tam1,	// 6 
		 esp,  -altG, -tam1,	// 7 

	// CimaG
		-esp,  altG,  tam1,	// 8 
		-esp,  altG, -tam1,	// 9 
		 esp,  altG, -tam1,	// 10 
		 esp,  altG,  tam1,	// 11 

	// BaixoG
		-esp,  -altG,  tam1,	// 12 
		-esp,  -altG, -tam1,	// 13
		 esp,  -altG, -tam1,	// 14 
		 esp,  -altG,  tam1,	// 15

	// frenteG
		 esp,  -altG,   tam1,	// 16
		 esp,   altG,   tam1,	// 17
		-esp,   altG,   tam1,	// 18 
		-esp,  -altG,   tam1,	// 19

	// trasG
		-esp,  -altG,   -tam1, // 20
		-esp,   altG,   -tam1, // 21
		 esp,   altG,   -tam1, // 22 
		 esp,  -altG,   -tam1, // 23



	//----------PORTA PEQUENA----------

	// EsquerdaP
		-esp,  -altP,  tamP,	// 24
		-esp,   altP,  tamP,	// 25 
		-esp,   altP, -tamP,	// 26 
		-esp,  -altP, -tamP,	// 27

	// DireitaP
		 esp,  -altP,  tamP,	// 28
		 esp,   altP,  tamP,	// 29
		 esp,   altP, -tamP,	// 30
		 esp,  -altP, -tamP,	// 31

	// CimaP
		-esp,  altP,  tamP,	// 32
		-esp,  altP, -tamP,	// 33
		 esp,  altP, -tamP,	// 34 
		 esp,  altP,  tamP,	// 35 

	// BaixoP
		-esp,  -altP,  tamP,	// 36 
		-esp,  -altP, -tamP,	// 37
		 esp,  -altP, -tamP,	// 38 
		 esp,  -altP,  tamP,	// 39

	// frenteP
		 esp,  -altP,   tamP,	// 40
		 esp,   altP,   tamP,	// 41
		-esp,   altP,   tamP,	// 42 
		-esp,  -altP,   tamP,	// 43

	// trasP
		-esp,  -altP,   -tamP, // 44
		-esp,   altP,   -tamP, // 45
		 esp,   altP,   -tamP, // 46 
		 esp,  -altP,   -tamP, // 47



	//-----------CENA DE VER------------

	// EsquerdaV
			-esp, -altV, tamPR,	// 48
			-esp, altV, tamPR,	// 49
			-esp, altV, -tamPR,	// 50 
			-esp, -altV, -tamPR,	// 51

	// DireitaV
			esp, -altV, tamPR,	// 52
			esp, altV, tamPR,	// 53
			esp, altV, -tamPR,	// 54
			esp, -altV, -tamPR,	// 55

	// CimaV
			-esp, altV, tamPR,	// 56
			-esp, altV, -tamPR,	// 57
			esp, altV, -tamPR,	// 58 
			esp, altV, tamPR,	// 59 

	// BaixoV
			-esp, -altV, tamPR,	// 60
			-esp, -altV, -tamPR,	// 61
			esp, -altV, -tamPR,	// 62
			esp, -altV, tamPR,	// 63

	// frenteV
			esp, -altV, tamPR,	// 64
			esp, altV, tamPR,	// 65
			-esp, altV, tamPR,	// 66
			-esp, -altV, tamPR,	// 67

	// trasV
			-esp, -altV, -tamPR, // 68
			-esp, altV, -tamPR, // 69
			esp, altV, -tamPR, // 70
			esp, -altV, -tamPR, // 71

};

static GLfloat normais[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	//…………………………………………………………………………………………………… x=tam (Direita)
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	//…………………………………………………………………………………………………… y=tam (Cima)
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	//…………………………………………………………………………………………………… y=tam (baixo)
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	//…………………………………………………………………………………………………… y=tam (frente)
	1.0,  1.0,  1.0,
	1.0,  1.0,  1.0,
	1.0,  1.0,  1.0,
	1.0,  1.0,  1.0,
	//…………………………………………………………………………………………………… y=tam (tras)
	-1.0,  -1.0,  -1.0,
	-1.0,  -1.0,  -1.0,
	-1.0,  -1.0,  -1.0,
	-1.0,  -1.0,  -1.0,
};
//------------------------------------------------------------ Cores
static GLfloat cor[] = {
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		//…………………………………………………………………………………………………… x=tam (Direita)
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		//…………………………………………………………………………………………………… y=tam (Cima)
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		//…………………………………………………………………………………………………… y=tam (baixo)
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		//…………………………………………………………………………………………………… y=tam (frente)
		1.0,  1.0,  1.0,
		1.0,  1.0,  1.0,
		1.0,  1.0,  1.0,
		1.0,  1.0,  1.0,
		//…………………………………………………………………………………………………… y=tam (tras)
		-1.0,  -1.0,  -1.0,
		-1.0,  -1.0,  -1.0,
		-1.0,  -1.0,  -1.0,
		-1.0,  -1.0,  -1.0,
};


GLboolean   frenteVisivel = 1;
//PORTA GRANDE
static GLuint		cima[] = { 8, 11, 10,  9 };   // regra da mao direita
static GLuint		direita[] = { 4 , 7, 6, 5 };
static GLuint		esquerda[] = { 0, 3, 2, 1 };
static GLuint		baixo[] = { 12, 15, 14, 13 };
static GLuint		frente[] = { 16, 19, 18, 17 };
static GLuint		tras[] = { 20, 23, 22, 21 };

//PORTA PEQUENA
static GLuint		cimaP[] = { 32, 35, 34,  33 };   // regra da mao direita
static GLuint		direitaP[] = { 28 , 31, 30, 29 };
static GLuint		esquerdaP[] = { 24, 27, 26, 25 };
static GLuint		baixoP[] = { 36, 39, 38, 37 };
static GLuint		frenteP[] = { 40, 43, 42, 41 };
static GLuint		trasP[] = { 44, 47, 46, 45 };


//CENA DE VER
static GLuint		cimaV[] = { 56, 59, 58,  57 };   // regra da mao direita
static GLuint		direitaV[] = { 52 , 55, 54, 53 };
static GLuint		esquerdaV[] = { 48, 51, 50, 49 };
static GLuint		baixoV[] = { 60, 63, 62, 61 };
static GLuint		frenteV[] = { 64, 67, 66, 65 };
static GLuint		trasV[] = { 68, 71, 70, 69 };


//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint		wScreen = 800, hScreen = 600;			//.. janela (pixeis)
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador 
GLfloat  rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat  obsP[] = { rVisao * cos(aVisao), 3.0, rVisao * sin(aVisao) };
GLfloat  angZoom = 90;
GLfloat  incZoom = 3;
GLfloat  angulo = 0.0, altura = 0;
GLboolean sobe = true;

//------------------------------------------------------------ Texturas (5 texturas)
GLuint   texture[5];
RgbImage imag;

static GLfloat texturas[] = {
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1 };

void initTexturas()
{
	//----------------------------------------- Chao
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("pedra1.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//------------------------------------------- Porta G
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("portagrande.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//------------------------------------------- Porta P
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("portaP.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//------------------------------------------- Cena de ver
	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	imag.LoadBmpFile("iron.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}

void inicializa(void)
{
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	
	
	initTexturas();
	glEnable(GL_DEPTH_TEST);   //………………………………………………………………………………Profundidade
	
	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………VertexArrays: vertices + normais + cores
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cor);
	glEnableClientState(GL_COLOR_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Chao : poligono regular
void drawChao() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);  	 glVertex3i(-xC, 0, -xC);
	glTexCoord2f(1.0f, 0.0f); 	 glVertex3i(-xC, 0, xC);
	glTexCoord2f(1.0f, 1.0f);    glVertex3i(xC, 0, xC);
	glTexCoord2f(0.0f, 1.0f);    glVertex3i(xC, 0, -xC);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	glColor4f(RED);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(10, 0, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 10, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 10);
	glEnd();

}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void desenhaPortaG() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);

	
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);

	glPopMatrix();
}

void desenhaPortaP() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cimaP);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerdaP);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direitaP);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixoP);
	
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frenteP);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, trasP);
	glPopMatrix();

}

void desenhaVer() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glPushMatrix();
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cimaV);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerdaV);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direitaV);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixoV);

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frenteV);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, trasV);
	
	glPopMatrix();
}

void drawScene() {

	glPopMatrix();
	//=================================================== Qual o lado visivel ???
	if (frenteVisivel);
	//falta fazer
	glScalef(zoom, zoom, zoom);
	glPushMatrix();




	//PORTA GRANDE
	if (PAberto == true || VAberto) {
		angG = 0;
	}
	if (angG < -90) {
		angG = -90;
	}
	else if (angG > 0) {
		angG = 0;
	}

	if (angG < 0) {
		GAberto = true;
	}
	else {
		GAberto = false;
	}

	glRotatef(angG, 0, 0, 1);
	glTranslatef(0.0, altG, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);  // valor final do ponto 'extremidade'
	glTranslatef(0.0, 0.0, tam1);
	glPushMatrix();
	glScalef(esp * 13, altG, tam1 * 2);
	desenhaPortaG();
	glPopMatrix();


	//RESTO PORTA GRANDE 1
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);  // valor final do ponto 'extremidade'
	glTranslatef(0.0, altP, -(tam1 + tam2));
	glPushMatrix();
	glScalef(esp * 13, altP, tam2 * 2);
	desenhaPortaG();
	glPopMatrix();


	//RESTO PORTA GRANDE 2
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);  // valor final do ponto 'extremidade'
	glTranslatef(0.0, -altP, -(tam2 + tam3));
	glPushMatrix();
	glScalef(esp * 13, altG, tam3 * 2);
	desenhaPortaG();
	glPopMatrix();


	//PORTA PEQUENA
	if (GAberto == true || VAberto == true) {
		angP = 0;
	}
	if (angP > 90) {
		angP = 90;
	}
	else if (angP < 0) {
		angP = 0;
	}

	if (angP > 0) {
		PAberto = true;
	}
	else {
		PAberto = false;
	}

	glRotatef(angP, 0, 1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);  // valor final do ponto 'extremidade'
	glTranslatef(0.0, -altP, tam2 + tamPR + tamP);
	desenhaPortaP();
	glTranslatef(0.0, 0, -(tam2 + 2 * tam3));
	desenhaPortaP();

	//RESTO PORTA PEQUENA 1
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);  // valor final do ponto 'extremidade'
	glTranslatef(0.0, 0.4, 0.2);
	glPushMatrix();
	glScalef(esp * 13, altP1 * 2, tamPR * 16);
	desenhaPortaP();
	glPopMatrix();

	//RESTO PORTA PEQUENA 2
	glTranslatef(0.0, -(altP + altV), -tamP);
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);  // valor final do ponto 'extremidade'
	glPushMatrix();
	glScalef(esp * 13, altP2 * 2, tamPR * 16);
	desenhaPortaP();
	glPopMatrix();

	//CENA DE VER
	if (GAberto == true || PAberto == true) {
		posV = tam3;
	}
	if (posV > tam3 * 6) {
		posV = tam3 * 6;
	}
	else if (posV < tam3) {
		posV = tam3;
	}
	if (posV > tam3) {
		VAberto = true;
	}
	else {
		VAberto = false;
	}
	glTranslatef(-(esp * 0.125), altP - altP1, posV);
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);  // valor final do ponto 'extremidade'
	desenhaVer();


	glPopMatrix();

}



void display(void) {

	//================================================================= APaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//================================================================= Não modificar !!!!!!!!!!!!
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	//================================================================= Não modificar !!!!!!!!!!!!


	//…………………………………………………………………………………………………………………………………………………………Objectos
	drawEixos();
	drawChao();
	drawScene();

	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


	switch (key) {
	case 'z':
	case 'Z':
		angG = angG - 2;	//DESCER PORTÃO
		glutPostRedisplay();
		break;

	case 'X':
	case 'x':
		angG = angG + 2;	//SUBIR PORTÃO
		glutPostRedisplay();
		break;

	case 'A':
	case 'a':
		angP = angP + 2;	//ABRIR PORTA
		glutPostRedisplay();
		break;


	case 'S':
	case 's':
		angP = angP - 2;	//FECHAR PORTA
		glutPostRedisplay();
		break;

	case 'Q':
	case 'q':
		posV = posV + 0.02;	//ABRIR ABERTURA
		glutPostRedisplay();
		break;

	case 'W':
	case 'w':
		posV = posV - 0.02;	//FECHAR ABERTURA
		glutPostRedisplay();
		break;


		//--------------------------- Escape
	case 27:
		exit(0);
		break;
	}

}


void teclasNotAscii(int key, int x, int y) {
	//.. observador pode andar à volda da cena  (setas esquerda / direita)
	//.. observador pode andar para cima e para baixo (setas cima / baixo )

	if (key == GLUT_KEY_UP)   obsP[1] = (obsP[1] + 0.1);
	if (key == GLUT_KEY_DOWN) obsP[1] = (obsP[1] - 0.1);
	if (key == GLUT_KEY_LEFT)  aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT) aVisao = (aVisao - 0.1);

	if (obsP[1] > yC)   obsP[1] = yC;   // limita altura
	if (obsP[1] < -yC)  obsP[1] = -yC;

	obsP[0] = rVisao * cos(aVisao);      // actualiza posicao (X,Z)
	obsP[2] = rVisao * sin(aVisao);

	glutPostRedisplay();
}


//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("|Portão: descer(Z) subir(X)|   |Portinha: abrir(A) fechar(S)|    |Abertura: abrir(Q) fechar(W)|    |Observador:'SETAS'|");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
