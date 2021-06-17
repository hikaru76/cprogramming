#include <stdio.h>
#include <math.h>
#include <string.h>

float goal_h = 3.05; //ゴール高さ
float goal_w = 4.2; //ゴールまで水平距離
float goal_r = 0.225; //ゴール半径
float ball_r = 0.1225; //ボール半径
float e = 0.1; //ゴール衝突の際の反発係数
float g = 9.8; //重力加速度
float x0 = 0.0; //直前ボールx座標
float y0 = 0.0; //直前ボールy座標
float x = 0.0; //今回ボールx座標
float y = 0.0; //今回ボールy座標
float dx = 0.0; //移動距離x
float dy = 0.0; //移動距離y
float t = 0.0; //経過時間
float vx = 0.0; //ボールx方向速度
float vy = 0.0; //ボールy方向速度 
float v0x = 0.0; //ボールx方向初速度
float v0y = 0.0; //ボールy方向初速度
float theta = 0.0; //初期打ち上げ角度
int flag1 = 0; //ゴール上面通過フラグ
int flag2 = 0; //ゴール下面通過フラグ
float dt = 0.1;

//ボールとゴールリングとの衝突判定
int check_bound() {
    if ((goal_w - goal_r - x) * (goal_w - goal_r - x) + (goal_w - goal_r - x) * (goal_w - goal_r - x) < ball_r * ball_r ||
        (goal_w + goal_r - x) * (goal_w + goal_r - x) + (goal_w + goal_r - x) * (goal_w + goal_r - x) < ball_r * ball_r)
        return (1);
    return (0);
}

//ボールのゴール通過判定 
int check_flag(int number) {
    int h_flag = goal_h + 0.05 ? number == 1 : goal_h - 0.05; //ゴールに入った判定をゴール鉛直方向±5cmの地点で行う
    if (goal_w - goal_r < x - ball_r && goal_w + goal_r > x + ball_r && abs(h_flag - y) < 0.01)
        return (1);
    return (0);
}

//ボールとゴールリング衝突時速度計算
void calculate_confliction() {
    vx = vx * e * (-1);
    vy = vy * e * (-1);
}

//毎フレーム速度位置計算
void calculate() {
    x0 = x;
    y0 = y;
    vx = vx;
    vy = vy - g * dt;
    dx = vx * dt;
    dy = vy * dt;
    x = x0 + dx;
    y = y0 + dy;
    printf("%f %f", x, y);
}

//./basket v0 theta
int main(int argc, char **argv) {
    if (argc != 3)
    {
        printf("need 3 arguments (./basket v0 theta)");
        return (1);
    }
    theta = atof(argv[2]);
    v0x = atof(argv[1]) * cos(theta);
    v0y = atof(argv[0]) * sin(theta);
    for (int i = 0; i < 100; i++) {
        calculate();
    }
    return (0);
}