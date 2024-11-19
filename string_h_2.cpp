#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* months[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};


const char* month_to_name(const char* month_str) {
    int month_number = atoi(month_str);
    if (month_number >= 1 && month_number <= 12) {
        return months[month_number - 1];
    }
    return "";
}


int is_separator(char c) {
    return c == '/' || c == '.';
}


int is_digit_char(char c) {
    return c >= '0' && c <= '9';
}


void convert_two_digit_year(const char* year_two_digits, char* year_full) {
    
    sprintf(year_full, "20%s", year_two_digits);
    year_full[4] = '\0'; 
}


void date_finder(const char* line, char* result) {
    int i = 0; 
    int j = 0; 
    int len = strlen(line);

    while (i < len) {
        if (is_digit_char(line[i])) {
            
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

                
                char year[5], month[3], day[3];
                strncpy(year, &line[i], 4);
                year[4] = '\0';
                strncpy(month, &line[i+5], 2);
                month[2] = '\0';
                strncpy(day, &line[i+8], 2);
                day[2] = '\0';

                int month_num = atoi(month);
                int day_num = atoi(day);
                if (month_num >= 1 && month_num <= 12 && day_num >=1 && day_num <= 31) {
                    const char* month_name = month_to_name(month);
                    if (strlen(month_name) > 0) {
                        
                        char temp[100];
                        int written = sprintf(temp, "%s %s %s", day, month_name, year);

                        
                        if (j + written >= 2048) {
                            fprintf(stderr, "Mistake");
                            result[j] = '\0';
                            return;
                        }

                        
                        memcpy(&result[j], temp, written);
                        j += written;
                        i += 10; 
                        continue;
                    }
                }
            }

            
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

                
                char day[3], month[3], year[5];
                strncpy(day, &line[i], 2);
                day[2] = '\0';
                strncpy(month, &line[i+3], 2);
                month[2] = '\0';
                strncpy(year, &line[i+6], 4);
                year[4] = '\0';

                int month_num = atoi(month);
                int day_num = atoi(day);
                if (month_num >= 1 && month_num <= 12 && day_num >=1 && day_num <= 31) {
                    const char* month_name = month_to_name(month);
                    if (strlen(month_name) > 0) {
                        
                        char temp[100];
                        int written = sprintf(temp, "%s %s %s", day, month_name, year);

                        
                        if (j + written >= 2048) {
                            fprintf(stderr, "Mistake");
                            result[j] = '\0';
                            return;
                        }

                        
                        memcpy(&result[j], temp, written);
                        j += written;
                        i += 10; // Пропускаем обработанную дату
                        continue;
                    }
                }
            }

    
            if (i + 7 < len &&
                is_digit_char(line[i+1]) &&
                is_separator(line[i+2]) &&
                is_digit_char(line[i+3]) &&
                is_digit_char(line[i+4]) &&
                is_separator(line[i+5]) &&
                is_digit_char(line[i+6]) &&
                is_digit_char(line[i+7])) {

                
                char day[3], month[3], year_two_digits[3];
                strncpy(day, &line[i], 2);
                day[2] = '\0';
                strncpy(month, &line[i+3], 2);
                month[2] = '\0';
                strncpy(year_two_digits, &line[i+6], 2);
                year_two_digits[2] = '\0';

            
                char year_full[5];
                convert_two_digit_year(year_two_digits, year_full);
                year_full[4] = '\0'; 

                int month_num = atoi(month);
                int day_num = atoi(day);
                if (month_num >= 1 && month_num <= 12 && day_num >=1 && day_num <= 31) {
                    const char* month_name = month_to_name(month);
                    if (strlen(month_name) > 0) {
                        
                        char temp[100];
                        int written = sprintf(temp, "%s %s %s", day, month_name, year_full);

                        
                        if (j + written >= 2048) {
                            fprintf(stderr, "Mistake");
                            result[j] = '\0';
                            return;
                        }

                    
                        memcpy(&result[j], temp, written);
                        j += written;
                        i += 8; 
                        continue;
                    }
                }
            }
        }

        
        result[j++] = line[i++];

        
        if (j < 2048) {
            result[j] = '\0';
        } else {
            
            result[2047] = '\0';
            
        }
}
}

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
