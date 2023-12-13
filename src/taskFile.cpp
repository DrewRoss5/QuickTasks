#include <iostream>
#include <fstream>
#include <cmath>
#include <format>
#include "task.h"
#include "taskFile.h"

 // creates a new task and adds it to the task list
void TaskFile::createTask(std::string taskName, std::string taskGroup){
    Task* newTask = new Task(taskName, taskGroup);
    taskList_.push_back(newTask);
}

// deletes a task given its index
void TaskFile::removeTask(int taskIndex){
    taskList_.erase(taskList_.begin()+taskIndex);
}

// removes every complete task
void TaskFile::removeComplete(){
    std::vector<Task*> newTasks;
    int initSize = taskList_.size();
    for (int i = 0; i < initSize; i++){
        if (!(taskList_[i]->getComplete())){
            newTasks.push_back(taskList_[i]);
        }
    }
    taskList_ = newTasks;
}

// marks a task complete given its index
void TaskFile::completeTask(int taskIndex){
    taskList_[taskIndex]->markComplete();
}

// prints each task's name, completion status, and group if applicable
void TaskFile::listTasks(){
    Task* task;
    std::string completeChar;
    std::string groupName;
    std::vector<int>::size_type size = taskList_.size();
    // ensure that the task list has been initalized
    if(size > 0){
        int completeCount = 0;
        std::cout << "Tasks:\n";
        // display each task, and increment the count of complete tasks
        for (int i = 0; i < size; i++){
            task = taskList_[i]; 
            if (task->getComplete()){
                completeCount += 1;
                completeChar =  "✔";
            }
            else{
                completeChar = "✖";
            }
            groupName = task->getGroup();
            std::string groupString = (groupName != "") ?  std::format("\n\t\tGroup: {}", task->getGroup()) : "";
            std::cout << std::format("\t{}:  {} {}{}\n", i+1, task->getName(), completeChar, groupString);
        }
        // calculate and display the percentage of completed tasks to the nearest whole percent
        int completePercent = std::ceil(completeCount * 100 /taskList_.size());
        std::cout << completePercent << "% of your tasks are complete" << std::endl;
    }
    else{
        std::cout << "There's nothing on your ToDo list." << std::endl;
    }
}

// loads tasks from the task file
void TaskFile::read(){
    std::string strBuffer; // a buffer to store each task string
    Task* taskBuffer; // a buffer to store each task
    std::ifstream fileStream(filePath_);
    if (fileStream.good()){
        while (std::getline(fileStream, strBuffer)){
            taskBuffer = taskBuffer->fromString(strBuffer);
            taskList_.push_back(taskBuffer);
        }
    }
    else{
        std::cout << "The task file could not be found!\nA new one has been created." << std::endl;
        // this is a hacky way to create a new task file 
        write();
    }
    fileStream.close();
}

// saves all of the tasks askList[i][i]to the task file, because this is only called before the program closes, it also deletes each task pointer to avoid memory leaks
void TaskFile::write(){
    // concatinate all task strings to a single string, and delete each tasks's pointer
    std::string saveString;
    for (Task* task : taskList_){
        saveString += task->toString()+"\n";
        delete(task);
    }
    std::ofstream fileStream;
    fileStream.open(filePath_);
    // the final character isn't written here because it creates an empty newline
    fileStream << saveString.substr(0, saveString.length()-1);
    fileStream.close();
}

// deletes all of the task pointers freeing all of the associated memory
void TaskFile::releaseMemory(){
    for (Task* task : taskList_){
        delete(task);
    }
}