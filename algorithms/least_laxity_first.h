


void init_task(task_t *t, unsigned int WCET, unsigned int period, int deadline);
void init_tasks(task_t t[], unsigned int WCET[], unsigned int period[], int deadline[], unsigned int numTasks);
void copy_tasks(task_t tasks_to_be_copied[], task_t place_to_copy[], unsigned int numTasks);
void print_task(task_t t);
void print_tasks(task_t t[], unsigned int numTasks);
float utilization(task_t t[], unsigned int numTasks);
unsigned int llf(task_t t[], unsigned int numTasks);
void sim_schedule(task_t t[], unsigned int numTasks, unsigned int schedule[], unsigned int schedule_length, sched_algo_t algo);
void print_schedule(unsigned int schedule[], unsigned int length);
//void print_missed(unsigned int schedule[], unsigned int length);
