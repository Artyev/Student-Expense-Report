#include <iostream>
#include <iostream>
#include <cstring>

using namespace std;

pair<float,float> calculate_report(FILE* report);

int main(){
    FILE* first_report = fopen("report.txt", "r");
    FILE* second_report = fopen("report_2.txt", "r");
    FILE* third_report = fopen("report_3.txt", "r");
    FILE* fourth_report = fopen("report_4.txt", "r");
    if(first_report == NULL || second_report == NULL || third_report == NULL || fourth_report == NULL){
        cout << "Some files are damaged or don't exist!" << endl;
        return 1;
    }
    auto result = calculate_report(fourth_report);
    cout << "Sum total: " << result.first << ' ' << "The coolest day: " << result.second << endl;
    return 0;
}

pair<float,float> calculate_report(FILE* report){
    float result = 0;
    float sum = 0;
    char report_str[255];
    char euro[4] = "€";
    int day_flag = 0;
    float max_cool_day = 0;
    while(fgets(report_str, 255, report) != NULL){
        int size_of_string = (int)strlen(report_str);
        int size_of_number = 0;
        string tmp_string_number;
        for(int a = 0; a < size_of_string; a++){
            if(report_str[a] == '-'){
                day_flag = 1;
            }
            if(report_str[a] == euro[0] && day_flag == 1){
                int count = a;
                while(report_str[count] != ' '){
                    if(report_str[count - 1] == ' '){
                        break;
                    } else if(report_str[count] == ','){
                        report_str[count] = '.';
                    }
                    count--;
                    size_of_number++;
                }
                char number[size_of_number];
                int index_of_number = 0;
                for(int b = count; b < a; b++){
                    number[index_of_number] = report_str[b];
                    tmp_string_number += number[index_of_number];
                    index_of_number++;
                }
                number[index_of_number] = '\0';
                sum = stof(tmp_string_number);
                result += sum;
                if(max_cool_day < sum){
                    max_cool_day = sum;
                }
            }
        }
        day_flag = 0;
    }
    return pair<float, float>(result, max_cool_day);
}