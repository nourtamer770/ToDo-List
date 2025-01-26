#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

struct Task {
    string title;
    string details;
    char priority = ' ';
    bool isDone = false;
    Date taskdate = {};
};

struct User {
    string username;
    string password;
    Task tasks[100];
    int taskCount = 0;
};

User allUsers[100];
int userCount = 0;
int currentUser = -1;

void readUserTasks(User& user) {
    ifstream userFile(user.username + ".txt");
    if (!userFile.is_open()) {
        cout << "Error opening file for reading tasks: " << user.username << ".txt" << endl;
        return;
    }
    userFile >> user.taskCount;
    userFile.ignore(); // consume the newline character
    for (int i = 0; i < user.taskCount; i++) {
        getline(userFile, user.tasks[i].title);
        getline(userFile, user.tasks[i].details);
        userFile >> user.tasks[i].taskdate.day >> user.tasks[i].taskdate.month >> user.tasks[i].taskdate.year;
        userFile >> user.tasks[i].priority;
        userFile >> user.tasks[i].isDone;
        userFile.ignore(); // consume the newline character
    }
    userFile.close(); // close the file after reading
}

void writeUserTasks(User& user) {
    ofstream userFile(user.username + ".txt");
    if (!userFile.is_open()) {
        cout << "Error opening file for writing tasks: " << user.username << ".txt" << endl;
        return;
    }
    userFile << user.taskCount << endl;
    for (int i = 0; i < user.taskCount; i++) {
        userFile << user.tasks[i].title << endl;
        userFile << user.tasks[i].details << endl;
        userFile << user.tasks[i].taskdate.day << " " << user.tasks[i].taskdate.month << " " << user.tasks[i].taskdate.year << endl;
        userFile << user.tasks[i].priority << endl;
        userFile << user.tasks[i].isDone << endl;
    }
    userFile.close(); // close the file after writing
}

void readAllUsers() {
    ifstream users("users.txt");
    if (!users.is_open()) {
        cout << "Error opening file for reading users: users.txt" << endl;
        return;
    }
    users >> userCount;
    users.ignore(); // consume the newline character
    for (int i = 0; i < userCount; i++) {
        getline(users, allUsers[i].username);
        getline(users, allUsers[i].password);
        readUserTasks(allUsers[i]); // Read tasks for each user
    }
    users.close(); // close the file after reading
}

void writeAllUsers() {
    ofstream users("users.txt");
    if (!users.is_open()) {
        cout << "Error opening file for writing users: users.txt" << endl;
        return;
    }
    users << userCount << endl;
    for (int i = 0; i < userCount; i++) {
        users << allUsers[i].username << endl
            << allUsers[i].password << endl;
        writeUserTasks(allUsers[i]); // Write tasks for each user
    }
    users.close(); // close the file after writing
}

Date getDate();
void first_menu();
void login();
void Resister();
int Exit();
void Menu();
void addTask(Task tasks[], int& taskCount);
void editTask(Task tasks[], int taskCount);
void deletetask(Task tasks[], int& task_count);
void displayTasks(Task tasks[], int taskcount);
void TasksDoneToday(Task tasks[], bool duetoday[], int taskCount);
void OverdueTasks(Task tasks[], bool overdue[], int taskCount);
void displayOverdueTasks(Task tasks[], bool overdue[], int taskCount);
void TasksDoneToday(Task tasks[], bool duetoday[], int taskCount);
void displayTasksDoneToday(Task tasks[], bool duetoday[], int taskCount);
void searchForTask(Task tasks[], int taskCount);
void markTasksAsDone(Task tasks[], int taskCount);
void displayDoneTasks(Task tasks[], int taskcount);
void changePassword();

int main() {
    readAllUsers();
    first_menu();
    return 0;
}

Date getDate() {
    Date currentDate = {};
    time_t currentTime = time(0);
    tm date = {};
    localtime_s(&date, &currentTime);
    currentDate.year = date.tm_year + 1900;
    currentDate.day = date.tm_mday;
    currentDate.month = date.tm_mon + 1;
    return currentDate;
}


void first_menu() {
    int choice;

    cout << "\t _____________________________________ \n\n";
    cout << "\t|      WELCOME TO THE TO-DO LIST      |\n\n";
    cout << "\t|________________ MENU _______________|\n\n";
    cout << "\t|                                     |\n";
    cout << "\t|       Press 1 to Login              |\n";
    cout << "\t|       Press 2 to Register           |\n";
    cout << "\t|       Press 3 to Exit               |\n";
    cout << "\t|_____________________________________|\n\n";

    cout << "\nPlease enter your choice: ";
    cin >> choice;
    if (cin.fail()) {
        cin.clear(); //reset the stream state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard any remaining characters (up to the newline character)
        cout << "You made a mistake, please try again" << endl;
        first_menu(); //recurrsion
    }
    cout << endl;

    switch (choice) {
    case 1:
        login();
        break;
    case 2:
        Resister();
        break;
    case 3:
        Exit();
        break;
    default:
        cout << "You made a mistake, please try again" << endl;
        first_menu(); //recurrsion
        break;
    }
}

void Menu() {
    int choice;

    cout << "\t __________________________________________\n\n";
    cout << "\t|        WELCOME TO MY TO-DO LIST          |\n\n";
    cout << "\t|_________________ MENU ___________________|\n\n";
    cout << "\t|                                          |\n";
    cout << "\t|    Press 1 to Add Task                   |\n";
    cout << "\t|    Press 2 to Edit Task                  |\n";
    cout << "\t|    Press 3 to Delete Task                |\n";
    cout << "\t|    Press 4 to Display All Tasks          |\n";
    cout << "\t|    Press 5 to Display Done Tasks         |\n";
    cout << "\t|    Press 6 to Display Overdue Tasks      |\n";
    cout << "\t|    Press 7 to Display Due Today Tasks    |\n";
    cout << "\t|    Press 8 to Search For A Task          |\n";
    cout << "\t|    Press 9 to Mark Task As Done          |\n";
    cout << "\t|    Press 10 to Change Password           |\n";
    cout << "\t|    press 11 to Logout                    |\n";
    cout << "\t|__________________________________________|\n\n";

    cout << "\nPlease enter your choice: ";
    cin >> choice;
    if (cin.fail()) { //if the user entered a character or a string 
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Input! Please Try Again.\n";
        Menu();
    }
    switch (choice) {
    case 1:

        addTask(allUsers[currentUser].tasks, allUsers[currentUser].taskCount);

        break;

    case 2:

        editTask(allUsers[currentUser].tasks, allUsers[currentUser].taskCount);

        break;

    case 3:
        deletetask(allUsers[currentUser].tasks, allUsers[currentUser].taskCount);
        break;

    case 4:
        displayTasks(allUsers[currentUser].tasks, allUsers[currentUser].taskCount);
        break;
    case 5:
        displayDoneTasks(allUsers[currentUser].tasks, allUsers[currentUser].taskCount);
        Menu();
        break;

    case 6:
    {
        bool overdue[100];
        char choice;
        OverdueTasks(allUsers[currentUser].tasks, overdue, allUsers[currentUser].taskCount);
        cout << "Do you want to display all tasks that are overdue? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            displayOverdueTasks(allUsers[currentUser].tasks, overdue, allUsers[currentUser].taskCount);
        };
        Menu();
        break;
    }

    case 7:
    {
        bool duetoday[100];
        char reply;
        TasksDoneToday(allUsers[currentUser].tasks, duetoday, allUsers[currentUser].taskCount);
        cout << "Do you want to display all tasks that  are Due Today? (y/n): ";
        cin >> reply;
        if (reply == 'y' || reply == 'Y') {
            displayTasksDoneToday(allUsers[currentUser].tasks, duetoday, allUsers[currentUser].taskCount);
        };
        Menu();
        break;

    }
    case 8:
        searchForTask(allUsers[currentUser].tasks, allUsers[currentUser].taskCount);
        Menu();
        break;

    case 9:
        markTasksAsDone(allUsers[currentUser].tasks, allUsers[currentUser].taskCount);
        Menu();
        break;

    case 10:
        changePassword();
        break;
    case 11:
        first_menu();
        break;
    default:
        cout << "You made a mistake, please select a number between 1 and 11" << endl;
        Menu();
    }
}

void login() {
    string user, password;
    cout << "Please Enter the following details: \n" << endl;
    cout << "Username: ";
    cin.ignore();
    getline(cin, user);
    cout << "Password: ";
    getline(cin, password);

    bool found = false;
    for (int i = 0; i < userCount; i++) {
        if (allUsers[i].username == user && allUsers[i].password == password) {
            currentUser = i;
            cout << "\nHELLO " << user << ", LOGIN SUCCESSFUL!\n\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n!!!LOGIN ERROR!!!\nPlease check your username/password and try again" << endl;
        first_menu();
    }
    Menu();
}

void Resister() {
    string reg_user, reg_password;
    cout << "Enter Username: ";
    cin.ignore();
    getline(cin, reg_user);
    cout << "Enter Password: ";
    getline(cin, reg_password);

    bool userExists = false;
    for (int i = 0; i < userCount; i++) {
        if (allUsers[i].username == reg_user) {
            userExists = true;
            break;
        }
    }

    if (userExists) {
        cout << "\nUser already exists. Please try logging in.\n" << endl;
        first_menu();
    }
    else {
        allUsers[userCount].username = reg_user;
        allUsers[userCount].password = reg_password;
        userCount++;
        cout << "\nUser registered successfully!\n" << endl;
        writeAllUsers();
        first_menu();
    }
}


void addTask(Task tasks[], int& taskCount) {
    char option = ' ';

    do {

        cout << "- Adding a New Task -\n" << endl;
        cout << "Enter task title: ";
        cin.ignore(); // <-- Add this line to consume the newline character
        getline(cin, tasks[taskCount].title);

        cout << "Enter task details: ";
        getline(cin, tasks[taskCount].details);

        cout << "Enter task duedate (day month year): ";
        cin >> tasks[taskCount].taskdate.day >> tasks[taskCount].taskdate.month >> tasks[taskCount].taskdate.year;

        char priorityInput;



        do {
            cout << "Enter task priority Capatlized - (L)ow - (M)edium - (H)igh: ";
            cin >> priorityInput;

            if (priorityInput != 'L' && priorityInput != 'M' && priorityInput != 'H') {
                cout << "\nInvalid 'Priority' Data Type! Please enter capitalized 'L', 'M', or 'H'!\n" << endl;
                continue;

            }
        } while (priorityInput != 'L' && priorityInput != 'M' && priorityInput != 'H');

        tasks[taskCount].priority = priorityInput;

        tasks[taskCount].isDone = false;

        cout << "\nTask Added Successfully!\n" << endl;

        taskCount++;

        cout << "Do you want to add another task? (y/n): ";
        cin.ignore();
        cin >> option;
        cout << endl;
        writeUserTasks(allUsers[currentUser]);
    } while (option == 'y' || option == 'Y');
    Menu();

}

void editTask(Task tasks[], int taskCount) {
    char answer = ' ';

    do {
        int index;
        cout << "Enter the number of the task you want to edit (1-" << taskCount << ") : ";
        cin >> index;
        cin.ignore();

        if (index >= 1 && index <= taskCount) {
            cout << "\n- Editig a Task -\n" << endl;

            cout << "Enter new task title: ";
            getline(cin, tasks[index - 1].title);

            cout << "Enter new task details: ";
            getline(cin, tasks[index - 1].details);

            cout << "Enter new task duedate (day month year): ";
            cin >> tasks[index - 1].taskdate.day >> tasks[index - 1].taskdate.month >> tasks[index - 1].taskdate.year;

            cout << "Enter New Task Priority - (L)ow - (M)edium - (H)igh: ";
            char priorityInput;
            cin >> priorityInput;
            if (priorityInput != 'L' && priorityInput != 'l' && priorityInput != 'M' && priorityInput != 'm' && priorityInput != 'H' && priorityInput != 'h') {
                cout << "\nInvalid 'Priority' Data Type! Please enter 'L', 'M', or 'H'!\n" << endl;
                continue; // Restart the loop
            }
            tasks[index - 1].priority = priorityInput;

            cout << "\nTask Edited Successfully!\n" << endl;
        }
        else {
            cout << "\nInvalid Task Index!" << endl;
            continue;
        }
        cout << "Do you want to edit another task? (y/n): ";
        cin >> answer;
        cin.ignore();

        writeUserTasks(allUsers[currentUser]);
    } while (answer == 'y' || answer == 'Y');
    Menu();

}

void deletetask(Task tasks[], int& taskCount) {
    char choice;
    do {
        cout << "Do you want to delete a single task (s) or all tasks (a)? ";
        cin >> choice;

        if (choice == 's' || choice == 'S') {
            int del_task;
            cout << "Enter the Task Number You Want to Delete " << "(1-" << taskCount << "): ";
            cin >> del_task;

            if (del_task < 1 || del_task > taskCount) {
                cout << "Invalid task number entered." << endl;
                continue;
            }

            for (int i = del_task - 1; i < taskCount - 1; i++) {
                tasks[i] = tasks[i + 1];
            }
            taskCount--;

            cout << "Task deleted successfully!\n" << endl;
        }
        else if (choice == 'a' || choice == 'A') {
            taskCount = 0;
            cout << "All tasks deleted successfully!" << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
            continue;
        }

        cout << "Do you want to delete another task? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');


    writeUserTasks(allUsers[currentUser]);
    Menu();
}


void displayTasks(Task tasks[], int taskcount)
{
    for (int i = 0; i < taskcount; i++)
    {
        cout << "\t\t- Task " << i + 1 << " - " << endl
            << "Title:" << tasks[i].title << endl
            << "Details:" << tasks[i].details << endl
            << "Duedate:" << tasks[i].taskdate.day << '/'
            << tasks[i].taskdate.month << '/' << tasks[i].taskdate.year << endl
            << "Priority:" << tasks[i].priority << endl;
        if (tasks[i].isDone)
        {
            cout << "This Task Has Been Done!\n\n";
        }
        else
        {
            cout << "This Task Hasn't Been Done!\n\n";
        }

    }
    Menu();
}


void displayDoneTasks(Task tasks[], int taskcount) {
    int sumTasks = 0;
    for (int i = 0; i < taskcount; i++)
    {
        if (tasks[i].isDone == false) {
            sumTasks++;
        }
        else {
            cout << "\n\t\t- Tasks Done -\t\t" << endl;
            cout << "\t\t\tTask " << i + 1 << ": " << endl
                << "Title:" << tasks[i].title << endl
                << "Details:" << tasks[i].details << endl
                << "Duedate:" << tasks[i].taskdate.day << '/'
                << tasks[i].taskdate.month << '/' << tasks[i].taskdate.year << endl
                << "Priority:" << tasks[i].priority << endl;
        }
    }
    if (sumTasks == taskcount) {
        cout << "No Tasks has been marked as done.\n";
    }

    Menu();
}

void OverdueTasks(Task tasks[], bool overdue[], int taskCount)
{
    Date today = getDate();
    int overduecount = 0;
    for (int i = 0; i < taskCount; i++) {
        if ((tasks[i].taskdate.day < today.day && tasks[i].taskdate.month <= today.month && tasks[i].taskdate.year <= today.year) || (tasks[i].taskdate.month < today.month && tasks[i].taskdate.year <= today.year) || tasks[i].taskdate.year < today.year) {
            overdue[i] = true;
            overduecount++;
        }
        else
            overdue[i] = false;
    }
    cout << "Number of Tasks Overdue: " << overduecount << endl;
}


void displayOverdueTasks(Task tasks[], bool overdue[], int taskCount)
{
    cout << "\n- Overdue Tasks -\n" << endl;
    bool foundAnOverdue = false;
    for (int i = 0; i < taskCount; i++) {
        if (overdue[i] == true) {
            cout << "\t\tTask " << i + 1 << ": " << endl
                << "Title:" << tasks[i].title << endl
                << "Details:" << tasks[i].details << endl
                << "Duedate:" << tasks[i].taskdate.day << '/'
                << tasks[i].taskdate.month << '/' << tasks[i].taskdate.year << endl
                << "Priority:" << tasks[i].priority << endl;
            if (tasks[i].isDone)
            {
                cout << "This Task Has Been Done!\n\n";
            }
            else
            {
                cout << "This Task Hasn't Been Done!\n\n";
            }
            foundAnOverdue = true;
        }
    }
    if (!foundAnOverdue)
        cout << "There are no overdue tasks to display.\n";
    Menu();
}


void TasksDoneToday(Task tasks[], bool duetoday[], int taskCount)
{
    Date today = getDate();
    int donetodaycount = 0;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].taskdate.day == today.day && tasks[i].taskdate.month == today.month && tasks[i].taskdate.year == today.year) {
            duetoday[i] = true;
            donetodaycount++;
        }
        else
            duetoday[i] = false;
    }
    cout << "Number of Tasks Due Today: " << donetodaycount << endl;

}


void displayTasksDoneToday(Task tasks[], bool duetoday[], int taskCount) {
    cout << "\n- Tasks that are Due Today -\n" << endl;
    bool foundTaskDueToday = false;
    for (int i = 0; i < taskCount; i++) {
        if (duetoday[i] == true) {
            cout << "\t\tTask " << i + 1 << ": " << endl
                << "Title:" << tasks[i].title << endl
                << "Details:" << tasks[i].details << endl
                << "Duedate:" << tasks[i].taskdate.day << '/'
                << tasks[i].taskdate.month << '/' << tasks[i].taskdate.year << endl
                << "Priority:" << tasks[i].priority << endl;
            if (tasks[i].isDone)
            {
                cout << "This Task Has Been Done!\n\n";
            }
            else
            {
                cout << "This Task Hasn't Been Done!\n\n";
            }
            foundTaskDueToday = true;
        }
    }
    if (!foundTaskDueToday)
        cout << "There are no tasks due today to display.\n";
    Menu();
}///

void searchForTask(Task tasks[], int taskCount)
{
    int userChoice;
    char choice;

    do {
        cout << "Select the way you'd like to search for a task by:\n"
            << "1. Title\n"
            << "2. Priority\n"
            << "3. Duedate\n"
            << "4. Number/index\n"
            << "Select a number: ";
        cin >> userChoice;
        if (cin.fail()) { //if the user entered a character or a string 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input! Please Try Again.\n";
            searchForTask(allUsers[currentUser].tasks, allUsers[currentUser].taskCount);
        }
        if (userChoice == 1) {
            string titleOfTask = {};
            cout << "Enter the title of the task you're looking for: ";
            cin.ignore();
            getline(cin, titleOfTask);
            cout << "\t\t------------------------\n";
            bool foundTask = false;
            for (int i = 0; i < taskCount; ++i) {
                if (tasks[i].title == titleOfTask)
                {
                    foundTask = true;
                    cout << "\t\tFound the task you're looking for! Here's the task:\n\n"
                        << "Title:" << tasks[i].title << endl
                        << "Details:" << tasks[i].details << endl
                        << "Duedate:" << tasks[i].taskdate.day << '/'
                        << tasks[i].taskdate.month << '/' << tasks[i].taskdate.year << endl
                        << "Priority:" << tasks[i].priority << endl;
                    if (tasks[i].isDone)
                    {
                        cout << "This Task Has Been Done!\n\n";
                    }
                    else
                    {
                        cout << "This Task Hasn't Been Done!\n\n";
                    }
                }
            }
            if (!foundTask)
            {
                cout << "Couldn't find the task!!\n";
            }

        }
        else if (userChoice == 2) {
            char priorityOfTask;
            cout << "Enter the priority of the task you're looking for (H/M/L):";
            cin >> priorityOfTask;
            cout << "\t\t------------------------\n";
            bool foundTask = false;
            if (priorityOfTask == 'H' || priorityOfTask == 'M' || priorityOfTask == 'L') {
                for (int i = 0; i < taskCount; i++)
                {
                    if (tasks[i].priority == priorityOfTask) {
                        cout << "\t\tFound the task you're looking for! Here's the task:\n\n"
                            << "Title:" << tasks[i].title << endl
                            << "Details:" << tasks[i].details << endl
                            << "Duedate:" << tasks[i].taskdate.day << '/'
                            << tasks[i].taskdate.month << '/' << tasks[i].taskdate.year << endl
                            << "Priority:" << tasks[i].priority << endl;
                        if (tasks[i].isDone)
                        {
                            cout << "This Task Has Been Done!\n\n";
                        }
                        else
                        {
                            cout << "This Task Hasn't Been Done!\n\n";
                        }
                        foundTask = true;
                        break;
                    }
                }
                if (!foundTask)
                {
                    cout << "Couldn't find a task that matched the entered priority!!\n";
                }
            }
            else
            {
                cout << "Invalid Input!! Please enter (H/M/L)\n";
                searchForTask(allUsers[currentUser].tasks, allUsers[currentUser].taskCount);
            }
        }
        else if (userChoice == 3)
        {
            Date dateOfTask = {};
            int nIter = 0;
            cout << "Enter the date of the task you're looking for in the following formate "
                << "day month year:";
            cin >> dateOfTask.day >> dateOfTask.month >> dateOfTask.year;
            cout << "\t\t------------------------\n";
            for (int i = 0; i < taskCount; i++)
            {
                bool checkExp = tasks[i].taskdate.day == dateOfTask.day && tasks[i].taskdate.month == dateOfTask.month
                    && tasks[i].taskdate.year == dateOfTask.year;
                if (checkExp)
                {
                    nIter++;
                }
            }
            if (nIter == 0)
            {
                cout << "Couldn't find a task that matched that date!!\n";
            }
            else if (nIter == 1)
            {
                for (int i = 0; i < taskCount; i++)
                {
                    bool checkExp = tasks[i].taskdate.day == dateOfTask.day && tasks[i].taskdate.month == dateOfTask.month
                        && tasks[i].taskdate.year == dateOfTask.year;
                    if (checkExp) {
                        cout << "\t\tFound the task you're looking for! Here's the task:\n\n"
                            << "Title:" << tasks[i].title << endl
                            << "Details:" << tasks[i].details << endl
                            << "Duedate:" << tasks[i].taskdate.day << '/'
                            << tasks[i].taskdate.month << '/' << tasks[i].taskdate.year << endl
                            << "Priority:" << tasks[i].priority << endl;
                        if (tasks[i].isDone)
                        {
                            cout << "This Task Has Been Done!\n";
                        }
                        else
                        {
                            cout << "This Task Hasn't Been Done!\n";
                        }
                    }
                }
            }
            else
            {
                cout << "I've found " << nIter << " tasks that have the same date.\n\n";
                int taskCount = 0;
                for (int i = 0; i < nIter; i++)
                {
                    bool checkExp = tasks[i].taskdate.day == dateOfTask.day && tasks[i].taskdate.month == dateOfTask.month
                        && tasks[i].taskdate.year == dateOfTask.year;
                    if (checkExp) {
                        cout << "Task " << i + 1 << "\n"
                            << "Title:" << tasks[i].title << endl
                            << "Details:" << tasks[i].details << endl
                            << "Duedate:" << tasks[i].taskdate.day << '/'
                            << tasks[i].taskdate.month << '/' << tasks[i].taskdate.year << endl
                            << "Priority:" << tasks[i].priority << endl;
                        if (tasks[i].isDone)
                        {
                            cout << "This Task Has Been Done!\n\n";
                        }
                        else
                        {
                            cout << "This Task Hasn't Been Done!\n\n";
                        }
                    }
                }
            }
        }
        else if (userChoice == 4)
        {
            int index = -1;
            cout << "Enter the number/index of the task ( 1 - " << allUsers[currentUser].taskCount << " ) : ";
            cin >> index;
            if (cin.fail()) {
                cin.clear(); //reset the stream state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard any remaining characters (up to the newline character)
                cout << "You made a mistake, please try again" << endl;
                searchForTask(allUsers[currentUser].tasks, allUsers[currentUser].taskCount); //recurrsion
            }
            if (index<1 || index>allUsers[currentUser].taskCount)
            {
                cout << "Invalid Input! Please try again.\n";
                searchForTask(allUsers[currentUser].tasks, allUsers[currentUser].taskCount);
            }
            index--;
            cout << "\t\tHere is the task you're looking for:\n"
                << "\t\t-------------------------------------\n"
                << "Title:" << tasks[index].title << endl
                << "Details:" << tasks[index].details << endl
                << "Duedate:" << tasks[index].taskdate.day << '/'
                << tasks[index].taskdate.month << '/' << tasks[index].taskdate.year << endl
                << "Priority:" << tasks[index].priority << endl;
            if (tasks[index].isDone)
            {
                cout << "This Task Has Been Done!\n\n";
            }
            else
            {
                cout << "This Task Hasn't Been Done!\n\n";
            }
        }
        else
        {
            cout << "Invalid Input! Please choose a number between 1 and 4.\n";
            searchForTask(allUsers[currentUser].tasks, allUsers[currentUser].taskCount);
        }
        cout << "\nDo you want to search again? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    Menu();
}


void markTasksAsDone(Task tasks[], int taskCount)
{
    char ans = ' ';
    do
    {
        int taskIndex = -1;
        cout << "Enter the Index of The task you'd like to mark as done (1 - " << taskCount << ") :";
        cin >> taskIndex;
        if (taskIndex > taskCount || taskIndex < 1) {
            cout << "Invalid Index! Please Try Again.\n";
            continue;
        }
        tasks[taskIndex - 1].isDone = true;
        cout << "Would like to mark another task (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    writeUserTasks(allUsers[currentUser]);
}



void changePassword()
{
    string currentPassword = { };
    cout << "Enter your current password: ";
    cin.ignore();
    getline(cin, currentPassword);

    if (allUsers[currentUser].password != currentPassword) {
        cout << "Incorrect password!! Please try again." << endl;
        changePassword();
        return;
    }

    string newPassword;
    cout << "Enter your new password: ";
    cin >> newPassword;

    allUsers[currentUser].password = newPassword;
    cout << "\nPassword changed successfully!" << endl;
    writeAllUsers();
    Menu();
}


int Exit() {
    cout << "Thank You For Your Time!" << endl;
    exit(1);
}
