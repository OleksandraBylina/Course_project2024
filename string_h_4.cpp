#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Добавляем библиотеку для работы с датой и временем

// Определение массива названий месяцев
const char* months[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

// Функция для преобразования номера месяца в название месяца
const char* month_to_name(const char* month_str) {
    int month_number = atoi(month_str);
    if (month_number >= 1 && month_number <= 12) {
        return months[month_number - 1];
    }
    return "";
}

// Функция для проверки, является ли символ разделителем ('/' или '.')
int is_separator(char c) {
    return c == '/' || c == '.';
}

// Функция для проверки, является ли символ цифрой
int is_digit_char(char c) {
    return c >= '0' && c <= '9';
}

// Функция для преобразования двухзначного года в четырехзначный
void convert_two_digit_year(const char* year_two_digits, char* year_full) {
    // Предполагаем, что все двухзначные годы относятся к 2000-м
    sprintf(year_full, "20%s", year_two_digits);
    year_full[4] = '\0'; // Обеспечиваем нулевую терминальность
}

// Функция для поиска и замены дат в строке
void date_finder(const char* line, char* result) {
    int i = 0; // Индекс для исходной строки
    int j = 0; // Индекс для результирующей строки
    int len = strlen(line);

    while (i < len) {
        if (is_digit_char(line[i])) {
            // Проверка на формат YYYY/MM/DD или YYYY.MM.DD (10 символов)
            if (i + 9 < len &&
                is_digit_char(line[i+1]) &&
                is_digit_char(line[i+2]) &&
                is_digit_char(line[i+3]) &&
                is_separator(line[i+4]) &&
                is_digit_char(line[i+5]) &&
                is_digit_char(line[i+6]) &&
                is_separator(line[i+7]) &&
                is_digit_char(line[i+8]) &&
                is_digit_char(line[i+9])) {

                // Получаем текущую дату и время
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                // Форматируем дату и время
                const char* current_month_name = months[tm.tm_mon];
                char temp[100];
                int written = sprintf(temp, "%02d %s %04d %02d:%02d:%02d",
                    tm.tm_mday, current_month_name, tm.tm_year + 1900,
                    tm.tm_hour, tm.tm_min, tm.tm_sec);

                // Проверка на переполнение буфера
                if (j + written >= 2048) {
                    fprintf(stderr, "Ошибка: превышен размер результирующего буфера.\n");
                    result[j] = '\0';
                    return;
                }

                // Копируем отформатированную строку в результирующий массив
                memcpy(&result[j], temp, written);
                j += written;
                i += 10; // Пропускаем обработанную дату
                continue;
            }

            // Проверка на формат DD/MM/YYYY или DD.MM.YYYY (10 символов)
            if (i + 9 < len &&
                is_digit_char(line[i+1]) &&
                is_separator(line[i+2]) &&
                is_digit_char(line[i+3]) &&
                is_digit_char(line[i+4]) &&
                is_separator(line[i+5]) &&
                is_digit_char(line[i+6]) &&
                is_digit_char(line[i+7]) &&
                is_digit_char(line[i+8]) &&
                is_digit_char(line[i+9])) {

                // Получаем текущую дату и время
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                // Форматируем дату и время
                const char* current_month_name = months[tm.tm_mon];
                char temp[100];
                int written = sprintf(temp, "%02d %s %04d %02d:%02d:%02d",
                    tm.tm_mday, current_month_name, tm.tm_year + 1900,
                    tm.tm_hour, tm.tm_min, tm.tm_sec);

                // Проверка на переполнение буфера
                if (j + written >= 2048) {
                    fprintf(stderr, "Ошибка: превышен размер результирующего буфера.\n");
                    result[j] = '\0';
                    return;
                }

                // Копируем отформатированную строку в результирующий массив
                memcpy(&result[j], temp, written);
                j += written;
                i += 10; // Пропускаем обработанную дату
                continue;
            }

            // Проверка на формат DD/MM/YY или DD.MM.YY (8 символов)
            if (i + 7 < len &&
                is_digit_char(line[i+1]) &&
                is_separator(line[i+2]) &&
                is_digit_char(line[i+3]) &&
                is_digit_char(line[i+4]) &&
                is_separator(line[i+5]) &&
                is_digit_char(line[i+6]) &&
                is_digit_char(line[i+7])) {

                // Получаем текущую дату и время
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                // Форматируем дату и время
                const char* current_month_name = months[tm.tm_mon];
                char temp[100];
                int written = sprintf(temp, "%02d %s %04d %02d:%02d:%02d",
                    tm.tm_mday, current_month_name, tm.tm_year + 1900,
                    tm.tm_hour, tm.tm_min, tm.tm_sec);

                // Проверка на переполнение буфера
                if (j + written >= 2048) {
                    fprintf(stderr, "Ошибка: превышен размер результирующего буфера.\n");
                    result[j] = '\0';
                    return;
                }

                // Копируем отформатированную строку в результирующий массив
                memcpy(&result[j], temp, written);
                j += written;
                i += 8; // Пропускаем обработанную дату
                continue;
            }
        }

        // Если не нашли дату, копируем текущий символ
        result[j++] = line[i++];

        // Завершаем результирующую строку
        if (j < 2048) {
            result[j] = '\0';
        } else {
            // Если j достигли предела буфера, гарантируем завершение строки
            result[2047] = '\0';
            fprintf(stderr, "Предупреждение: результирующая строка была обрезана.\n");
        }
    }
}

// Функция для обработки файла и вывода результата
void printer(FILE* inputFile) {
    // Определяем максимальную длину строки
    const int MAX_LINE_LENGTH = 1024;
    const int MAX_REPLACED_LINE_LENGTH = 2048;

    char line[MAX_LINE_LENGTH];
    char final_line[MAX_REPLACED_LINE_LENGTH];

    while (fgets(line, sizeof(line), inputFile)) {
        // Удаляем символ новой строки, если он есть
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }

        date_finder(line, final_line);
        printf("%s\n", final_line);
    }
}

// Функция для открытия файла
void file_opener(const char* textfile) {
    FILE* inputFile = fopen(textfile, "r");
    if (inputFile != NULL) {
        printer(inputFile);
        fclose(inputFile);
    } else {
        fprintf(stderr, "Failed to open file: %s\n", textfile);
    }
}

int main() {
    file_opener("textfile.txt");
    return 0;
}
