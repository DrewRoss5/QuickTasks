mkdir ~/.quicktasks
touch ~/.quicktasks/tasks.todo
echo "Installing..."
if ! command -v g++ &> /dev/null; then
    echo "Installation failed!\nPlease install g++ to install this program"
    exit 1
fi
sudo g++ -std=c++20 src/main.cpp src/task.h src/taskFile.h -o /usr/bin/tasks
if test -f /usr/bin/tasks; then
    echo "Installation complete"
else 
    echo "Installation failed"
fi
