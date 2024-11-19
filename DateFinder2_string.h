#ifndef DATE_FINDER_STRING_H
#define DATE_FINDER_STRING_H

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

/**
 * @brief Масив назв місяців англійською.
 *
 * Містить назви місяців від "January" до "December".
 */
extern std::string months[];

/**
 * @brief Перевіряє, чи всі символи у рядку є цифрами.
 *
 * Проходить по кожному символу рядка і перевіряє, чи є він цифрою.
 *
 * @param str Рядок для перевірки.
 * @return true, якщо всі символи є цифрами, і false в іншому випадку.
 */
bool is_digits(const std::string& str);

/**
 * @brief Перевіряє, чи є рядок роком.
 *
 * Рядок вважається роком, якщо його довжина 2 або 4 символи і всі символи є цифрами.
 *
 * @param part Рядок для перевірки.
 * @return true, якщо рядок є роком, і false в іншому випадку.
 */
bool is_year(const std::string& part);

/**
 * @brief Перевіряє, чи є рядок місяцем або днем.
 *
 * Рядок вважається місяцем або днем, якщо його довжина 2 символи і всі символи є цифрами.
 *
 * @param part Рядок для перевірки.
 * @return true, якщо рядок є місяцем або днем, і false в іншому випадку.
 */
bool is_month_or_day(const std::string& part);

/**
 * @brief Перетворює номер місяця у назву місяця.
 *
 * Використовує масив `months`, щоб перетворити числовий номер місяця (1-12)
 * у його текстове представлення. Повертає пустий рядок для некоректних номерів.
 *
 * @param month Рядок із номером місяця.
 * @return Назва місяця або пустий рядок для некоректного номера.
 */
std::string month_to_name(const std::string& month);

/**
 * @brief Отримує поточну дату та час у форматі "YYYY Month DD HH:MM:SS".
 *
 * Використовує функції `time` і `localtime` для отримання поточного часу.
 *
 * @return Рядок із поточною датою та часом.
 */
std::string get_current_datetime();

/**
 * @brief Знаходить дати у рядку та замінює їх на поточну дату і час.
 *
 * Аналізує рядок для знаходження дат у форматах:
 * - YYYY/MM/DD або YYYY.MM.DD
 * - DD/MM/YYYY або DD.MM.YYYY
 * - DD/MM/YY або DD.MM.YY
 *
 * Замінює знайдені дати на поточну дату і час у форматі "YYYY Month DD HH:MM:SS".
 *
 * @param line Рядок для аналізу.
 * @param count Змінна, що зберігає кількість знайдених дат.
 * @return Рядок із заміненими датами.
 */
std::string date_finder(const std::string& line, int& count);

/**
 * @brief Зчитує рядки з файлу, обробляє дати та виводить результат.
 *
 * Зчитує кожен рядок із файлу, передає його у функцію `date_finder` для обробки дат,
 * і виводить оброблений рядок у консоль.
 *
 * @param inputFile Посилання на відкритий файл для читання.
 */
void printer(std::ifstream& inputFile);

/**
 * @brief Відкриває текстовий файл для читання та обробляє його.
 *
 * Перевіряє, чи файл відкрився успішно. У разі успіху передає файл у функцію `printer`.
 * У разі невдачі виводить повідомлення про помилку.
 *
 * @param textfile Ім'я текстового файлу.
 */
void file_opener(const std::string& textfile);

#endif // DATE_FINDER_STRING_H
