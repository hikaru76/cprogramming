/* このファイルの中身は書き換えないこと */
/* 中身の具体的なことは来週以降の授業で */

#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "matrix.h"

#define WIDTH 1024          /* 初期画面の幅 */
#define HEIGHT 1024         /* 初期画面の高さ */
#define MIN_X -10           /* 初期画面の左端座標 */
#define MAX_X 10            /* 初期画面の右端座標 */
#define MIN_Y -10           /* 初期画面の下端座標 */
#define MAX_Y 10            /* 初期画面の上端座標 */
#define TICK_LEN 0.1        /* 目盛りサイズ */
#define TICK_INTERVAL 1     /* 目盛り間隔 */
#define POINT_SIZE	0.01    /* 点列表示サイズ */

#define length(arr)	((int)(sizeof(arr)/sizeof(arr[0])))

/* 離散点列の座標 */
double p[][2] = {
    {-8.0, 3.0},
    {-4.0, 1.0},
    {0.0, -1.0},
    {4.0, -2.0},
    {6.0, 3.0},
};

/*
double p[][2] = {
    {-4.0, -3.0},
    {-2.0, -2.7},
    {0.0, 0.0},
    {2.0, 6.0},
    {4.0, 1.0},
    {6.0, -3.0}
};
*/

/* 関数プロトタイプ宣言 */
extern double lagrange(double x, matrix points);

void init(void);
void set_ortho(void);
void DrawAxes(double x1, double x2, double y1, double y2);
void DrawTicks(double x1, double x2, double y1, double y2, double interval);
void DrawPoints(double x1, double y1);

/* グローバル変数宣言 */
double dx;
double min_x, min_y, max_x, max_y;
int x_orgn, y_orgn, left_down, right_down;
int width, height;
double speed_x, speed_y;
int samples;
matrix points;


void init(void)
{
    int i;
    
    min_x = MIN_X; max_x = MAX_X;
    min_y = MIN_Y; max_y = MAX_Y;
    set_ortho();
    left_down = 0;
    width = WIDTH;
    height = HEIGHT;
    
    if (!mat_alloc(&points, length(p), 2)) {
        printf("Allocation error.\n");
        exit(-1);
    }

    for (i = 0; i < length(p); i++) {
        mat_elem(points, i, 0) = p[i][0];
        mat_elem(points, i, 1) = p[i][1];
    }
}

void set_ortho(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(min_x, max_x, min_y, max_y, -1.0, 1.0);
    samples = width;
    dx = (max_x - min_x) / (double)samples;
    speed_x = (max_x - min_x) / (double)width;
    speed_y = (max_y - min_y) / (double)height;
}

void DrawAxes(double x1, double x2, double y1, double y2)
{
    glColor3f(0.5, 0.5, 0.0);
    glBegin(GL_LINES);
    glVertex2d(x1, 0);
    glVertex2d(x2, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(0, y1);
    glVertex2d(0, y2);
    glEnd();
}

void DrawTicks(double x1, double x2, double y1, double y2, double interval)
{
    double i, min_tick;
    glColor3f(0.5, 0.0, 0.0);
    min_tick = (int)(x1 / interval) * interval;
    for (i = min_tick; i <= x2; i+=interval) {
        glBegin(GL_LINES);
        glVertex2d(i, -TICK_LEN);
        glVertex2d(i, TICK_LEN);
        glEnd();
    }
    min_tick = (int)(y1 / interval) * interval;
    for (i = min_tick; i <= y2; i+=interval) {
        glBegin(GL_LINES);
        glVertex2d(-TICK_LEN, i);
        glVertex2d(TICK_LEN, i);
        glEnd();
    }
}

void DrawPoints(double x1, double y1)
{
    double w, h;
    w = (max_x - min_x) * POINT_SIZE;
    h = (max_y - min_y) * POINT_SIZE;
    glBegin(GL_LINES);
    glVertex2d(x1 - w, y1 - h);
    glVertex2d(x1 + w, y1 + h);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2d(x1 - w, y1 + h);
    glVertex2d(x1 + w, y1 - h);
    glEnd();
}

void display(void)
{
    double i;
    int j;
    
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    DrawAxes(min_x, max_x, min_y, max_y);
    DrawTicks(min_x, max_x, min_y, max_y, TICK_INTERVAL);
    glColor3f(0.0, 0.0, 0.0);
    for (i = min_x; i < max_x+dx; i+=dx) {
        glBegin(GL_LINES);
        glVertex2d( i - dx/2., lagrange(i-dx/2., points));
        glVertex2d( i + dx/2., lagrange(i+dx/2., points));
        glEnd();
    }
    glColor3f(1.0, 0.0, 0.0);
    for (j = 0; j < length(p); j++) {
        DrawPoints(p[j][0], p[j][1]);
    }
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    width = w; height = h;
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    set_ortho();
}

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
        x_orgn = x; y_orgn = y;
    }
    left_down = (button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN);
    right_down = (button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'q' || key == 0x1b) {
        glutDestroyWindow(glutGetWindow());
        exit(0);
    }
}

void motion(int x, int y)
{
    if (left_down) {
        min_x -= (x - x_orgn) * speed_x;
        max_x -= (x - x_orgn) * speed_x;
        min_y += (y - y_orgn) * speed_y;
        max_y += (y - y_orgn) * speed_y;
        x_orgn = x; y_orgn =y;
    } else if (right_down) {
        min_x -= (x - x_orgn) * speed_x;
        max_x += (x - x_orgn) * speed_x;
        min_y += (y - y_orgn) * speed_y;
        max_y -= (y - y_orgn) * speed_y;
        x_orgn = x; y_orgn = y;
    }
    set_ortho();
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow(argv[0]);
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}
