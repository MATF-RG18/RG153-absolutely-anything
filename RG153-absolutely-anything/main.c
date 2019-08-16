#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#define TREE_NUM 10
#define COLOR_NUM 3
#define _POSIX_C_SOURCE 199309L

typedef struct Color{
	GLfloat ambient_coeffs[4];
	GLfloat diffuse_coeffs[4];
	GLfloat specular_coeffs[4];
}Color;

 
  /* Konstanta pi. */
const static float pi = 3.141592653589793;
 
  /* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int id);
static void draw_tree();
static void draw_forest();
static void draw_ground();
static void draw_something();
 
  /*
   * Funkcije za lakse testiranje programa:
   *
   * draw_debug_cube -- iscrtava kvadar ciji je centar u (x, y, z),
   *                    a dimenzije w x h x d
   *
   * draw_debug_coosys -- iscrtava koordinatni sistem
   *
   */
 
static void draw_debug_cube(float x, float y, float z, float w, float h,
                float d);
static void draw_debug_coosys();
 
  /* Parametar animacije, fleg koji odredjuje da li je
   * animacija u toku ili nije */
#define TIMER_ID 0
#define TIMER_ID2 0
#define TIMER_INTERVAL 1



double animation_parameter = 0;
int animation_ongoing = 0;
double brzina=0;
int crtajDrvece=1;
int nivo = 1;
int posX = 0;
int posY = 0;

//niz indikatora koja drveta ce se zapravo crtati
bool drawColor[COLOR_NUM];

/*Spisak svih mogucih materijala, za sada su koef. oblika atribut_coeff[inicijal boje materijala]*/

GLfloat ambient_coeffs[] = { 0.3, 0.7, 0.3, 1 };
GLfloat diffuse_coeffs[] = { 0.2, 1, 0.2, 1 };
GLfloat specular_coeffs[] = { 0.5, 0.5, 0.5, 1 };
GLfloat shininess = 50;

GLfloat ambient_coeffsR[] = { 0.7, 0.3, 0.3, 1 };
GLfloat diffuse_coeffsR[] = { 1, 0.2, 0.2, 1 };
GLfloat specular_coeffsR[] = { 0.5, 0.5, 0.5, 1 };


GLfloat ambient_coeffsG[] = { 0.3, 0.7, 0.3, 1 };
GLfloat diffuse_coeffsG[] = { 0.2, 0.5, 0.2, 1 };
GLfloat specular_coeffsG[] = { 0, 0, 0, 0.1 };

GLfloat ambient_coeffsB[] = { 0.3, 0.3, 0.7, 1 };
GLfloat diffuse_coeffsB[] = { 0.2, 0.2, 1, 1 };
GLfloat specular_coeffsB[] = { 0, 0, 0, 1 };

GLfloat ambient_coeffsBrown[] = { 139/255.0, 69/255.0, 19/255.0, 1 };
GLfloat diffuse_coeffsBrown[] = { 139/255.0, 89/255.0, 29/255.0, 1 };
GLfloat specular_coeffsBrown[] = { 0, 0, 0, 1 };

Color Colors[3];

 
  /*
   * Funkcija koja iscrtava zelenu podlogu
   */
void draw_ground()
{
	/*postavljanje podloge, odnosno grass plain*/
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsG);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsG);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsG);
	glMateriali(GL_FRONT,GL_SHININESS,50);

	glPushMatrix();
	glTranslatef(0,0,-0.5);
	glScalef(10,10,0.3);
	glutSolidCube(1);
	glPopMatrix();
}
void draw_forest()
{
	srand(101);

	for(int i=0; i<TREE_NUM; i++)
	{
		
		/*odredjivanje polarnih koordinata svakog drveta*/
		double a = ((double)rand()/RAND_MAX)*360;
		double r = ((double)rand()/RAND_MAX)*5;
		int random = rand();
		int randomColor = (int)(((double)(random*1.0)/(double)(RAND_MAX))*3);
		printf("number:%jd\nColor: %d\n",random,randomColor);
		if(drawColor[randomColor]==true)
		{
			glPushMatrix();
			glTranslatef(r*cos(a),r*sin(a),0);
			draw_tree(randomColor);
			glPopMatrix();
		}else
		{
			for(int i=0;i<80;i++)
				rand();
		}
	}
}
void draw_tree(int randomColor)
{
	if(drawColor[randomColor]==false)return;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsBrown);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsBrown);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsBrown);
	glMateriali(GL_FRONT,GL_SHININESS,25);	


	glPushMatrix();
	glScalef(0.2,0.2,1.5);
	GLUquadric* quad = gluNewQuadric();
	gluCylinder(quad,1,1,1,50,50);
	glPopMatrix();


	GLfloat ambient_coeffsRandom[] = { 0.05, 0.05, 0.05, 1 };
	GLfloat diffuse_coeffsRandom[] = { 0.05, 0.05, 0.05, 1 };
	GLfloat specular_coeffsRandom[] = { 0.05, 0.05, 0.05, 0.5 };
	ambient_coeffsRandom[randomColor]=0.7;
	diffuse_coeffsRandom[randomColor]=1;


	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsRandom);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsRandom);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsG);

	/*glavni deo krosnje*/
	glPushMatrix();
	glTranslatef(0,0,1.5);
	glScalef(0.2,0.2,0.2);
	glutSolidSphere(2.8,50,50);
	glPopMatrix();

	/*delovi krosnje*/

	for(int i =0;i<40;i++)
	{
		
		double a = ((double)rand()/RAND_MAX)*360;
		double b = ((double)rand()/RAND_MAX)*360;
		glPushMatrix();

		glTranslatef(0.56*cos(a)*cos(b), 0.56*sin(a)*cos(b), 0.56*sin(b)+1.5);
		glScalef(0.1,0.1,0.1);
		glutSolidSphere(2.8,50,50);
		glPopMatrix();

	}



}

 
static void on_keyboard(unsigned char key, int x, int y)
{
	if(nivo==0)
	{
		switch(key)
		{
			case '1':
			{
				nivo = 1;
				glutPostRedisplay();
			}
			break;
			case '0':
			{
				nivo = 0;
				glutPostRedisplay();
			}
			break;
		}
	}
	if(nivo==1)
	{
		switch(key)
		{
			case 'a':
			posX +=1;
			glutPostRedisplay();
			break;

			case 'd':
			posX -=1;
			glutPostRedisplay();
			break;

			case 's':
			posY +=1;
			glutPostRedisplay();
			break;

			case 'w':
			posY -=1;
			glutPostRedisplay();
			break;

			case 'r':
			drawColor[0]=(drawColor[0]==false)? true :false;
			glutPostRedisplay();
			break;

			case 'g':
			drawColor[1]=(drawColor[1]==false)? true :false;
			glutPostRedisplay();
			break;
			case 'b':
			drawColor[2]=(drawColor[2]==false)? true :false;
			glutPostRedisplay();
			break;

			// case 'S':
			// case 's':
			// {
			// 	animation_ongoing=0;
			// }
			break;
			// case 'd':
			// case 'D':
			// {
			// 	if(crtajDrvece==1)
			// 		crtajDrvece=0;
			// 	else
			// 		crtajDrvece=1;
			// 	animation_ongoing=0;
			// 	glutPostRedisplay();
			// }
			// break;

			case '-':
			{
				if(!animation_ongoing)
				{
					
					animation_ongoing=1;
					glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID2);
					

				}

			}
			break;
			


		}
	}

}
 
static void on_display(void)
{


    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    /* Inicijalizuje se matrica transformacije. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX+8*sin(animation_parameter*2*pi),posY+8*cos(animation_parameter*2*pi),4,posX,posY,0,0,0,1);
	
	

    if(nivo == 0)
    {
	    //drawTitleScreen();
	}

    else if(nivo == 1)
    {
	    draw_ground();
		

	    glPushMatrix();
	    glTranslatef(0,0,0);
	    if(crtajDrvece==1)
	    	draw_forest();

	    glPopMatrix();
	}


    draw_debug_coosys();


 
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
 
int main(int argc, char **argv)
{

    /* Parametri svetla i podrazumevanog materijala */
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat light_diffuse[] = { 0.3, 0.3, 0.3, 1 };
    GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1 };
	
	/*Pravljenja crvene,plave i zelene boje*/
	for(int i=0; i<COLOR_NUM;i++)
	{
		Colors[i].ambient_coeffs[0]=0.3;
		Colors[i].ambient_coeffs[1]=0.3;
		Colors[i].ambient_coeffs[2]=0.3;
		Colors[i].ambient_coeffs[3]=1;

		Colors[i].diffuse_coeffs[0]=0.2;
		Colors[i].diffuse_coeffs[1]=0.2;
		Colors[i].diffuse_coeffs[2]=0.2;
		Colors[i].diffuse_coeffs[3]=1;

		Colors[i].specular_coeffs[0]=0;
		Colors[i].specular_coeffs[1]=0;
		Colors[i].specular_coeffs[2]=0;
		Colors[i].specular_coeffs[3]=1;

		Colors[i].ambient_coeffs[i]=0.7;
		Colors[i].diffuse_coeffs[0]=1;
	}
	
	//inicijalizacija, sve drvece se iscrtava
	for(int i=0;i<TREE_NUM;i++)
	{
		drawColor[i]=true;
	}
 
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
 
    /* Kreira se prozor. */
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
 
    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
 
    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);

	/* Pozicija svetla (u pitanju je beskonacno daleko svetlo). */
    GLfloat light_position[] = { 100, 100, 100, 0 };
 
    glEnable(GL_LIGHTING);
 
    /* Postavljaju se svojstva prvog svetla */
    glEnable(GL_LIGHT0);
 
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);
 

    /* Postavljaju se svojstva materijala */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

     /* Program ulazi u glavnu petlju. */
    glutMainLoop();
 
    return 0;
}
static void on_timer(int id)
{
	if(id==TIMER_ID)
	{	
	    animation_parameter += 0.001;

	 	glutPostRedisplay();
	    if (animation_ongoing) {
	        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
	    }
	}
	else if(id==TIMER_ID2)
	{
	    animation_parameter -= 0.001;


	 	glutPostRedisplay();
	    if (animation_ongoing) {
	        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
	    }
	}
	if(animation_parameter>=1)animation_parameter=0;
}
 
static void on_reshape(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);
 
    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width / height, 1, 100);
}
 
static void draw_debug_cube(float x, float y, float z, float w, float h,
                float d)
{
    glDisable(GL_LIGHTING);
    glColor3f(1, 0.5, 0.5);
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(w, h, d);
    glutWireCube(1);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}
 
static void draw_debug_coosys()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(100, 0, 0);
    glVertex3f(0, 0, 0);
 
    glColor3f(0, 1, 0);
    glVertex3f(0, 100, 0);
    glVertex3f(0, 0, 0);
 
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 100);
    glVertex3f(0, 0, 0);
    glEnd();
    glEnable(GL_LIGHTING);
}