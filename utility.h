#ifndef __util__
#define __util__
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define TIMER_ID 0
#define TIMER_ID2 0
#define TIMER_ID3 2
#define TIMER_ID4 3
#define TIMER_ID5 4
#define TIMER_ID6 5
#define TIMER_ID7 6
#define TIMER_INTERVAL 1
#define TIMER_INTERVAL2 10

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

#define OBJECT_2_NUM 6
#define GUN 0
#define BIBLE 1
#define CAGE 2
#define NUMBERS 3
#define GREEN_MILE 4
#define CLOCK 5



#define _POSIX_C_SOURCE 199309L

typedef struct Color{
	GLfloat ambient_coeffs[4];
	GLfloat diffuse_coeffs[4];
	GLfloat specular_coeffs[4];
}Color;

 

 
  /* Deklaracije callback funkcija. */
void init_colors();
void on_timer(int id);
void draw_tree();
void draw_forest();
void draw_ground();
void draw_rock();
void draw_rocks();
void draw_cloud();
void draw_clouds();
void printColor(int i);
bool toggle(bool shouldDraw); 
void triggerColors();
void restartLevelOne();
void draw_scene();
void pop_in();
void draw_bible();
void draw_cage();
void draw_green_mile();
void draw_numbers();
void draw_gun();
void check_win_condition();
void check_win_condition_level_one();
void draw_clock();

  /*
   * Funkcije za lakse testiranje programa:
   *
   * draw_debug_cube -- iscrtava kvadar ciji je centar u (x, y, z),
   *                    a dimenzije w x h x d
   *
   * draw_debug_coosys -- iscrtava koordinatni sistem
   *
   */
 
void draw_debug_cube(float x, float y, float z, float w, float h,
                float d);
void draw_debug_coosys();
 
  /* Parametar animacije, fleg koji odredjuje da li je
   * animacija u toku ili nije */





#endif