#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Преобразование строки в число с плавающей запятой
float string_to_float(const char* str) {
    return atof(str);
}

// Форматирование числа с четырьмя знаками после запятой в строку
void format_number(char* buffer, float number) {
    sprintf(buffer, "%.4f", number);
}

// Обработка числа с десятичной точкой
void punkt_number(const char* num, char* buffer) {
    float number = string_to_float(num);
    format_number(buffer, number);
}

// Обработка числа с запятой, заменяя её на точку
void comma_number(const char* num, char* buffer) {
    char temp[100];
    strcpy(temp, num);
    for (int i = 0; temp[i] != '\0'; ++i) {
        if (temp[i] == ',') {
            temp[i] = '.';
        }
    }
    float number = string_to_float(temp);
    format_number(buffer, number);
}

// Обработка числа с экспонентой
void e_number(const char* num, char* buffer) {
    char temp[100];
    strcpy(temp, num);
    for (int i = 0; temp[i] != '\0'; ++i) {
        if (temp[i] == 'E') {
            temp[i] = 'e';
        }
    }

    float number = string_to_float(temp);
    format_number(buffer, number);
}

// Проверка, окружено ли число буквами
int is_surrounded_by_letters(const char* line, int start, int end) {
    return (start > 0 && isalpha(line[start - 1])) || (end < strlen(line) && isalpha(line[end]));
}

// Пропуск даты в формате DD/MM/YYYY или DD.MM.YYYY
void skip_date(const char* line, int* i) {
    while (line[*i] && (isdigit(line[*i]) || line[*i] == '/' || line[*i] == '.')) {
        (*i)++;
    }
}

// Пропуск времени в формате HH:MM
void skip_time(const char* line, int* i) {
    while (line[*i] && (isdigit(line[*i]) || line[*i] == ':')) {
        (*i)++;
    }
}

// Поиск чисел и замена их на унифицированные форматы
void number_finder(char* line) {
    char result[1000];
    strcpy(result, line);
    char temp[100];
    char number[100];
    int i = 0;
    int len = strlen(line);
    int result_index = 0;

    while (i < len) {
        if (isdigit(line[i]) || (line[i] == '-' && i + 1 < len && isdigit(line[i + 1]))) {
            // Сохраняем начальную позицию числа
            int start_index = i;
            int number_index = 0;
            if (line[i] == '-') {
                number[number_index++] = line[i++];
            }
            while (i < len && (isdigit(line[i]) || line[i] == '.' || line[i] == ',' || line[i] == 'e' || line[i] == 'E')) {
                number[number_index++] = line[i++];
            }
            number[number_index] = '\0';

            // Игнорируем даты и время
            if (line[i] == '/' && isdigit(line[i + 1])) {
                skip_date(line, &i);
                continue;
            } else if (line[i] == ':' && isdigit(line[i + 1])) {
                skip_time(line, &i);
                continue;
            }

            // Унифицируем число
            if (strchr(number, '.') != NULL) {
                punkt_number(number, temp);
            } else if (strchr(number, ',') != NULL) {
                comma_number(number, temp);
            } else if (strchr(number, 'e') != NULL || strchr(number, 'E') != NULL) {
                e_number(number, temp);
            } else {
                sprintf(temp, "%.4f", string_to_float(number));
            }

            // Проверяем, окружено ли число буквами
            if (!is_surrounded_by_letters(line, start_index, i)) {
                // Копируем унифицированное число в результат
                for (int j = 0; temp[j] != '\0'; ++j) {
                    result[result_index++] = temp[j];
                }
            } else {
                // Если число окружено буквами, копируем оригинальное число
                for (int j = start_index; j < i; ++j) {
                    result[result_index++] = line[j];
                }
            }
        } else {
            result[result_index++] = line[i++];
        }
    }
    result[result_index] = '\0';
    printf("%s\n", result);
}


void file_opener(const char* textfile) {
    FILE* file = fopen(textfile, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", textfile);
        return;
    }

    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {
        number_finder(line);
    }

    fclose(file);
}

int main() {
    file_opener("textfile.txt");
    return 0;
}
