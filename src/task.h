#ifndef TASK_H
#define TASK_H

#include <format>
#include <string>

class Task{
    private: 
        std::string name_;
        std::string group_;
        bool complete_;
    
    public:
        Task(std::string name, std::string group);
        static Task* fromString(std::string str);
        std::string toString();
        void markComplete();
        void setGroup(std::string newGroup);
        // setter functions
        void markComplete(){complete_ = true;}
        void setGroup(std::string newGroup){group_ = newGroup;}
        // getter functions
        std::string getName(){return name_;}
        std::string getGroup(){return group_;}
        bool getComplete(){return complete_;}
};

#endif
