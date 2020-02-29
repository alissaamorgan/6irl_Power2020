#include <kipr/botball.h>
#include <math.h>
#include <create_functions.h>
#include <create_comp_lib.h>
#include <alissa.h>
#include <filter.h>
#include <timer.h>

#define right_motor 0
#define left_motor 1
#define target_theta_45 224900
#define target_theta_90 480500 // WORKING ON NUMBERS FOR 3999 // was 500500 //was 512500
#define target_theta_180 986000 // ALL NUMBERS SHOULD BE GOOD
#define target_theta_01 25000
#define target_theta_02 557500
int target_theta_m45 = target_theta_45;
int target_theta_m90 = target_theta_90;
int target_theta_m180 = target_theta_180; 

#define analog_white 300
#define analog_black 3500
#define digital_right 0
#define digital_left 1
#define left_IR 1
#define right_IR 0
#define stop 0
#define cliff 2000

#define hat 0
int turn = 150; // was 110
int square = 175; // was 200
int PID = 150; // was 150
int white = 1;
int black = 2;
int physical = 3;
int black_speed;
double bias = 0.0;
double calibrate_gyro(){
    int i = 0;
    double avg = 0;
    while( i < 50){
        avg += gyro_z();
        msleep(1);
        i++;
        printf("Gyro Z: %d\n",gyro_z());
    }
    bias = avg / 50.0;
    printf("New Bias: %f\n", bias);
    return bias;
}

void turn_with_gyro_create(int speed, int deg){
    double theta = 0;
    int targetTheta;
    switch(deg){
        case 45:
            targetTheta = target_theta_45;
            create_drive_direct(speed,speed*-1);
            break;
        case 90:
            targetTheta = target_theta_90;
            create_drive_direct(speed,speed*-1);
            break;
        case 180:
            targetTheta = target_theta_180;
            create_drive_direct(speed,speed*-1);
            break;
        case -45:
            targetTheta = target_theta_m45;
            create_drive_direct(speed*-1,speed);
            break;
        case -90:
            targetTheta = target_theta_m90;
            create_drive_direct(speed*-1,speed);
            break;
        case -180:
            targetTheta = target_theta_m180;
            create_drive_direct(speed*-1,speed);
            break;
        case 01:
            targetTheta = target_theta_01;
            create_drive_direct(speed,speed*-1);
            break;
        default:
            targetTheta = 0;
            break;
    }  
    while(theta < targetTheta){
        msleep(10);
        theta += abs(gyro_z() - bias) * 10;
        printf("Turn Gyro Z: %d\n",gyro_z());
    }
    create_drive_direct(0,0);
}

void PID_gyro_drive_create(int speed, double time){
    double startTime = seconds();
    double theta = 0;
    while ((seconds() - startTime) < time){
        if (speed > 0){
            create_drive_direct((speed + (speed * theta/100000)),(speed - (speed * theta/100000)));
        }
        else{
            create_drive_direct((speed - (speed * theta/100000)), (speed + (speed * theta/100000)));
        }
        msleep(15);
        theta += (gyro_z() - bias) * 10;  //was gyro_z()
        printf("%f",(seconds() - startTime));
    }
    create_stop();
}

// white = 1 "through"
// black = 2 "stop"
void square_up_front_create(int ending,int speed){
    if(speed > 0 && speed < 600){
        black_speed = 0.5*speed;
    }
    else{black_speed = 0.25*speed;}
    if(ending == 1 || ending == 2){
        while(1){
            if(get_create_lfcliff_amt()>cliff && get_create_rfcliff_amt()>cliff){
                create_drive_direct(speed,speed);
            }
            if(get_create_rfcliff_amt()<cliff){
                create_drive_direct(speed,stop);
            }
            if(get_create_lfcliff_amt()<cliff){
                create_drive_direct(stop,speed);
            }
            if(get_create_lfcliff_amt()<cliff && get_create_rfcliff_amt()<cliff) {
                create_drive_direct(stop,stop);
                break;
            }
        }
    }
    switch(ending){
        case 1:
            {
                while(1){
                    if(get_create_lfcliff_amt()<cliff && get_create_rfcliff_amt()<cliff){
                        create_drive_direct(black_speed,black_speed);
                    }
                    if(get_create_lfcliff_amt()>cliff){
                        create_drive_direct(stop,black_speed);
                    }
                    if(get_create_rfcliff_amt()>cliff){
                        create_drive_direct(black_speed,stop);
                    }
                    if(get_create_lfcliff_amt()>cliff && get_create_rfcliff_amt()>cliff){
                        create_drive_direct(stop,stop);
                        break;
                    }
                }
            }
        case 2:
            {
                while(1){
                    if(get_create_lfcliff_amt()<cliff && get_create_rfcliff_amt()<cliff){
                        create_drive_direct(-1*black_speed,-1*black_speed);
                    }
                    if(get_create_lfcliff_amt()>cliff){
                        create_drive_direct(stop,-1*black_speed);
                    }
                    if(get_create_rfcliff_amt()>cliff){
                        create_drive_direct(-1*black_speed,stop);
                    }
                    if(get_create_lfcliff_amt()>cliff && get_create_rfcliff_amt()>cliff){
                        create_drive_direct(stop,stop);
                        break;
                    }
                }
            }
    }
}

void linefollow_create(double time, int speed, int side){
    if(side == right){
        timer_reset(1);
        while(time_calc(1) < time){
            if(get_create_rfcliff_amt()<cliff){
                create_drive_direct((3*speed)/4,speed);
            }
            if(get_create_rfcliff_amt()>cliff){
                create_drive_direct(speed,(3*speed)/4);
            }
            time_calc(1);
        }
    }
    if(side == left){
        timer_reset(1);
        while(time_calc(1) < time){
            if(get_create_lfcliff_amt()<cliff){
                create_drive_direct(speed,(3*speed)/4); 
            }
            if(get_create_lfcliff_amt()>cliff){
                create_drive_direct((3*speed)/4,speed);
            }
            time_calc(1);
        }
    }
}

void square_up_back_create(int ending,int speed){
    if(speed > 0 && speed < 600){
        black_speed = 0.5*speed;
    }
    else{black_speed = 0.25*speed;}
    if(ending == 1 || ending == 2){
        while(1){
            if(get_create_lcliff_amt()>cliff && get_create_rcliff_amt()>cliff){
                create_drive_direct(speed,speed);
            }
            if(get_create_rcliff_amt()<cliff){
                create_drive_direct(speed,stop);
            }
            if(get_create_lcliff_amt()<cliff){
                create_drive_direct(stop,speed);
            }
            if(get_create_lcliff_amt()<cliff && get_create_rcliff_amt()<cliff) {
                create_drive_direct(stop,stop);
                break;
            }
        }
    }
    switch(ending){
        case 1:
            {
                while(1){
                    if(get_create_lcliff_amt()<cliff && get_create_rcliff_amt()<cliff){
                        create_drive_direct(black_speed,black_speed);
                    }
                    if(get_create_lcliff_amt()>cliff){
                        create_drive_direct(stop,black_speed);
                    }
                    if(get_create_rcliff_amt()>cliff){
                        create_drive_direct(black_speed,stop);
                    }
                    if(get_create_lcliff_amt()>cliff && get_create_rcliff_amt()>cliff){
                        create_drive_direct(stop,stop);
                        break;
                    }
                }
            }
        case 2:
            {
                while(1){
                    if(get_create_lcliff_amt()<cliff && get_create_rcliff_amt()<cliff){
                        create_drive_direct(-1*black_speed,-1*black_speed);
                    }
                    if(get_create_lcliff_amt()>cliff){
                        create_drive_direct(stop,-1*black_speed);
                    }
                    if(get_create_rcliff_amt()>cliff){
                        create_drive_direct(-1*black_speed,stop);
                    }
                    if(get_create_lcliff_amt()>cliff && get_create_rcliff_amt()>cliff){
                        create_drive_direct(stop,stop);
                        break;
                    }
                }

            }
    }
}

void turn_90(){
    double theta = 0;
    int targetTheta = target_theta_90; 

    create_drive_direct(60,60*-1);
    while(theta < targetTheta){
        msleep(10);
        theta += abs(gyro_z() - bias) * 10;
        printf("Turn Gyro Z: %d\n",gyro_z());
    }
    create_drive_direct(0,0);
}

int bump = 100;

void reach_material(){
    while(get_create_lclightbump_amt() < bump || get_create_llightbump_amt() < bump){
        if (get_create_lfcliff_amt() < 1600){
            create_drive_direct(50,100);
        }
        else{
            create_drive_direct(100,50);
        }
        msleep(15);
    }
    while(1){
        if(get_create_lclightbump_amt() > bump){
            create_drive_direct(-11,-11);
        }
        if(get_create_lclightbump_amt() < bump){
            break;
        }
    }
    while(1){
        if(get_create_lclightbump_amt() < bump){
            create_drive_direct(11,11);
        }
        if(get_create_lclightbump_amt() > bump){
            break;
        }
    }
    while(1){
        if(get_create_lclightbump_amt() > bump){
            create_drive_direct(-11,-11);
        }
        if(get_create_lclightbump_amt() < bump){
            break;
        }
    }
    printf("AVG BUMP: %d\n", get_create_lclightbump_amt());
}

void create_line_follow(int dist){
    set_create_distance(0);
    if(dist > 0){
        while (get_create_distance() < dist){
            if(get_create_lfcliff_amt() > 1600){
                create_drive_direct(166,250);
            }
            else{
                create_drive_direct(250,166);
            }
            msleep(15);
        }
    }
    if(dist > 0){
        while (get_create_distance() < dist){
            if(get_create_lfcliff_amt() > 1600){
                create_drive_direct(-250,-166); 
            }
            else{
                create_drive_direct(-166,-250); 
            }
            msleep(15);
        }
    }
}

void create_line_follow_materials(){
    create_full();
    msleep(15);
    while(get_create_lcliff_amt()>cliff && get_create_rcliff_amt()>cliff){
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

void bang(){
    create_drive_direct(250,250);
    while(get_create_lbump()==0 && get_create_rbump()==0){msleep(15);}
    create_stop();
}

void back_til_black(){
    create_drive_direct(-100,-100);
    while(get_create_lfcliff_amt()>cliff){}
    create_stop();
}

void one_wheel_turn(int speed){
    double theta = 0;
    int targetTheta = target_theta_02;
    create_drive_direct(0,speed*-1);
    while(theta < targetTheta){
        msleep(10);
        theta += abs(gyro_z() - bias) * 10;
    }
    create_drive_direct(0,0);
}

void short_pause(){
    create_stop();
    msleep(100);
}

void triple_square(){
    square_up_front_create(white,250);
    PID_gyro_drive_create(-250,0.2);
    one_wheel_turn(500);
    PID_gyro_drive_create(-250,0.2);
    square_up_back_create(white,square);
    short_pause(); short_pause();
    turn_with_gyro_create(250,-90);
    short_pause(); short_pause();
    square_up_back_create(black,250);
}

void straight_distance(double distance, double base_speed)
{
    create_drive_straight(base_speed);
    double mathh = distance/abs(base_speed);
    msleep(mathh*1000);
    create_stop();
    msleep(16);
}


void turn_create(int deg)
{
    int speed = 200;
    switch(deg){
        case 45:
            create_spin_CW(speed);
            msleep(475);
            break;
        case 90:
            create_spin_CW(speed);
            msleep(930);
            break;
        case 180:
            create_spin_CW(speed);
            msleep(1875);
            break;
        case -45:
            create_spin_CCW(speed);
            msleep(475);
            break;
        case -90:
            create_spin_CCW(speed);
            msleep(930);
            break;
        case -180:
            create_spin_CCW(speed);
            msleep(1875);
            break;
    }  
}
void PID_gyro_drive_create_et(int speed, int buff){ //uses a distance sensor to drive straight
    double theta = 0;
    while (buffer(cET)<buff){
        if (speed > 0){
            create_drive_direct((speed + (speed * theta/100000)),(speed - (speed * theta/100000)));
        }
        else{
            create_drive_direct((speed - (speed * theta/100000)), (speed + (speed * theta/100000)));
        }
        if (get_create_lbump()==1 || get_create_rbump()==1){
            PID_gyro_drive_create (-normal,0.6); 
            break;
        }//insurance
        msleep(12);
        theta += (gyro_z() - bias) * 10;  //was gyro_z()
    }
    create_stop();
}