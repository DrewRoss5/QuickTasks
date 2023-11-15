#include <iostream>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#include <vector>
#include <map>
#include <format>
#include <functional>

#include "taskFile.h"

enum TaskOpperations {complete, erase};

// takes a reference to a map of parameters and their values, and updates if
int parseArgs(char* argv[], int argc, int startPos, std::map<std::string, std::string> &argMap){
    int assignPos;
    std::string argument;
    std::string value;
    std::string arg;
    for (int i = startPos; i < argc; i++){
        arg = argv[i];
        assignPos = arg.find("=");
        if (assignPos > 0){
            // seperate the argument from the value
            argument = arg.substr(0, assignPos);
            value = arg.substr(assignPos+1, arg.length()-1);
            // validate the argument
            if (argMap.find(argument) == argMap.end()){
                std::cout << "Unrecognized parameter \"" << argument << "\"" << std::endl;
                return 1;
            }
            // append the name of the argument and it's value to the map
            argMap[argument] = value; 
            return 0;
        }
        else{
            std::cout << "The parameter " << arg << " has no value";
            return 1;
        }
    }
    return 0;
}

// takes a task id, the taskFile, and an opperation, validates the task ID, and runs the opperation if it is valid
void callTaskOpperation(int argc, char* argv[], TaskFile &taskFile, int opperation){
    if (argc == 3){
        // valdiate the provided task ID, and convert it to an interger
        int taskIndex;
        try{
            taskIndex = std::stoi(argv[2]);
            if (taskIndex >= taskFile.getTaskCount()){
                std::cout << "There is no task with the ID " << taskIndex << std::endl;
                taskFile.releaseMemory();
                return;
            }
            // run the opperation
            switch(opperation){
                case TaskOpperations::complete:
                    taskFile.completeTask(taskIndex-1);
                    std::cout << "Task has been succesfully marked complete" << std::endl;
                    break;
                case TaskOpperations::erase:
                    taskFile.removeTask(taskIndex-1);
                    break;
            }
            taskFile.write();
        }
        catch (...){
            std::cout << "Invalid Task ID" << std::endl;
            taskFile.releaseMemory();
        }
    }
    else{
        std::cout << "Opperation takes exactly one argument" << std::endl;
    }
}

// display a help dialog
void showHelp(){
    std::cout << "usage: task <command>:";
    std::string entries[] = {
                            "tasks view: displays the current tasks, their names, and if they're complete or not.",
                            "tasks new [task name] [(optionalg) --groupname=]: creates a new task of a specified name. A group may be specifed as well.",
                            "tasks complete [task ID]: marks the task with a given ID complete.",
                            "tasks delete [task ID]: deletes the tasks with a given ID",
                            "tasks delete-complete: deletes all completed tasks from the list",
    };
    for (int i = 0; i < (sizeof(entries) / sizeof(std::string)); i++){
        std::cout << "\n\t" << entries[i];
    }
    std::cout << std::endl;
   
}

int main(int argc, char* argv[]){
    // get the user's home directory
    struct passwd* pw = getpwuid(getuid());
    const std::string homeDir = getpwuid(getuid())->pw_dir;
    // initalize the task std::map<std::string, std::string> args = parseArgs(argv)file
    TaskFile taskFile(homeDir + "/.quicktasks/tasks.todo");
    taskFile.read();
    // determine the user's action
    if (argc < 2){
        std::cout << "Please provide at least one argument or run tasks help for a list of available commands" << std::endl;
        return 0;
    }
    std::string command = argv[1];
    std::map<std::string, std::string> args;
    // run the user's action 
    if (command == "help"){
        showHelp();
    }
    else if (command == "view"){
        taskFile.listTasks();
    }
    else if (command == "new"){
        if (argc >= 3){
            std::map<std::string, std::string> args;
            args["--group"] = "";
            if (parseArgs(argv, argc, 3, args) == 0){
                taskFile.createTask(argv[2], args["--group"]);
                taskFile.write();
                std::cout << "The task " << argv[2] << " was created succesfully" << std::endl;
            }
            else{
                taskFile.releaseMemory();
            }
        }
        else{
            std::cout << "Please provide the name of the task to be created" << std::endl;
        }
       
    }
    else if (command == "complete"){
        callTaskOpperation(argc, argv, taskFile, TaskOpperations::complete);
    }
    else if (command == "delete"){
       callTaskOpperation(argc, argv, taskFile, TaskOpperations::erase);
    }
    else if (command == "delete-complete"){
        taskFile.removeComplete();
        taskFile.write();
        std::cout << "All completed tasks have been deleted." << std::endl;
    }
    else{
        std::cout << "Unrecognized command \"" << argv[1] << "\"\nFor a list of available commands, please run tasks help" << std::endl;
    }
    return 0;
}
