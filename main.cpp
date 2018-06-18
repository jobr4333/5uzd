#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <locale>
#include <iomanip>
#include <sstream>


using std::cout; using std::endl; using std::string; using std::ifstream; using std::map;
using std::transform; using std::left; using std::setw; using std::getline; using std::istringstream;

void removeFromWord(string &s, char x) {
    cout << "STRING: " << s << endl;
    for(auto i = 0; i < s.length(); i++) {
        auto position = s.find(x);
        if (position != string::npos) s.erase(s.begin() + position, s.begin() + position + 1);
    }
}

void process(string &word) {
    removeFromWord(word, '.');
    removeFromWord(word, ',');
    removeFromWord(word, '-');
    removeFromWord(word, '?');
    removeFromWord(word, '!');
    removeFromWord(word, ':');
    removeFromWord(word, ';');
    removeFromWord(word, '"');
    removeFromWord(word, '(');
    removeFromWord(word, ')');
    transform(word.begin(), word.end(), word.begin(), ::tolower);
}

void read(map<string, unsigned int> &textWords) {
    const string filename = "../text.txt";
    string word, line;
    int lineNR{};
    ifstream rd(filename);
    while(getline(rd, line)) {
        istringstream iss(line);
        while (iss >> word) {
            process(word);
            if (textWords.find(word) != textWords.end()) textWords[word]++;
            else textWords[word] = 1;
        }
        lineNR++;
    }
    rd.close();
}

void print(map<string, unsigned int> &textWords) {
    auto it = textWords.begin();
    while(it != textWords.end()) {
        cout << left << setw(20) << it -> first << "  " << it -> second << endl;
        it++;
    }
}

int main() {
    map<string, unsigned int> textWords;
    read(textWords);
    print(textWords);
}