#include "utility.h"
////////////////////////////////////////////////////////////////////////////
  /* Konstanta pi. */
extern const float pi;
extern double animation_parameter;
extern double animation_parameter_angle;
extern double animation_parameter_hover;
extern double clip_animation;
extern int animation_ongoing;
extern double brzina;
extern int crtajDrvece;
extern int nivo;
extern int posX;
extern int posY;
extern double scaleAnimation;
extern double scaleAnimationObjects;


//niz indikatora koja drveta ce se zapravo crtati
extern bool shouldDrawColor[COLOR_NUM];
extern bool shouldDrawColorClouds[COLOR_NUM];
extern bool shouldDrawColorTrees[COLOR_NUM];
extern bool shouldDrawColorRocks[COLOR_NUM];


extern bool shouldDrawRocks;
extern bool shouldDrawTrees;
extern bool shouldDrawClouds;

// niz indikatora koji oznacavaju da li ce se promeniti stanje crtanja 
// odredjene grupe objekata
extern bool triggerColor[COLOR_NUM];

extern bool triggerLargeClouds;
extern bool triggerLargeTrees;
extern bool triggerTinyRocks;
extern bool triggerSolidRocks;
extern bool triggerSolidTrees;
extern bool triggerAiryClouds;

extern bool triggerRocks;
extern bool triggerTrees;
extern bool triggerClouds;
extern bool triggerAlive;
extern bool triggerDeadRocks;
extern bool triggerDeadClouds;

extern bool level_two_guessed_pulp_fiction;
extern bool level_two_guessed_green_mile;
extern bool level_two_guessed_shawshank;
extern bool level_two_guessed_looper;
extern bool level_two_guessed_preacher;
extern bool level_two_selected[OBJECT_2_NUM];
extern int level_two_cursor;

/*Spisak svih mogucih materijala, za sada su koef. oblika atribut_coeff[inicijal boje materijala]*/

extern GLfloat ambient_coeffs[4];
extern GLfloat diffuse_coeffs[4];
extern GLfloat specular_coeffs[4];
extern GLfloat shininess;

extern GLfloat ambient_coeffsR[4];
extern GLfloat diffuse_coeffsR[4];
extern GLfloat specular_coeffsR[4];


extern GLfloat ambient_coeffsG[4];
extern GLfloat diffuse_coeffsG[4];
extern GLfloat specular_coeffsG2[4];
extern GLfloat specular_coeffsG[4];

extern GLfloat ambient_coeffsB[4];
extern GLfloat diffuse_coeffsB[4];
extern GLfloat specular_coeffsB[4];

extern GLfloat ambient_coeffsBrown[4];
extern GLfloat diffuse_coeffsBrown[4];
extern GLfloat specular_coeffsBrown[4];

extern GLfloat ambient_coeffsGray[4];
extern GLfloat diffuse_coeffsGray[4];
extern GLfloat specular_coeffsGray[4];

extern GLfloat ambient_coeffsBlack[4];
extern GLfloat diffuse_coeffsBlack[4];
extern GLfloat specular_coeffsBlack[4];


extern GLfloat ambient_coeffsW[4];
extern GLfloat diffuse_coeffsW[4];
extern GLfloat specular_coeffsW[4];

extern Color Colors[COLOR_NUM];
////////////////////////////////////////////////////////////////////////////

void on_keyboard(unsigned char key, int x, int y);
void on_reshape(int width, int height);
void on_display(void);

 
void on_keyboard(unsigned char key, int x, int y)
{
	if(nivo==0)
	{
		switch(key)
		{
			case '1':
			{
				nivo = 1;
				clip_animation=0;
				restartLevelOne();
				glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID3);
				
				glutPostRedisplay();
			}
			break;
			case '0':
			{
				nivo = 0;
				glutPostRedisplay();
			}
			break;
			case '2':
			{
				level_two_guessed_pulp_fiction=false;
				level_two_guessed_green_mile=false;
				level_two_guessed_shawshank=false;
				level_two_guessed_looper=false;
				level_two_guessed_preacher=false;
				scaleAnimation=0;
				clip_animation=0;
				nivo = 2;
				glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID3);
				glutPostRedisplay();
			}
			break;
		}
	}
	if(nivo==2)
	{
		switch(key)
		{
			case ']':
			level_two_guessed_pulp_fiction=true;
			level_two_guessed_green_mile=true;
			level_two_guessed_shawshank=true;
			level_two_guessed_looper=true;
			level_two_guessed_preacher=true;
			check_win_condition();
			break;
			case '1':
			{
				scaleAnimation=0;
				nivo = 1;
				clip_animation=0;
				restartLevelOne();
				glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID3);
				glutPostRedisplay();
			}
			break;
			case '0':
			{
				nivo = 0;
				glutPostRedisplay();
			}
			break;
			case '2':
			{
				level_two_guessed_pulp_fiction=false;
				level_two_guessed_green_mile=false;
				level_two_guessed_shawshank=false;
				level_two_guessed_looper=false;
				level_two_guessed_preacher=false;
				scaleAnimation=0;
				clip_animation=0;
				nivo = 2;
				glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID3);
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
			case '=':
			{
				if(animation_ongoing)
				{
					
					animation_ongoing=0;		

				}

			}
			break;

			case 'j':
			animation_parameter_angle+=0.01;
			glutPostRedisplay();
			break;

			case 'k':
			animation_parameter_angle-=0.01;
			glutPostRedisplay();
			break;

			case 'm':
			if(level_two_cursor!=OBJECT_2_NUM-1)
			{
				animation_parameter_hover=0;
				level_two_cursor+=1;
				glutPostRedisplay();
			}
			else
			{
				animation_parameter_hover=0;
				glutPostRedisplay();
				break;
			}
			
			break;


			case 's':
			level_two_selected[level_two_cursor]=true;

			break;

			case 'a':
			level_two_selected[level_two_cursor]=false;

			break;

			case 'x':
			check_win_condition();

			break;


			case 'n':
			if(level_two_cursor!=0)
			{
				level_two_cursor-=1;
				glutPostRedisplay();
			}
			else
			{
				glutPostRedisplay();
				break;
			}
			
			
			break;

		}
			
	}
	if(nivo==1)
	{
		printf("##########################\n");
		printf("Clouds:%d\n",shouldDrawClouds);
		printf("Rocks:%d\n",shouldDrawRocks);
		printf("Trees:%d\n",shouldDrawTrees);
		switch(key)
		{
			case ']':
			level_two_guessed_pulp_fiction=true;
			level_two_guessed_green_mile=true;
			level_two_guessed_shawshank=true;
			level_two_guessed_looper=true;
			level_two_guessed_preacher=true;
			check_win_condition();
			break;
			case '1':
			{

				scaleAnimation=0;
				nivo = 1;
				clip_animation=0;
				restartLevelOne();
				glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID3);
				glutPostRedisplay();
			}
			break;
			case '0':
			{
				nivo = 0;
				glutPostRedisplay();
			}
			break;
			case '2':
			{
				level_two_guessed_pulp_fiction=false;
				level_two_guessed_green_mile=false;
				level_two_guessed_shawshank=false;
				level_two_guessed_looper=false;
				level_two_guessed_preacher=false;
				scaleAnimation=0;
				clip_animation=0;
				nivo = 2;
				glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID3);
				glutPostRedisplay();
			}
			break;
			// case 'a':
			// posX +=1;
			// glutPostRedisplay();
			// break;
			case 'x':
			case 'X':
			check_win_condition_level_one();
			break;

			case 'd':
			case 'D':
			triggerDeadClouds=true;
			triggerDeadRocks=true;
			scaleAnimationObjects=0;
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID4);
			
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
			scaleAnimationObjects=0;
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID4);
			glutPostRedisplay();
			break;


			case 'q':
			case 'Q':
			triggerColor[GRAY_COLOR]=true;
			scaleAnimationObjects=0;
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID4);
			glutPostRedisplay();
			break;

			case 'e':
			case 'E':
			triggerDeadClouds=true;
			triggerDeadRocks=true;
			scaleAnimationObjects=0;
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID4);
			glutPostRedisplay();
			break;

			case 'r':
			case 'R':
			triggerColor[RED_COLOR]=true;
			scaleAnimationObjects=0;
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID4);
			glutPostRedisplay();
			break;

			case 'g':
			case 'G':
			triggerColor[GREEN_COLOR]=true;
			scaleAnimationObjects=0;
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID4);
			glutPostRedisplay();
			break;

			case 'b':
			case 'B':
			triggerColor[BLUE_COLOR]=true;
			scaleAnimationObjects=0;
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID4);
			glutPostRedisplay();
			break;


			case 's':
			case 'S':
			triggerSolidRocks=true;
			triggerSolidTrees=true;
			scaleAnimationObjects=0;
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID4);
			glutPostRedisplay();

			break;

			case 'a':
			case 'A':
			triggerAiryClouds=true;
			scaleAnimationObjects=0;
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID4);
			glutPostRedisplay();

			break;

			case 'l':
			case 'L':
			triggerLargeClouds=true;
			triggerLargeTrees=true;
			scaleAnimationObjects=0;
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID4);
			glutPostRedisplay();
			break;

			case 't':
			case 'T':
			triggerTinyRocks=true;
			scaleAnimationObjects=0;
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID4);
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
 
void on_display(void)
{


    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    /* Inicijalizuje se matrica transformacije. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(posX+12*sin(animation_parameter*2*pi+pi/4),posY+12*cos(animation_parameter*2*pi+pi/4),6,posX,posY,0,0,0,1);
	//gluLookAt(posX+12*sin(animation_parameter*2*pi),posY+12*cos(animation_parameter*2*pi),2,posX,posY,0,0,0,1);
	
	

    if(nivo == 0)
    {
		gluLookAt(posX+12,posY+12,6,posX,posY,0,0,0,1);
	    //drawTitleScreen();
	}

    else if(nivo == 1)
    {
		double clip_plane[] = {-1, 0, 0, 15-35*clip_animation};
		glClipPlane(GL_CLIP_PLANE1, clip_plane);
    	glEnable(GL_CLIP_PLANE1);
		gluLookAt(posX+12*sin(animation_parameter*2*pi+pi/4),posY+12*cos(animation_parameter*2*pi+pi/4),6,posX,posY,0,0,0,1);
	    draw_ground();
		

		glScalef(scaleAnimationObjects,scaleAnimationObjects,scaleAnimationObjects);
	    
	    draw_forest();
		draw_rocks();
		draw_clouds();
		for(int i=0; i<COLOR_NUM; i++)
		{
			triggerColor[i]=false;
		}
		glDisable(GL_CLIP_PLANE1);

		
	}

	else if(nivo == 2)
    {
		
		gluLookAt(12*sin(animation_parameter_angle*2*pi),12*cos(animation_parameter_angle*2*pi),5,0,0,3,0,0,1);
		
		double clip_plane[] = {-1, 0, 0, 15-35*clip_animation};
		glClipPlane(GL_CLIP_PLANE0, clip_plane);
    	glEnable(GL_CLIP_PLANE0);
	    
		draw_scene();
		draw_bible();
		
		draw_cage();
		draw_green_mile();
		draw_numbers();
		draw_gun();
		draw_clock();
		glDisable(GL_CLIP_PLANE0);
	    
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
	//init_colors();
	
	//inicijalizacija, sve drvece se iscrtava
	for(int i=0;i<COLOR_NUM;i++)
	{
		shouldDrawColorClouds[i]=true;
		shouldDrawColorRocks[i]=true;
		shouldDrawColorTrees[i]=true;
	}

	for(int i=0; i<OBJECT_2_NUM; i++)
	{
		level_two_selected[i]=false;
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
    glClearColor(0.5, 0.8, 1, 0);
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

 
 void on_reshape(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);
 
    /* Podesava se projekcija. */
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width / height, 1, 100);
}
 
void draw_debug_cube(float x, float y, float z, float w, float h,
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
 
void draw_debug_coosys()
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