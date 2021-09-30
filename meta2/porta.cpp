/*
 * Sofia Meireles Fonseca Costa
 * 2018296218
*/


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
#define GREY	(0.66275, 0.66275, 0.66275, 0.0)
#define PI		 3.14159

//………………………………………………………………………………………………………………………………………………………………………………………… A variar no programa
bool 		Focos[] = { 1,1 };		//.. Dois Focos ligados ou desligados
GLfloat		aberturaFoco = 100.0;		//.. angulo inicial do foco
GLfloat		anguloINC = 3.0;		//.. incremento
GLfloat		anguloMIN = 3.0;		//.. minimo
GLfloat		anguloMAX = 70.0;		//.. maximo




void initMaterials(int material);

char Materiais[18][30] = {
	"Esmerald",  "Jade",  "obsidian",    "Pearl",        "Ruby",
	"Turquoise", "Brass", "Bronze",      "Chrome",       "Copper",
	"Gold",      "Silver","blackPlastic","cyankPlastic", "greenPlastic",
	"redPlastic", "whitePlastic","yellowPlastic" };

#include "RgbImage.h"

//================================================================================
//===========================================================Variaveis e constantes

GLfloat grey[] = { 1.0, 1.0, 1.0, 1.0};
GLboolean nevoeiro = FALSE;

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

	// PAREDE
			1.5, -1.5, 1.5, // 72
			1.5, 1.5, 1.5, // 73
			1.5, 1.5, -1.5, // 74
			1.5, -1.5, -1.5, // 75

};

static GLfloat normais[] = {
	//----------- PORTA GRANDE ------------
	// EsquerdaG
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	// DireitaG
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	// CimaG
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	// BaixoG
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	// frenteG
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	// trasG
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,

	//----------- PORTA PEQUENA ------------
	// EsquerdaP
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	// DireitaP
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	// CimaP
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	// BaixoP
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	// frenteP
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	// trasP
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,

	//----------- CENA DE VER ------------
	// EsquerdaV
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	// DireitaV
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	// CimaV
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	// BaixoV
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	// frenteV
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	// trasV
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,
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

//PAREDE
static GLuint		parede[] = { 72, 75, 74, 73 };	// regra da mao direita


//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint		wScreen = 800, hScreen = 600;			//.. janela (pixeis)
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;		//.. Mundo  (unidades mundo)
char     texto[30];
GLint    msec = 100;
GLfloat angPersp = 109.0;

//------------------------------------------------------------ Visualizacao/Observador 
GLfloat  rVisao = 3.0, aVisao = 0.5 * PI, incVisao = 0.1;
GLfloat  obsPini[] = { 1, 2.0, static_cast<GLfloat>(0.5 * xC) };
GLfloat  obsP[] = { obsPini[0] - rVisao * cos(aVisao), obsPini[1], obsPini[2] - rVisao * sin(aVisao) }; GLfloat  angZoom = 90;
GLfloat  incZoom = 3;
GLfloat  angulo = 0.0, altura = 0;
GLboolean sobe = true;

//------------------------------------------------------------ Texturas (5 texturas)
GLuint   texture[5];
RgbImage imag;

GLfloat Pos1[] = { -1.0f, 10.0f,  1.0f, 1.0f };   // Foco 1
GLfloat Pos2[] = { 2.0f, 10.0f,  2.0f, 1.0f };   // Foco 2

//…………………………………………………………………………………………………………………………………
GLint	  dim = 64;   //numero divisoes da grelha

//---------------------------------------------------- AMBIENTE - fixa
GLint   Dia = 1;     //:::   'D'  
GLfloat intensidadeDia = 0.9;
GLfloat luzGlobalCorAmb[4] = { intensidadeDia, intensidadeDia,intensidadeDia, 1.0 };   // 

//---------------------------------------------------- Luz pontual no TETO (eixo Y)
GLint   ligaTeto = 1;		 //:::   'T'  
GLfloat intensidadeT = 0.3;  //:::   'I'  
GLint   luzR = 1;		 	 //:::   'R'  
GLint   luzG = 1;			 //:::   'G'  
GLint   luzB = 1;			 //:::   'B'  
GLfloat localPos[4] = { 0.0, 10.0, 0.0, 1.0 };
GLfloat localCorAmb[4] = { 0, 0, 0, 0.0 };
GLfloat localCorDif[4] = { luzR, luzG, luzB, 1.0 };
GLfloat localCorEsp[4] = { luzR, luzG, luzB, 1.0 };
GLfloat localAttCon = 1;
GLfloat localAttLin = 1;
GLfloat localAttQua = 1;

GLfloat   quadS = 5.0;
GLint     material = 8;

GLboolean malhaa = FALSE;

GLfloat matAmb[] = { 0.8 ,0.8 ,0.8 };
GLfloat matDif[] = { 0.55 ,0.55 ,0.55 };
GLfloat matSpec[] = { 0.87 ,0.87 ,0.87 };
GLint matCoef = 0.25 * 128;

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

void materialSpec() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, matCoef);
}

//…………………………………………………………………………………………………………………………………………… LUZES
void initLights(void) {
	GLfloat Foco_direccao[] = { 0, -1, 0, 0 };	//……… -Z
	GLfloat Foco1_cor[] = { 0, 1,  0, 1 };	//……… Cor da luz 1
	GLfloat Foco2_cor[] = { 1, 0,  0, 1 };	//……… Cor da luz 2
	GLfloat Foco_ak = 1.0;
	GLfloat Foco_al = 0.05f;
	GLfloat Foco_aq = 0.0f;
	GLfloat Foco_Expon = 2.0;		// Foco, SPOT_Exponent

	//…………………………………………………………………………………………………………………………………………… Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);

	//…………………………………………………………………………………………………………………………………………… Teto
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);

	//……………………………………………………………………………………………………………………………Foco Esquerda
	glLightfv(GL_LIGHT0, GL_POSITION, Pos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Foco1_cor);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, Foco_Expon);

	//……………………………………………………………………………………………………………………………Foco Direita
	glLightfv(GL_LIGHT1, GL_POSITION, Pos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Foco2_cor);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon);
}

void initTexturas()
{
	//----------------------------------------- Chao
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("pedra1.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//------------------------------------------- parede
	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	imag.LoadBmpFile("parede1.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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
	glEnable(GL_NORMALIZE);

	initTexturas();
	glEnable(GL_DEPTH_TEST);   //………………………………………………………………………………Profundidade
	
	//…………………………………………………………………………………………………………………………… ILUMINACAO / MAteriais
	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);


	initLights();
	initMaterials(22);

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
	initMaterials(8);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glTranslatef(0, 0.0, 0);
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
	initMaterials(7); //white plastic
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
	glDisable(GL_TEXTURE_2D);
}

void desenhaPortaP() {
	glEnable(GL_TEXTURE_2D);
	//materialSpec(); //white plastic
	initMaterials(7);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cimaP);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerdaP);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direitaP);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixoP);
	
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frenteP);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, trasP);
	
	glDisable(GL_TEXTURE_2D);
	
}

void desenhaVer() {
	initMaterials(7); //bronze
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glColor4f(0.000, 1.000, 0.000, 0.15);
	glPushMatrix();
	//glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cimaV);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerdaV);
	//glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direitaV);
	//glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixoV);

	//glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frenteV);
	//glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, trasV);
	
	glPopMatrix();

	//glBlendFunc(GL_ONE, GL_ZERO);
	glDisable(GL_BLEND);
	

}

void desenhaParede() {
	initMaterials(material); //bronze
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glPushMatrix();
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, parede);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawMalha();
void desenhaTexto(char* string, GLfloat x, GLfloat y, GLfloat z);

void drawInformacao(){
	float x = 0;
	float y = 10;
	float z = -15;

	char linhas[8][30] = { "[T] Teto", "[D] Dia/Noite", "[I] Intensidade", "[O] Foco", "[K] Chao/Malha", "[M] Material Parede", "[N] Nevoeiro","[R/G/B] Cor da Luz" };

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR);
	glColor3f(1.0, 1.0, 1.0);

	for (int i = 0; i<8; i++) {
		snprintf(texto, 30, linhas[i]);
		desenhaTexto(texto, x, y, z);
		y-=1.1;
	}	
	glDisable(GL_COLOR);
	glEnable(GL_LIGHTING);;
}

void drawScene() {

	glPopMatrix();
	//=================================================== Qual o lado visivel ???
	if (frenteVisivel);
	//falta fazer
	glScalef(zoom, zoom, zoom);
	glPushMatrix();

	

	if (nevoeiro == TRUE) {
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_EXP2);
		glFogf(GL_FOG_DENSITY, 0.035);
		glFogfv(GL_FOG_COLOR, grey);
	}
	else {
		glDisable(GL_FOG);
	}

	if (malhaa == TRUE) {
		drawMalha();
	}
	else {
		drawChao();
	}



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
	//PAREDE
	glTranslatef(-0.55, altG-0.25, 1.60);
	glScalef(0.4, 0.86, 0.4);
	desenhaParede();
	glTranslatef(0.0, 0.0, -7.0);
	//glScalef(0.4, 0.86, 0.4);
	desenhaParede();
	glTranslatef(0.9, 2.25, 3.5);
	glScalef(0.45, 0.6, 3.3);
	desenhaParede();
	glPopMatrix();

	//PORTA GRANDE
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



	//glPopMatrix();

}

void drawMalha() {
	int				i, j;
	float			med_dim = (float)dim / 2;
	//----------------------------------------------- Desenha malha poligonos
	glPushMatrix();
	glTranslatef(-5.0, 0.0, -10.0);  // meio do poligono 
	glRotatef(90, 1, 0, 0);
	glScalef(10, 10, 10);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glNormal3f(0, 1, 0);          //normal 
	glBegin(GL_QUADS);
	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++) {
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d((float)j / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)(i + 1) / med_dim, 0);
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d((float)j / med_dim, (float)(i + 1) / med_dim, 0);
		}
	glEnd();

	glPopMatrix();
}

//================================================================================
//======================================================================== DISPLAY
void desenhaTexto(char* string, GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(2, 2, 2);
	glRasterPos2f(0, 0);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *string++);
	glPopMatrix();
}

GLvoid resize(GLsizei width, GLsizei height) {
	wScreen = width;
	hScreen = height;
	glViewport(0, 0, wScreen, hScreen);
	glutPostRedisplay();
}

void iluminacao() {
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
	if (ligaTeto)  glEnable(GL_LIGHT0);
	else   		  glDisable(GL_LIGHT0);
}


void display(void) {

	//================================================================= APaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//================================================================= Não modificar !!!!!!!!!!!!
	glEnable(GL_LIGHTING);
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	//================================================================= Não modificar !!!!!!!!!!!!
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angPersp, (float)wScreen / hScreen, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsPini[0], obsPini[1], obsPini[2], obsP[0], obsP[1], obsP[2], 0, 1, 0);

	//============================================Esferasverde e vermelha
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	//============================================ Grelha de polionos (dim*dim)
	//============================================ O ponto minimo   e (0,0), o maximo (2,2)
	//============================================ A textura minimo e (0,0), o maximo (1,1)
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);


	//----------------------------------------------- Quadro Material - branco
	float corAmb[] = { 0.7,0.7,0.7,1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, corAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corAmb);
		


	//…………………………………………………………………………………………………………………………………………………………Objectos
	iluminacao();
	//drawEixos();
	drawInformacao();
	drawScene();
	

	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers(); 
}


void updateLuz() {
	localCorAmb[0] = luzR * intensidadeT;
	localCorAmb[1] = luzG * intensidadeT;
	localCorAmb[2] = luzB * intensidadeT;
	localCorDif[0] = luzR * intensidadeT;
	localCorDif[1] = luzG * intensidadeT;
	localCorDif[2] = luzB * intensidadeT;
	localCorEsp[0] = luzR * intensidadeT;
	localCorEsp[1] = luzG * intensidadeT;
	localCorEsp[2] = luzB * intensidadeT;;
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
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

		//===================================== ILUMINCAAO
		//--------------------------- Dia/noite
	case 'd':	case 'D':
		Dia = !Dia;
		if (Dia) { luzGlobalCorAmb[0] = 0.7;   luzGlobalCorAmb[1] = 0.7;   luzGlobalCorAmb[2] = 0.7; }
		else { luzGlobalCorAmb[0] = 0.2;   luzGlobalCorAmb[1] = 0.2;   luzGlobalCorAmb[2] = 0.2; }
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
		glutPostRedisplay();
		break;

		//--------------------------- TETO
	case 't':case 'T':
		ligaTeto = !ligaTeto;
		updateLuz();
		glutPostRedisplay();
		break;
		//--------------------------- Iluminacaoda sala
	case 'i': case 'I':
		intensidadeT = intensidadeT + 0.1;
		if (intensidadeT > 1.1) intensidadeT = 0;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'r':case 'R':
		luzR = (luzR + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'g':case 'G':
		luzG = (luzG + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'b':case 'B':
		luzB = (luzB + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;

		//--------------------------- MAterial
	case 'm': case 'M':
		material = (material + 1) % 18;
		initMaterials(material);
		glutPostRedisplay();
		break;
	case 'O':
	case 'o':
		Focos[1] = !Focos[1];
		if (Focos[1] == 0)
			glDisable(GL_LIGHT1);
		else
			glEnable(GL_LIGHT1);
		glutPostRedisplay();
		break;

	case 'K':
	case 'k':
		if (malhaa == FALSE) {
			malhaa = TRUE;
		}
		else {
			malhaa = FALSE;
		}
		glutPostRedisplay();
		break;

	case 'L':
	case 'l':
		if (matSpec[0] > 1) {
			matSpec[0] = 0.0;
		}
		else {
			for (int i = 0; i < 3; i++) {
				matSpec[i] += 0.1;
			}
		}
		glutPostRedisplay();
		break;

	case 'N':
	case 'n':
		if (nevoeiro == FALSE) {
			nevoeiro = TRUE;
		}
		else {
			nevoeiro = FALSE;
		}
		glutPostRedisplay();
		break;

	}
}


void teclasNotAscii(int key, int x, int y) {

	if (key == GLUT_KEY_UP) {
		obsPini[0] = obsPini[0] + incVisao * cos(aVisao);
		obsPini[2] = obsPini[2] - incVisao * sin(aVisao);
	}
	if (key == GLUT_KEY_DOWN) {
		obsPini[0] = obsPini[0] - incVisao * cos(aVisao);
		obsPini[2] = obsPini[2] + incVisao * sin(aVisao);
	}
	if (key == GLUT_KEY_LEFT)
		aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT)
		aVisao = (aVisao - 0.1);

	obsP[0] = obsPini[0] + rVisao * cos(aVisao);
	obsP[2] = obsPini[2] - rVisao * sin(aVisao);
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
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}
