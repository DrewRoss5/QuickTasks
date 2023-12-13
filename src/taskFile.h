#ifndef TASKFILE_H
#define TASKFILE_H

#include <string>
#include <format>
#include <vector>


#include "task.h"

class TaskFile{
    private:
        std::string filePath_;
        std::vector<Task*> taskList_;
       
    public:
        TaskFile(std::string path){ filePath_ = path}
        void createTask(std::string taskName, std::string taskGroup);
        void removeTask(int taskIndex);
        void removeComplete();
        void completeTask(int taskIndex);
        void listTasks();
        void read();
        void write();
        void releaseMemory();
       
        // getter functions
        int getTaskCount(){ return taskList_.size();}
};

#endif
