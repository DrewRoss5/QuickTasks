#include <iostream>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

#include "taskFile.h"




void showHelp(){
    std::cout << "This should show the help dialog.";
}

int main(int argc, char* argv[]){
    // get the user's home directory
    struct passwd* pw = getpwuid(getuid());
    const std::string homeDir = getpwuid(getuid())->pw_dir;
    // initalize the task file
    TaskFile taskFile(homeDir + "/.quicktasks/tasks.todo");
    taskFile.read();
    // parse arguments
    if (argc < 2){
        std::cout << "Please provide at least one argument" << std::endl;
    }
    return 0;
}
