#include <kipr/botball.h>
#include <math.h>
#include <create_functions.h>
#include <create_comp_lib.h>
#include <alissa.h>
int base_front = base_start + 1450;
int normal = 300;
int back = front - 1200;
int half = front - 700;
int open = closed + 1647;
int tight = closed - 200;
int small_open = closed + 1200;
int tightish = closed - 125;
int ajar = closed + 800;
int sET = 1;
int cET = 2;

void slow_arm02 (int x )//this funtion slows 
{ 

    enable_servo(arm);
    int desired_position;
    int current_position = get_servo_position(arm);
    if (x > arm_max) {desired_position = arm_max;}
    else if(x < arm_min) {desired_position = arm_min;}
    else {desired_position = x;}

    while(current_position != desired_position)
    {
        if(current_position < desired_position)
        { current_position=current_position +1;
         set_servo_position(arm, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -1;
         set_servo_position(arm, current_position);
         msleep(2);
        }
    }

    set_servo_position (arm, x);
    disable_servo (arm);
}

void slow_arm (int x,int speed)//this funtion slows 
{ 

    enable_servo (arm);
    int desired_position;
    int current_position = get_servo_position(arm);
    if (0) {desired_position = arm_max;}
    else if(0) {desired_position = arm_min;}
    else {desired_position = x;}

    switch(speed){
        case 1:
            while(current_position <= desired_position-2 || current_position >= desired_position+2)
            {
                if(current_position < desired_position)
                { current_position=current_position +2;
                 set_servo_position(arm, current_position);
                 msleep(1);
                }
                if(current_position > desired_position)
                { current_position=current_position -2;
                 set_servo_position(arm, current_position);

                 msleep(1);
                }
            }
            break;
        case 2:
            while(current_position != desired_position)
            {
                if(current_position < desired_position)
                { current_position=current_position +1;
                 set_servo_position(arm, current_position);
                 msleep(2);
                }
                if(current_position > desired_position)
                { current_position=current_position -1;
                 set_servo_position(arm, current_position);

                 msleep(2);
                }
            }
            break;
    }

    set_servo_position (arm, x);
    msleep(25);
    disable_servo (arm);

}

void slow_hand ( int z, int speed )//this funtion slows 
{ 

    enable_servo (hand);
    int desired_position;
    int current_position = get_servo_position(hand);
    if (0) {desired_position = hand_max;}
    else if(0) {desired_position = hand_min;}
    else {desired_position = z;}


    switch(speed){
        case 1:
            while(current_position <= desired_position-2 || current_position >= desired_position+2)
            {
                if(current_position < desired_position)
                { current_position=current_position +2;
                 set_servo_position(hand, current_position);
                 msleep(1);
                }
                if(current_position > desired_position)
                { current_position=current_position -2;
                 set_servo_position(hand, current_position);
                 msleep(1);
                }
            }
            break;
        case 2:

            while(current_position != desired_position)
            {
                if(current_position < desired_position)
                { current_position=current_position +1;
                 set_servo_position(hand, current_position);
                 msleep(2);
                }
                if(current_position > desired_position)
                { current_position=current_position -1;
                 set_servo_position(hand, current_position);

                 msleep(2);
                }
            }
            break;
    }
    set_servo_position (hand, z);
    msleep(25);
    disable_servo (hand);
}

void slow_base(int x ) 
{ 
    enable_servo(base);
    int desired_position;
    int current_position = get_servo_position(base);
    if (x > base_max) {desired_position = base_max;}
    else if(x < base_min) {desired_position = base_min;}
    else {desired_position = x;}
    while(current_position != desired_position){
        if(current_position < desired_position)
        { current_position=current_position +1;
         set_servo_position(base, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -1;
         set_servo_position(base, current_position);
         msleep(2);
        }
    }
    set_servo_position (base, x);
    disable_servo (base);
}

void start_position(){
    slow_base(base_start);
 	msleep(500);
    slow_arm(darm_start,60);//clear_swings
    msleep(300);
    slow_hand(dhand_start,60);//grab_yellow
    msleep(1000);
}

void arm_out(){
    slow_base(front);
    slow_arm(down, 1);
}

void slow_base_valve()//this function slows 
{ 

    enable_servo(base);
    int desired_position;
    int current_position = get_servo_position(base);
    if (front-750 > base_max) {desired_position = base_max;}
    else if(front-750 < base_min) {desired_position = base_min;}
    else {desired_position = front-750;}

    while(current_position != desired_position)
    {
        if(current_position < desired_position)
        { current_position=current_position +1;
         set_servo_position(base, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -1;
         set_servo_position(base, current_position);
         msleep(2);
        }
    }

    set_servo_position (base, front-750);
    disable_servo (base);
}

void slow_start() 
{ 	
    enable_servo(arm);
    enable_servo(hand);
    enable_servo(base);
    int d = mid;
    int dd = open;
    int ddd = back;
    int c = get_servo_position(arm);
    int cc = get_servo_position(hand);
    int ccc = get_servo_position(base);

    while((c != d) || (cc != dd) || (ccc != ddd)) // this loop is being exited instantly. need to fix.
    {
        if(c < d)
        { c=c+1;
         set_servo_position(arm, c);
         msleep(2);
        }
        if(c > d)
        { c=c-1;
         set_servo_position(arm, c);
         msleep(2);
        }
        if(cc < dd)
        { cc=cc+1;
         set_servo_position(hand, cc);
         msleep(2);
        }
        if(cc > dd)
        { cc=cc-1;
         set_servo_position(hand, cc);
         msleep(2);
        }
        if(ccc < ddd)
        { ccc=ccc+1;
         set_servo_position(base, ccc);
         msleep(2);
        }
        if(ccc > ddd)
        { ccc=ccc-1;
         set_servo_position(base, ccc);
         msleep(2);
        }
        msleep(2);
    }
    set_servo_position(arm, mid);
    set_servo_position(hand,open);
    set_servo_position(base,back);
    disable_servo(arm);
    disable_servo(hand);
    disable_servo(base);
}

void slow_arm_pre_valve()//this funtion slows 
{ 
    enable_servo(arm);
    int desired_position;
    int current_position = get_servo_position(arm);
    if ((up+625) > arm_max) {desired_position = arm_max;}
    else if((up+625) < arm_min) {desired_position = arm_min;}
    else {desired_position = (up+625);}

    while(current_position != desired_position)
    {
        if(current_position < desired_position)
        { current_position=current_position +1;
         set_servo_position(arm, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -1;
         set_servo_position(arm, current_position);
         msleep(2);
        }
    }

    set_servo_position (arm, (up+625));
    disable_servo (arm);
}

void slow_base_front()//this funtion slows 
{ 
    enable_servo(base);
    int desired_position;
    int current_position = get_servo_position(base);
    if (front > base_max) {desired_position = base_max;}
    else if(front < base_min) {desired_position = base_min;}
    else {desired_position = front;}

    while(current_position >= desired_position+2 || current_position <= desired_position-2)
    {
        if(current_position < desired_position)
        { current_position=current_position +2;
         set_servo_position(base, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -2;
         set_servo_position(base, current_position);
         msleep(2);
        }
    }

    set_servo_position (base, front);
    disable_servo (base);
}

void slow_arm_up()//this funtion slows 
{ 
    enable_servo(arm);
    int desired_position;
    int current_position = get_servo_position(arm);
    if (up > arm_max) {desired_position = arm_max;}
    else if(up < arm_min) {desired_position = arm_min;}
    else {desired_position = up;}

    while(current_position >= desired_position+2 || current_position <= desired_position-2)
    {
        if(current_position < desired_position)
        { current_position=current_position +2;
         set_servo_position(arm, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -2;
         set_servo_position(arm, current_position);
         msleep(2);
        }
    }

    set_servo_position (arm, up);
    disable_servo (arm);
}

void slow_arm_up2()//this funtion slows 
{ 
    enable_servo(arm);
    int desired_position;
    int current_position = get_servo_position(arm);
    if (up > arm_max) {desired_position = arm_max;}
    else if(up < arm_min) {desired_position = arm_min;}
    else {desired_position = up;}

    while(current_position != desired_position)
    {
        if(current_position < desired_position)
        { current_position=current_position +1;
         set_servo_position(arm, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -1;
         set_servo_position(arm, current_position);
         msleep(2);
        }
    }

    set_servo_position (arm, up);
    disable_servo (arm);

    enable_servo(base);
    int desired_position2;
    int current_position2 = get_servo_position(base);
    if (front > base_max) {desired_position2 = base_max;}
    else if(front < base_min) {desired_position2 = base_min;}
    else {desired_position2 = front;}

    while(current_position2 != desired_position2)
    {
        if(current_position2 < desired_position2)
        { current_position2=current_position2 +1;
         set_servo_position(base, current_position2);
         msleep(2);
        }
        if(current_position2 > desired_position2)
        { current_position2=current_position2 -1;
         set_servo_position(base, current_position2);
         msleep(2);
        }
    }

    set_servo_position (base, front);
    disable_servo (base);
}

void slow_hand_open()//this funtion slows 
{ 
    enable_servo(hand);
    int desired_position;
    int current_position = get_servo_position(hand);
    if (small_open > hand_max) {desired_position = hand_max;}
    else if(small_open < hand_min) {desired_position = hand_min;}
    else {desired_position = small_open;}

    while(current_position >= desired_position+2 || current_position <= desired_position-2)
    {
        if(current_position < desired_position)
        { current_position=current_position +2;
         set_servo_position(hand, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -2;
         set_servo_position(hand, current_position);
         msleep(2);
        }
    }
    set_servo_position (hand, small_open);
    disable_servo (hand);
}

void slow_hand_small_open()//this funtion slows 
{ 
    enable_servo(hand);
    int desired_position = ajar+450;
    int current_position = get_servo_position(hand);
    if (closed-50 > hand_max) {desired_position = hand_max;}
    else if(closed-50 < hand_min) {desired_position = hand_min;}
    else {desired_position = closed-50;}

    while(current_position != desired_position)
    {
        if(current_position < desired_position)
        { current_position=current_position +1;
         set_servo_position(hand, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -1;
         set_servo_position(hand, current_position);
         msleep(2);
        }
    }
    set_servo_position (hand, ajar+450);
    disable_servo (hand);
}

void slow_arm_down()//this funtion slows 
{ 
    enable_servo(arm);
    int desired_position;
    int current_position = get_servo_position(arm);
    if (down > arm_max) {desired_position = arm_max;}
    else if(down < arm_min) {desired_position = arm_min;}
    else {desired_position = down;}

    while(current_position >= desired_position+2 || current_position <= desired_position-2)
    {
        if(current_position < desired_position)
        { current_position=current_position +2;
         set_servo_position(arm, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -2;
         set_servo_position(arm, current_position);
         msleep(2);
        }
    }

    set_servo_position (arm, down);
    disable_servo (arm);
}

void slow_hand_close()//this funtion slows 
{ 
    enable_servo(hand);
    int desired_position = tight;
    int current_position = get_servo_position(hand);
    //if (tight > hand_max) {desired_position = hand_max;}
    //else if(tight < hand_min) {desired_position = hand_min;}
    //else {desired_position = tight;}

    while(current_position >= desired_position+2 || current_position <= desired_position-2)
    {
        if(current_position < desired_position)
        { current_position=current_position +2;
         set_servo_position(hand, current_position);
         msleep(1);
        }
        if(current_position > desired_position)
        { current_position=current_position -2;
         set_servo_position(hand, current_position);
         msleep(1);
        }
    }

    set_servo_position (hand, tight);
    disable_servo (hand);
}

/*void short_pause(){
    create_stop();
    msleep(100);
}*/

void slow_arm_bucket()//this funtion slows 
{ 
    enable_servo(arm);
    int desired_position;
    int current_position = get_servo_position(arm);
    if (down-500 > arm_max) {desired_position = arm_max;}
    else if(down-500 < arm_min) {desired_position = arm_min;}
    else {desired_position = down-500;}

    while(current_position != desired_position)
    {
        if(current_position < desired_position)
        { current_position=current_position +1;
         set_servo_position(arm, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -1;
         set_servo_position(arm, current_position);
         msleep(2);
        }
    }

    set_servo_position (arm, down-500);
    disable_servo (arm);
}

void shake_arm(){
    enable_servos(arm);
    int i = 0;
    while(i < 20){
        set_servo_position(arm,arm_building+325);
        msleep(30);
        set_servo_position(arm,arm_building-250);
        msleep(30);
        i=i+1;
    }
}

void fast_hand (int x){ 
    enable_servo(hand);
    int desired_position;
    int current_position = get_servo_position(hand);
    if (x > hand_max) {desired_position = hand_max;}
    else if(x < tight) {desired_position = tight;}
    else {desired_position = x;}
    while(current_position >= desired_position+3 || current_position <= desired_position-3){
        if(current_position < desired_position)
        { current_position=current_position +3;
         set_servo_position(hand, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -3;
         set_servo_position(hand, current_position);
         msleep(2);
        }
    }
    set_servo_position (hand, x);
    disable_servo (hand);
}

/*void first_water_down(){

    thread ab2;

    ab2 = thread_create(slow_arm_bucket);

    PID_gyro_drive_create(PID,2.3);
    slow_arm(down-250);
    fast_hand(closed+700);
    shake_arm();
    thread_start(ab2);
    create_stop();
    msleep(650);

    thread_destroy(ab2);
}

void all_water_drop(){
    PID_gyro_drive_create(-(PID*2),1.25);
    short_pause();
    turn_with_gyro_create(turn,-90);
    PID_gyro_drive_create(-(PID*4/3),2);
    PID_gyro_drive_create(PID,0.3);
    short_pause();
    turn_with_gyro_create(turn,90);
    slow_arm(arm_water);
    square_up_front_create(black,square);
    turn_with_gyro_create(turn-50,01);
    fast_hand(open);
}

void shake_arm_bucket(){
    enable_servos(arm);
    int i = 0;
    while(i < 20){
        set_servo_position(arm,down-400);
        msleep(30);
        set_servo_position(arm,down-475);
        msleep(30);
        i=i+1;
    }
}
*/
void fast_arm (int x )//this funtion slows 
{ 

    enable_servo(arm);
    int desired_position;
    int current_position = get_servo_position(arm);
    if (x > arm_max) {desired_position = arm_max;}
    else if(x < arm_min) {desired_position = arm_min;}
    else {desired_position = x;}
    while(current_position >= desired_position+3 || current_position <= desired_position-3)
    {
        if(current_position < desired_position)
        { current_position=current_position +3;
         set_servo_position(arm, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -3;
         set_servo_position(arm, current_position);
         msleep(2);
        }
    }
    set_servo_position (arm, x);
    disable_servo (arm);
}

void slow_arm_building()//this funtion slows 
{ 
    enable_servo(arm);
    int desired_position;
    int current_position = get_servo_position(arm);
    if (arm_building > arm_max) {desired_position = arm_max;}
    else if(arm_building < arm_min) {desired_position = arm_min;}
    else {desired_position = arm_building;}

    while(current_position >= desired_position+2 || current_position <= desired_position-2)
    {
        if(current_position < desired_position)
        { current_position=current_position +2;
         set_servo_position(arm, current_position);
         msleep(2);
        }
        if(current_position > desired_position)
        { current_position=current_position -2;
         set_servo_position(arm, current_position);
         msleep(2);
        }
    }
    set_servo_position (arm, arm_building);
    disable_servo (arm);
}