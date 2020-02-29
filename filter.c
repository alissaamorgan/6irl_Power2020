#include <kipr/botball.h>
#include <filter.h>
thread af_zero,af_one,af_two,af_three,af_three,af_four,af_five;

///////////////////////////////////////////////////////////////////////////////////////////////
int filt_distribute=0, filter_delay=10;                                                      //
float filter_out[6];                                                                         //                              
const int a_filter_ports[6]={0,1,1,0,0,0};                                                   //
                                                                                          	 //
void moving_win(){																			 //
    int port = filt_distribute;																 //
    filt_distribute++;																		 //
    int length = 40;																		 //
    if(length < 20){length=20;}																 //
    if(length > 100){length=100;}															 //
    int pos,i;																				 //
    float total,average,win[length];														 //
    while(1){																				 //
        win[pos]=analog(port);																 //
        i=0;																				 //
        total=0;																			 //
        while(i<length){																	 //
            total=total+win[i];																 //
            i++;																			 //
        }																					 //
        average=total/length;																 //
        pos++;																				 //
        if(pos>=length){pos=0;}//reset pos when it reaches length							 //
        filter_out[port]=average;//"return" the average of the total stored data			 //
        msleep(filter_delay);																 //
    }																						 //
}																							 //
void csf_threads(){																			 //
    af_zero=thread_create(moving_win);														 //
    af_one=thread_create(moving_win);														 //
    af_two=thread_create(moving_win);														 //
    af_three=thread_create(moving_win);														 //
    af_four=thread_create(moving_win);														 //
    af_five=thread_create(moving_win);														 //
    if(a_filter_ports[0]){thread_start(af_zero);msleep(50);}else{filt_distribute++;}		 //
    if(a_filter_ports[1]){thread_start(af_one);msleep(50);}else{filt_distribute++;}			 //
    if(a_filter_ports[2]){thread_start(af_two);msleep(50);}else{filt_distribute++;}			 //
    if(a_filter_ports[3]){thread_start(af_three);msleep(50);}else{filt_distribute++;}		 //
    if(a_filter_ports[4]){thread_start(af_four);msleep(50);}else{filt_distribute++;}		 //
    if(a_filter_ports[5]){thread_start(af_five);msleep(50);}else{filt_distribute++;}		 //
}           																				 //
void kf_threads(){																			 //
    if(a_filter_ports[0]){thread_destroy(af_zero);}											 //
    if(a_filter_ports[1]){thread_destroy(af_one);}											 //
    if(a_filter_ports[2]){thread_destroy(af_two);}											 //
    if(a_filter_ports[3]){thread_destroy(af_three);}										 //
    if(a_filter_ports[4]){thread_destroy(af_four);}											 //
    if(a_filter_ports[5]){thread_destroy(af_five);}											 //
}																							 //
///////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int cet,CET_conf[4]={/*time between checks*/100,/*ammount of times to check*/ 3,/*port to use*/1,/*setpoint*/ 500}; //
void cet_thread(){																									//
	cet=-1;																											//
	int i , time=CET_conf[0] , checks=CET_conf[1] , port = CET_conf[2] , setpoint = CET_conf[3];					//
	while(i<checks){																								//
		float in = filter_out[port];																				//
		i++;																										//
		msleep(time);																								//
		if(in<setpoint){																							//
			cet=0;																									//
		}																											//
	}																												//
	if(cet!=0){																										//
		cet=1;																										//
	}																												//
}																													//
																													//
int set_out,SET_conf[3]={/*time between checks*/  500,  /*port*/  1,  /*setpoint*/ 200};							//
																													//
void set_thread(){//green																							//
	int time=SET_conf[0] , port=SET_conf[1] , setpoint = SET_conf[2];												//
    set_out=0;																										//
    float in = filter_out[port];																					//
    while(in>=setpoint){																							//
    	msleep(time);																								//
    }																												//
    set_out=1;																										//
}																													//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//average analog sensor
int buffer(int port)
{
	int i = 0;
	int sum = 0;
	int average;
    while(i < 3)
    {
        i++;
        sum = sum + analog(port);
        msleep(1);
    }
    average = sum/i;
    return average;
}
//sydni was supposed to comment this
