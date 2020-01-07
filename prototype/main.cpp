#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctime>

void count(int counter_max) {
    for (int i = 0; i < counter_max; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    srand(time(NULL));

    //waitpid()
    int* statusPtr = new int;
    pid_t in_pid;
    std::cout << "Input PID: ";
    std::cin >> in_pid;

    pid_t return_pid = waitpid(in_pid, statusPtr, 0);
    std::cout << "Did the process terminate normally?: " << WIFEXITED(*statusPtr) << std::endl;
    std::cout << "Terminated process pid: " << return_pid << std::endl << std::endl;

    //fork()
    pid_t newProcess = fork();
    int count_max = rand() % 10 + 1; // to ensure child and parent get different rand() results
    waitpid(newProcess, statusPtr, 0); //make sure child exits first
    if (newProcess == 0) { //child process
        std::cout << "Entered child process" << std::endl;
        count(count_max);
        return 0;
    }
    count(rand() % 10 + 1); //parent process

    //execvp
    const char* args[] = {"./test", NULL};
    execvp(args[0], (char* const*)args); //(char* const*) hotfix for type conflict between C and C++
    return 0;
}