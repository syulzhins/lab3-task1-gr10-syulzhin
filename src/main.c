#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 8
#define MAX_NAME_LENGTH 50

// Структура для хранения данных о студентах
typedef struct {
    char Name[MAX_NAME_LENGTH]; // Фамилия и инициалы
    struct {
        int year;
        int month;
        int day;
    } DAT; // Дата поступления
    int SES[3]; // Успеваемость
} GROUP;

// Функция для проверки корректности даты
int is_valid_date(int year, int month, int day) {
    if (year < 1900 || year > 2023) return 0; // Проверка года
    if (month < 1 || month > 12) return 0; // Проверка месяца

    // Проверка дня в зависимости от месяца
    if (month == 2) {
        // Учитываем високосный год
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day < 1 || day > 29) return 0; // Февраль в високосный год
        } else {
            if (day < 1 || day > 28) return 0; // Февраль в невисокосный год
        }
    } else {
        // Для других месяцев
        int days_in_month[] = { 31, 30, 31, 30, 31, 31, 31, 31, 30, 31, 30, 31 };
        if (day < 1 || day > days_in_month[month - 1]) return 0;
    }
    return 1; // Дата корректная
}