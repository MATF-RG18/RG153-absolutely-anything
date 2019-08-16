#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#define _POSIX_C_SOURCE 199309L


 
  /* Konstanta pi. */
const static float pi = 3.141592653589793;
 
  /* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int);
static void draw_tree();
static void draw_forest();
static void draw_ground();
 
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
int nivo = 0;
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
GLfloat specular_coeffsG[] = { 0, 0, 0, 1 };

GLfloat ambient_coeffsB[] = { 0.3, 0.3, 0.7, 1 };
GLfloat diffuse_coeffsB[] = { 0.2, 0.2, 1, 1 };
GLfloat specular_coeffsB[] = { 0, 0, 0, 1 };

GLfloat ambient_coeffsBrown[] = { 139/255.0, 69/255.0, 19/255.0, 1 };
GLfloat diffuse_coeffsBrown[] = { 139/255.0, 89/255.0, 29/255.0, 1 };
GLfloat specular_coeffsBrown[] = { 0, 0, 0, 1 };
 
  /*
   * Funkcija koja iscrtava zeleni most
   */
void draw_ground()
{
	/*postavljanje podloge, odnosno grass plain*/
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsG);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsG);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsG);
	glMateriali(GL_FRONT,GL_SHININESS,100);

	glPushMatrix();
	glTranslatef(0,0,-0.5);
	glScalef(10,10,0.3);
	glutSolidCube(1);
	glPopMatrix();
}
void draw_forest()
{
	srand(50);
	for(int i=0; i<20; i++)
	{
		/*odredjivanje polarnih koordinata svakog drveta*/
		double a = ((double)rand()/RAND_MAX)*360;
		double r = ((double)rand()/RAND_MAX)*5;
		glPushMatrix();
		glTranslatef(r*cos(a),r*sin(a),0);
		draw_tree();
		glPopMatrix();


	}
}
void draw_tree()
{
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsBrown);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsBrown);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsBrown);	

	glPushMatrix();
	glScalef(0.2,0.2,1.5);
	GLUquadric* quad = gluNewQuadric();
	gluCylinder(quad,1,1,1,50,50);
	glPopMatrix();

	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsG);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsG);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsG);

	/*glavni deo krosnje*/
	glPushMatrix();
	glTranslatef(0,0,1.5);
	glScalef(0.2,0.2,0.2);
	glutSolidSphere(2.8,50,50);
	glPopMatrix();

	/*delovi krosnje*/

	for(int i =0;i<50;i++)
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
			case 27:
			animation_parameter=0;
			brzina=0;
			nivo=0;
			glutPostRedisplay();
			break;
			case 'S':
			case 's':
			{
				animation_ongoing=0;
				brzina=0;

			}
			break;
			case 'd':
			case 'D':
			{
				if(crtajDrvece==1)
					crtajDrvece=0;
				else
					crtajDrvece=1;
				animation_ongoing=0;
				brzina=0;
				glutPostRedisplay();
			}
			break;

			case '-':
			{
				if(!animation_ongoing)
				{
					
					animation_ongoing=1;
					glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID2);
					

				}

			}
			break;
			case 'G':
			case 'g':
			{
				if(!animation_ongoing)
				{
					
					animation_ongoing=1;
					glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
					

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
    gluLookAt(8,8,2,0,0,0,0,0,1);
 
    if(nivo == 0)
    {
	    drawTitleScreen();
	}

    else if(nivo == 1)
    {
	    draw_ground();

	    glPushMatrix();
	    glTranslatef(0,0,animation_parameter);
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
    GLfloat light_position[] = { 1, 100, 100, 0 };
 
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
	    animation_parameter += 0.01;

	    brzina+=0.01;

	 	glutPostRedisplay();
	    if (animation_ongoing) {
	        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
	    }
	}
	else if(id==TIMER_ID2)
	{
	    animation_parameter -= 0.01;

	    brzina= brzina - 0.01;

	 	glutPostRedisplay();
	    if (animation_ongoing) {
	        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
	    }
	}
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