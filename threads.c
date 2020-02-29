#include <kipr/botball.h>
#include <create_functions.h>
#include <create_comp_lib.h>
#include <threads.h>
#include <trey.h>
#include <ross.h>

void thread_green_up(){
    msleep(300);
    servo(arm,arm_min,2);
}

void thread_four_down(){
    msleep(1000);
    servo(arm,chain_arm,3);
}

void thread_red_up(){
    //msleep(250);
    servo(arm,arm_min,4);
}

void thread_four_close(){
    servo(hand,chain_grab,3);
}

void thread_small_1(){
    servo(arm,arm_min,3);
}

void thread_arm_bigBlock(){
    servo(arm,830,3);
}
void thread_arm_down(){
    servo(arm,low_cubes-100,3);   
}
void thread_hand_open(){
    servo(hand,unstack_hand,3);
}