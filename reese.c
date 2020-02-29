#include <math.h>
#include <reese.h>

int arm_hold=1000;
int arm_grab=1200;
int base_out=1400;
int block_grab=450;
int block_no=800;

int turn_theta=0.2;
///////////////////////////////////
int reese(){
  
    reese_start();
    if(0){
        turn_with_gyro_create(200,-45);
        square_up_front_create(1,-150);
        PID_gyro_drive_create(-120,1.5);
        return 0;
    }

    square_up_front_create(1,200);
    PID_gyro_drive_create(200,0.6);
    //create_spin_CCW(500); = 90
    create_spin_CCW(70);
    msleep(400);
    create_stop();
    servo(arm,arm_hold+100,3);
    servo(hand,block_no,3);
    servo(arm,arm_hold-500,3);
    create_spin_CW(100);
    servo(hand,closed,3);
    create_stop();
    servo(arm,arm_grab,3);
    create_spin_CCW(110);
    msleep(400);
    create_stop();
    reese_end();
    return 0;
}
///////////////////////////////////

//////////////////////////////////
int reese_start(){				//
    create_connect();			//
    calibrate_gyro();			//
    servo(arm,arm_hold-750,3);
    msleep(200);
    servo(base,base_out,3);
    servo(hand,block_grab,3);
    return 0;					//
}								//
int reese_end(){				//
    							//
    create_disconnect();		//
    return 0;					//
}								//
//////////////////////////////////

int reese_turn(int target_angle,int speed){
    //create_drive_direct
    double current_angle=0,turn_power=0;
    while(current_angle<target_angle){
        current_angle+=gyro_z()*turn_theta;
        printf("%f\n",current_angle);
        
        turn_power=current_angle/(target_angle*1.0000);
        
        turn_power=1-turn_power; // invert
        
        create_drive_direct(speed*turn_power, -speed*turn_power);
        msleep(15);
    }
	while(current_angle>target_angle){
        current_angle+=gyro_z()*turn_theta;
        turn_power=current_angle/(target_angle*1.0000);
        if(target_angle>0){
            turn_power=-1-turn_power;
        }
        create_drive_direct(speed*turn_power, -speed*turn_power);
    }
    create_stop();
    return 0;
}