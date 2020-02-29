#include <kipr/botball.h>

int base = 0;   // Replace variables to match your robot.
//int dozer = 1;  // Else define at top of library.
int arm = 2;
int hand = 3;
void servo(int port, int position, int speed){   // Recommend "speed" to be 1-3. Would not advise higher than 4.
    enable_servo(port);
    int current = get_servo_position(port);
    if(position > 2047){position = 2047;} if(position < 0){position = 0;}   // Fail-safe in case of user error.
    while(current <= position-speed || current >= position+speed){   // Value of "speed" alters servo speed and margin of error.
        if(current < position){
            current += speed;
            set_servo_position(port, current);
            msleep(2);
        }
        if(current > position){
            current -= speed;
            set_servo_position(port, current);
            msleep(2);
        }
    }
    set_servo_position(port,position);
    disable_servo(port);
}
