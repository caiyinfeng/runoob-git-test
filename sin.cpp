#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>

int main()
{
    double cam_x_value=-4.22;
    double cam_z_value=150;
    double cam_angle_value=-10.83;
    double cam_a_length=44;
    double l = 33;
    double a;
    double pi=3.14;
    double cam_j_h =(cam_angle_value/180)*pi;
    double cam_angle = abs(cam_j_h);
    double cam_xx_value = cam_a_length * sin(cam_angle);
    double cam_zz_value = cam_a_length * cos(cam_angle);
    double cam_X_value = abs(cam_x_value + cam_xx_value);
    double cam_Z_value = cam_z_value + cam_zz_value;
    double dz = sqrt(cam_X_value*cam_X_value+cam_Z_value*cam_Z_value);
    double dl = sqrt((dz-cam_Z_value)*(dz-cam_Z_value)+cam_X_value*cam_X_value);
    double jd_a = atan2(cam_Z_value, cam_X_value) ;
    double bb = dl/(2*sin(jd_a/2));
    printf("bb=%2f\n", bb);    
    printf("jd_a=%2f\n", jd_a);
    //printf("cam_Z_value:%2f,cam_X_value:%2f,cam_xx_value:%2f,cam_zz_value:%2f\n", cam_Z_value, cam_X_value, cam_xx_value, cam_zz_value);
    //    double a1 = 2*cam_x_value*cam_z_value;
    //    double a2 =
    //    2*cam_x_value*sqrt(abs(3*cam_x_value*cam_x_value-2*cam_z_value*cam_z_value));
    //    double a3 = 4*cam_z_value*cam_z_value;
    double a1 = 2 * cam_X_value * cam_Z_value;
    double a2 = 2 * cam_Z_value * sqrt(abs(3 * cam_X_value * cam_X_value - 2 * cam_Z_value * cam_Z_value));
    double a3 = 4 * cam_Z_value * cam_Z_value;
    a = acos((a1 + a2) / a3);
    double cam_length = abs((cam_z_value -115) / sin(cam_angle_value));
    short v_l = -100;
    short v_r = (2 * bb + l) * v_l /abs (2 * bb - l);
    //short v_r = (short)((abs(cam_length-1 ) * v_l) / 45);
    // printf("a1:%2f,a2:%2f,a3:%2f\n",a1,a2,a3);
     printf("a=%2f\n", a);
     printf("cam_length=%2f\n", cam_length);
    printf("v_l=%d\n", v_l);    
    printf("v_r=%d\n", v_r);
    return 0;
}

