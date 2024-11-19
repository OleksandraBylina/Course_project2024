#include "DateFinder_string.h"

using namespace std;


string months[] = {"January", "February", "March", "April", "May", "June",
                   "July", "August", "September", "October", "November", "December"};


bool is_digits(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool is_year(const string& part) {
    return (part.length() == 4 || part.length() == 2) && is_digits(part);
}

bool is_month_or_day(const string& part) {
    return part.length() == 2 && is_digits(part);
}


string month_to_name(const string& month) {
    int month_number = stoi(month);
    if (month_number >= 1 && month_number <= 12) {
        return months[month_number - 1];
    }
    return "";
}

string date_finder(const string& line, int& count) {
    string* massive_of_dates = new string[line.length()];
    int* massive_of_lengthes = new int[line.length()];
    int* massive_of_positions = new int[line.length()];
    count = 0;
    int i = 0;

    while (i < line.length()) {
        string date = "";
        int start_index = i;

        if (isdigit(line[i])) {
            string part1, part2, part3;
            int pos = i;

            while (pos < line.length() && isdigit(line[pos])) {
                part1 += line[pos++];
            }

            if (pos < line.length() && (line[pos] == '/' || line[pos] == '.')) {
                char separator = line[pos++];
                while (pos < line.length() && isdigit(line[pos])) {
                    part2 += line[pos++];
                }

                if (pos < line.length() && line[pos] == separator) {
                    pos++;
                    while (pos < line.length() && isdigit(line[pos])) {
                        part3 += line[pos++];
                    }

                    if ((is_year(part1) && is_month_or_day(part2) && is_month_or_day(part3)) ||
                        (is_month_or_day(part1) && is_month_or_day(part2) && is_year(part3))) {
                        string year, month_name, day;
                        if (is_year(part1)) {
                            year = part1;
                            month_name = month_to_name(part2);
                            day = part3;
                        } else {
                            year = part3;
                            month_name = month_to_name(part2);
                            day = part1;
                        }
                        date = year + " " + month_name + " " + day;
                    }
                }
            }

            if (!date.empty()) {
                massive_of_dates[count] = date;
                massive_of_positions[count] = start_index;
                massive_of_lengthes[count] = pos - start_index;
                count++;
                i = pos;
            } else {
                ++i;
            }
        } else {
            ++i;
        }
    }

    string result = line;
    for (int j = count - 1; j >= 0; --j) {
        result.replace(massive_of_positions[j], massive_of_lengthes[j], massive_of_dates[j]);
    }

    delete[] massive_of_dates;
    delete[] massive_of_lengthes;
    delete[] massive_of_positions;

    return result;
}

void printer(ifstream& inputFile) {
    string line;
    while (getline(inputFile, line)) {
        int count = 0;
        string final_line = date_finder(line, count);
        cout << final_line << endl;
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