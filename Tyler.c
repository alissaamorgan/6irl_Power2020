#include <kipr/botball.h>
#include <math.h>
#include <create_functions.h>
#include <create_comp_lib.h>
#include <trey.h>
#include <alissa.h>
#include <reese.h>
#include <camera.h>
#include <threads.h>

int Tyler(){
    create_connect();
    calibrate_gyro();
    thread thread_small;
    	thread_small = thread_create(thread_small_1);
    thread arm_bigBlock;
    	arm_bigBlock = thread_create(thread_arm_bigBlock);
    thread arm_down;
    	arm_down = thread_create(thread_arm_down);
    thread hand_unstack;
    	hand_unstack = thread_create(thread_hand_open);
    ///////////////////////////////////////////////// setup for first_cube()
    servo(base,base_down+40,3);
    msleep(16);
    servo(arm,low_cubes,3);
    msleep(16);
    servo(hand,unstack_hand,3);
    PID_gyro_drive_create(300,1.7);
    msleep(16);
    create_stop();
    msleep(16);
    turn_with_gyro_create(200,-90);
    msleep(16);
    servo(base,base_down,3);
    msleep(16);
    PID_gyro_drive_create(100,0.5/1.5);
    msleep(16);
    square_up_back_create(black,square);
    msleep(16);
    PID_gyro_drive_create(-200,.12);
    msleep(16);
    servo(arm,arm_max-400,3);
    msleep(16);
    ///////////////////////////////////////////////// grab first smol boi
    servo(hand,hand_min,2);
    msleep(16);
    thread_start(thread_small);
    msleep(16);
    turn_with_gyro_create(100,-90);
    msleep(16);
    create_stop();
    msleep(16);
    bang();
    msleep(16);
    turn_with_gyro_create(300,90);
    msleep(16);
    thread_start(arm_bigBlock);
    msleep(16);
    square_up_front_create(black,-square);
    msleep(16);
    PID_gyro_drive_create(100,.3);
    msleep(16);
    create_drive_direct(0,150);
    msleep(500);
    create_stop();
    msleep(16);
    servo(hand,hand_min+400,3);
    ///////////////////////////////////////////////// delivered first smol boi
    msleep(16);

    thread_start(hand_unstack);
    msleep(16);
    
    square_up_front_create(black,-square);
    msleep(16);
    
    thread_start(arm_down);
    msleep(16);
    
    turn_with_gyro_create(300,90);
    msleep(16);
    
    thread_start(arm_down);
    msleep(16);
    
    create_drive_direct(-200,-200);
    msleep(500);
    create_stop();
    msleep(16);
    
    PID_gyro_drive_create(300,1.7);
    msleep(16);
    
    turn_with_gyro_create(200,-90);
    msleep(16);
    
    square_up_back_create(white,square);
    msleep(16);
    
    PID_gyro_drive_create(-200,.1);
    msleep(16);
    
    servo(arm,arm_max+400,3);
    msleep(16);
    
    servo(hand,hand_min,3);
    msleep(16);
    
    thread_start(thread_small);
    msleep(16);
    
    turn_with_gyro_create(100,-90);
    msleep(16);
    
    create_stop();
    msleep(16);
    
    bang();
    msleep(16);
    
    turn_with_gyro_create(300,90);
    msleep(16);
    
    thread_start(arm_bigBlock);
    msleep(16);
    
    square_up_front_create(black,-square);
    msleep(16);
    
    PID_gyro_drive_create(200,.5);
    msleep(16);
    
    thread_start(hand_unstack);
    msleep(16);
    
    square_up_front_create(black,-square);
    msleep(16);
    
     thread_start(hand_unstack);
    msleep(16);
    
    square_up_front_create(black,-square);
    msleep(16);
    
    thread_start(arm_down);
    msleep(16);
    
    turn_with_gyro_create(300,90);
    msleep(16);
    
    thread_start(arm_down);
    msleep(16);
    
    create_drive_direct(-200,-200);
    msleep(500);
    create_stop();
    msleep(16);
    
    PID_gyro_drive_create(300,1.7);
    msleep(16);
    
    turn_with_gyro_create(200,-90);
    msleep(16);
    
    square_up_back_create(white,square);
    msleep(16);
    
    PID_gyro_drive_create(200,.1);
    msleep(16);
    
    servo(arm,arm_max-400,3);
    msleep(16);
    
    servo(hand,hand_min,3);
    msleep(16);

	thread_start(thread_small);
    msleep(16);
    
    turn_with_gyro_create(100,-90);
    msleep(16);
    
    create_stop();
    msleep(16);
    
    bang();
    msleep(16);
    
    turn_with_gyro_create(300,90);
    msleep(16);
    
    square_up_front_create(black,-square);
    msleep(16);
    
    create_drive_direct(-100,0);
    msleep(500);
    
    create_stop();
    msleep(16);
    
    thread_start(arm_bigBlock);
    msleep(16);
    
    create_drive_direct(-200,-200);
    msleep(200);
    
    create_stop();
    msleep(16);
    
    thread_start(arm_bigBlock);
    msleep(16);
    
    square_up_front_create(black,-square);
    msleep(16);

    /////////////////////////////////////////////////thread destroys
    thread_destroy(hand_unstack);
    thread_destroy(arm_down);
    thread_destroy(arm_bigBlock);
    thread_destroy(thread_small);
    create_disconnect();
    return 0;

}