#include "HyperlinkFinder_stringh.h"

#define MAX_LINE_LENGTH 1000

int* hyperlink_beginning_finder(const char* line, int* count);
int* hyperlink_ending_finder(const char* line, int* massive_of_beginnings, int count);
int* end_of_word_finder(const char* line, int* count);
int* begin_of_word_finder(const char* line, int* count);
void printer(FILE* inputFile);
void file_opener(const char* textfile);

int* hyperlink_beginning_finder(const char* line, int* count) {
    const char* types[] = {"https://", "http://", "www.", "ftp://"};
    int* massive_of_indexes = (int*)malloc(strlen(line) * sizeof(int));
    *count = 0;

    for (int i = 0; i < sizeof(types) / sizeof(types[0]); ++i) {
        const char* position_of_beginning = line;

        while ((position_of_beginning = strstr(position_of_beginning, types[i])) != NULL) {
            massive_of_indexes[(*count)++] = position_of_beginning - line;
            position_of_beginning += strlen(types[i]);
        }
    }
    return massive_of_indexes;
}

int* hyperlink_ending_finder(const char* line, int* massive_of_beginnings, int count) {
    int* massive_of_endings = (int*)malloc(count * sizeof(int));

    for (int i = 0; i < count; ++i) {
        const char* pos = strchr(line + massive_of_beginnings[i], ' ');
        if (pos == NULL) {
            pos = line + strlen(line);
        }
        massive_of_endings[i] = pos - line;
    }

    return massive_of_endings;
}

int* end_of_word_finder(const char* line, int* count) {
    int beginning_count = 0;
    int* beginnings = hyperlink_beginning_finder(line, &beginning_count);
    int* massive_of_word_endings = (int*)malloc(beginning_count * sizeof(int));

    for (int i = 0; i < beginning_count; ++i) {
        int e = beginnings[i] - 1;
        while (e >= 0) {
            if (!isspace(line[e]) && line[e] != ',' && line[e] != ';' && line[e] != ':' && line[e] != '.') {
                massive_of_word_endings[i] = e;
                break;
            }
            --e;
        }
    }

    free(beginnings);
    *count = beginning_count;
    return massive_of_word_endings;
}

int* begin_of_word_finder(const char* line, int* count) {
    int beginning_count = *count;
    int* endings = end_of_word_finder(line, &beginning_count);
    int* massive_of_word_beginnings = (int*)malloc(beginning_count * sizeof(int));

    for (int i = 0; i < beginning_count; i++) {
        int e = endings[i];
        while (e >= 0) {
            if (isspace(line[e]) || line[e] == ',' || line[e] == ';' || line[e] == ':' || line[e] == '.') {
                massive_of_word_beginnings[i] = e + 1;
                break;
            }
            --e;
        }
    }

    free(endings);
    return massive_of_word_beginnings;
}

void printer(FILE* inputFile) {
    FILE* outputFile = fopen("string_h_1.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Failed to open output file: string_h_1.txt\n");
        return;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, inputFile)) {
        int beginning_count = 0;
        int* beginning_of_the_word = begin_of_word_finder(line, &beginning_count);
        int* beginnings = hyperlink_beginning_finder(line, &beginning_count);
        int* endings = hyperlink_ending_finder(line, beginnings, beginning_count);

        for (int i = 0; i < beginning_count; ++i) {
            for (int j = beginning_of_the_word[i]; j < endings[i]; ++j) {
                putchar(line[j]);
                fputc(line[j], outputFile);
            }
            putchar('\n');
            fputc('\n', outputFile);
        }

        free(beginnings);
        free(endings);
        free(beginning_of_the_word);
    }
    fclose(outputFile);
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
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    file_opener("textfile.txt");
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time: %.6f seconds\n", cpu_time_used);

    return 0;
}
