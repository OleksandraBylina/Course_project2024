
#ifndef NUMBERFINDER_H
#define NUMBERFINDER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <cmath>

// Оголошення функцій

std::string punkt_number(std::string num);
/**
 * @brief Форматує число з десятковою точкою у вигляді "0.0000".
 *
 * Використовує функцію `stof` з  для перетворення рядка в число з плаваючою точкою.
 * Використовує `ostringstream` та `setprecision` для встановлення формату "0.0000".
 *
 * @param num Рядок з числом, яке потрібно відформатувати.
 * @return Число у форматі з точністю до 4 знаків після коми.
 */

std::string comma_number(std::string num);
/**
 * @brief Замінює кому на крапку та форматує число до "0.0000".
 *
 * Знаходить кому у рядку та замінює її на крапку, після чого форматує як число з 4 знаками.
 *
 * @param num Рядок з числом з комою.
 * @return Відформатоване число з крапкою, у форматі "0.0000".
 */

std::string e_number(std::string num);
/**
 * @brief Обробляє числа з експоненційною нотацією ("E/e") і форматує їх у вигляді "0.0000".
 *
 * Замінює літеру "E" на "e", якщо потрібно. Розбиває число на основну та експонентну частини,
 * після чого форматує його у стандартний вигляд з точкою.
 *
 * @param num Рядок з числом в експоненційному форматі.
 * @return Число у форматі "0.0000".
 */

std::string number_unificator(const std::string& number);
/**
 * @brief Визначає тип числа (з крапкою, комою або експоненційне) та форматує його у "0.0000".
 *
 * Викликає відповідну функцію для обробки числа залежно від його виду.
 *
 * @param number Рядок з числом.
 * @return Уніфіковане число у форматі "0.0000".
 */

bool is_surrounded_by_letters(const std::string& line, int start, int end);
/**
 * @brief Перевіряє, чи оточене число літерами.
 *
 * Використовується для виключення випадків, коли числа є частинами слів.
 *
 * @param line Рядок, що містить число.
 * @param start Початкова позиція числа.
 * @param end Кінцева позиція числа.
 * @return Повертає true, якщо число оточене літерами.
 */

void skip_date(const std::string& line, int& i);
/**
 * @brief Пропускає формат дати у вигляді числа з роздільником "/".
 *
 * Зупиняється, коли закінчується частина дати.
 *
 * @param line Рядок для обробки.
 * @param i Індекс символу в рядку, що буде змінений.
 */

void skip_time(const std::string& line, int& i);
/**
 * @brief Пропускає формат часу у вигляді числа з роздільником ":".
 *
 * Зупиняється, коли закінчується частина часу.
 *
 * @param line Рядок для обробки.
 * @param i Індекс символу в рядку, що буде змінений.
 */

void process_exponential_part(const std::string& line, int& i, std::string& new_string);
/**
 * @brief Обробляє експоненційну частину числа.
 *
 * Додає символ "e" та знак (+/-) до числа для коректної обробки експоненти.
 *
 * @param line Рядок, що містить експоненційну частину.
 * @param i Індекс позиції "e" або "E".
 * @param new_string Рядок, куди додається частина експоненти.
 */

void add_number_if_valid(const std::string& line, int start_index, int i, std::string& new_string,
                         std::string* massive_of_numbers, int* massive_of_positions, int* massive_of_lengthes, int& count);
/**
 * @brief Додає число у масиви, якщо воно не є частиною слова.
 *
 * Виконує перевірку на відсутність літер біля числа і зберігає його в масивах для подальшої обробки.
 *
 * @param line Рядок для обробки.
 * @param start_index Початкова позиція числа.
 * @param i Поточна позиція в рядку.
 * @param new_string Зібране число.
 * @param massive_of_numbers Масив для збереження чисел.
 * @param massive_of_positions Масив для позицій чисел.
 * @param massive_of_lengthes Масив для довжин чисел.
 * @param count Лічильник чисел у масивах.
 */

std::string number_finder(const std::string& line, int& count);
/**
 * @brief Знаходить числа в рядку, перевіряє їх на різні формати і замінює на формат "0.0000".
 *
 * Створює масиви на купі `massive_of_numbers`, `massive_of_positions`, і `massive_of_lengthes` для зберігання чисел,
 * їхніх позицій і довжин у рядку. Лічильник `count` відслідковує кількість знайдених чисел.
 *
 * Основні етапи роботи:
 * - Ітерує по рядку, шукаючи числові значення, враховуючи можливі роздільники та експоненційні позначки.
 * - Перевіряє формат числа: десятковий (з крапкою або комою), експоненційний (з "e" або "E") або звичайний цілий.
 * - Враховує випадки з датами (формат з "/") та часом (формат з ":"), щоб уникнути їхньої обробки як числа.
 * - Кожне знайдене число перевіряється на наявність оточуючих літер і за необхідності додається у масиви для заміни.
 * - Замінює знайдені числа на уніфікований формат та додає в масив `massive_of_numbers`.
 * - Виконує цикл назад для заміни чисел у рядку `line` на уніфіковані версії, щоб зберегти коректні позиції.
 * - Звільняє пам’ять, виділену для динамічних масивів, щоб уникнути витоків пам’яті.
 *
 * @param line Рядок для обробки.
 * @param count Лічильник кількості знайдених чисел.
 * @return Рядок з числами у форматі "0.0000".
 */

void printer(std::ifstream& inputFile);
/**
 * @brief Читає рядки з файлу, замінює числа та виводить їх.
 *
 * Ініціалізує змінну `line` для кожного рядка з файлу. Викликає `number_finder`
 * для кожного рядка, щоб знайти і замінити числа на формат "0.0000" та виводить в
 * консоль змінений текст по рядках.
 *
 * @param inputFile Посилання на об'єкт ifstream для читання файлу.
 */

void file_opener(const std::string& textfile);
/**
 * @brief Відкриває файл і викликає функцію `printer` для обробки чисел.
 *
 * Відкриває текстовий файл, перевіряє успішність відкриття,
 * і передає його у функцію `printer` для подальшої обробки. Якщо файл не відкривається,
 * виводить повідомлення про помилку.
 *
 * @param textfile Ім'я або шлях до текстового файлу для обробки.
 */

#endif // NUMBERFINDER_H
