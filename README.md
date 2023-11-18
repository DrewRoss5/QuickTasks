# QuickTasks
A simple CLI ToDo utility made to learn C++

# Installation
Clone this repo, and run the install.sh bash script from the repo, this will complile the source code, and add the ``tasks`` binary to your /usr/bin/ directory.

# Usage
## Commands
### ``tasks help``:
Displays a list of all commands.
### ``tasks view``:
Displays all current tasks, their ID's, and their completion status. Additionally displays what percentage of your tasks are complete (rounded to the nearest percent)<br>
**Example:**<br>
![2023-11-18_10-23_1](https://github.com/DrewRoss5/QuickTasks/assets/145530440/176ce4f8-58de-42be-81dc-5d84136254ea)
### ``tasks new [task_name] [--group= (optional)]``
Creates a new task with a specified name, the tasks group may also be specified
### ``tasks complete [task_id]``:
Marks the tasks with a specified ID complete
### ``tasks delete [task_id]``:
Deletes the task with the specified id
### ``tasks delete-complete``:
Deletes all completed tasks.
