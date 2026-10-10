#include <iostream>   
#include <string>     
#include <vector> 
#include <Windows.h> 
#pragma execution_character_set("utf-8")
using namespace std;  

// Структура - один студент. Хранит ФИО, группу и список оценок
struct Student {
    string name;         
    string group;        
    vector<int> grades;  
};

vector<Student> studs;   
vector<string> groups;   
// Поиск группы. Возвращает номер группы в списке или -1, если не нашли.
// const string& - ссылка: строка не копируется, а const защищает её от изменения
int findGroup(const string& g) {
    for (int i = 0; i < groups.size(); i++) {
        if (groups[i] == g) {
            return i;   // нашли - возвращаем номер
        }
    }
    return -1;          // не нашли
}
// Поиск студента. Возвращает УКАЗАТЕЛЬ на студента (его адрес в памяти).
// Если студента нет - возвращает nullptr (пустой указатель).
// Через указатель можно менять самого студента из вектора, а не его копию
Student* findStudent(const string& name) {
    for (int i = 0; i < studs.size(); i++) {
        if (studs[i].name == name) {
            return &studs[i];   // & - взять адрес студента
        }
    }
    return nullptr;
}
// Добавление студента.
// vector<Student>& list - ссылка на вектор: студент добавится в настоящий, список studs, а не в его копию (без & ничего бы не сохранилось)
void addStudent(vector<Student>& list) {
    Student s;   // временный студент, заполним его и добавим в список
    cout << "Введите ФИО: ";
    getline(cin, s.name);    // getline читает всю строку вместе с пробелами
    cout << "Введите группу: ";
    getline(cin, s.group);
    if (findGroup(s.group) == -1) {      // нельзя добавить в несуществующую группу
        cout << "Такой группы нет\n";
        return;
    }
    int count;
    cout << "Сколько оценок: ";
    cin >> count;
    cin.ignore();   // убираем Enter после числа, иначе следующий getline пропустится
    for (int i = 0; i < count; i++) {
        int grade;
        cout << "Оценка " << i + 1 << ": ";
        cin >> grade;
        cin.ignore();
        if (grade < 2 || grade > 5) {    // оценка только от 2 до 5
            cout << "Оценка должна быть от 2 до 5\n";
            i--;                         // повторяем ввод этой же оценки
        }
        else {
            s.grades.push_back(grade);   // добавляем оценку в конец списка
        }
    }
    list.push_back(s);   // добавляем студента в общий список
    cout << "Студент добавлен\n";
}
// Изменение студента
void editStudent() {
    string name;
    cout << "ФИО студента которого меняем: ";
    getline(cin, name);
    Student* s = findStudent(name);   // получаем указатель на студента
    if (s == nullptr) {               // nullptr - значит такого студента нет
        cout << "Нет такого студента\n";
        return;
    }
    cout << "Новое ФИО: ";
    getline(cin, s->name);   // -> обращение к полю через указатель (то же, что (*s).name)
    string g;
    cout << "Новая группа: ";
    getline(cin, g);
    if (findGroup(g) == -1) {   // новая группа должна существовать
        cout << "Такой группы нет, группа не изменилась\n";
        return;
    }
    s->group = g;
    cout << "Готово\n";
}
// Удаление студента
void deleteStudent() {
    string name;
    cout << "ФИО студента для удаления: ";
    getline(cin, name);
    for (int i = 0; i < studs.size(); i++) {
        if (studs[i].name == name) {
            studs.erase(studs.begin() + i);   // erase удаляет элемент по номеру
            cout << "Студент удалён\n";
            return;
        }
    }
    cout << "Нет такого студента\n";   // сюда пойдем, только если не нашли
}
// Добавление группы
void addGroup() {
    string g;
    cout << "Название группы: ";
    getline(cin, g);
    if (findGroup(g) != -1) {   // такая группа уже есть - второй раз не добавляем
        cout << "Такая группа уже есть\n";
        return;
    }
    groups.push_back(g);
    cout << "Группа добавлена\n";
}
// Изменение (переименование) группы
void editGroup() {
    string old, nw;
    cout << "Какую группу меняем: ";
    getline(cin, old);
    int ind = findGroup(old);   // номер группы в списке
    if (ind == -1) {
        cout << "Такой группы нет\n";
        return;
    }
    cout << "Новое название: ";
    getline(cin, nw);
    // auto& - ссылка на студента из вектора, поэтому изменения сохраняются.
    // Меняем название группы у всех студентов этой группы
    for (auto& s : studs) {
        if (s.group == old) {
            s.group = nw;
        }
    }
    groups[ind] = nw;   // меняем название в списке групп
    cout << "Готово\n";
}
// Удаление группы (только если в ней нет студентов)
void deleteGroup() {
    string g;
    cout << "Какую группу удалить: ";
    getline(cin, g);
    int ind = findGroup(g);
    if (ind == -1) {
        cout << "Такой группы нет\n";
        return;
    }
    // проверяем всех студентов: если кто-то из этой группы - удалять нельзя
    for (int i = 0; i < studs.size(); i++) {
        if (studs[i].group == g) {
            cout << "В группе есть студенты, удалить нельзя\n";
            return;
        }
    }
    groups.erase(groups.begin() + ind);   // студентов нет - удаляем
    cout << "Группа удалена\n";
}
// Добавление оценки конкретному студенту
void addMark() {
    string name;
    cout << "ФИО студента: ";
    getline(cin, name);
    Student* s = findStudent(name);
    if (s == nullptr) {
        cout << "Нет такого студента\n";
        return;
    }
    int grade;
    cout << "Оценка: ";
    cin >> grade;
    cin.ignore();
    if (grade < 2 || grade > 5) {
        cout << "Оценка должна быть от 2 до 5\n";
        return;
    }
    s->grades.push_back(grade);   // добавляем оценку через указатель
    cout << "Оценка добавлена\n";
}
// Средний балл студента = сумма оценок / количество оценок
void studentAverage() {
    string name;
    cout << "ФИО студента: ";
    getline(cin, name);
    Student* s = findStudent(name);
    if (s == nullptr) {
        cout << "Нет такого студента\n";
        return;
    }
    if (s->grades.size() == 0) {   // без оценок считать нельзя (деление на 0)
        cout << "У студента нет оценок\n";
        return;
    }
    double sum = 0;   // double, чтобы получилось дробное число
    for (int i = 0; i < s->grades.size(); i++) {
        sum += s->grades[i];   // складываем все оценки
    }
    cout << "Средний балл: " << sum / s->grades.size() << "\n";
}
// Средний балл группы = сумма всех оценок группы / количество всех оценок
void groupAverage() {
    string g;
    cout << "Группа: ";
    getline(cin, g);
    if (findGroup(g) == -1) {
        cout << "Такой группы нет\n";
        return;
    }
    double sum = 0;   // сумма всех оценок
    int count = 0;    // сколько всего оценок
    for (int i = 0; i < studs.size(); i++) {
        if (studs[i].group == g) {   // берём только студентов нужной группы
            for (int j = 0; j < studs[i].grades.size(); j++) {
                sum += studs[i].grades[j];
                count++;
            }
        }
    }
    if (count == 0) {
        cout << "В группе нет оценок\n";
        return;
    }
    cout << "Средний балл группы: " << sum / count << "\n";
}
// Статистика группы: сколько отличников, хорошистов и т.д.
// Категорию определяем по самой МАЛЕНЬКОЙ оценке студента
void stat() {
    string g;
    cout << "Группа: ";
    getline(cin, g);
    if (findGroup(g) == -1) {
        cout << "Такой группы нет\n";
        return;
    }
    // счётчики для каждой категории
    int five = 0, four = 0, three = 0, two = 0, none = 0;
    for (int i = 0; i < studs.size(); i++) {
        if (studs[i].group != g) continue;   // чужую группу пропускаем
        if (studs[i].grades.size() == 0) {   // нет оценок - отдельная категория
            none++;
            continue;
        }
        // ищем минимальную оценку студента
        int mn = studs[i].grades[0];
        for (int j = 0; j < studs[i].grades.size(); j++) {
            if (studs[i].grades[j] < mn) {
                mn = studs[i].grades[j];
            }
        }
        if (mn == 5) five++;          // все пятёрки - отличник
        else if (mn == 4) four++;     // нет троек и двоек - хорошист
        else if (mn == 3) three++;    // есть тройка - троечник
        else two++;                   // есть двойка
    }
    cout << "Отличников: " << five << "\n";
    cout << "Хорошистов: " << four << "\n";
    cout << "Троечников: " << three << "\n";
    cout << "С двойками: " << two << "\n";
    cout << "Без оценок: " << none << "\n";
}
// Показать все группы и студентов (чтобы удобно проверять, что изменилось)
void showAll() {
    for (int i = 0; i < groups.size(); i++) {
        cout << "\nГруппа " << groups[i] << ":\n";
        for (int j = 0; j < studs.size(); j++) {
            if (studs[j].group == groups[i]) {   // студенты этой группы
                cout << "  " << studs[j].name << " - ";
                for (int k = 0; k < studs[j].grades.size(); k++) {
                    cout << studs[j].grades[k] << " ";
                }
                cout << "\n";
            }
        }
    }
}
// Начальные данные: заполняем списки при запуске программы
void initData() {
    groups.push_back("БД-1-25");
    groups.push_back("П-1-25");
    groups.push_back("ИС-2-25");   // эта группа пустая, на ней можно проверить удаление

    // в фигурных скобках: ФИО, группа, оценки
    studs.push_back({ "Какашкин Иван", "БД-1-25", {5, 5, 5} });     
    studs.push_back({ "Пукович Пётр", "БД-1-25", {5, 4, 5} });      
    studs.push_back({ "Лохушкина Анна", "БД-1-25", {4, 4, 3} });    
    studs.push_back({ "Калатушкин Олег", "БД-1-25", {3, 2, 4} });    
    studs.push_back({ "Крысина Мария", "БД-1-25", {} });          
    studs.push_back({ "Шакалов Дмитрий", "П-1-25", {5, 5, 4} });
    studs.push_back({ "Дудкина Елена", "П-1-25", {5, 5, 5} });
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    initData();   // сначала заполнем начальные данные
    int answer = -1;
    while (answer != 0) {   
        cout << "\n1. добавить студента\n2. изменить студента\n3. удалить студента\n"
            << "4. добавить группу\n5. изменить группу\n6. удалить группу\n"
            << "7. средний балл студента\n8. средний балл группы\n9. добавить оценку\n"
            << "10. статистика по группе\n11. показать всех\n0. выход\nВыбор: ";
        cin >> answer;
        cin.ignore();   // убираем Enter

        // switch выбирает, какую функцию вызвать, по номеру пункта
        switch (answer) {
        case 1: addStudent(studs); break;   // передаём studs по ссылке
        case 2: editStudent(); break;
        case 3: deleteStudent(); break;
        case 4: addGroup(); break;
        case 5: editGroup(); break;
        case 6: deleteGroup(); break;
        case 7: studentAverage(); break;
        case 8: groupAverage(); break;
        case 9: addMark(); break;
        case 10: stat(); break;
        case 11: showAll(); break;
        case 0: break;   // выход: цикл while закончится сам
        default: cout << "Нет такого пункта\n"; break;
        }
    }
    return 0;
}