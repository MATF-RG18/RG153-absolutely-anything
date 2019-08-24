#include "utility.h"
////////////////////////////////////////////////////////////////////////////
 /* Konstanta pi. */
const float pi = 3.141592653589793;
double animation_parameter = 0;
double animation_parameter_angle = 0;
double animation_parameter_hover = 0;
double clip_animation = 0;
int animation_ongoing = 0;
double brzina=0;
int crtajDrvece=1;
int nivo = 0;
int posX = 0;
int posY = 0;
double scaleAnimation = 0;
double scaleAnimationObjects = 1;


//niz indikatora koja drveta ce se zapravo crtati
bool shouldDrawColor[COLOR_NUM];
bool shouldDrawColorClouds[COLOR_NUM];
bool shouldDrawColorTrees[COLOR_NUM];
bool shouldDrawColorRocks[COLOR_NUM];


bool shouldDrawRocks=true;
bool shouldDrawTrees=true;
bool shouldDrawClouds=true;

// niz indikatora koji oznacavaju da li ce se promeniti stanje crtanja 
// odredjene grupe objekata
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

bool level_two_guessed_pulp_fiction=false;
bool level_two_guessed_green_mile=false;
bool level_two_guessed_shawshank=false;
bool level_two_guessed_looper=false;
bool level_two_guessed_preacher=false;
bool level_two_selected[OBJECT_2_NUM];
int level_two_cursor = BIBLE;

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

GLfloat ambient_coeffsBlack[] = {0, 0, 0, 0};
GLfloat diffuse_coeffsBlack[] = {0, 0, 0, 0};
GLfloat specular_coeffsBlack[] = { 0, 0, 0, 1 };


GLfloat ambient_coeffsW[] = {1, 1, 1, 1};
GLfloat diffuse_coeffsW[] = {1, 1, 1, 1};
GLfloat specular_coeffsW[] = { 1, 1, 1, 1 };

Color Colors[COLOR_NUM];
////////////////////////////////////////////////////////////////////////////
void on_timer(int id)
{
	if(id==TIMER_ID)
	{	
		if(animation_parameter>=1)
			animation_parameter=0;
	    else
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
	else if(id==TIMER_ID3)
	{
		
		//printf("\nScale:%lf\n",scaleAnimation);
		
		if(scaleAnimation<1)
		{
			scaleAnimation+=0.03;
			glutPostRedisplay();
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID3);

		}
	}
	else if(id==TIMER_ID4)
	{
		
		//printf("\nScale:%lf\n",scaleAnimationObjects);
		
		if(scaleAnimationObjects<1)
		{
			scaleAnimationObjects+=0.03;
			glutPostRedisplay();
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID4);

		}
	}
	else if(id==TIMER_ID5)
	{
		
		
		
		if(animation_parameter_hover<=1.0)
		{
			animation_parameter_hover+=0.0005;
			glutPostRedisplay();
			glutTimerFunc(TIMER_INTERVAL2, on_timer, TIMER_ID5);
			

		}
		else
		{
			glutPostRedisplay();
			//printf("\n greater than 1:%lf\n",animation_parameter_hover);
			glutTimerFunc(TIMER_INTERVAL2, on_timer, TIMER_ID6);
		}	
	}
	else if(id==TIMER_ID6)
	{
		
		//printf("\nAnimation:%lf \n",animation_parameter_hover);
		
		if(animation_parameter_hover>=0.0)
		{
			animation_parameter_hover-=0.0005;
			glutPostRedisplay();
			glutTimerFunc(TIMER_INTERVAL2, on_timer, TIMER_ID6);
		}
		else
		{
			glutPostRedisplay();
			//printf("\n lesser than 0:%lf\n",animation_parameter_hover);
			glutTimerFunc(TIMER_INTERVAL2, on_timer, TIMER_ID5);
		}	
	}
	else if(id==TIMER_ID7)
	{
		
		//printf("\nAnimation:%lf \n",animation_parameter_hover);
		clip_animation+=0.05;
		if(clip_animation<1)
		{
			glutTimerFunc(TIMER_INTERVAL2, on_timer, TIMER_ID7);
		}
			
	}
	
}

void draw_clock()
{
	glPushMatrix();
		if(level_two_cursor==CLOCK)
		{
			glTranslatef(0,0,animation_parameter_hover);
			glutTimerFunc(TIMER_INTERVAL2, on_timer, TIMER_ID5);
		}
		glTranslatef(-6,1,6);
		glScalef(0.5,0.5,0.5);
		glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsB);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsB);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsB);
		glMateriali(GL_FRONT,GL_SHININESS,0);
		
		//spoljasnji plavi ram sata
		glPushMatrix();
			glRotatef(90,1,0,0);
			glScalef(4,4,1);
			GLUquadric* quad = gluNewQuadric();
			gluCylinder(quad,1,1,1,20,20);
		glPopMatrix();


		glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsW);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsW);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsW);

		//unutrasnji beli deo
		glPushMatrix();
			glTranslatef(0,-0.8,0);
			glRotatef(90,1,0,0);
			glScalef(4,4,1);
			
			glutSolidSphere(0.99,20,20);
		glPopMatrix();
		

		glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsBlack);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsBlack);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsBlack);
		//spoljasnje recke
		for(int i=0;i<12;i++)
		{
			glPushMatrix();
				glTranslatef(0+3*sin(2*pi/12*i),0,0.3+3*cos(2*pi/12*i));
				glRotatef(360.0*(i/12.0),0,1,0);
				glScalef(0.2,0.2,0.8);
				
				glutSolidCube(1);
			glPopMatrix();
		}

		//velika kazaljka
		glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsR);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsR);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsR);

		glPushMatrix();
			glRotatef(-15,0,1,0);
			glTranslatef(0,0.2,1.8);
			glScalef(0.2,0.2,3.6);
			
			glutSolidCube(1);
		glPopMatrix();

		//mala kazaljka
		glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsBlack);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsBlack);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsBlack);

		glPushMatrix();
			glRotatef(15,0,1,0);
			glTranslatef(0,0.2,1.3);
			glScalef(0.2,0.2,2.3);
			
			glutSolidCube(1);
		glPopMatrix();
	glPopMatrix();



}
void check_win_condition_level_one()
{
	if(shouldDrawClouds && !shouldDrawColorClouds[0] && !shouldDrawColorClouds[1] && !shouldDrawColorClouds[2] && shouldDrawColorClouds[3])
    {
        if(shouldDrawTrees && !shouldDrawColorTrees[0] && shouldDrawColorTrees[1] && !shouldDrawColorTrees[2] && !shouldDrawColorTrees[3])
        {
            if(shouldDrawRocks && !shouldDrawColorRocks[0] && !shouldDrawColorRocks[1] && !shouldDrawColorRocks[2] && shouldDrawColorRocks[3])
            {
                glutTimerFunc(TIMER_INTERVAL2, on_timer, TIMER_ID7);
            }
        }
    }
}
void check_win_condition()
{

	if(level_two_selected[0]&& level_two_selected[1] && !level_two_selected[2] && level_two_selected[3] && !level_two_selected[4] && !level_two_selected[5])
	{
		level_two_guessed_pulp_fiction=true;
		printf("\nYOU GUESSED:\nPULP FICTION\n");
	}
	if(!level_two_selected[0]&& level_two_selected[1] && level_two_selected[2] && !level_two_selected[3] && level_two_selected[4] && !level_two_selected[5])
	{
		level_two_guessed_green_mile=true;
		printf("\nYOU GUESSED:\nTHE GREEN MILE\n");
	}
	if(!level_two_selected[0]&& !level_two_selected[1] && level_two_selected[2] && !level_two_selected[3] && !level_two_selected[4] && level_two_selected[5])
	{
		level_two_guessed_shawshank=true;
		printf("\nYOU GUESSED:\nTHE SHAWHANK REDEMPTION\n");
	}
	if(level_two_selected[0]&& !level_two_selected[1] && !level_two_selected[2] && !level_two_selected[3] && !level_two_selected[4] && level_two_selected[5])
	{
		level_two_guessed_looper =true;
		printf("\nYOU GUESSED:\nLOOPER\n");
	}
	if(level_two_selected[0]&& level_two_selected[1] && !level_two_selected[2] && !level_two_selected[3] && !level_two_selected[4] && !level_two_selected[5])
	{
		level_two_guessed_preacher=true;
		printf("\nYOU GUESSED:\nPREACHER\n");
	}

	if(level_two_guessed_pulp_fiction && level_two_guessed_green_mile && level_two_guessed_shawshank && level_two_guessed_looper && level_two_guessed_preacher){
		glutTimerFunc(TIMER_INTERVAL2, on_timer, TIMER_ID7);
	}
}

void draw_gun()
{	
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsGray);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsGray);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsGray);
	glMateriali(GL_FRONT,GL_SHININESS,1);

	
	glPushMatrix();
	if(level_two_cursor==GUN)
		{
			glTranslatef(0,0,animation_parameter_hover);
			glutTimerFunc(TIMER_INTERVAL2, on_timer, TIMER_ID5);
		}
	glTranslatef(4,1,3);

		glPushMatrix();
			glTranslatef(3.1,0,1.75);
			glRotatef(90,0,1,0);
			glScalef(1,1,5);
			glScalef(0.2,0.2,0.2);
			glutSolidTorus(0.2,1,10,10);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.5,0,1.75);
			
			glScalef(0.1,0.1,1);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1,0,1);
			glRotatef(10,0,1,0);
			glScalef(0.1,0.1,1);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.8,0,0.8);
			glRotatef(90,1,0,0);
			glScalef(0.5,0.5,0.5);
			glutSolidTorus(0.2,1,10,10);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1,0,1.5);
			glRotatef(90,0,1,0);
			glScalef(1,1,4);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glRotatef(8,0,1,0);
			glScalef(1.1,0.8,3);
			glutSolidCube(1);
		glPopMatrix();

	glPopMatrix();
}

void draw_numbers()
{
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsR);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsR);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsR);
	glMateriali(GL_FRONT,GL_SHININESS,0);

	
	
	
	glPushMatrix();

		if(level_two_cursor==NUMBERS)
		{
			glTranslatef(0,0,animation_parameter_hover);
			glutTimerFunc(TIMER_INTERVAL2, on_timer, TIMER_ID5);
		}
		glTranslatef(-2,2,4);
		
		
		glScalef(0.3,0.3,0.3);
		//dvojka
		glTranslatef(-1.6,2,3);
		
		glRotatef(10,0,0,1);

		for(int i=0; i<3; i++)
		{
			glPushMatrix();
				glRotatef(i*90+180,0,1,0);
				
				glTranslatef(0,0,1);
				glRotatef(90,0,1,0);
				glScalef(0.4,0.75,1.5);
				glutSolidCube(1);
			glPopMatrix();
		}

		for(int i=0; i<3; i++)
		{
			glPushMatrix();

				glTranslatef(0,0,-2);
				glRotatef(i*90,0,1,0);
				glTranslatef(0,0,1);
				glRotatef(90,0,1,0);
				glScalef(0.4,0.75,1.5);
				glutSolidCube(1);
			glPopMatrix();
		}
		//petica
		glPushMatrix();
			glTranslatef(-3,0,0);
			for(int i=0; i<3; i++)
			{
				glPushMatrix();
					glRotatef(i*90,0,1,0);
					
					glTranslatef(0,0,1);
					glRotatef(90,0,1,0);
					glScalef(0.4,0.75,1.5);
					glutSolidCube(1);
				glPopMatrix();
			}

			for(int i=0; i<3; i++)
			{
				glPushMatrix();

					glTranslatef(0,0,-2);
					glRotatef(i*90+180,0,1,0);
					glTranslatef(0,0,1);
					glRotatef(90,0,1,0);
					glScalef(0.4,0.75,1.5);
					glutSolidCube(1);
				glPopMatrix();
			}
		glPopMatrix();
		glTranslatef(-2.5,0,0);
		glPushMatrix();
		glTranslatef(-1.5,0,0);
			
			glPushMatrix();
				
				glTranslatef(-1,0,-2);
				glutSolidCube(0.4);
			glPopMatrix();

			glPushMatrix();
				
				glTranslatef(-1,0,0);
				glutSolidCube(0.4);
			glPopMatrix();

		glPopMatrix();

		glTranslatef(-3,0,0);
		//jedinica
		glPushMatrix();
			
			glPushMatrix();
				
				glTranslatef(-1,0,-2);
				glScalef(0.4,0.75,1.5);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				
				glTranslatef(-1,0,0);
				glScalef(0.4,0.75,1.5);
				glutSolidCube(1);
			glPopMatrix();

		glPopMatrix();

		//sedmica
		glPushMatrix();
			glTranslatef(-3,0,0);
			glPushMatrix();
				
				glTranslatef(0,0,1.25);
				glRotatef(90,0,1,0);
				glScalef(0.4,0.75,1.5);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				
				glTranslatef(-1,0,-2);
				glScalef(0.4,0.75,1.5);
				glutSolidCube(1);
			glPopMatrix();

			glPushMatrix();
				
				glTranslatef(-1,0,0);
				glScalef(0.4,0.75,1.5);
				glutSolidCube(1);
			glPopMatrix();

		glPopMatrix();
	glPopMatrix();
}

void draw_green_mile()
{
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsG);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsG);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsG2);
	glMateriali(GL_FRONT,GL_SHININESS,1);

	glPushMatrix();
		if(level_two_cursor==GREEN_MILE)
		{
			glTranslatef(0,0,animation_parameter_hover);
			glutTimerFunc(TIMER_INTERVAL2, on_timer, TIMER_ID5);
		}
		glTranslatef(-3.5,0,3);
		glScalef(3,10,0.3);
		glutSolidCube(1);
	glPopMatrix();
}

void draw_cage()
{
	glPushMatrix();
		if(level_two_cursor==CAGE)
		{
			glTranslatef(0,0,animation_parameter_hover);
			glutTimerFunc(TIMER_INTERVAL2, on_timer, TIMER_ID5);
		}
		/*pozicioniranje i skaliranje objekta*/
		glTranslatef(0,0,5);
		glRotatef(10,0,0,1);
		glScalef(0.65,0.65,1);

		glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsBrown);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsBrown);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsBrown);
		glMateriali(GL_FRONT,GL_SHININESS,20);

		glPushMatrix();
			glScalef(4,4,5);
			glutSolidCube(1);
		glPopMatrix();

		glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsW);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsW);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsW);
		glMateriali(GL_FRONT,GL_SHININESS,20);

		//resetke
		for(int i=0;i<5;i++)
		{
			glPushMatrix();
				glTranslatef(-1.6+0.8*i,2,0);
				glScalef(0.25,0.75,5);
				glutSolidCube(1);
			glPopMatrix();
		}

		//leva i desna strana
		for(int i=0;i<2;i++)
		{
			glPushMatrix();
				glRotatef(i*180,0,1,0);
				glTranslatef(2.25,0,0);
				glScalef(0.5,6,5);
				glutSolidCube(1);
			glPopMatrix();
		}
		//gornja donja strana
		for(int i=0;i<2;i++)
		{
			glPushMatrix();
				glRotatef(90+i*180,0,1,0);
				glTranslatef(2.25,0,0);
				glScalef(0.75,6,5);
				glutSolidCube(1);
			glPopMatrix();
		}
	glPopMatrix();
	
}

void draw_bible()
{
	
	glPushMatrix();
		if(level_two_cursor==BIBLE)
		{
			glTranslatef(0,0,animation_parameter_hover);
			glutTimerFunc(TIMER_INTERVAL2, on_timer, TIMER_ID5);
		}

		glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsBrown);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsBrown);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsBrown);
		glMateriali(GL_FRONT,GL_SHININESS,20);	

		glRotatef(10,0,0,1);


		glPushMatrix();
			glTranslatef(3,3,5);
			glRotatef(90,1,0,0);
			glScalef(0.5,0.7,0.1);
			glutSolidCube(3);
		glPopMatrix();

		glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsW);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsW);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsW);

		glPushMatrix();
			glTranslatef(0,0,1.2);
			glTranslatef(2.7,1.3,1);
			glScalef(0.1,0.6,0.6);
			glTranslatef(3,3,5);
			glRotatef(90,1,0,0);
			glScalef(0.5,0.7,0.1);
			glutSolidCube(3);
		glPopMatrix();

		glPushMatrix();
			
			glTranslatef(3,3.1,5.4);
			glRotatef(90,0,1,0);
			glRotatef(90,1,0,0);
			glScalef(1,1,0.6);
			glScalef(0.1,0.6,0.6);
			glScalef(0.5,0.7,0.1);
			glRotatef(90,0,0,1);
			glutSolidCube(3);
		glPopMatrix();
	glPopMatrix();
}

void draw_scene()
{	
	glScalef(scaleAnimation,scaleAnimation,scaleAnimation);
	
	
	/*postavljanje materijala*/


	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsBlack);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsBlack);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsBlack);
	glMateriali(GL_FRONT,GL_SHININESS,1);


	
	//drawing bottom part
	glPushMatrix();
		glTranslatef(0,0,-0.5);
		glScalef(15,15,0.3);
		glutSolidCube(1);
	glPopMatrix();

	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffsW);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffsW);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffsW);

	//drawing back part
	glPushMatrix();
		glTranslatef(0,-5,0);
		glRotatef(90,1,0,0);
		glScalef(30,30,0.3);
		glutSolidCube(1);
	glPopMatrix();


}

void restartLevelOne()
{
	for(int i=0;i<COLOR_NUM;i++)
	{
		shouldDrawColorClouds[i]=true;
		shouldDrawColorRocks[i]=true;
		shouldDrawColorTrees[i]=true;
	}

	shouldDrawRocks=true;
	shouldDrawTrees=true;
	shouldDrawClouds=true;
}

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
	glScalef(scaleAnimation,scaleAnimation,scaleAnimation);
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
    init_colors();

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
    init_colors();

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
	glMateriali(GL_FRONT,GL_SHININESS,0);
	

	glPushMatrix();
	glTranslatef(0,0,-0.4);
	glScalef(0.25,0.25,0.25);
	glRotatef(0.5*randomColor,0,0,1);
	glutSolidDodecahedron();
	glPopMatrix();
}


void draw_forest()
{
	
	srand(100);
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
			int randomColor = (int)(((double)(random*1.0)/(double)(RAND_MAX))*4);
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
	glMateriali(GL_FRONT,GL_SHININESS,20);	


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