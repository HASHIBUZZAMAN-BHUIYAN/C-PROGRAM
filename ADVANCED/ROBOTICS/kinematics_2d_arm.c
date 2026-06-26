/*
 * 2-Link Arm Kinematics (Forward + Inverse)
 * Models: a planar 2-DOF robotic arm (like a SCARA arm in 2D).
 *
 * Compile: gcc kinematics_2d_arm.c -o kinematics_2d_arm.exe -lm
 */
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979

typedef struct { double x, y; } Vec2;

/* Forward kinematics: given joint angles (radians), compute end-effector position */
Vec2 forward_kinematics(double l1, double l2, double theta1, double theta2) {
    double x = l1 * cos(theta1) + l2 * cos(theta1 + theta2);
    double y = l1 * sin(theta1) + l2 * sin(theta1 + theta2);
    return (Vec2){x, y};
}

/* Inverse kinematics: given target (x,y), compute joint angles */
typedef struct { double theta1, theta2; int valid; } IKResult;

IKResult inverse_kinematics(double l1, double l2, double tx, double ty) {
    IKResult r = {0, 0, 0};
    double d2 = tx*tx + ty*ty;
    double cos_theta2 = (d2 - l1*l1 - l2*l2) / (2*l1*l2);
    if (cos_theta2 < -1.0 || cos_theta2 > 1.0) return r;  /* out of reach */

    r.theta2 = acos(cos_theta2);  /* elbow-up solution */
    double k1 = l1 + l2 * cos(r.theta2);
    double k2 = l2 * sin(r.theta2);
    r.theta1 = atan2(ty, tx) - atan2(k2, k1);
    r.valid  = 1;
    return r;
}

void print_arm(double l1, double l2, double t1, double t2) {
    double j1x = l1*cos(t1), j1y = l1*sin(t1);
    Vec2 ee = forward_kinematics(l1, l2, t1, t2);
    printf("  Joint1=(%.2f,%.2f)  EE=(%.2f,%.2f)  "
           "theta1=%.1f° theta2=%.1f°\n",
           j1x, j1y, ee.x, ee.y,
           t1*180/PI, t2*180/PI);
}

int main(void) {
    double l1 = 3.0, l2 = 2.0;  /* link lengths */
    printf("=== 2-Link Arm Kinematics ===\n");
    printf("Link lengths: L1=%.1f  L2=%.1f\n\n", l1, l2);

    /* --- Forward Kinematics demo --- */
    printf("--- Forward Kinematics ---\n");
    double angles[][2] = {
        {0, 0}, {45, 0}, {45, -90}, {0, 90}, {90, 45}
    };
    for (int i = 0; i < 5; i++) {
        double t1 = angles[i][0] * PI/180;
        double t2 = angles[i][1] * PI/180;
        Vec2 ee = forward_kinematics(l1, l2, t1, t2);
        printf("  theta1=%5.1f°  theta2=%5.1f°  ->  EE=(%.3f, %.3f)\n",
               angles[i][0], angles[i][1], ee.x, ee.y);
    }

    /* --- Inverse Kinematics demo --- */
    printf("\n--- Inverse Kinematics ---\n");
    Vec2 targets[] = {{5.0,0.0},{3.0,3.0},{0.0,4.5},{-2.0,3.0},{4.0,-2.0}};
    for (int i = 0; i < 5; i++) {
        double tx = targets[i].x, ty = targets[i].y;
        IKResult ik = inverse_kinematics(l1, l2, tx, ty);
        if (!ik.valid) {
            printf("  Target(%.1f,%.1f): OUT OF REACH\n", tx, ty);
        } else {
            Vec2 check = forward_kinematics(l1, l2, ik.theta1, ik.theta2);
            printf("  Target(%.1f,%.1f)  ->  theta1=%.1f°  theta2=%.1f°  "
                   " verify=(%.3f,%.3f)\n",
                   tx, ty, ik.theta1*180/PI, ik.theta2*180/PI,
                   check.x, check.y);
        }
    }

    /* --- Workspace boundary scan --- */
    printf("\n--- Reachable Workspace (ASCII) ---\n");
    int grid[21][41]; /* -5..5 y  x -5..5 */
    for (int r=0;r<21;r++) for(int c=0;c<41;c++) grid[r][c]=0;
    for (int t1=-180;t1<=180;t1+=5) for(int t2=-180;t2<=180;t2+=5) {
        Vec2 ee = forward_kinematics(l1,l2,t1*PI/180,t2*PI/180);
        int cx=(int)round(ee.x*4)+20, cy=(int)round(ee.y*4)+10;
        if(cx>=0&&cx<41&&cy>=0&&cy<21) grid[cy][cx]=1;
    }
    for(int r=20;r>=0;r--){
        for(int c=0;c<41;c++) printf("%c", grid[r][c]?'*':' ');
        printf("|\n");
    }

    return 0;
}
