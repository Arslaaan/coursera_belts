#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstdint>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

ostream &operator<<(ostream &out, const TaskStatus &status) {
    if (status == TaskStatus::NEW) {
        out << "NEW";
    } else if (status == TaskStatus::IN_PROGRESS) {
        out << "IN_PROGRESS";
    } else if (status == TaskStatus::TESTING) {
        out << "TESTING";
    } else {
        out << "DONE";
    }
    return out;
}

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
    map<string, TasksInfo> teamTasks;
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo &GetPersonTasksInfo(const string &person) const {
        return teamTasks.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string &person) {
        TasksInfo &info = teamTasks[person];
        ++info[TaskStatus::NEW];
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person, int task_count) {
        if (teamTasks.count(person) == 0) {
            return make_tuple(TasksInfo(), TasksInfo());
        }
        TasksInfo &tasksInfo = teamTasks[person];
        vector<TaskStatus> allTasks;
        for (auto &taskInfo: tasksInfo) {
            for (int i = 0; i < taskInfo.second; ++i) {
                allTasks.push_back(taskInfo.first);
            }
        }
        sort(allTasks.begin(), allTasks.end());

        TasksInfo updatedTasks;
        TasksInfo notChangedTasks;
        size_t i;
        for (i = 0; i < task_count; ++i) {
            if (allTasks[i] != TaskStatus::DONE) {
                allTasks[i] = static_cast<TaskStatus>(static_cast<int>(allTasks[i]) + 1);
                ++updatedTasks[allTasks[i]];
            } else {
                break;
            }
        }
        for (size_t k = i; k < allTasks.size(); ++k) {
            if (allTasks[k] != TaskStatus::DONE) {
                ++notChangedTasks[allTasks[k]];
            }
        }
        tasksInfo.clear();
        for (size_t j = 0; j < allTasks.size(); ++j) {
            ++tasksInfo[allTasks[j]];
        }
        return make_tuple(updatedTasks, notChangedTasks);
    }
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    TasksInfo updated_tasks, untouched_tasks;

    for (int i = 0; i < 1; ++i) {
        tasks.AddNewTask("Ivan");
    }
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    tasks.PerformPersonTasks("Ivan", 1);
    tasks.PerformPersonTasks("Ivan", 1);
    tasks.PerformPersonTasks("Ivan", 1);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    //появилась 1 задача в Done

    for (int i = 0; i < 4; ++i) {
        tasks.AddNewTask("Ivan");
    }
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    tasks.PerformPersonTasks("Ivan", 4);
    tasks.PerformPersonTasks("Ivan", 4);
    //появилось 4 задачи в testing
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    for (int i = 0; i < 2; ++i) {
        tasks.AddNewTask("Ivan");
    }
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    tasks.PerformPersonTasks("Ivan", 2);
    //появилось 2 задачи в in progress
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    //появилось 3 задачи в new

    cout << "Раньше была подготовка, теперь тест" << endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 4);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);

    return 0;
}
