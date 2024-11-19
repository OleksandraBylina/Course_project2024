#include "NumberFinder_regex.h"

using namespace std;

string punkt_number(string num) {
    float number = stof(num);
    ostringstream out;
    out << fixed << setprecision(4) << number;
    return out.str();
}

string comma_number(string num) {
    size_t pos = num.find(',');
    if (pos != string::npos) {
        num[pos] = '.';
    }
    float number = stof(num);
    ostringstream out;
    out << fixed << setprecision(4) << number;
    return out.str();
}

string e_number(string num) {
    size_t Epos = num.find('E');
    if (Epos != string::npos) {
        num[Epos] = 'e';
    }

    size_t epos = num.find('e');
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
        return punkt_number(const_cast<string&>(number));
    }
    else if (number.find(',') != string::npos) {
        return comma_number(const_cast<string&>(number));
    }
    else if ((number.find('e') != string::npos) || (number.find('E') != string::npos)) {
        return e_number(const_cast<string&>(number));
    }
    else {
        return number + ".0000";
    }
}

bool is_part_of_date_time(const string& line, size_t match_pos, size_t match_length) {

    if (match_pos > 0) {
        char before = line[match_pos - 1];
        if (before == '/' || before == ':' || before == '.') {
            return true;
        }
    }

    if (match_pos + match_length < line.length()) {
        char after = line[match_pos + match_length];
        if (after == '/' || after == ':') {
            return true;
        }
    }
    return false;
}

string number_finder(const string& line) {
    regex number_pattern(R"(\b-?\d+(?:[.,]\d+)?(?:[eE][+-]?\d+)?\b)");

    string result = line;
    size_t search_start_pos = 0;

    while (search_start_pos < result.length()) {
        smatch match;
        string::const_iterator search_start = result.cbegin() + search_start_pos;

        if (regex_search(search_start, result.cend(), match, number_pattern)) {
            size_t match_pos = distance(result.cbegin(), match.position(0) + search_start);

            if (is_part_of_date_time(result, match_pos, match.length(0))) {
                search_start_pos = match_pos + match.length(0);
                continue;
            }
            string number = match.str(0);
            string formatted_number = number_unificator(number);
            result.replace(match_pos, match.length(0), formatted_number);
            search_start_pos = match_pos + formatted_number.length();
        }
        else {
            break;
        }
    }

    return result;
}

void printer(ifstream& inputFile) {
    ofstream outputFile("regex_3.txt");
    if (!outputFile.is_open()) {
        cerr << "Failed to open output file: regex_3.txt" << endl;
        return;
    }
    string line;
    while (getline(inputFile, line)) {
        string final_line = number_finder(line);
        cout << final_line << endl;
        outputFile << final_line << endl;
    }
    outputFile.close();
}

void file_opener(const string& textfile) {
    ifstream inputFile(textfile.c_str());
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
