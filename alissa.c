#include <Tyler.h>
#include <kipr/botball.h>
#include <math.h>
#include <create_functions.h>
#include <create_comp_lib.h>
#include <alissa.h>
#include <camera.h>
#include <filter.h>
#include <ross.h>
int above_yellow = arm_min + 800;
int clear_bridge = arm_min;
int clear_swings = arm_min + 450;
int grab_yellow = arm_min + 1140;
int yellow_above_pvc = arm_min + 200;
int yellow_place = arm_min + 1200;
int under_bridge = arm_min + 1500;
int open_claw = closed + 1150;
int open_yellow = closed + 1050;
int semi_open_yellow = closed + 600;
int close_yellow = closed + 25;
int cET_buff = 1800;
int servo_shave=0;
double correction = 0.66667;

int alissa()
{
    create_connect();
    calibrate_gyro();
    adjust_cube();
    /*servo (hand, close_yellow, 3);
    start_position();//create_functions.c
    //wait_for_light(port);
    out_of_box();
    ///////////////////////////////////////////
    thread servos_thread;//creation and execution of servo thread for squaring up first yellow block
    servos_thread = thread_create(servo_shave_func);// case 0
    start_shave(0);
    ///////////////////////////////////////////
    get_to_yellow();
    get_to_one();
    //kill_shave();//kill case to avoid servo failure
    take_yellow();
    yellow_one();
    get_to_yellow();
    get_to_two();
    take_yellow();
    yellow_two();
    get_to_yellow();
	get_to_three();
    take_yellow();
    yellow_three();*/
    create_disconnect();
    return 0;
}




int out_of_box(){
    //notes
    //base postition = 150 
    create_drive_direct(400,400);
    msleep (40);
    square_up_back_create(black,square+50);
    create_drive_direct(100,100);
    msleep (50);
    square_up_back_create(white,square);
    return 0;
}
void create_line_follow_bang(){
    create_drive_direct(250,250);
    msleep(15);
    while(get_create_lbump()==0 && get_create_rbump()==0){
        if(get_create_lfcliff_amt() < 1600){
            create_drive_direct(166,250);
        }
        else{
            create_drive_direct(250,166);
        }
        msleep(15);
    }
    create_safe();
    msleep(15);
}
int get_to_yellow(){
    create_stop();
    msleep(55);
    PID_gyro_drive_create(normal,(1*correction)); //runs towards cubes //1.3 //original=(200,1)
    turn_with_gyro_create(250, -90); 
    create_drive_direct(-300,-300);  //physical square up  
    msleep(800);
    create_stop();
    msleep(15);
    return 0;
}
int get_to_one(){
    PID_gyro_drive_create(normal, .4*correction); //distance until yellow 1
    start_shave(1);
    turn_with_gyro_create(250, 90);  // infront of yellow 1
    create_stop();
    msleep(100);
    kill_shave();
    return 0;
}
int take_yellow(){
    create_stop();
    msleep(300);
    bang();
    PID_gyro_drive_create (-normal,0.6);
    start_shave(3);
    msleep(2700);
    kill_shave();
    return 0;
}
int yellow_one(){
    adjust_cube();
    
    turn_with_gyro_create(200, 180);  // deliever one
    PID_gyro_drive_create(-1*normal, 0.95*correction);
    kill_shave();
    square_up_back_create(black,square); //on box line
    PID_gyro_drive_create(normal, 0.1*correction); 
    start_shave(6);
    create_drive_direct(-200,200); // -250, 200
    msleep (95);					//225
    create_stop();
    msleep(1150);
    create_drive_direct(-200,-300); 
    msleep(700); 
    square_up_back_create(black, square+50); 
    turn_with_gyro_create(200, 180);  
    square_up_back_create(black, -square-50); 
    kill_shave();
    return 0;
}

int get_to_two(){
    start_shave(5);
    PID_gyro_drive_create(normal, 2*correction); //2.2
    kill_shave();
    start_shave(1);
    turn_with_gyro_create(250, 90);// infront of yellow 2
    create_stop();
    msleep(100);
    kill_shave();
    return 0;
}

int yellow_two(){
    adjust_cube();
    
    turn_with_gyro_create(250, 90);   
    bang();
    //PID_gyro_drive_create(normal, 2.2);
    turn_with_gyro_create(250, 180);
    PID_gyro_drive_create(-normal, 0.8);
    PID_gyro_drive_create(normal, 0.3);
    turn_with_gyro_create(200, -90);
    PID_gyro_drive_create(-normal, 1);
    square_up_back_create(black,square); //square up on box line facing inside of box 
    
    /*turn_with_gyro_create(250, -90);   // deliever two
    PID_gyro_drive_create(-1*normal, 2.5);
    PID_gyro_drive_create(normal, 0.3);
    turn_with_gyro_create(200, -90);
    PID_gyro_drive_create(-normal, 1);
    square_up_back_create(black,square); //square up on box line facing inside of box */
    
   	PID_gyro_drive_create(-normal, 0.5); 
    start_shave(6);
    create_drive_direct(-200,200); // -250, 200
    msleep (100);					//225
    create_stop();
    msleep(1100);
    create_drive_direct(-200,-300); 
    msleep(700); 
    square_up_back_create(black, square+50); 
    turn_with_gyro_create(200, 180);  
    square_up_back_create(black, -square-50); 
    kill_shave();
    PID_gyro_drive_create(-normal, 0.5);
    square_up_back_create(black, square+50);
    return 0;
}
int get_to_three(){
    start_shave(5);
    PID_gyro_drive_create(300, 2.2);
    kill_shave();
    start_shave(1);
    turn_with_gyro_create(200, 90);// infront of yellow 1
    create_stop();
    //square_up_back_create(black,-square-50);
    msleep(200);
    kill_shave();
    
    return 0;
}
int yellow_three(){
	adjust_cube();
    
    turn_with_gyro_create(250, 90);   
    bang();
    //PID_gyro_drive_create(normal, 2.2);
    turn_with_gyro_create(250, 180);
    PID_gyro_drive_create(-normal, 0.8);
    PID_gyro_drive_create(normal, 0.7);
    turn_with_gyro_create(200, -90);
    PID_gyro_drive_create(-normal, 0.8);
    square_up_back_create(black,square); //square up on box line facing inside of box 
    
    start_shave(6);				
    create_stop();
    msleep(1600);
    kill_shave();
    start_shave(2);
    create_stop();
    msleep(1000);
    create_drive_direct(300,-300); 
    msleep(200); 
    create_stop();
    msleep(1000);
    create_drive_direct(-300,300); 
    msleep(300);  
    PID_gyro_drive_create(-normal, 0.8);
    kill_shave();
    square_up_back_create(black,square); //square up on box line facing inside of box 
    return 0;
}
int adjust_cube(){
    start_shave(4);
    square_up_back_create(black,-square-50); //square up on middle line facing cubes
    create_stop();
    msleep (1000);
    kill_shave();
    start_shave(7);
    PID_gyro_drive_create_et(normal, 230);
    //PID_gyro_drive_create(normal, 0.1); //adjust block in claw
    msleep (2100);
    kill_shave();
    return 0;
}
void start_shave(int option){
    servo_shave=option;
    servos_thread = thread_create(servo_shave_func);
    thread_start(servos_thread);
}
void kill_shave(){
    thread_destroy(servos_thread);
}
void servo_shave_func(){
    switch(servo_shave){
        case 0:
            servo (arm, clear_swings, 3);    
            servo (hand, open_yellow, 3);
            servo (base,base_front, 3);
            break;
        case 1:
            servo (arm, clear_swings, 7);
            servo (hand, close_yellow, 5); //thread the needle
            break;
        case 2:
            servo (arm, above_yellow, 3);
            servo (hand, close_yellow, 2); // smooshing blocks in scoring zone
            servo (arm, under_bridge + 250, 3);
            servo (arm, above_yellow, 2);
            break;
        case 3:
            servo (hand, open_yellow, 4);
            servo (arm, grab_yellow, 4);            
    		servo (hand, close_yellow, 4);   //grabing a block
    		servo (arm, yellow_above_pvc, 3);
            break;
        case 4:
            servo (arm, yellow_place, 2);
    		servo(hand, open_yellow, 5); //adjust block in claw
            
   			/*servo (arm, under_bridge + 250, 5);
    		servo (hand, close_yellow, 2);
            msleep(35);
    		servo (arm, clear_swings, 5);*/
            break;
        case 5:
            servo (arm, clear_bridge, 7);
            servo (hand, open_claw, 7);
            break;
        case 6:
            servo (arm, yellow_place, 4);
            servo (hand, open_yellow, 2); //place block in zone
            servo (arm, clear_swings, 3);
            break;
        case 7:
            servo (arm, under_bridge + 250, 5);
    		servo (hand, close_yellow, 2);
            msleep(35);
    		servo (arm, clear_swings, 5);
            break;
        default:
            printf("alissa.c/servo_shave_func: ERROR CASE UNDEFINED");
    }
    //servo_shave = servo_shave +1;
}