#include "DateFinder2_regex.h"

using namespace std;

string months[] = {"January", "February", "March", "April", "May", "June",
                   "July", "August", "September", "October", "November", "December"};

string month_to_name(const string& month) {
    int month_number = stoi(month);
    if (month_number >= 1 && month_number <= 12) {
        return months[month_number - 1];
    }
    return "";
}

string get_current_datetime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    int hour = ltm->tm_hour;
    int minute = ltm->tm_min;
    int second = ltm->tm_sec;
    string current_date = to_string(year) + " " + months[month - 1] + " " + to_string(day);
    string current_time = to_string(hour) + ":" +
                          (minute < 10 ? "0" : "") + to_string(minute) + ":" +
                          (second < 10 ? "0" : "") + to_string(second);
    return current_date + " " + current_time;
}

string format_date(const string& part1, const string& part2, const string& part3, bool year_first) {
    string year, month, day;
    if (year_first) {
        year = part1.length() == 2 ? "20" + part1 : part1;
        month = month_to_name(part2);
        day = part3;
    } else {
        day = part1;
        month = month_to_name(part2);
        year = part3.length() == 2 ? "20" + part3 : part3;
    }
    return day + " " + month + " " + year;
}

string date_finder(const string& line) {
    regex date_pattern(R"((\b(\d{2}|\d{4})[./](\d{2})[./](\d{2}|\d{4})\b))");
    smatch match;
    string result = line;
    string::const_iterator search_start = result.cbegin();
    while (regex_search(search_start, result.cend(), match, date_pattern)) {
        string current_datetime = get_current_datetime();
        size_t pos = match.position(0) + distance(result.cbegin(), search_start);
        result.replace(pos, match.length(0), current_datetime);
        search_start = result.cbegin() + pos + current_datetime.length();
    }
    return result;
}

void printer(ifstream& inputFile) {
    ofstream outputFile("regex_4.txt");
    if (!outputFile.is_open()) {
        cerr << "Failed to open output file: regex_4.txt" << endl;
        return;
    }
    string line;
    while (getline(inputFile, line)) {
        string final_line = date_finder(line);
        cout << final_line << endl;
        outputFile << final_line << endl;
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
