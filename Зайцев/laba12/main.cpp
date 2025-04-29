#include <iostream>
#include <queue>
#include <stack>

using namespace std;

enum TaskType {
    T1 = 1,
    T2 = 2,
    T3 = 3
};

struct Task {
    TaskType type;
    int id;
};

int main() {
    setlocale(LC_ALL, "Russian");

    queue<Task> taskQueue;
    stack<Task> taskStack;

    bool processorBusy[3] = { false, false, false }; // Состояние занятости процессоров
    int processorFinishTime[3] = { 0, 0, 0 }; // Время, когда процессор освободится
    int currentTime = 0; // Текущее время

    // Добавляем задачи в очередь
    taskQueue.push({ T1, 1 });
    taskQueue.push({ T2, 2 });
    taskQueue.push({ T3, 3 });
    taskQueue.push({ T1, 4 });
    taskQueue.push({ T2, 5 });
    taskQueue.push({ T3, 6 });
    taskQueue.push({ T3, 7 });

    while (!taskQueue.empty() || !taskStack.empty()) {

        // Проверяем завершение задач на процессорах
        for (int i = 0; i < 3; ++i) {
            if (processorBusy[i] && currentTime >= processorFinishTime[i]) {
                cout << "Процессор " << i + 1 << " завершил работу и сейчас свободен." << endl;
                processorBusy[i] = false;
            }
        }

        // Проверяем стек на задачи для свободных процессоров
        if (!taskStack.empty() && !processorBusy[taskStack.top().type - 1]) {
            Task t = taskStack.top();
            taskStack.pop();
            processorBusy[t.type - 1] = true;
            processorFinishTime[t.type - 1] = currentTime + 5; 
            cout << "Процессор " << t.type << " выполняет задачу " << t.id << endl;
            continue;
        }

        // Обрабатываем очередь
        if (!taskQueue.empty()) {
            Task t = taskQueue.front();

            if (!processorBusy[t.type - 1]) {
                taskQueue.pop();
                processorBusy[t.type - 1] = true;
                processorFinishTime[t.type - 1] = currentTime + 5; 
                cout << "Процессор " << t.type << " выполняет задачу " << t.id << endl;
            }
            else {
                taskStack.push(t);
                taskQueue.pop();
                cout << "Задача " << t.id << " типа " << t.type
                    << " перемещена в стек потому что процессор " << t.type
                    << " занят" << endl;
            }
        }

        currentTime++; // Увеличиваем текущее время
    }

    return 0;
}
