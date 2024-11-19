#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

void hyperlink_finder(const string& line) {
    regex pattern(R"(\b(\w+)\b([^\S\n]*[[:punct:]\s]*)(https://[^\s]+[a-zA-Z0-9][a-zA-Z0-9]|http://[^\s]+[a-zA-Z0-9]|ftp\.[^\s]+|www\.[^\s]+[a-zA-Z0-9]))");
    smatch match;
    string::const_iterator first_pos = line.cbegin();
    while (regex_search(first_pos, line.cend(), match, pattern)) {
        cout << match[1] << match[2] << match[3] << endl;
        first_pos = match.suffix().first;
    }
}

void printer(ifstream& inputFile) {
    string line;
    while (getline(inputFile, line)) {
        hyperlink_finder(line);
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
