#include "HyperlinkFinder_regex.h"
using namespace std;

void hyperlink_finder(const string& line, ofstream& outputFile) {
    regex pattern(R"(\b(\w+)\b([^\S\n]*[[:punct:]\s]*)(https://[^\s]+[a-zA-Z0-9][a-zA-Z0-9]|http://[^\s]+[a-zA-Z0-9]|ftp\.[^\s]+|www\.[^\s]+[a-zA-Z0-9]))");
    smatch match;
    string::const_iterator first_pos = line.cbegin();
    while (regex_search(first_pos, line.cend(), match, pattern)) {
        string result = match[1].str() + match[2].str() + match[3].str();
        cout << result << endl;
        outputFile << result << endl;
        first_pos = match.suffix().first;
    }
}

void printer(ifstream& inputFile) {
    ofstream outputFile("regex_1.txt");
    if (!outputFile.is_open()) {
        cerr << "Failed to open output file: regex_1.txt" << endl;
        return;
    }
    string line;
    while (getline(inputFile, line)) {
        hyperlink_finder(line, outputFile);
    }
    outputFile.close();
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

    auto start = std::chrono::high_resolution_clock::now();

    file_opener("textfile.txt");

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
