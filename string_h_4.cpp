#include "DateFinder2_stringh.h"

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

                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                const char* current_month_name = months[tm.tm_mon];
                char temp[100];
                int written = sprintf(temp, "%02d %s %04d %02d:%02d:%02d",
                    tm.tm_mday, current_month_name, tm.tm_year + 1900,
                    tm.tm_hour, tm.tm_min, tm.tm_sec);

                if (j + written >= 2048) {
                    fprintf(stderr, "Error: Buffer size exceeded.\n");
                    result[j] = '\0';
                    return;
                }

                memcpy(&result[j], temp, written);
                j += written;
                i += 10;
                continue;
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

                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                const char* current_month_name = months[tm.tm_mon];
                char temp[100];
                int written = sprintf(temp, "%02d %s %04d %02d:%02d:%02d",
                    tm.tm_mday, current_month_name, tm.tm_year + 1900,
                    tm.tm_hour, tm.tm_min, tm.tm_sec);

                if (j + written >= 2048) {
                    fprintf(stderr, "Error: Buffer size exceeded.\n");
                    result[j] = '\0';
                    return;
                }

                memcpy(&result[j], temp, written);
                j += written;
                i += 10;
                continue;
            }

            if (i + 7 < len &&
                is_digit_char(line[i+1]) &&
                is_separator(line[i+2]) &&
                is_digit_char(line[i+3]) &&
                is_digit_char(line[i+4]) &&
                is_separator(line[i+5]) &&
                is_digit_char(line[i+6]) &&
                is_digit_char(line[i+7])) {

                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                const char* current_month_name = months[tm.tm_mon];
                char temp[100];
                int written = sprintf(temp, "%02d %s %04d %02d:%02d:%02d",
                    tm.tm_mday, current_month_name, tm.tm_year + 1900,
                    tm.tm_hour, tm.tm_min, tm.tm_sec);

                if (j + written >= 2048) {
                    fprintf(stderr, "Error: Buffer size exceeded.\n");
                    result[j] = '\0';
                    return;
                }

                memcpy(&result[j], temp, written);
                j += written;
                i += 8;
                continue;
            }
        }

        result[j++] = line[i++];

        if (j < 2048) {
            result[j] = '\0';
        } else {
            result[2047] = '\0';
            fprintf(stderr, "Warning: Output truncated.\n");
        }
    }
}

void printer(FILE* inputFile) {
    FILE* outputFile = fopen("string_h_4.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error: Unable to open output file.\n");
        return;
    }

    const int MAX_LINE_LENGTH = 1024;
    const int MAX_REPLACED_LINE_LENGTH = 2048;

    char line[MAX_LINE_LENGTH];
    char final_line[MAX_REPLACED_LINE_LENGTH];

    while (fgets(line, sizeof(line), inputFile)) {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }

        date_finder(line, final_line);
        printf("%s\n", final_line);
        fprintf(outputFile, "%s\n", final_line);
    }

    fclose(outputFile);
}

void file_opener(const char* textfile) {
    FILE* inputFile = fopen(textfile, "r");
    if (inputFile != NULL) {
        printer(inputFile);
        fclose(inputFile);
    } else {
        fprintf(stderr, "Error: Unable to open file.\n");
    }
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
