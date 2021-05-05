//セグフォ原因不明、デバッグしたいなぁ

#ifndef __APPLE__  // OSがMacでない (= WindowsやLinux)
#include <GL/glut.h>  // Windows, Linuxの場合のヘッダ
#else
#include <GLUT/glut.h>  // Macの場合のヘッダ
#endif

#include <stdio.h>
#include "matrix.h"
#include <math.h>

#define MAX_POINTS 5

int WINDOW_WIDTH = 500;   // ウィンドウの横幅
int WINDOW_HEIGHT = 500;  // ウィンドウの高さ

typedef struct list_node_ {
    int x, y;
    struct list_node_ *next;
} list_node;

typedef struct {
    list_node *root;
    int size;
} linked_list;

linked_list *points;

// リストの作成
void init_list(linked_list *list) {
    list->root = NULL;
    list->size = 0;
}

// rootを先頭要素とする連結リストの末尾に新しいノードを追加
void add_node(linked_list *list, int x, int y) {
    // 新しいノードの作成
    list_node *node = (list_node*)malloc(sizeof(list_node));
    node->x = x;
    node->y = y;
    node->next = NULL;

    // 末尾要素を探す
    if (list->root == NULL) {
        // まだ要素がなければ、先頭要素を新規ノードにする
        list->root = node;
    } else {
        // あるノードの次のノード (next) がNULLになるものを探す
        list_node *iter = list->root;
        while (iter->next != NULL) {
            iter = iter->next;
        }

        // 見つかったら末尾要素を新規ノードで置き換える
        iter->next = node;
    }

    // リストの要素数を1増やす
    list->size += 1;
}

// nodeで示されるノードをlistから削除する
void remove_node(linked_list *list, list_node *node) {
    // ノードが見つかったかどうか
    bool found = false;

    // ノードを探索する
    if (list->root == node) {
        // 先頭ノードがnodeならrootを置き換える
        list->root = list->root->next;
        found = true;
    } else {
        // 次の要素がnodeとなるノードを探す
        list_node *iter = list->root;
        while (iter != NULL) {
            if (iter->next == node) {
                // もし次のノードがnodeなら、さらにその次のノードとつなぎ直す
                iter->next = iter->next->next;
                found = true;
                break;
            }
            iter = iter->next;
        }
    }

    // もしnode見つかっていたら、メモリを解放してリストの要素数を1減らす
    if (found) {
        free(node);
        list->size -= 1;
    }
}

// リストのデータを全て削除する
void free_list(linked_list *list) {
    // 先頭から順にノードをfreeしていく
    list_node *iter = list->root;
    while (iter != NULL) {
        // 先に次のノードのポインタを別の変数にコピーしてからfreeする
        list_node *next = iter->next;
        free(iter);
        iter = next;
    }

    // 最後にリスト自体をfreeする
    free(list);
}

int get_list_xy(linked_list *list, int n, int xy) {
    int i = -1;
    list_node *it = list->root;

    while (++i < n && it->next)
        it = it->next;
    if (xy == 0)
        return (it->x);
    else
        return (it->y);
}

list_node *get_node(linked_list *list, int n) {
    int i = -1;
    list_node *it = list->root;

    while (++i < n && it->next)
        it = it->next;
    return (it);
}

void lagrange(double t, linked_list *points, double *x, double *y) {    
    double xt=0.0,lit=0.0,yt=0.0;
    int n=points->size;
    for (int i=0; i<n+1; i++) {
        lit=1;
        for (int j=0; j<n+1; j++) {
            if (j==i) {
                continue;
            }
            if (get_list_xy(points,i,0)-get_list_xy(points,j,0)==0) {
                continue;
            }
            
            else {
                lit*=(t-j) / (i-j);
                
            }
        }
        xt+=lit * get_list_xy(points,i,0);
        yt+=lit * get_list_xy(points,i,1);
        
    }
    
    *x = xt;
    *y = yt;
    
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display() {
    // ウィンドウ表示内容のクリア
    glClear(GL_COLOR_BUFFER_BIT);    
    glPointSize(10.0);
    // 点をあるだけ描く
       glPointSize(10.0);
       glBegin(GL_POINTS);
       for (int i = 0; i < points->size; i++) {
           const double x = get_list_xy(points, i, 0);
           const double y = get_list_xy(points, i, 1);
           glVertex2d(x, y);
       }
    glEnd();
    
    glPointSize(2.0);
    // 曲線を描く
    const double segments = 100;
    double x, y;
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= segments; i++) {
        // 以下のtは0から(n_points - 1)までをsegment分割したもの(この場合は100分割)
        const double t = (double)((points->size - 1) * i) / (double)segments;
        lagrange(t, points, &x, &y);
        glVertex2d(x, y);
    }
    glEnd();
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

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (points->size < MAX_POINTS)
            add_node(points, x, WINDOW_HEIGHT - y - 1);
        else
            printf("点の数は%dを超えられません\n", MAX_POINTS);
        glutPostRedisplay();//全体を再描画
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        int tmpx, tmpy;
        for (int i = 0; i < points->size; i++) {
            tmpx = get_list_xy(points, i, 0);
            tmpy = get_list_xy(points, i, 1);
            if (abs(tmpx - x) < 10 && abs(tmpy - y) < 10)
            {
                list_node *tmp =  get_node(points, i);
                remove_node(points, tmp);
                break;
            }
        }
        glutPostRedisplay();
    }
}

int main(int argc, char **argv) {
    init_list(points);

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
    // マウス操作時に呼ばれる関数の登録
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    // OpenGLの初期化処理  (これはコールバック関数ではないので直接呼び出す)
    init();
    // 描画ループの開始
    glutMainLoop();
    return (0);
}
