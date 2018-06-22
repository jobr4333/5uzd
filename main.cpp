#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <locale>
#include <iomanip>
#include <sstream>
#include <vector>


using std::cout; using std::endl; using std::string; using std::ifstream; using std::map;
using std::transform; using std::left; using std::setw; using std::getline; using std::istringstream;
using std::vector;

void removeFromWord(string &s, char x) {
    //cout << "STRING: " << s << endl;
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

void read(map<string, unsigned int> &textWords,  map<string, map<size_t, size_t>> &references) {
    vector<int> refs;

    const string filename = "../text.txt";
    string word, line;
    int lineNR = 1;
    ifstream rd(filename);
    while(getline(rd, line)) {
        istringstream iss(line);
        while (iss >> word) {
            process(word);
            if (textWords.find(word) != textWords.end()) textWords[word]++, references[word][lineNR]++;
            else textWords[word] = 1;
        }
        lineNR++;
    }
    rd.close();
}

void print(map<string, unsigned int> &textWords, map<string, map<size_t, size_t>> references) {
    /*auto it = textWords.begin();
    while(it != textWords.end()) {
        cout << left << setw(20) << "zodis: " << it -> first << "  " << "tekste tiek kartu pasikartojo: " << it -> second << " ";
        for (auto &j : references ){
            cout << j.first << "-" << j.second << " ";
        }
        it++;
    }*/

    for(auto i : textWords) {
        if(i.second > 1) {
            cout << left << setw(8) << "zodis: " << setw(8) << "*"+i.first+"*" << "  " << "tekste pasikartojo "  << setw(3) << i.second << " kartu: " << " ";
            cout << "Eilutese - kartus : ";
            for (auto j : references.at(i.first)){
                cout << j.first << "-" << j.second << "  ";
            }
            cout << endl;
        }
    }

}

int main() {
    map<string, unsigned int> textWords;
    map<string, map<size_t, size_t>> references;
    read(textWords, references);
    print(textWords, references);
}