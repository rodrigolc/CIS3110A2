/* main.cpp

    Student: Rodrigo Lopes de Carvalho
    Student ID: 0905095

    Grabs arguments, reads input, and runs scheduler simulation
*/

#include "scheduler.hpp"
#include <cstdio>
#include <cstdlib>

using namespace std;

int handle_args(int argc,char* argv[], Scheduler* scheduler);

int main(int argc, char* argv[]){

    Scheduler* scheduler = new Scheduler();

    if( handle_args(argc,argv,scheduler) == -1){
        printf("wrong argument usage.\n");
        printf("See usage below:\n");
        printf("simcpu [-d] [-v] [-r quantum]\n");

        return (1);
    }


    int number_of_processes;
    int thread_switch;
    int process_switch;

    scanf("%d %d %d",&number_of_processes,&thread_switch,&process_switch);
    scheduler->thread_switch = thread_switch;
    scheduler->process_switch = process_switch;

    for (int i = 0; i < number_of_processes; i++)
    {
        int process_number;
        int number_of_threads;

        scanf("%d %d",&process_number,&number_of_threads);
        Process* process = new Process(process_number);

        for (int j = 0; j < number_of_threads ; j++)
        {
            int thread_number;
            int arrival_time;
            int cpu_bursts;
            scanf("%d %d %d", &thread_number,&arrival_time,&cpu_bursts);

            Thread* thread = new Thread(thread_number);
            thread->arrival_time = arrival_time;
            for (int k = 0; k < cpu_bursts; k++)
            {
                int cpu_time;
                int io_time;
                int aux;
                if(k == (cpu_bursts - 1))
                {
                    scanf("%d %d",&aux,&cpu_time);
                    thread->add_cpu_time(cpu_time);
                }
                else
                {
                    scanf("%d %d %d",&aux,&cpu_time,&io_time);
                    thread->add_cpu_time(cpu_time);
                    thread->add_io_time(io_time);
                }
            }
            process->add_thread(thread);
            scheduler->add_thread(thread);
        }
        scheduler->add_process(process);
    }

    //scheduler is filled
    //TODO
    scheduler->fill_queue();
    scheduler->run();
    scheduler->print_stats();
    // scheduler->clean();

    delete scheduler;

    return 0;
}

int handle_args(int argc,char* argv[], Scheduler* scheduler){
    for(int i = 1; i < argc; i++){ //argv[0] == name of program
        if(strcmp(argv[i],"-d") == 0){
            scheduler->detailed = true;
        }else if(strcmp(argv[i],"-v") == 0){
            scheduler->verbose = true;
        }else if(strcmp(argv[i],"-r") == 0){
            if(argc > (i+1) && atoi(argv[i+1]) > 0){
                scheduler->type = RR;
                scheduler->quantum = atoi(argv[i+1]);
                i++;
            }else{
                return -1; //bad arguments;
            }
        }else {
            return -1; //bad arguments;
        }
    }
    return 0;
}
