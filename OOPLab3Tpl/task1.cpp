#include <iostream>
#include <string>
#include <iomanip>


class Date {
private:
    int day;
    int month;
    int year;

    // Перевірка правильності дати
    bool isValidDate(int d, int m, int y) const {
        if (m < 1 || m > 12)
            return false;

        int daysInMonth;
        switch (m) {
            case 2: // Лютий
                // Перевірка на високосний рік
                if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
                    daysInMonth = 29;
                else
                    daysInMonth = 28;
                break;
            case 4: case 6: case 9: case 11: // Квітень, червень, вересень, листопад
                daysInMonth = 30;
                break;
            default: // Решта місяців мають 31 день
                daysInMonth = 31;
                break;
        }

        return (d >= 1 && d <= daysInMonth);
    }

    // Отримання назви місяця українською
    std::string getMonthName() const {
        std::string monthNames[] = {"", "січня", "лютого", "березня", "квітня", 
                                  "травня", "червня", "липня", "серпня", 
                                  "вересня", "жовтня", "листопада", "грудня"};
        return monthNames[month];
    }

public:
    // Конструктор за замовчуванням
    Date() : day(1), month(1), year(2000) {}

    // Конструктор з параметрами
    Date(int d, int m, int y) {
        if (isValidDate(d, m, y)) {
            day = d;
            month = m;
            year = y;
        } else {
            std::cout << "Некоректна дата! Встановлено значення за замовчуванням.\n";
            day = 1;
            month = 1;
            year = 2000;
        }
    }

    // Конструктор копіювання
    Date(const Date& other) : day(other.day), month(other.month), year(other.year) {}

    // Функції встановлення значень
    bool setDay(int d) {
        if (isValidDate(d, month, year)) {
            day = d;
            return true;
        }
        return false;
    }

    bool setMonth(int m) {
        if (isValidDate(day, m, year)) {
            month = m;
            return true;
        }
        return false;
    }

    bool setYear(int y) {
        if (isValidDate(day, month, y)) {
            year = y;
            return true;
        }
        return false;
    }

    // Функція встановлення всієї дати
    bool setDate(int d, int m, int y) {
        if (isValidDate(d, m, y)) {
            day = d;
            month = m;
            year = y;
            return true;
        }
        return false;
    }

    // Функції отримання значень
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    // Функція друку у форматі "5 січня 2019 року"
    void printFormatted() const {
        std::cout << day << " " << getMonthName() << " " << year << " року" << std::endl;
    }

    // Функція друку у форматі "05.01.2019"
    void printNumeric() const {
        std::cout << std::setfill('0') << std::setw(2) << day << "."
                  << std::setfill('0') << std::setw(2) << month << "."
                  << year << std::endl;
    }
};

// Програма тестування класу Date
int main() {
    // Тестування конструкторів
    std::cout << "Тестування конструкторів:\n";
    Date date1; // Конструктор за замовчуванням
    std::cout << "date1 (за замовчуванням): ";
    date1.printFormatted();
    date1.printNumeric();

     Date date2(15, 3, 2023); // Конструктор з параметрами
    std::cout << "date2 (з параметрами): ";
    date2.printFormatted();
    date2.printNumeric();

    Date date3(31, 4, 2022); // Некоректна дата
    std::cout << "date3 (некоректна дата): ";
    date3.printFormatted();
    date3.printNumeric();

    Date date4(date2); // Конструктор копіювання
    std::cout << "date4 (копія date2): ";
    date4.printFormatted();
    date4.printNumeric();

    // Тестування функцій встановлення і отримання
    std::cout << "\nТестування функцій встановлення і отримання:\n";
    Date date5;
    date5.setDay(25);
    date5.setMonth(12);
    date5.setYear(2024);
    std::cout << "date5 після встановлення значень: ";
    date5.printFormatted();
    date5.printNumeric();

    std::cout << "Отримані значення date5: день = " << date5.getDay() 
              << ", місяць = " << date5.getMonth() 
              << ", рік = " << date5.getYear() << std::endl;

    // Тестування встановлення некоректних значень
    std::cout << "\nТестування встановлення некоректних значень:\n";
    Date date6(1, 1, 2020);
    std::cout << "date6 початкова: ";
    date6.printFormatted();
    
    bool result = date6.setDay(32); // Некоректний день
    std::cout << "Встановлення дня 32: " << (result ? "успішно" : "помилка") << std::endl;
    std::cout << "date6 після спроби встановлення некоректного дня: ";
    date6.printFormatted();

    result = date6.setMonth(13); // Некоректний місяць
    std::cout << "Встановлення місяця 13: " << (result ? "успішно" : "помилка") << std::endl;
    std::cout << "date6 після спроби встановлення некоректного місяця: ";
    date6.printFormatted();

    // Тестування встановлення повної дати
    std::cout << "\nТестування встановлення повної дати:\n";
    Date date7;
    result = date7.setDate(29, 2, 2024); // Високосний рік
    std::cout << "Встановлення дати 29.02.2024: " << (result ? "успішно" : "помилка") << std::endl;
    date7.printFormatted();
    date7.printNumeric();

    result = date7.setDate(29, 2, 2023); // Не високосний рік
    std::cout << "Встановлення дати 29.02.2023: " << (result ? "успішно" : "помилка") << std::endl;
    date7.printFormatted();
    date7.printNumeric();

    return 0;
}