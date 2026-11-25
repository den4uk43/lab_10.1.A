#include <iostream>
#include <iomanip>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

enum Specialnist {
    KOMPYUTERNI_NAUKY,
    INFORMATYKA,
    MATEMATYKA_TA_EKONOMIKA,
    FIZYKA_TA_INFORMATYKA,
    TRUDOVE_NAVCHANNYA
};

struct Student {
    string prizvyshche;
    int kurs;
    Specialnist specialnist;
    int fizyka;
    int matematyka;
    int informatyka;
};

size_t Utf8Length(const string& str) {
    size_t len = 0;
    for (unsigned char c : str) {
        if ((c & 0xC0) != 0x80) {
            ++len;
        }
    }
    return len;
}

string PadRightUtf8(const string& str, size_t width) {
    size_t len = Utf8Length(str);
    if (len >= width) {
        return str;
    }
    return str + string(width - len, ' ');
}

string GetSpecialnistName(Specialnist spec) {
    switch (spec) {
    case KOMPYUTERNI_NAUKY:       return "Комп'ютерні науки";
    case INFORMATYKA:             return "Інформатика";
    case MATEMATYKA_TA_EKONOMIKA: return "Математика та економіка";
    case FIZYKA_TA_INFORMATYKA:   return "Фізика та інформатика";
    case TRUDOVE_NAVCHANNYA:      return "Трудове навчання";
    default:                      return "Невідома спеціальність";
    }
}

void Create(Student* p, const int N) {
    int specChoice;
    for (int i = 0; i < N; i++) {
        cout << "\nСтудент № " << i + 1 << ":" << endl;
        cout << "  Прізвище: ";
        cin >> p[i].prizvyshche;

        cout << "  Курс (1-6): ";
        cin >> p[i].kurs;

        cout << "  Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, "
            << "2 - Математика та економіка, 3 - Фізика та інформатика, "
            << "4 - Трудове навчання): ";
        cin >> specChoice;
        if (specChoice < 0 || specChoice > 4) {
            specChoice = 0;
        }
        p[i].specialnist = static_cast<Specialnist>(specChoice);

        cout << "  Оцінка з фізики: ";
        cin >> p[i].fizyka;

        cout << "  Оцінка з математики: ";
        cin >> p[i].matematyka;

        cout << "  Оцінка з інформатики: ";
        cin >> p[i].informatyka;
    }
}

void PrintTable(const Student* p, const int N) {
    const string line = "=====================================================================================================";
    const string sep = "-----------------------------------------------------------------------------------------------------";

    cout << "\n" << line << endl;
    cout << "                                 ВІДОМІСТЬ УСПІШНОСТІ СТУДЕНТІВ (РІВЕНЬ А)                            " << endl;
    cout << line << endl;
    cout << "| " << PadRightUtf8("№", 3)
        << " | " << PadRightUtf8("Прізвище", 16)
        << " | " << PadRightUtf8("Курс", 4)
        << " | " << PadRightUtf8("Спеціальність", 25)
        << " | " << PadRightUtf8("Фізика", 8)
        << " | " << PadRightUtf8("Математика", 11)
        << " | " << PadRightUtf8("Інформатика", 12) << " |" << endl;
    cout << sep << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << right << i + 1
            << " | " << PadRightUtf8(p[i].prizvyshche, 16)
            << " | " << setw(4) << right << p[i].kurs
            << " | " << PadRightUtf8(GetSpecialnistName(p[i].specialnist), 25)
            << " | " << setw(8) << right << p[i].fizyka
            << " | " << setw(11) << right << p[i].matematyka
            << " | " << setw(12) << right << p[i].informatyka << " |" << endl;
    }
    cout << line << endl;
}

double CalcStudentAverage(const Student& st) {
    return (st.fizyka + st.matematyka + st.informatyka) / 3.0;
}

double FindMaxAverageGrade(const Student* p, const int N) {
    if (N <= 0) {
        return 0.0;
    }
    double maxAvg = CalcStudentAverage(p[0]);
    for (int i = 1; i < N; i++) {
        double currentAvg = CalcStudentAverage(p[i]);
        if (currentAvg > maxAvg) {
            maxAvg = currentAvg;
        }
    }
    return maxAvg;
}

double CalcGoodPhysicsPercent(const Student* p, const int N) {
    if (N <= 0) {
        return 0.0;
    }
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (p[i].fizyka == 5 || p[i].fizyka == 4) {
            count++;
        }
    }
    return (static_cast<double>(count) / N) * 100.0;
}

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    int N;
    cout << "Введіть кількість студентів: ";
    cin >> N;

    if (N <= 0) {
        cout << "Кількість студентів має бути додатним числом!" << endl;
        return 1;
    }

    Student* p = new Student[N];

    Create(p, N);
    PrintTable(p, N);

    double maxAvg = FindMaxAverageGrade(p, N);
    double physPercent = CalcGoodPhysicsPercent(p, N);

    cout << fixed << setprecision(2);
    cout << "\n1. Найбільший середній бал серед студентів: " << maxAvg << endl;
    cout << "2. Процент студентів, які отримали з фізики оцінки \"5\" або \"4\": "
        << physPercent << "%" << endl;

    delete[] p;
    return 0;
}