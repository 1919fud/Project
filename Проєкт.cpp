#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

class CourseProject {
private:
    static int colvsego;
    int nomerkyps;
    string prisvishe;
    string inicial;
    string programQuality;
    string zapiskaQuality;
    string defenseQuality;
    int kypsMark;

    string generateinicial() {
        string Alphabet = "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЮЯ";
        char first = Alphabet[rand() % Alphabet.size()];
        char second = Alphabet[rand() % Alphabet.size()];
        return string(1, first) + "." + string(1, second) + ".";
    }

    string generateQuality() {
        int choice = rand() % 4;
        if (choice == 0) return "чудово";
        if (choice == 1) return "добре";
        if (choice == 2) return "погано";
        if (choice == 3) return "дуже погано";
    }

    int getQualityScore(const string& quality) const {
        if (quality == "чудово") return 5;
        if (quality == "добре") return 4;
        if (quality == "погано") return 3;
        if (quality == "дуже погано")return 2;
    }


    int calculateMark() {
        int total = getQualityScore(programQuality)
            + getQualityScore(zapiskaQuality)
            + getQualityScore(defenseQuality);

        return (total + 1) / 3;
    }

public:
    CourseProject() {
        prisvishe = "";
        nomerkyps = 0;
        inicial = "";
        programQuality = "";
        zapiskaQuality = "";
        defenseQuality = "";
        kypsMark = 0;
    }



    CourseProject(const string& lastName) {
        prisvishe = lastName;
        nomerkyps = ++colvsego;
        inicial = generateinicial();
        programQuality = generateQuality();
        zapiskaQuality = generateQuality();
        defenseQuality = generateQuality();
        kypsMark = calculateMark();
    }

    string getPrizvishe() const {
        return prisvishe;
    }

    int getMark() const {
        return kypsMark;
    }

    string getProgramQuality() const {
        return programQuality;
    }

    string getZapiskaQuality() const {
        return zapiskaQuality;
    }

    string getDefenseQuality() const {
        return defenseQuality;
    }

    void setNomerkyps(int newNomerkyps) {
        nomerkyps = newNomerkyps;
    }

    void vivid() const {
        cout << "Номер курсового: " << nomerkyps << "\n"
            << "Прізвище студента: " << prisvishe << "\n"
            << "Ініціали студента: " << inicial << "\n"
            << "Якість програми: " << programQuality << "\n"
            << "Якість записки: " << zapiskaQuality << "\n"
            << "Якість захисту: " << defenseQuality << "\n"
            << "Оцінка за курсовий проект: " << kypsMark << "\n"
            << "--------------------------\n";
    }

    static int getcolvsego() {
        return colvsego;
    }

    static void decrementColvsego() {
        --colvsego;
    }

    void setProgramQuality(const string& quality) {
        programQuality = quality;
        kypsMark = calculateMark();
    }

    void setZapiskaQuality(const string& quality) {
        zapiskaQuality = quality;
        kypsMark = calculateMark();
    }

    void setDefenseQuality(const string& quality) {
        defenseQuality = quality;
        kypsMark = calculateMark();
    }
};

int CourseProject::colvsego = 0;

class Node {
public:
    CourseProject project;
    Node* next;

    Node(const CourseProject& proj) {
        project = proj;
        next = 0;
    }
};

class CourseList {
private:
    Node* head;
    int count;

public:
    CourseList() {
        head = 0;
        count = 0;
    }

    ~CourseList() {
        Node* current = head;
        while (current != 0) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

void vividAllProjectsBySurname() const {
    vector<vector<Node*>> groups(33);
    Node* current = head;

    while (current != nullptr) {
        char firstChar = current->project.getPrizvishe()[0];
        if (firstChar >= 'А' && firstChar <= 'Я') {
            groups[firstChar - 'А'].push_back(current);
        }
        current = current->next;
        }

    for (int i = 0; i < groups.size(); ++i) {
        if (!groups[i].empty()) {
            for (int j = 0; j < groups[i].size(); ++j) {
                for (int k = j + 1; k < groups[i].size(); ++k) {
                    string surnameA = groups[i][j]->project.getPrizvishe();
                    string surnameB = groups[i][k]->project.getPrizvishe();
                    int minLength = min(surnameA.length(), surnameB.length());
                    bool swapFlag = false;
                    for (int l = 1; l < minLength; ++l) {
                        if (surnameA[l] < surnameB[l]) {
                            break;
                        }
                        else if (surnameA[l] > surnameB[l]) {
                            swapFlag = true;
                            break;
                        }
                    }
                    if (swapFlag || (surnameA.length() > surnameB.length() && surnameA[minLength] > surnameB[minLength])) {
                        swap(groups[i][j], groups[i][k]);
                    }
                }
            }
            for (Node* node : groups[i]) {
                    node->project.vivid();
            }
        }
    }
}



void vividAllProjectsByMark() const {
    vector<vector<Node*>> marks(4);
    Node* current = head;

    while (current != 0) {
        int mark = current->project.getMark();
        if (mark >= 2 && mark <= 5) {
            marks[mark - 2].push_back(current);
        }
        current = current->next;
    }

    for (int i = 0; i < marks.size(); ++i) {
        for (int j = 0; j < marks[i].size(); ++j) {
            marks[i][j]->project.vivid();
        }
    }
}

void vividFilteredProjects(const string& filterType, const string& filterValue) const {
    Node* current = head;
    bool found = false;

    while (current != nullptr) {
        bool matches = false;

        if (filterType == "programQuality" && current->project.getProgramQuality() == filterValue) {
            matches = true;
        }
        else if (filterType == "zapiskaQuality" && current->project.getZapiskaQuality() == filterValue) {
            matches = true;
        }
        else if (filterType == "defenseQuality" && current->project.getDefenseQuality() == filterValue) {
            matches = true;
        }
        else if (filterType == "mark" && to_string(current->project.getMark()) == filterValue) {
            matches = true;
        }

        if (matches) {
            cout << "Знайдено відповідність для фільтра: " << filterValue << endl;
            current->project.vivid();
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Проектів, що відповідають фільтру \"" << filterValue << "\", не знайдено.\n";
    }
}

void vividAllProjectsReverse() const {
    vividAllProjectsReverseHelper(head);
}

void vividAllProjectsReverseHelper(Node* node) const {
    if (node == 0) {
        return;
    }
    vividAllProjectsReverseHelper(node->next);
    node->project.vivid();
}


void addProject(const CourseProject& project) {
        if (count >= 30) {
            cout << "Досягнуто максимальної кількості курсових робіт.\n";
            return;
        }
        Node* newNode = new Node(project);

        if (head == 0) {
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next != 0) {
                current = current->next;
            }
            current->next = newNode;
        }
        count++;
}

void removeProject(int index) {
        if (index < 0 || index >= count) {
            cout << "Некоректний індекс курсової роботи.\n";
            return;
        }

        // Якщо треба видалити перший елемент
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }

        --count;
        CourseProject::decrementColvsego();
        cout << "Курсову роботу успішно видалено.\n";
        renumberProjects();
}

void renumberProjects() {
    Node* current = head;
    int currentNumber = 1;  // Починаємо нумерацію з 1

    while (current != nullptr) {
        current->project.setNomerkyps(currentNumber);
        currentNumber++;
        current = current->next;
    }
}
void vividAllProjects() const {
    Node* current = head;
    while (current != 0) {
        current->project.vivid();
        current = current->next;
        }
}


double calculateAverageMark() const {
        if (count == 0) return 0.0;

        double total = 0.0;
        Node* current = head;
        while (current != 0) {
            total += current->project.getMark();
            current = current->next;
        }
        return total / count;
}

int getCount() const {
        return count;
}

CourseProject& operator[](int index) {
        do {
            if (index < 0 || index >= count) {
                cout << "Индекс вне диапазона\n";
                cout << "Введіть індекс курсової роботи:";
                cin >> index;
                --index;
            }
        } while (index < 0 || index >= count);

        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->project;
}
};

void loadSurnames(const string& filename, vector<string>& surnames) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не вдалося відкрити файл із прізвищами.\n";
        exit(1);
    }
    string surname;
    while (file >> surname) {
        surnames.push_back(surname);
    }
    file.close();

    for (int i = 0; i < surnames.size(); ++i) {
        int randomIndex = rand() % surnames.size();
        string temp = surnames[i];
        surnames[i] = surnames[randomIndex];
        surnames[randomIndex] = temp;
    }
}

int main() {
    system("chcp 1251");
    system("cls");
    srand(time(0));

    vector<string> surnames;
    loadSurnames("surnames.txt", surnames);
    CourseList courseList;
    int surnameIndex = 0;

    while (true) {
        cout << "1. Додати курсову роботу\n"
            << "2. Видалити курсову роботу\n"
            << "3. Показати всі курсові роботи (прямий порядок)\n"
            << "4. Показати всі курсові роботи (обратний порядок)\n"
            << "5. Показати всі курсові роботи за прізвищем\n"  
            << "6. Показати всі курсові роботи за оцінкою\n"   
            << "7. Показати курсову за індексом\n"
            << "8. Показати кількість створених курсових проєктів\n"
            << "9. Показати середній бал серед усіх студентів\n"
            << "10. Змінити якість параметра курсового проєкту\n"
            << "11. Фільтрувати курсові роботи за критерієм\n"
            << "12. Автор програми\n"
            << "13. Вихід\n"; 
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            if (surnameIndex < surnames.size()) {
                CourseProject project(surnames[surnameIndex++]);
                courseList.addProject(project);
            }
            else {
                cout << "Усі прізвища з файлу вже використані.\n";
            }
            break;
        case 2: {
            int index;
            cout << "Введіть індекс курсової роботи для видалення: ";
            cin >> index;

            courseList.removeProject(index - 1);
            break;
        }
        case 3:
            courseList.vividAllProjects();
            break;
        case 4: {
            courseList.vividAllProjectsReverse();
            break;
        }
        case 5: {
            courseList.vividAllProjectsBySurname();
            break;
        }
        case 6: {
            courseList.vividAllProjectsByMark();
            break;
        }
        case 7: {
            int index= courseList.getCount();
            if (index>0) {
                cout << "Введіть індекс курсової роботи:";
                cin >> index;
                courseList[index - 1].vivid();
            }
            cout << "Немає створених курсових проєктів\n";
            break;
        }
        case 8:
            cout << "Кількість створених курсових проєктів:" << CourseProject::getcolvsego() << "\n";
            break;
        case 9: {
            double averageMark = courseList.calculateAverageMark();
            cout << "Середній бал серед усіх студентів:" << averageMark << "\n";
            break;
        }
        case 10: {
            int index;
            cout << "Введіть індекс курсової роботи для редагування: ";
            cin >> index;

            if (index < 1 || index > courseList.getCount()) {
                cout << "Некоректний індекс.\n";
                break;
            }

            CourseProject& project = courseList[index - 1];
            courseList[index - 1].vivid();
            cout << "Виберіть параметр для зміни:\n"
                << "1. Якість програми\n"
                << "2. Якість записки\n"
                << "3. Якість захисту\n";
            int paramChoice;
            cin >> paramChoice;

            cout << "Введіть нову якість (чудово, добре, погано, дуже погано): ";
            string newQuality;
            cin >> newQuality;

            switch (paramChoice) {
            case 1:
                project.setProgramQuality(newQuality);
                break;
            case 2:
                project.setZapiskaQuality(newQuality);
                break;
            case 3:
                project.setDefenseQuality(newQuality);
                break;
            default:
                cout << "Некоректний вибір параметра.\n";
                break;
            }

            cout << "Якість оновлено, оцінка перерахована.\n";
            break;
        }
        case 11: {
            cout << "Виберіть критерій фільтрації:\n"
                << "1. Якість програми\n"
                << "2. Якість записки\n"
                << "3. Якість захисту\n"
                << "4. Оцінка\n";
            int filterChoice;
            cin >> filterChoice;

            string filterType, filterValue;
            switch (filterChoice) {
            case 1:
                filterType = "programQuality";
                break;
            case 2:
                filterType = "zapiskaQuality";
                break;
            case 3:
                filterType = "defenseQuality";
                break;
            case 4:
                filterType = "mark";
                break;
            default:
                cout << "Некоректний вибір критерію.\n";
                continue;
            }

            cout << "Введіть значення фільтру ('чудово', 'добре', 'погано' 'дуже погано', '5', '4', '3', '2'):\n";
            cin.ignore();
            getline(cin, filterValue);

            courseList.vividFilteredProjects(filterType, filterValue);
            break;
        }
        case 12: {
            cout << "Пєтріщев Денис Андрійович ОПК-312\n";
            break;
               }
        case 13: {
            return 0;
        }
        default:
            cout << "Некоректний вибір. Спробуйте знову.\n";
            break;
        }
    }

    return 0;
}