#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//// Перечислимый тип для статуса задачи
//enum class TaskStatus {
//    NEW,          // новая
//    IN_PROGRESS,  // в разработке
//    TESTING,      // на тестировании
//    DONE          // завершена
//};
//
//// Объявляем тип-синоним для map<TaskStatus, int>,
//// позволяющего хранить количество задач каждого статуса
//using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
    map<string, TasksInfo> teamTasks;
    vector<TaskStatus> getSortedTasks(const TasksInfo &tasksInfo) const {
        vector<TaskStatus> allTasks;
        for (const auto &taskInfo: tasksInfo) {
            for (int i = 0; i < taskInfo.second; ++i) {
                allTasks.push_back(taskInfo.first);
            }
        }
        sort(allTasks.begin(), allTasks.end());
        return allTasks;
    }
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
        vector<TaskStatus> allTasks = getSortedTasks(tasksInfo);

        TasksInfo updatedTasks, notChangedTasks;
        size_t i;
        for (i = 0; i < task_count && i < allTasks.size(); ++i) {
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
        for (auto & taskStatus : allTasks) {
            ++tasksInfo[taskStatus];
        }
        return make_tuple(updatedTasks, notChangedTasks);
    }
};

//void PrintTasksInfo(const TasksInfo& tasks_info) {
//    if (tasks_info.count(TaskStatus::NEW)) {
//        std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
//    }
//    if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
//        std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
//    }
//    if (tasks_info.count(TaskStatus::TESTING)) {
//        std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
//    }
//    if (tasks_info.count(TaskStatus::DONE)) {
//        std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
//    }
//}
//
//void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
//    std::cout << "Updated: [";
//    PrintTasksInfo(updated_tasks);
//    std::cout << "] ";
//
//    std::cout << "Untouched: [";
//    PrintTasksInfo(untouched_tasks);
//    std::cout << "] ";
//
//    std::cout << std::endl;
//}

int main() {
//    TeamTasks tasks;
//    TasksInfo updated_tasks;
//    TasksInfo untouched_tasks;
//
//    /* TEST 1 */
//    std::cout << "Alice" << std::endl;
//
//    for (auto i = 0; i < 5; ++i) {
//        tasks.AddNewTask("Alice");
//    }
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]
//
//    for (auto i = 0; i < 5; ++i) {
//        tasks.AddNewTask("Alice");
//    }
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice",
//                                                                   2);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
//    PrintTasksInfo(updated_tasks, untouched_tasks);
//
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
//    std::cout << std::endl;
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
//
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
//    std::cout << std::endl;
//
//    /* TEST 2 */
//    std::cout << "\nJack" << std::endl;
//
//    tasks.AddNewTask("Jack");
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]
//
//    tasks.AddNewTask("Jack");
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]
//
//    tasks.AddNewTask("Jack");
//
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
//    std::cout << std::endl;
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]
//
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
//    std::cout << std::endl;
//
//    /* TEST 3 */
//    std::cout << "\nLisa" << std::endl;
//
//    for (auto i = 0; i < 5; ++i) {
//        tasks.AddNewTask("Lisa");
//    }
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]
//
//    for (auto i = 0; i < 5; ++i) {
//        tasks.AddNewTask("Lisa");
//    }
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
//
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
//    std::cout << std::endl;
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
//
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
//    std::cout << std::endl;
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]
//
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"TESTING": 8, "DONE": 2}
//    std::cout << std::endl;
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 8}, {}]
//
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
//    std::cout << std::endl;
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]
//
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
//    std::cout << std::endl;
//
//    tasks.AddNewTask("Lisa");
//
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 1, "DONE": 10}
//    std::cout << std::endl;
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]
//
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 1, "DONE": 10}
//    std::cout << std::endl;
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
//    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]
//
//    return 0;
}
