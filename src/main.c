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

// Функция для удаления букв на четных позициях и подсчета количества удаленных букв
int remove_even_positions(char *str) {
    int length = strlen(str);
    int count_removed = 0;
    char temp[length + 1]; // Временный массив для хранения новой строки
    int j = 0;

    for (int i = 0; i < length; i++) {
        if (i % 2 != 0) { // Оставляем буквы на нечетных позициях
            temp[j++] = str[i];
        } else {
            count_removed++; // Увеличиваем счетчик удаленных букв
        }
    }
    temp[j] = '\0'; // Завершаем строку

    strcpy(str, temp); // Копируем измененную строку обратно
    return count_removed;
}
// Функция для сортировки студентов по возрастанию поля SES
void sort_students(GROUP students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (students[i].SES[0] > students[j].SES[0]) {
                GROUP temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

// Функция для вывода студентов, возраст которых не превышает 20 лет на 01.12.2020
void print_young_students(GROUP students[], int n) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        int age = 2020 - students[i].DAT.year;
        if (age < 20 || (age == 20 && (students[i].DAT.month < 12 || (students[i].DAT.month == 12 && students[i].DAT.day == 1)))) {
            printf("Студент: %s, Дата поступления: %04d-%02d-%02d\n", students[i].Name, students[i].DAT.year, students[i].DAT.month, students[i].DAT.day);
            found = 1;
        }
    }
    if (!found) {
        printf("Студентов в возрасте до 20 лет нет.\n");
    }
}