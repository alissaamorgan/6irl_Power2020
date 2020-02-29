#include <kipr/botball.h>
#include <camera.h>
int initialize(){
    camera_open_black();
    int count=0;
    while(count<6){
        camera_update();
        msleep(50);
        count=count+1;
    }
    return 0;
}
int camera_rotate(int channel)
{
    initialize();
    while(1)
    {

        if(get_object_count(channel)>0)
        { printf("%d\n", get_object_center_x(channel,0));

         mav(0,(get_object_center_x(channel,0)-80));
         mav(3,(80-(get_object_center_x(0,0))));
         camera_update();

        }
        msleep(50);

    }

    camera_close();
    return 0;
}
int is_present(int channel)
{

    if(get_object_count(0)>0) {return 1;} 
    else { return 0;}
}

void camera_thread_func()
{
    camera_open_black();
    msleep(500);
    while(1){camera_update();}

}
int where(int channel)
{
return get_object_center_x(channel, 0);
}
