#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

#define TREE_NUM 10
#define CLOUD_NUM 10
#define ROCK_NUM 10
#define COLOR_NUM 4

#define RED_COLOR 0
#define GREEN_COLOR 1
#define BLUE_COLOR 2
#define GRAY_COLOR 3

#define OBJECT_NUM 3
#define TREE 0
#define ROCK 1
#define CLOUD 2

#define _POSIX_C_SOURCE 199309L

typedef struct Color{
	GLfloat ambient_coeffs[4];
	GLfloat diffuse_coeffs[4];
	GLfloat specular_coeffs[4];
}Color;

 
  /* Konstanta pi. */
static const float pi = 3.141592653589793;
 
  /* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int id);
static void draw_tree();
static void draw_forest();
static void draw_ground();
static void draw_rock();
static void draw_rocks();
static void draw_cloud();
static void draw_clouds();
static void printColor(int i);
static bool toggle(bool shouldDraw); 
static void triggerColors();

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
bool shouldDrawColor[COLOR_NUM];
bool shouldDrawColorClouds[COLOR_NUM];
bool shouldDrawColorTrees[COLOR_NUM];
bool shouldDrawColorRocks[COLOR_NUM];
bool shouldDraw[OBJECT_NUM];

bool shouldDrawLarge=true;
bool shouldDrawTiny=true;
bool shouldDrawSolid=true;
bool shouldDrawAiry=true;

bool shouldDrawRocks=true;
bool shouldDrawTrees=true;
bool shouldDrawClouds=true;
bool shouldDrawAlive=true;
bool shouldDrawDead=true;

bool triggerColor[COLOR_NUM];

bool triggerLargeClouds=false;
bool triggerLargeTrees=false;
bool triggerTinyRocks=false;
bool triggerSolidRocks=false;
bool triggerSolidTrees=false;
bool triggerAiryClouds=false;

bool triggerRocks=false;
bool triggerTrees=false;
bool triggerClouds=false;
bool triggerAlive=false;
bool triggerDeadRocks=false;
bool triggerDeadClouds=false;

/*Spisak svih mogucih materijala, za sada su koef. oblika atribut_coeff[inicijal boje materijala]*/

GLfloat ambient_coeffs[] = { 0.3, 0.7, 0.3, 1 };
GLfloat diffuse_coeffs[] = { 0.2, 1, 0.2, 1 };
GLfloat specular_coeffs[] = { 0.5, 0.5, 0.5, 1 };
GLfloat shininess = 50;

GLfloat ambient_coeffsR[] = { 0.7, 0.3, 0.3, 1 };
GLfloat diffuse_coeffsR[] = { 1, 0.2, 0.2, 1 };
GLfloat specular_coeffsR[] = { 0.7, 0.5, 0.5, 1 };


GLfloat ambient_coeffsG[] = { 0.3, 0.7, 0.3, 1 };
GLfloat diffuse_coeffsG[] = { 0.2, 0.5, 0.2, 1 };
GLfloat specular_coeffsG2[] = { 0.2, 0.5, 0.2, 0.5 };
GLfloat specular_coeffsG[] = { 0, 0, 0, 0.1 };

GLfloat ambient_coeffsB[] = { 0.3, 0.3, 0.7, 1 };
GLfloat diffuse_coeffsB[] = { 0.2, 0.2, 1, 1 };
GLfloat specular_coeffsB[] = { 0, 0, 0, 1 };

GLfloat ambient_coeffsBrown[] = { 139/255.0, 69/255.0, 19/255.0, 1 };
GLfloat diffuse_coeffsBrown[] = { 139/255.0, 89/255.0, 29/255.0, 1 };
GLfloat specular_coeffsBrown[] = { 0, 0, 0, 1 };

GLfloat ambient_coeffsGray[] = {0.3, 0.3, 0.3, 1};
GLfloat diffuse_coeffsGray[] = {0.5, 0.5, 0.5, 1};
GLfloat specular_coeffsGray[] = { 0, 0, 0, 1 };

Color Colors[COLOR_NUM];


void init_colors()
{
	/*Pravljenja crvene,plave i zelene boje*/
	for(int i=0; i<3;i++)
	{
		Colors[i].ambient_coeffs[0]=0.05;
		Colors[i].ambient_coeffs[1]=0.05;
		Colors[i].ambient_coeffs[2]=0.05;
		Colors[i].ambient_coeffs[3]=1;

		Colors[i].diffuse_coeffs[0]=0.05;
		Colors[i].diffuse_coeffs[1]=0.05;
		Colors[i].diffuse_coeffs[2]=0.05;
		Colors[i].diffuse_coeffs[3]=1;

		Colors[i].specular_coeffs[0]=0.5;
		Colors[i].specular_coeffs[1]=0.5;
		Colors[i].specular_coeffs[2]=0.5;
		Colors[i].specular_coeffs[3]=0.5;

		Colors[i].ambient_coeffs[i]=0.7;
		Colors[i].diffuse_coeffs[i]=1;
	}
	
	/*Dodavanje sive boje*/
	Colors[3].ambient_coeffs[0]=0.3;
	Colors[3].ambient_coeffs[1]=0.3;
	Colors[3].ambient_coeffs[2]=0.3;
	Colors[3].ambient_coeffs[3]=1;

	Colors[3].diffuse_coeffs[0]=0.5;
	Colors[3].diffuse_coeffs[1]=0.5;
	Colors[3].diffuse_coeffs[2]=0.5;
	Colors[3].diffuse_coeffs[3]=1;

	Colors[3].specular_coeffs[0]=0;
	Colors[3].specular_coeffs[1]=0;
	Colors[3].specular_coeffs[2]=0;
	Colors[3].specular_coeffs[3]=0.1;


}
void printColor(int i)
{
	printf("%lf,%lf,%lf,%lf\n",Colors[i].specular_coeffs[0],Colors[i].specular_coeffs[1],Colors[i].specular_coeffs[2],specular_coeffs[3]);
}
 
  /*
   * Funkcija koja iscrtava zelenu podlogu
   */
void draw_ground()
{
	/*postavljanje podloge, odnosno grass plain*/
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsG);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsG);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsG2);
	glMateriali(GL_FRONT,GL_SHININESS,1);

	glPushMatrix();
	glTranslatef(0,0,-0.5);
	glScalef(10,10,0.3);
	glutSolidCube(1);
	glPopMatrix();
}
void draw_clouds()
{

	srand(999);
	// for(int i=0; i<COLOR_NUM;i++)
	// {
	// 	printColor(i);
	// }
	if(triggerLargeClouds)
	{
		triggerLargeClouds=false;
		shouldDrawClouds = shouldDrawClouds == true?false:true;
	}
	if(triggerAiryClouds)
	{
		triggerAiryClouds=false;
		shouldDrawClouds = shouldDrawClouds == true?false:true;
	}
	if(triggerDeadClouds)
	{
		triggerDeadClouds=false;
		shouldDrawClouds = shouldDrawClouds == true?false:true;
	}
	
	if(shouldDrawClouds)
	{
		for(int i=0; i<COLOR_NUM; i++)
		{
			if(triggerColor[i]==true)
			{
				// triggerColor[i]=false;
				shouldDrawColorClouds[i] = shouldDrawColorClouds[i] == true?false:true;
			}
		}
		for(int i=0; i<CLOUD_NUM; i++)
		{
			
			/*odredjivanje polarnih koordinata svakog drveta*/
			double a = ((double)rand()/RAND_MAX)*360;
			double r = ((double)rand()/RAND_MAX)*5;
			int random = rand();
			int randomColor = (int)(((double)(random*1.0)/(double)(RAND_MAX))*4);

			
			//printf("Color of rock: %d\n",randomColor);
			//printf("number:%jd\nColor: %d\n",random,randomColor);
			
			if(shouldDrawColorClouds[randomColor])
			{
				glPushMatrix();
				glTranslatef(r*cos(a),r*sin(a),0);
				draw_cloud(randomColor);
				glPopMatrix();
			}else
			{
				for(int i=0;i<10;i++)
					rand();
			}
		
		}
	}

}

void draw_cloud(int randomColor)
{
	//if(shouldDrawColor[randomColor]==false)return;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,Colors[randomColor].ambient_coeffs);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,Colors[randomColor].diffuse_coeffs);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsG);
	// glMaterialfv(GL_FRONT,GL_SPECULAR,Colors[randomColor].specular_coeffs);
	glMateriali(GL_FRONT,GL_SHININESS,10);
	
	glTranslatef(0,0,4);
	glScalef(0.6,0.6,0.4);
	/*glavni deo krosnje*/
	glPushMatrix();
	glScalef(0.2,0.4,0.2);
	glutSolidSphere(2.8,50,50);
	glPopMatrix();

	/*delovi krosnje*/

	for(int i =0;i<5;i++)
	{
		
		double a = ((double)rand()/RAND_MAX)*360;
		double b = ((double)rand()/RAND_MAX)*360;
		glPushMatrix();
		glScalef(2.5,1,1);
		glTranslatef(0.56*cos(a)*cos(b), 0.56*sin(a)*cos(b), 0.56*sin(b));
		glScalef(0.1,0.6,0.1);
		glutSolidSphere(2.8,20,20);
		glPopMatrix();

	}

}
void draw_rocks()
{


	srand(101);
	// for(int i=0; i<COLOR_NUM;i++)
	// {
	// 	printColor(i);
	// }
	if(triggerTinyRocks)
	{
		triggerTinyRocks=false;
		shouldDrawRocks = shouldDrawRocks == true?false:true;
	}
	if(triggerSolidRocks)
	{
		triggerSolidRocks=false;
		shouldDrawRocks = shouldDrawRocks == true?false:true;
	}
	if(triggerDeadRocks)
	{
		triggerDeadRocks=false;
		shouldDrawRocks = shouldDrawRocks == true?false:true;
	}
	if(shouldDrawRocks)
	{
		for(int i=0; i<COLOR_NUM; i++)
		{
			if(triggerColor[i]==true)
			{
				// triggerColor[i]=false;
				shouldDrawColorRocks[i] = shouldDrawColorRocks[i] == true?false:true;
			}
		}
		for(int i=0; i<ROCK_NUM; i++)
		{
			
			/*odredjivanje polarnih koordinata svakog drveta*/
			double a = ((double)rand()/RAND_MAX)*360;
			double r = ((double)rand()/RAND_MAX)*5;
			int random = rand();
			int randomColor = (int)(((double)(random*1.0)/(double)(RAND_MAX))*4);
			//printf("Color of rock: %d\n",randomColor);
			//printf("number:%jd\nColor: %d\n",random,randomColor);
			
			
			if(shouldDrawColorRocks[randomColor])
			{
				glPushMatrix();
				glTranslatef(r*cos(a),r*sin(a),0);
				draw_rock(randomColor);
				glPopMatrix();
			}
		
		}
	}
	
}

void draw_rock(int randomColor)
{
	//if(shouldDrawColor[randomColor]==false)return;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,Colors[randomColor].ambient_coeffs);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,Colors[randomColor].diffuse_coeffs);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsG);
	// glMaterialfv(GL_FRONT,GL_SPECULAR,Colors[randomColor].specular_coeffs);
	glMateriali(GL_FRONT,GL_SHININESS,10);
	

	glPushMatrix();
	glTranslatef(0,0,-0.4);
	glScalef(0.25,0.25,0.25);
	glRotatef(0.5*randomColor,0,0,1);
	glutSolidDodecahedron();
	glPopMatrix();
}


void draw_forest()
{
	srand(101);
	if(triggerLargeTrees)
	{
		triggerLargeTrees=false;
		shouldDrawTrees = shouldDrawTrees == true?false:true;
	}
	if(triggerAlive)
	{
		triggerAlive=false;
		shouldDrawTrees = shouldDrawTrees == true?false:true;
	}
	if(triggerSolidTrees)
	{
		triggerSolidTrees=false;
		shouldDrawTrees = shouldDrawTrees == true?false:true;
	}

	
	if(shouldDrawTrees)
	{
		for(int i=0; i<COLOR_NUM; i++)
		{
			if(triggerColor[i]==true)
			{
				// triggerColor[i]=false;
				shouldDrawColorTrees[i] = shouldDrawColorTrees[i] == true?false:true;
			}
		}
		for(int i=0; i<TREE_NUM; i++)
		{
			
			
			/*odredjivanje polarnih koordinata svakog drveta*/
			double a = ((double)rand()/RAND_MAX)*360;
			double r = ((double)rand()/RAND_MAX)*5;
			int random = rand();
			int randomColor = (int)(((double)(random*1.0)/(double)(RAND_MAX))*3);
			//printf("number:%jd\nColor: %d\n",random,randomColor);
			if(shouldDrawColorTrees[randomColor])
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
}
void draw_tree(int randomColor)
{
	//if(shouldDrawColor[randomColor]==false)return;
	
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
			// case 'a':
			// posX +=1;
			// glutPostRedisplay();
			// break;

			case 'd':
			case 'D':
			triggerDeadClouds=true;
			triggerDeadRocks=true;
			glutPostRedisplay();
			break;

			// case 's':
			// posY +=1;
			// glutPostRedisplay();
			// break;

			// case 'w':
			// posY -=1;
			// glutPostRedisplay();
			// break;


			case 'v':
			case 'V':
			triggerAlive=true;
			glutPostRedisplay();
			break;


			case 'q':
			case 'Q':
			triggerColor[GRAY_COLOR]=true;
			glutPostRedisplay();
			break;

			case 'e':
			case 'E':
			triggerDeadClouds=true;
			triggerDeadRocks=true;
			glutPostRedisplay();
			break;

			case 'r':
			case 'R':
			triggerColor[RED_COLOR]=true;
			glutPostRedisplay();
			break;

			case 'g':
			case 'G':
			triggerColor[GREEN_COLOR]=true;
			glutPostRedisplay();
			break;

			case 'b':
			case 'B':
			triggerColor[BLUE_COLOR]=true;
			glutPostRedisplay();
			break;


			case 's':
			case 'S':
			triggerSolidRocks=true;
			triggerSolidTrees=true;
			glutPostRedisplay();

			break;

			case 'a':
			case 'A':
			triggerAiryClouds=true;
			glutPostRedisplay();

			break;

			case 'l':
			case 'L':
			triggerLargeClouds=true;
			triggerLargeTrees=true;
			glutPostRedisplay();
			break;

			case 't':
			case 'T':
			triggerTinyRocks=true;
			glutPostRedisplay();
			break;
			// case 'S':
			// case 's':
			// {
			// 	animation_ongoing=0;
			// }
			// break;
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
			case '=':
			{
				if(animation_ongoing)
				{
					
					animation_ongoing=0;		

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
    gluLookAt(posX+12*sin(animation_parameter*2*pi+pi/4),posY+12*cos(animation_parameter*2*pi+pi/4),6,posX,posY,0,0,0,1);
	//gluLookAt(posX+12*sin(animation_parameter*2*pi),posY+12*cos(animation_parameter*2*pi),2,posX,posY,0,0,0,1);
	
	

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

		draw_rocks();
		draw_clouds();
		for(int i=0; i<COLOR_NUM; i++)
		{
			triggerColor[i]=false;
		}
		

		printf("##########################\n");
		printf("Red:%d\n",shouldDrawColor[0]);
		printf("Green:%d\n",shouldDrawColor[1]);
		printf("Blue:%d\n",shouldDrawColor[2]);
		printf("Gray:%d\n",shouldDrawColor[3]);
		printf("Solid:%d\n",shouldDrawSolid);
		printf("Airy:%d\n",shouldDrawAiry);
		printf("Large:%d\n",shouldDrawLarge);
		printf("Tiny:%d\n",shouldDrawTiny);
		printf("Alive:%d\n",shouldDrawAlive);
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
	
	/*inicijalizacija globalnog niza boja*/
	init_colors();
	
	//inicijalizacija, sve drvece se iscrtava
	for(int i=0;i<COLOR_NUM;i++)
	{
		shouldDrawColorClouds[i]=true;
		shouldDrawColorRocks[i]=true;
		shouldDrawColorTrees[i]=true;
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