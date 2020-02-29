#include <kipr/botball.h>
#include <math.h>
#include <create_functions.h>
#include <create_comp_lib.h>
#include <trey.h>
#include <alissa.h>
#include <camera.h>
long area_close=2139607924;
long area_far=2128616692;//less than area_close by 10,991,232
int camera_initialize(){
    camera_open_black();
    int a=0;
    while(a<6){
        camera_update();
        a=a+1;
    }
    return 0;
}
int full_check(int c){ 
    int a=0;
    int b=0;
    while(a<30){  
        camera_update();
        if(get_object_count(c)>0){b=b+1;}
        a=a+1;
    }
    if(b>10){printf("i see color");
             return 1;}
    else{printf("i dont see color");
         return 0;}
}
/*int camera_center(int color){
    camera_initialize();
    if(full_check(color)==1&&get_object_center_x(color,0)==!0){
        while(1){
            mav(0,18.75*(get_object_center_x(color,0)-80));
            mav(3,18.75*(80-(get_object_center_x(color,0))));
        }
        return 1;
    }
    else{return 0;}
}*/
int yb1,y2,y3,g1,g2,g3,g4,r1,r2,r3,r4 = initial;
int block_check(){
    camera_initialize();
    if (full_check(yellow)==1){}
    else {yb1=-1;}
    return 0;
}
int check_thread(int color){  //if yb1 = 0 then its not centered, if yb1 = 1 then the camera is centered
    camera_initialize();
    while(1){
        full_check(color);
        if(get_object_center_x(color,0)==!79){yb1=0;}
        if(get_object_center_x(color,0)==79){yb1=1;}
    }
    return 0;
}

int yellow_camera(int color){
    camera_initialize();
   	create_drive_straight(150);
    printf("%d location",get_object_area(color,0));
    yb1=0;
    while(yb1<1){   
        camera_update();
        if(get_object_count(color)>0){
            if(get_object_center_x(color,0)<81 || get_object_area(color,0) >= area_far ){yb1=0; }
        	else{
                yb1=1;
                break;
                }
    	}
   	}
    printf("yellow %d", yb1);
    create_stop();
    return 0;
}

