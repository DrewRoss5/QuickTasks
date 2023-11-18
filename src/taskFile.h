#include <string>
#include <format>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include "task.h"

class TaskFile{
    private:
        std::string filePath;
        std::vector<Task*> taskList;
    public:
        TaskFile(std::string path){
            filePath = path;
        }
        // creates a new task and adds it to the task list
        void createTask(std::string taskName, std::string taskGroup){
            Task* newTask = new Task(taskName, taskGroup);
            taskList.push_back(newTask);
        }
        // deletes a task given its index
        void removeTask(int taskIndex){
            taskList.erase(taskList.begin()+taskIndex);
        }
        // removes every complete task
        void removeComplete(){
            std::vector<Task*> newTasks;
            int initSize = taskList.size();
            for (int i = 0; i < initSize; i++){
                if (!(taskList[i]->getComplete())){
                    newTasks.push_back(taskList[i]);
                }
            }
            taskList = newTasks;
        }
        // marks a task complete given its index
        void completeTask(int taskIndex){
            taskList[taskIndex]->markComplete();
        }
        // prints each task's name, completion status, and group if applicable
        void listTasks(){
            Task* task;
            std::string completeChar;
            std::string groupName;
            std::vector<int>::size_type size = taskList.size();
            // ensure that the task list has been initalized
            if(size > 0){
                int completeCount = 0;
                std::cout << "Tasks:\n";
                // display each task, and increment the count of complete tasks
                for (int i = 0; i < size; i++){
                    task = taskList[i]; 
                    if (task->getComplete()){
                        completeCount += 1;
                        completeChar =  "✔";
                    }
                    else{
                        completeChar = "✖";
                    }
                    groupName = task->getGroup();
                    std::string groupString = (groupName != "") ?  std::format("\n\t\tGroup: {}", task->getGroup()) : "";
                    std::cout << std::format("\t{}:  {} {}{}\n", i, task->getName(), completeChar, groupString);
                }
                // calculate and display the percentage of completed tasks to the nearest whole percent
                int completePercent = std::ceil(completeCount * 100 /taskList.size());
                std::cout << completePercent << "% of your tasks are complete" << std::endl;
            }
            else{
                std::cout << "There's nothing on your ToDo list." << std::endl;
            }
        }
        // loads tasks from the task file
        void read(){
            std::string strBuffer; // a buffer to store each task string
            Task* taskBuffer; // a buffer to store each task
            std::ifstream fileStream(filePath);
            if (fileStream.good()){
                while (std::getline(fileStream, strBuffer)){
                    taskBuffer = taskBuffer->fromString(strBuffer);
                    taskList.push_back(taskBuffer);
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
        void write(){
            // concatinate all task strings to a single string, and delete each tasks's pointer
            std::string saveString;
            for (Task* task : taskList){
                saveString += task->toString()+"\n";
                delete(task);
            }
            std::ofstream fileStream;
            fileStream.open(filePath);
            // the final character isn't written here because it creates an empty newline
            fileStream << saveString.substr(0, saveString.length()-1);
            fileStream.close();
        }
        // deletes all of the task pointers freeing all of the associated memory
        void releaseMemory(){
            for (Task* task : taskList){
                delete(task);
            }
        }
        // getter functions
        int getTaskCount(){
            return taskList.size();
        }
};
