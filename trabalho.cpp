// Feito no Linux por: Lara Pereira Finamora Zoio e Nicolas Caseiro de Abreu
/* Para funcionar no Windows troque a bibloteca <cmath> por <math.h>
   desconte o float M_PI* e certifique-se que as imagens chamadas estão baixadas*/

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glut.h>
#include <cmath>

GLuint idTexturaFundo;
GLuint idTexturaSol;
GLuint idTexturaMercurio;
GLuint idTexturaVenus;
GLuint idTexturaTerra;
GLuint idTexturaLua;
GLuint idTexturaMarte;
GLuint idTexturaJupiter;
GLuint idTexturaSaturno;
GLuint idTexturaUrano;
GLuint idTexturaNetuno;
GLuint idTexturaAneisSaturno;

static int translacao, rotacao = 0;

struct Planeta
{
	float distanciaSol;
	float tamanho;
	float translacao;
	float rotacao;
	float r, g, b;
	GLuint texturaID;
};

Planeta planetas[] = {
	{33.3, 4.0, 5.2, 60.0, 0.7, 0.5, 0.5, 0},	  // Merc�rio
	{45.0, 7.0, 6.4, 200.0, 1.0, 0.5, 0.3, 0},	  // V�nus
	{63.3, 8.0, 10.0, 150.0, 0.2, 0.5, 0.8, 0},	  // Terra
	{80.0, 6.7, 17.0, 120.0, 1.0, 0.2, 0.0, 0},	  // Marte
	{110.0, 11.0, 26.0, 100.0, 1.0, 0.8, 0.6, 0}, // J�piter
	{142.0, 10.0, 33.0, 90.0, 0.8, 0.8, 0.6, 0},  // Saturno
	{175.0, 9.5, 42.0, 80.0, 0.6, 0.8, 0.9, 0},	  // Urano
	{200.0, 9.0, 60.0, 70.0, 0.2, 0.3, 1.0, 0}	  // Netuno
};

void myWireSphere(GLfloat raio, int fatias, int camadas)
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutWireSphere(raio, fatias, camadas);
	glPopMatrix();
}

void bizuTexturaDaEsfera(GLfloat raio, int fatias, int camadas, GLuint textura)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);

	GLUquadric *quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	gluSphere(quadric, raio, fatias, camadas);
	glPopMatrix();

	gluDeleteQuadric(quadric);
	glDisable(GL_TEXTURE_2D);
}

void desenhaFundo()
{
	glDisable(GL_LIGHTING);
	glDepthMask(GL_FALSE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, idTexturaFundo);

	GLUquadric *quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricOrientation(quadric, GLU_INSIDE);

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	gluSphere(quadric, 1000.0, 30, 30);
	glPopMatrix();

	gluDeleteQuadric(quadric);
	glDepthMask(GL_TRUE);
	glDisable(GL_TEXTURE_2D);
}

void desenhaOrbita(float raio)
{
	glDisable(GL_LIGHTING);
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_LINE_LOOP);
	//float M_PI = 3.1415;
	for (int i = 0; i < 360; i++)
	{
		float ang = i * M_PI / 180.0;
		glVertex3f(cos(ang) * raio, 0.0, sin(ang) * raio);
	}
	glEnd();
	glEnable(GL_LIGHTING);
}

void desenhaPlaneta(Planeta &planeta)
{
	desenhaOrbita(planeta.distanciaSol);

	glPushMatrix();
	glRotatef((GLfloat)translacao / planeta.translacao, 0.0, 1.0, 0.0);
	glTranslatef(planeta.distanciaSol, 0.0, 0.0);
	glRotatef((GLfloat)rotacao / planeta.rotacao, 0.0, 1.0, 0.0);

	if (planeta.texturaID != 0)
	{
		bizuTexturaDaEsfera(planeta.tamanho, 20, 20, planeta.texturaID);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glColor3f(planeta.r, planeta.g, planeta.b);
		myWireSphere(planeta.tamanho, 20, 20);
		glEnable(GL_LIGHTING);
	}

	// Lua da Terra
	if (&planeta == &planetas[2])
	{
		glPushMatrix();
		glRotatef(translacao / 10.0, 0.0, 1.0, 0.0);
		glTranslatef(11.1, 0.0, 0.0);
		glDisable(GL_LIGHTING);
		bizuTexturaDaEsfera(1.1, 20, 20, idTexturaLua);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	// Anel de Saturno
	if (&planeta == &planetas[5])
	{
		glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glDisable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D, idTexturaAneisSaturno);
		glutWireTorus(0.9, 20.2, 30, 30);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	glPopMatrix();
}

void iluminacaoSol()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat luzAmbiente[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat luzDifusa[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat posicaoLuz[] = {0.0f, 0.0f, 0.0f, 1.0f};

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	glMaterialfv(GL_FRONT, GL_SPECULAR, luzDifusa);
	glMateriali(GL_FRONT, GL_SHININESS, 10);
}

GLuint carregarTextura(const char *nomeArquivo)
{
	GLuint texturaID;
	int largura, altura, canais;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *imagem = stbi_load(nomeArquivo, &largura, &altura, &canais, 0);

	if (imagem)
	{
		glGenTextures(1, &texturaID);
		glBindTexture(GL_TEXTURE_2D, texturaID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, (canais == 4 ? GL_RGBA : GL_RGB), largura, altura, 0, (canais == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, imagem);
		stbi_image_free(imagem);
		return texturaID;
	}
	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	desenhaFundo();

	glPushMatrix();

	//Sol
	glDisable(GL_LIGHTING);

	glPushMatrix();
	bizuTexturaDaEsfera(18.0, 40, 40, idTexturaSol);
	glPopMatrix();

	glEnable(GL_LIGHTING);

	// Planetas
	for (int i = 0; i < 8; ++i)
		desenhaPlaneta(planetas[i]);

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

static GLfloat u = 0.0;
static GLfloat du = 0.1;
static float aceleracao = 10;
static float camX = 0.0, camY = 125.0, camZ = 275.0;

void tempo(int v)
{
	u += du;
	rotacao += 1.0f * aceleracao;
	translacao += 1.0f * aceleracao;

	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);

	GLfloat posicaoLuz[] = {0.0f, 0.0f, 0.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, tempo, v);
}

void redimensionar(GLint largura, GLint altura)
{
	glViewport(0, 0, largura, altura);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, (GLfloat)largura / (GLfloat)altura, 1.0, 5000.0);
	glMatrixMode(GL_MODELVIEW);
}

void bizuTeclas(unsigned char tecla, int x, int y)
{
	switch (tecla)
	{
	case 'w':
		camY += 5;
		break;
	case 's':
		camY -= 5;
		break;
	case 'a':
		camZ += 5;
		break;
	case 'd':
		camZ -= 5;
		break;
	case '+':
		aceleracao *= 1.1f;
		break;
	case '-':
		aceleracao /= 1.1f;
		break;
	case ' ':
		static float a;
		aceleracao = aceleracao ? (a = aceleracao, 0) : a;
		break;
	case '0':
		aceleracao = 10, camX = 0.0, camY = 125.0, camZ = 275.0;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 400);
	glutCreateWindow("Sistema Solar");

	glEnable(GL_DEPTH_TEST);

	iluminacaoSol();

	// Texturas
	idTexturaSol = carregarTextura("2k_sun.jpg");
	idTexturaMercurio = carregarTextura("2k_mercury.jpg");
	idTexturaVenus = carregarTextura("2k_venus_surface.jpg");
	idTexturaTerra = carregarTextura("2k_earth_daymap.jpg");
	idTexturaLua = carregarTextura("2k_moon.jpg");
	idTexturaMarte = carregarTextura("2k_mars.jpg");
	idTexturaJupiter = carregarTextura("2k_jupiter.jpg");
	idTexturaSaturno = carregarTextura("2k_saturn.jpg");
	idTexturaAneisSaturno = carregarTextura("2k_saturn_ring_alpha.png");
	idTexturaUrano = carregarTextura("2k_uranus.jpg");
	idTexturaNetuno = carregarTextura("2k_neptune.jpg");
	idTexturaFundo = carregarTextura("2k_stars_milky_way.jpg");

	planetas[0].texturaID = idTexturaMercurio;
	planetas[1].texturaID = idTexturaVenus;
	planetas[2].texturaID = idTexturaTerra;
	planetas[3].texturaID = idTexturaMarte;
	planetas[4].texturaID = idTexturaJupiter;
	planetas[5].texturaID = idTexturaSaturno;
	planetas[6].texturaID = idTexturaUrano;
	planetas[7].texturaID = idTexturaNetuno;

	glutDisplayFunc(display);
	glutReshapeFunc(redimensionar);
	glutTimerFunc(1000, tempo, 0);
	glutKeyboardFunc(bizuTeclas);

	glClearColor(0.0, 0.0, 0.0, 1.0);

	glutMainLoop();
	return 0;
}