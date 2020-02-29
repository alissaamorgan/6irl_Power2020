#include <kipr/botball.h>
#include <math.h>
#include <create_functions.h>
#include <create_comp_lib.h>
#include <trey.h>
#include <ross.h>
#include <threads.h>

int cube_stack1 = arm_max - 500;
int cube_stack2 = arm_max - 700;
int top_cube = arm_max - 900;
int low_cubes = arm_max - 600;
int smol_cubes = closed - 50;
int stack_hand = closed;
int unstack_hand = closed + 900;
int over_block = arm_max - 1300;
int squeeze = closed + 300;
int release = closed + 200;
int base_up = base_min + 600;
int base_down = base_min + 1200;
int chain_grab = closed + 100;
int chain_arm = arm_max - 300;

int trey()
{
    create_connect();
    calibrate_gyro();

    servo(base,base_down,3);
    	msleep(16);
    servo(arm,cube_stack1,3);
    	msleep(16);
    servo(hand,open,3);
    	msleep(16);
    med_cubes();
    first_cube();
    four_cubes();
    
    create_disconnect();
    return 0;
}

int med_cubes()
{
    thread green_up;
    	green_up = thread_create(thread_green_up);
    
    ///////////////////////////////////////////////// to stack
    PID_gyro_drive_create(300,2.8/1.5);//200,2.9
    	msleep(16);
    create_spin_CW(50);
        msleep(900);
    PID_gyro_drive_create(75,1.25/1.5);//40,1
    	msleep(16);
    servo(hand,stack_hand,3);
    	msleep(16);
    /////////////////////////////////////////////////
    
    ///////////////////////////////////////////////// wiggle
    create_spin_CW(150);
        msleep(100);
    create_spin_CCW(150);
        msleep(100);
    create_spin_CW(150);
        msleep(100);
    create_spin_CCW(150);
        msleep(100);
    /////////////////////////////////////////////////
    
    ///////////////////////////////////////////////// back up
    create_spin_CCW(50);
        msleep(900);
    
    thread_start(green_up);
    	msleep(16);
    
    PID_gyro_drive_create(-300,3.5/1.5);//200,2.9
    	msleep(16);
    	create_stop();
    	msleep(16);
    PID_gyro_drive_create(150,1.9/1.5);
    	msleep(16);
    turn_with_gyro_create(200,-90);
    	msleep(16);
    square_up_front_create(black,square);
    	msleep(16);
    /////////////////////////////////////////////////
    
    ///////////////////////////////////////////////// unstack
    servo(arm,cube_stack1,3);
    	msleep(16);
    servo(hand,unstack_hand,3);
    	msleep(16);
    servo(arm,top_cube,3);
    	msleep(16);
    servo(hand,stack_hand,3); //2
    	msleep(16);
    servo(arm,over_block,3); //2
    	msleep(16);
    create_drive_direct(150,-150);
    	msleep(250);
    	create_stop();
    	msleep(16);
    //PID_gyro_drive_create(37.5,0.6/1.5);//25,1
    	msleep(16);
    servo(arm,cube_stack2,3);//2
    	msleep(16);
    servo(hand,unstack_hand,3);//2
    	msleep(16);
    
    servo(arm,over_block,3);//2
    	msleep(16);
    
    //PID_gyro_drive_create(37.5,1/1.5);//25,1
    	msleep(16);
    servo(hand,open,3);
    	msleep(16);
    create_drive_direct(-150,150);
    	msleep(150);
    	create_stop();
    	msleep(16);
    servo(arm,cube_stack1,3);
    	msleep(16);
    PID_gyro_drive_create(37.5,1/1.5);//25,1
    	msleep(16);
    create_drive_direct(-150,150);
    	msleep(100);
    	create_stop();
    	msleep(16);
    
    servo(hand,squeeze,3);//2			//start pack green cubes in corner
    	msleep(16);
    
    
    
    square_up_front_create(black,-square);
    	msleep(16);
    	create_stop();
    	msleep(16);
    PID_gyro_drive_create(150,0.4/1.5);//65,1
    	msleep(16);
    	create_stop();
    	msleep(16);
    servo(hand,unstack_hand,3);//2
    	msleep(16);
    square_up_front_create(black,-square);
    	msleep(16);
    servo(arm,arm_min,3);
    	msleep(16);
    PID_gyro_drive_create(150,0.5/1.5);
    	msleep(16);
    
    /////////////////////////////////////////////////

    ///////////////////////////////////////////////// setup for first_cube()
    turn_with_gyro_create(200,90);
    	msleep(16);
    servo(base,base_up,3);
    	msleep(16);
    linefollow_create(1.75,250,left);
    	msleep(16);
    	create_stop();
    	msleep(16);
    turn_with_gyro_create(200,-90);
    	msleep(16);
    servo(hand,unstack_hand,3);
    	msleep(16);
    servo(arm,low_cubes,3);
    	msleep(16);
    servo(base,base_down,3);
    	msleep(16);
    PID_gyro_drive_create(100,0.5/1.5);
    	msleep(16);
    square_up_back_create(black,-square);
    	msleep(16);
    /////////////////////////////////////////////////
    thread_destroy(green_up);
    
    return 0;
}

int first_cube()
{
    thread four_down;
    	four_down = thread_create(thread_four_down);
    thread red_up;
    	red_up = thread_create(thread_red_up);
    /////////////////////////////////////////////////
    PID_gyro_drive_create(100,0.5/1.5);
    	msleep(16);
    servo(hand,smol_cubes,3);
    	msleep(16);
    square_up_back_create(black,-square);
    	msleep(16);
    
    thread_start(red_up);
    	msleep(16);
    
    turn_with_gyro_create(200,-180);
    	msleep(16);
    	create_stop();
    	msleep(16);
    
    create_spin_CCW(100);				// slight turn to avoid green cubes
        msleep(200);
    
    PID_gyro_drive_create(-300,3/1.5);
    	msleep(16);
    PID_gyro_drive_create(150,0.65/1.5);
    	msleep(16);
    turn_with_gyro_create(200,90);
    	msleep(16);
    square_up_front_create(black,square);
    	msleep(16);
    PID_gyro_drive_create(200,1.75/1.5);
    	msleep(16);
    square_up_back_create(black,-square);
    	msleep(16);
    PID_gyro_drive_create(-200,1.2/1.5);
    	msleep(16);
    servo(arm,top_cube,3);
    	msleep(16);
    
    create_drive_direct(50,-50);
    	msleep(250);
    	create_stop();
    	msleep(16);
    
    servo(hand,release,3);
    	msleep(160);
    servo(arm,arm_min,3);
    	msleep(16);
    
    create_drive_direct(-50,50);
    	msleep(250);
    	create_stop();
    	msleep(16);
    /////////////////////////////////////////////////
    
    ///////////////////////////////////////////////// set up for four_cubes()
    PID_gyro_drive_create(200,2/1.5);
    	msleep(16);
    square_up_front_create(black,-square);
    	msleep(16);
    servo(hand,open,3);
    	msleep(16);
    PID_gyro_drive_create(100,1.25/1.5);
    	msleep(16);
    thread_start(four_down);
    	msleep(16);
    turn_with_gyro_create(200,-180);
    	msleep(16);
    square_up_back_create(black,-square);
    	msleep(16);
    create_drive_direct(-50,50);
    	msleep(50);
    	create_stop();
    	msleep(16);
    PID_gyro_drive_create(100,1.5/1.5);
    	msleep(16);
    /////////////////////////////////////////////////
    
    thread_destroy(four_down);
    thread_destroy(red_up);
    return 0;
}

int four_cubes()
{
    thread four_close;
    	four_close = thread_create(thread_four_close);
    
    /////////////////////////////////////////////////
    thread_start(four_close);
    	msleep(16);
    PID_gyro_drive_create(-15,2/1.5);
    	msleep(16);
    	create_stop();
    	msleep(16);
    
    create_drive_direct(-50,50);
    	msleep(50);
    	create_stop();
    	msleep(16);
    servo(arm,over_block,3);
    	msleep(16);
    turn_with_gyro_create(200,180);
    	msleep(16);
    PID_gyro_drive_create(200,1/1.5);
    	msleep(16);
    square_up_back_create(black,-square);
    	msleep(16);
    PID_gyro_drive_create(-200,0.75/1.5);
    	msleep(16);
    
    create_drive_direct(50,-50);
    	msleep(250);
    	create_stop();
    	msleep(16);
    
    servo(hand,open,3);
    	msleep(16);
    
    create_drive_direct(-50,50);
    	msleep(250);
    	create_stop();
    	msleep(16);
    /////////////////////////////////////////////////
    
    thread_destroy(four_close);
    return 0;
}