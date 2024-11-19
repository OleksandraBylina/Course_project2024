#include "HyperlinkFinder_string.h"

using namespace std;

int* hyperlink_ending_finder(const std::string& line, int* massive_of_beginnings, int count) {
    int* massive_of_endings = new int[count];

    for (int i = 0; i < count; ++i) {
        size_t pos = line.find(" ", massive_of_beginnings[i]);
        if (pos == string::npos) {
            pos = line.length();
        }
        while (pos > massive_of_beginnings[i] && (line[pos - 1] == ',' || line[pos - 1] == ';' || line[pos - 1] == ':' || line[pos - 1] == '.')) {
            --pos;
        }
        massive_of_endings[i] = static_cast<int>(pos);
    }

    return massive_of_endings;
}

int* hyperlink_beginning_finder(const string& line, int& count) {
    string types[] = {"https://", "http://", "www.", "ftp://"};
    int* massive_of_indexes = new int[line.length()];
    count = 0;

    for (int i = 0; i < sizeof(types) / sizeof(types[0]); ++i) {
        size_t position_of_beginning = 0;

        while ((position_of_beginning = line.find(types[i], position_of_beginning)) != string::npos) {
            massive_of_indexes[count++] = static_cast<int>(position_of_beginning);
            position_of_beginning += types[i].length();
        }
    }
    return massive_of_indexes;
}

int* end_of_word_finder(const string& line, int& count) {
    int beginning_count = 0;
    int* beginnings = hyperlink_beginning_finder(line, beginning_count);
    int* massive_of_word_endings = new int[beginning_count];

    for (int i = 0; i < beginning_count; i++) {
        int e = beginnings[i] - 1;
        while (e >= 0) {
            if (!isspace(line[e]) && line[e] != ',' && line[e] != ';' && line[e] != ':' && line[e] != '.') {
                massive_of_word_endings[i] = e;
                break;
            }
            --e;
        }
    }

    delete[] beginnings;
    count = beginning_count;
    return massive_of_word_endings;
}

int* begin_of_word_finder(const string& line, int& count) {
    int beginning_count = count;
    int* endings = end_of_word_finder(line, beginning_count);
    int* massive_of_word_beginnings = new int[beginning_count];

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

    delete[] endings;
    return massive_of_word_beginnings;
}

void printer(ifstream& inputFile) {
    string line;
    while (getline(inputFile, line)) {
        int beginning_count = 0;
        int* beginning_of_the_word = begin_of_word_finder(line, beginning_count);
        int* beginnings = hyperlink_beginning_finder(line, beginning_count);
        int* endings = hyperlink_ending_finder(line, beginnings, beginning_count);

        for (int i = 0; i < beginning_count; ++i) {
            string final_line = line.substr(beginning_of_the_word[i], endings[i] - beginning_of_the_word[i]);
            if (final_line != ""){
                cout << final_line << endl;
            }
        }

        delete[] beginnings;
        delete[] endings;
        delete[] beginning_of_the_word;
    }
}

void file_opener(const string& textfile) {
    ifstream inputFile(textfile);
    if (inputFile.is_open()) {
        printer(inputFile);
        inputFile.close();
    } else {
        cerr << "Failed to open file: " << textfile << endl;
    }
}

int main() {
    file_opener("textfile.txt");
    return 0;
}
