#ifndef __APPLE__  // OSがMacでない (= WindowsやLinux)
#include <GL/glut.h>  // Windows, Linuxの場合のヘッダ
#else
#include <GLUT/glut.h>  // Macの場合のヘッダ
#endif

int WINDOW_WIDTH = 500;   // ウィンドウの横幅
int WINDOW_HEIGHT = 500;  // ウィンドウの高さ

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display() {
    // ウィンドウ表示内容のクリア
    glClear(GL_COLOR_BUFFER_BIT);

	//S
	glColor3d(1.0, 0.0, 0.0);
	glLineWidth(10.0);
	glBegin(GL_LINE_STRIP);
	glVertex2d(250, 430);
	glVertex2d(150, 480);
	glVertex2d(50, 430);
	glColor3d(0.0, 1.0, 0.0);
	glVertex2d(50, 380);
	glVertex2d(250, 330);
	glColor3d(0.0, 0.0, 1.0);
	glVertex2d(250, 280);
	glVertex2d(150, 230);
	glVertex2d(50, 280);
	glEnd();
	glLineWidth(1.0);

    //H(長方形と直線を使って)
    glColor3d(0.0, 1.0, 0.0);
    glRectd(260, 20, 480, 240);
	glColor3d(0.0, 0.0, 0.0);
	glRectd(270, 20, 470, 240);
	glColor3d(0.3, 0.5, 0.7);
	glLineWidth(10.0);
	glBegin(GL_LINES);
	glVertex2d(270, 125);
	glColor3d(0.7, 0.5, 0.7);
	glVertex2d(470, 125);
	glEnd();
	glLineWidth(1.0);

	//星
	glColor3d(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);  
	glVertex2d(100, 150);
	glVertex2d(150, 150);
	glVertex2d(175, 100);
	glVertex2d(125, 60);
	glVertex2d(75, 100);
	glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2d(100, 150);
    glVertex2d(125, 200);
    glVertex2d(150, 150);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2d(150, 150);
    glVertex2d(210, 145);
    glVertex2d(175, 100);
	glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2d(175, 100);
    glVertex2d(180, 40);
    glVertex2d(125, 60);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2d(125, 60);
    glVertex2d(70, 40);
    glVertex2d(75, 100);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2d(75, 100);
    glVertex2d(40, 145);
    glVertex2d(100, 150);
	glEnd();

	//カービィ https://www.pinterest.jp/pin/661325526506360617/
	int kirbymap[26][29] = 	{
	{0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,1, 1,1,1,0,0, 0,0,0,0,0, 0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,1, 1,2,2,2,2, 2,2,2,1,1, 0,0,0,0,0, 0,0,0,0},
	{0,0,0,0,0, 0,0,1,1,2, 2,2,2,2,2, 2,2,2,2,2, 1,1,0,0,0, 0,0,0,0},
	{0,0,0,0,0, 0,1,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,1,0,0, 0,0,0,0},
	{0,0,0,0,0, 1,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,1,0, 0,0,0,0},

	{0,0,0,0,0, 1,2,2,2,2, 2,1,2,2,2, 2,2,1,2,2, 2,2,2,1,0, 0,0,0,0},
	{0,0,0,0,1, 2,2,2,2,2, 1,0,1,2,2, 2,1,0,1,2, 2,2,2,2,1, 0,0,0,0},
	{0,0,0,0,1, 2,2,2,2,2, 1,0,1,2,2, 2,1,0,1,2, 2,2,2,2,1, 0,0,0,0},
	{0,0,0,1,2, 2,2,2,2,2, 1,1,1,2,2, 2,1,1,1,2, 2,2,2,2,2, 1,0,0,0},
	{0,0,1,2,2, 2,2,2,2,2, 1,4,1,2,2, 2,1,4,1,2, 2,2,2,2,2, 2,1,0,0},

	{0,1,2,2,2, 2,2,5,5,2, 1,4,1,2,2, 2,1,4,1,2, 5,5,2,2,2, 2,2,1,0},
	{1,2,2,2,2, 2,5,5,5,5, 2,1,2,2,2, 2,2,1,2,5, 5,5,5,2,2, 2,2,2,1},
	{1,2,2,2,2, 2,2,5,5,2, 2,2,2,1,2, 1,2,2,2,2, 5,5,2,2,2, 2,2,2,1},
	{1,2,2,2,2, 2,2,2,2,2, 2,2,2,2,1, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,1},
	{1,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,1},
	
	{0,1,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,1, 2,2,1,0},
	{0,0,1,1,1, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,1,1, 1,1,0,0},
	{0,0,0,0,1, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,2,1,0, 0,0,0,0},
	{0,0,0,0,1, 1,2,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,1,1,0, 0,0,0,0},
	{0,0,0,1,5, 5,1,2,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,2,1,5,5, 1,0,0,0},

	{0,0,1,5,5, 5,5,1,2,2, 2,2,2,2,2, 2,2,2,2,2, 2,1,5,5,5, 5,1,0,0},
	{0,1,5,5,5, 5,5,5,1,1, 2,2,2,2,2, 2,2,2,2,1, 1,5,5,5,5, 5,5,1,0},
	{0,1,5,5,5, 5,5,5,5,5, 1,1,1,1,1, 1,1,1,1,5, 5,5,5,5,5, 5,5,1,0},
	{0,1,5,5,5, 5,5,5,5,5, 5,5,5,5,1, 5,5,5,5,5, 5,5,5,5,5, 5,5,1,0},
	{0,0,1,5,5, 5,5,5,5,5, 5,5,5,1,0, 1,5,5,5,5, 5,5,5,5,5, 5,1,0,0},

	{0,0,0,1,1, 1,1,1,1,1, 1,1,1,0,0, 0,1,1,1,1, 1,1,1,1,1, 1,0,0,0}
	};

	int y = 480.0;
	int x = 260.0;
	double kirby_size = 8.0;
	glLineWidth(kirby_size);
	for (int j = 0; j < 26; j++){
		for (int i = 0; i < 29; i++){
			if (kirbymap[j][i] == 0)
				glColor3d(1.0, 1.0, 1.0);
			else if (kirbymap[j][i] == 1)
				glColor3d(0.0, 0.0, 0.0);
			else if (kirbymap[j][i] == 2)
				glColor3d(1.0, 0.5, 0.5);
			else if (kirbymap[j][i] == 4)
				glColor3d(0.2, 0.2, 1.0);
			else if (kirbymap[j][i] == 5)
				glColor3d(1.0, 0.0, 0.0);
			glBegin(GL_LINES);
	    	glVertex2d(x + i * kirby_size, y - j * kirby_size);
    		glVertex2d(x + i * kirby_size, y - j * kirby_size - kirby_size);
    		glEnd();
		}
	}
    glFlush();
}

void reshape(int width, int height) {
	// OpenGLウィンドウの描画範囲を設定
	// 下記は描画範囲が[0, width] x [0, height]となるように設定している
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)width, 0.0, (double)height);
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
}

int main(int argc, char **argv) {
	// GLUTの初期化
	glutInit(&argc, argv);
	// ウィンドウのサイズを設定
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	// ウィンドウの作成 (引数はウィンドウのタイトル)
	glutCreateWindow("First GLUT program");
	// 描画に使う関数の登録
	glutDisplayFunc(display);
	// ウィンドウのサイズ変更時に呼ばれる関数の登録
	glutReshapeFunc(reshape);
	init();
	// 描画ループの開始
	glutMainLoop();
}