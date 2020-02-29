;//originally 200
thread servos_thread;
int above_yellow;
int clear_bridge;
int clear_swings;
int grab_yellow;
int yellow_above_pvc;
int yellow_place;
int under_bridge;
int open_claw;
int open_yellow;
int semi_open_yellow;
int close_yellow;
int cET_buff;
int servo_shave;

int alissa();

int out_of_box();
void create_line_follow_bang();
int get_to_yellow();
int get_to_one();
int take_yellow();
int yellow_one();
int get_to_two();
int yellow_two();
int get_to_three();
int yellow_three();
double correction;
void first_servos();
int adjust_cube();
void start_shave(int option);
void kill_shave();
void servo_shave_func();
