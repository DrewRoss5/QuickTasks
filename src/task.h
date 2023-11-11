#include <format>
#include <string>


class Task{
    private: 
        std::string name;
        std::string group;
        bool complete;
    public:
        // primary constructor
        Task(std::string _name, std::string _group){
            name = _name;
            group = _group;
            complete = false;
        }

        // construct the task from the string
        static Task* fromString(std::string str){
            std::string taskName;
            std::string taskGroup;
            bool complete = ( str[0] == (char) *"1") ? true : false;
            int delimPos = str.find('@'); // the location of the @ delimeter for task groups
            if(delimPos > 0){
                // parse the task's name and group based on the @ delimeter
                taskName = str.substr(1, delimPos-1);
                taskGroup = str.substr(delimPos+1, str.length()-1);
            }
            else{
                taskName = str.substr(1, str.length()-1);
            }
            Task* task = new Task(taskName, taskGroup);
            return task;
        }

        // converts the task into a string to be saved into the ToDo file
        std::string toString(){
            std::string groupStr = (group != "") ? std::format("@{}", group) : "";
            return std::format("{}{}{}", (int) complete, name, groupStr);
        }
        // setter functions
        void markComplete(){
            complete = true;
        }
        void setGroup(std::string newGroup){
            group = newGroup;
        }
        // getter functions
        std::string getName(){
            return name;
        }
        std::string getGroup(){
            return group;
        }
        bool getComplete(){
            return complete;
        }
};