#include <string>
#include <format>
#include "task.h"

// primary constructor
Task::Task(std::string name, std::string group){
    name_ = name;
    group_ = group;
    complete_ = false;
}

// construct the task from the string
Task* Task::fromString(std::string str){
    std::string taskName;
    std::string taskGroup;
    bool complete_ = (str[0] == (char) *"1") ? true : false;
    int delimPos = str.find('@'); // the location of the @ delimeter for task groups
    if(delimPos > 0){
        // parse the task's name_ and group_ based on the @ delimeter
        taskName = str.substr(1, delimPos-1);
        taskGroup = str.substr(delimPos+1, str.length()-1);
    }
    else{
        taskName = str.substr(1, str.length()-1);
    }
    Task* task = new Task(taskName, taskGroup);
    if (complete_){
        task->markComplete();
    }
    return task;
}

// converts the task into a string to be saved into the ToDo file
std::string Task::toString(){
    std::string groupStr = (group_ != "") ? std::format("@{}", group_) : "";
    return std::format("{}{}{}", (int) complete_, name_, groupStr);
}