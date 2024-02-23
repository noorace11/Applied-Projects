#include <iostream>
#include <string>
using std::string;
#include <cctype>
#include <algorithm> 

//https://www.geeksforgeeks.org/naive-algorithm-for-pattern-searching/ : heavy influence from 
//here to apply to all characters not just special characters
//It is just a Brute force algorithm repeated to do it for all cases including % and #

//This project the way it is was the only way I was able to incorporate the special character 
//cases without failing. Calling the functions and applying the adjustments did not work in any way
//because of the formatting I have

bool ImprovedContains(string const &text, string const &pattern, bool const* case_context){
    string pattern_1 = pattern;
    string text_1 = text;
    int M = pattern_1.length();
    int N = text_1.length();
    if (*case_context){
        transform(text_1.begin(), text_1.end(), text_1.begin(), ::tolower);
        transform(pattern_1.begin(), pattern_1.end(), pattern_1.begin(), ::tolower);
    }
    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++){
            if (text_1.at(i + j) == pattern_1.at(j) || pattern_1.at(j)=='%')
                continue;
            if (text_1.at(i + j)== pattern_1[j] || (isdigit(text_1.at(i + j)) && pattern_1.at(j)=='#'))
                continue;
            if (text_1.at(i + j) != pattern_1.at(j))
                break;
        }
        if (j == M){
            return true;
        }   
    }
    return false;
}

int ImprovedMatches(string const &text, string const &pattern, bool const* case_context){
    string pattern_1 = pattern;
    string text_1 = text;
    int count = 0;
    int M = pattern_1.length();
    int N = text_1.length();
    if (*case_context){
        transform(text_1.begin(), text_1.end(), text_1.begin(), ::tolower);
        transform(pattern_1.begin(), pattern_1.end(), pattern_1.begin(), ::tolower);
    }
    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++){
            if (text_1.at(i + j) == pattern_1.at(j) || pattern_1.at(j)=='%')
                continue;
            if (text_1.at(i + j)== pattern_1.at(j) || (isdigit(text_1.at(i + j)) && pattern_1.at(j)=='#'))
                continue;
            if (text_1.at(i + j) != pattern_1.at(j))
                break;
        }
        if (j == M){
            count++;
        }   
    }
    return count;
}


int ImprovedFindFirstOf(string const &text, string const &pattern, bool const* case_context){
    string pattern_1 = pattern;
    string text_1 = text;
    int M = pattern_1.length();
    int N = text_1.length();
    if (*case_context){
        transform(text_1.begin(), text_1.end(), text_1.begin(), ::tolower);
        transform(pattern_1.begin(), pattern_1.end(), pattern_1.begin(), ::tolower);
    }
    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++){
            if (text_1.at(i + j) == pattern_1.at(j) || pattern_1.at(j)=='%')
                continue;
            if (text_1.at(i + j)== pattern_1.at(j) || (isdigit(text_1.at(i + j)) && pattern_1.at(j)=='#'))
                continue;
            if (text_1.at(i + j) != pattern_1.at(j))
                break;
        }
        if (j == M){
            return i;
        }   
    }
    return -1;
}

void ImprovedReplace(string &text, string const &pattern, string const &replacement, bool const* case_context){
    string lower_line = text;
    string pattern_1 = pattern;
    if(*case_context){
        transform(lower_line.begin(), lower_line.end(), lower_line.begin(), tolower);
        transform(pattern_1.begin(), pattern_1.end(), pattern_1.begin(), tolower);
    }
    int word_search = pattern_1.size();
    if(ImprovedContains(lower_line, pattern_1, case_context) || lower_line.find(pattern_1) != string::npos) {
        int found_pos = ImprovedFindFirstOf(lower_line, pattern_1, case_context);
        lower_line.erase(found_pos, word_search);
        lower_line.insert(found_pos, replacement);
        text.erase(found_pos, word_search);
        text.insert(found_pos, replacement);
    }
}

int ImprovedNumberOfDifferences(string const &char1, string const &char2, bool const &case_context){
    int count = 0;
    string copy1 = char1;
    string copy2 = char2;
    if(case_context){
        transform(copy1.begin(), copy1.end(), copy1.begin(), tolower);
        transform(copy2.begin(), copy2.end(), copy2.begin(), tolower);
    }
    for(int i = 0; i < char1.length(); i++){
        if(copy1.at(i) != copy2.at(i)){
            count++;
        }
    }
    return count;
}

int main() 
{
    return 0;
}
