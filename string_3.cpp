#include "NumberFinder_string.h"

using namespace std;

string punkt_number(string num) {
    float number = stof(num);
    ostringstream out;
    out << fixed << setprecision(4) << number;
    return out.str();
}

string comma_number(string num) {
    int pos = num.find(',', 0);
    if (pos != string::npos) {
        num[pos] = '.';
    }
    float number = stof(num);
    ostringstream out;
    out << fixed << setprecision(4) << number;
    return out.str();
}

string e_number(string num) {
    int Epos = num.find('E', 0);
    if (Epos != string::npos) {
        num[Epos] = 'e';
    }

    int epos = num.find('e', 0);
    if (epos != string::npos) {
        string main_part = num.substr(0, epos);
        string exp_part = num.substr(epos + 1);

        float main_part_num = stof(main_part);
        int exp_part_num = stoi(exp_part);

        float final_num = main_part_num * pow(10, exp_part_num);
        ostringstream out;
        out << fixed << setprecision(4) << final_num;
        return out.str();
    }
    return num;
}

string number_unificator(const string& number) {
    if (number.find('.') != string::npos) {
        return punkt_number(number);
    }
    else if (number.find(',') != string::npos) {
        return comma_number(number);
    }
    else if ((number.find('e') != string::npos) || (number.find('E') != string::npos)) {
        return e_number(number);
    }
    else {
        return number + ".0000";
    }
}

bool is_surrounded_by_letters(const string& line, int start, int end) {
    return (start > 0 && isalpha(line[start - 1])) || (end < line.length() && isalpha(line[end]));
}

void skip_date(const string& line, int& i) {
    while (i < line.length() && (isdigit(line[i]) || line[i] == '/')) {
        ++i;
    }
}

void skip_time(const string& line, int& i) {
    while (i < line.length() && (isdigit(line[i]) || line[i] == ':')) {
        ++i;
    }
}

void process_exponential_part(const string& line, int& i, string& new_string) {
    if (i < line.length()) {
        new_string += line[i];
        ++i;
        if (i < line.length() && (line[i] == '+' || line[i] == '-')) {
            new_string += line[i];
            ++i;
        }
        while (i < line.length() && isdigit(line[i])) {
            new_string += line[i];
            ++i;
        }
    }
}

void add_number_if_valid(const string& line, int start_index, int i, string& new_string, string* massive_of_numbers, int* massive_of_positions, int* massive_of_lengthes, int& count) {
    if (!new_string.empty() && !is_surrounded_by_letters(line, start_index, i)) {
        massive_of_numbers[count] = new_string;
        massive_of_positions[count] = start_index;
        massive_of_lengthes[count] = i - start_index;
        count++;
    }
}

string number_finder(const string& line, int& count) {
    string* massive_of_numbers = new string[line.length()];
    int* massive_of_lengthes = new int[line.length()];
    int* massive_of_positions = new int[line.length()];
    count = 0;
    int i = 0;

    while (i < line.length()) {
        string new_string = "";
        int start_index = i;
        if (isdigit(line[i]) || (line[i] == '-' && i + 1 < line.length() && isdigit(line[i + 1]))) {
            if (line[i] == '-') {
                new_string += line[i];
                ++i;
            }
            while (i < line.length()) {
                if (isdigit(line[i])) {
                    new_string += line[i];
                    ++i;
                }
                else if ((line[i] == '.' || line[i] == ',') && (i + 1 < line.length()) && isdigit(line[i + 1])) {
                    new_string += line[i];
                    ++i;
                }
                else if ((line[i] == 'e' || line[i] == 'E') && (i + 1 < line.length())) {
                    process_exponential_part(line, i, new_string);
                    break;
                }
                else if (line[i] == ':' && i > 0 && isdigit(line[i - 1]) && i + 1 < line.length() && isdigit(line[i + 1])) {
                    i = start_index;
                    skip_time(line, i);
                    new_string = "";
                    break;
                }
                else if (line[i] == '/' && i > 0 && isdigit(line[i - 1]) && i + 1 < line.length() && isdigit(line[i + 1])) {
                    i = start_index;
                    skip_date(line, i);
                    new_string = "";
                    break;
                }
                else {
                    break;
                }
            }
            add_number_if_valid(line, start_index, i, new_string, massive_of_numbers, massive_of_positions, massive_of_lengthes, count);
        }
        else if (line[i] == '/' || line[i] == ':') {
            if (line[i] == '/') {
                skip_date(line, i);
            }
            else {
                skip_time(line, i);
            }
        }
        else {
            ++i;
        }
    }

    string result = line;
    for (int j = count - 1; j >= 0; --j) {
        string uninumber = number_unificator(massive_of_numbers[j]);
        result.replace(massive_of_positions[j], massive_of_lengthes[j], uninumber);
    }

    delete[] massive_of_numbers;
    delete[] massive_of_lengthes;
    delete[] massive_of_positions;

    return result;
}

void printer(ifstream& inputFile) {
    ofstream outputFile("string_3.txt");
    if (!outputFile.is_open()) {
        cerr << "Failed to open output file: string_3.txt" << endl;
        return;
    }
    string line;
    while (getline(inputFile, line)) {
        int count = 0;
        string final_line = number_finder(line, count);
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
