#include "NumberFinder_stringh.h"

float string_to_float(const char* str) {
    return atof(str);
}

void format_number(char* buffer, float number) {
    sprintf(buffer, "%.4f", number);
}

void punkt_number(const char* num, char* buffer) {
    float number = string_to_float(num);
    format_number(buffer, number);
}

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

int is_surrounded_by_letters(const char* line, int start, int end) {
    return (start > 0 && isalpha(line[start - 1])) || (end < strlen(line) && isalpha(line[end]));
}

void skip_date(const char* line, int* i) {
    while (line[*i] && (isdigit(line[*i]) || line[*i] == '/' || line[*i] == '.')) {
        (*i)++;
    }
}

void skip_time(const char* line, int* i) {
    while (line[*i] && (isdigit(line[*i]) || line[*i] == ':')) {
        (*i)++;
    }
}

void number_finder(const char* line, char* result) {
    char temp[100];
    char number[100];
    int i = 0;
    int len = strlen(line);
    int result_index = 0;

    while (i < len) {
        if (isdigit(line[i]) || (line[i] == '-' && i + 1 < len && isdigit(line[i + 1]))) {
            int start_index = i;
            int number_index = 0;
            if (line[i] == '-') {
                number[number_index++] = line[i++];
            }
            while (i < len && (isdigit(line[i]) || line[i] == '.' || line[i] == ',' || line[i] == 'e' || line[i] == 'E')) {
                number[number_index++] = line[i++];
            }
            number[number_index] = '\0';

            if (line[i] == '/' && isdigit(line[i + 1])) {
                skip_date(line, &i);
               
                for (int j = start_index; j < i; ++j) {
                    result[result_index++] = line[j];
                }
                continue;
            } else if (line[i] == ':' && isdigit(line[i + 1])) {
                skip_time(line, &i);
                for (int j = start_index; j < i; ++j) {
                    result[result_index++] = line[j];
                }
                continue;
            }

            if (strchr(number, '.') != NULL) {
                punkt_number(number, temp);
            } else if (strchr(number, ',') != NULL) {
                comma_number(number, temp);
            } else if (strchr(number, 'e') != NULL || strchr(number, 'E') != NULL) {
                e_number(number, temp);
            } else {
                sprintf(temp, "%.4f", string_to_float(number));
            }

            if (!is_surrounded_by_letters(line, start_index, i)) {
                for (int j = 0; temp[j] != '\0'; ++j) {
                    result[result_index++] = temp[j];
                }
            } else {
                for (int j = start_index; j < i; ++j) {
                    result[result_index++] = line[j];
                }
            }
        } else {
            result[result_index++] = line[i++];
        }
    }
    result[result_index] = '\0';
}

void file_opener(const char* textfile) {
    FILE* file = fopen(textfile, "r");
    FILE* outputFile = fopen("string_h_3.txt", "w");
    if (file == NULL || outputFile == NULL) {
        fprintf(stderr, "Error: Could not open file.\n");
        return;
    }

    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        char result[1000];
        number_finder(line, result);
        printf("%s\n", result);
        fprintf(outputFile, "%s\n", result);
    }

    fclose(file);
    fclose(outputFile);
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    file_opener("textfile.txt");
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time: %.6f s\n", cpu_time_used);

    return 0;
}
