#ifndef DATE_FINDER_STRING_H
#define DATE_FINDER_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/**
 * @brief Масив з назвами місяців англійською мовою.
 */
extern const char* months[];

/**
 * @brief Перетворює номер місяця на його назву.
 *
 * @param month_str Номер місяця у вигляді рядка (наприклад, "01").
 * @return Назва місяця (наприклад, "January") або порожній рядок, якщо номер некоректний.
 */
const char* month_to_name(const char* month_str);

/**
 * @brief Перевіряє, чи є символ роздільником ('/' або '.').
 *
 * @param c Символ для перевірки.
 * @return 1, якщо символ є роздільником, 0 в іншому випадку.
 */
int is_separator(char c);

/**
 * @brief Перевіряє, чи є символ цифрою.
 *
 * @param c Символ для перевірки.
 * @return 1, якщо символ є цифрою, 0 в іншому випадку.
 */
int is_digit_char(char c);

/**
 * @brief Перетворює двозначний рік на чотиризначний (наприклад, "23" -> "2023").
 *
 * @param year_two_digits Двозначний рік у вигляді рядка.
 * @param year_full Масив для збереження чотиризначного року.
 */
void convert_two_digit_year(const char* year_two_digits, char* year_full);

/**
 * @brief Знаходить дати у рядку та замінює їх на формат "DD Month YYYY".
 *
 * Підтримувані формати:
 * - YYYY/MM/DD
 * - DD/MM/YYYY
 * - DD/MM/YY
 *
 * @param line Вхідний рядок.
 * @param result Результуючий рядок із заміненими датами.
 */
void date_finder(const char* line, char* result);

/**
 * @brief Зчитує файл рядок за рядком і замінює дати.
 *
 * Обробляє кожен рядок у файлі, знаходить дати та змінює їх на формат "DD Month YYYY".
 * Виводить оброблені рядки в консоль.
 *
 * @param inputFile Посилання на файл для читання.
 */
void printer(FILE* inputFile);

/**
 * @brief Відкриває файл для обробки дат.
 *
 * Здійснює спробу відкрити текстовий файл. Якщо файл відкрито успішно,
 * передає його у функцію `printer` для обробки. У разі невдачі виводить повідомлення про помилку.
 *
 * @param textfile Ім'я текстового файлу для обробки.
 */
void file_opener(const char* textfile);

#endif // DATE_FINDER_STRING_H
