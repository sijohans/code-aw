#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

static string vowels = "aeiouyáéíóúãẽĩõũâêîôûåäö";
static string consonants = "bcdfghjklmnpqrstvwxzʃʒʧʤθð";

static int lookup[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,1,2,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,2,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,1,2,0,1,0,2,2,0,0,2,2,0,1,0,0,2,2,2,2,0,1,0,2,2,0,2,0,0,0,0,0,1,2,2,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int calculateWordValue(const string& word) {
    int value = 0;

    for (char c : word) {
        if (vowels.find(c) != string::npos) {
            value += 2;
        } else if (consonants.find(c) != string::npos) {
            value += 1;
        }
    }

    return value;
}

int calculateWordValue2(const string& word) {
    int value = 0;



    for (char c : word) {
        value += lookup[(unsigned char)c];
    }

    return value;
}

int main() {
    ifstream inputFile("../loTSoFWOrds.txt.txt");

    if (!inputFile) {
        cerr << "Failed to open input file!" << endl;
        return 1;
    }

    map<int, set<string>> wordsByLength;

    for (int i = 0; i < 25; i++) {
        wordsByLength[i] = set<string>();
    }

    string word;
    while (inputFile >> word) {
        wordsByLength[word.length()].insert(word);
    }

    inputFile.close();

    int sum = 0;

    for (const auto& entry : wordsByLength) {
        const set<string>& words = entry.second;
        if (words.size() > 2) {
            auto it = words.begin();
            it++; // Skip the first word
            auto last = words.end();
            last--; // Skip the last word
            while (it != last) {
                sum += calculateWordValue(*it);
                it++;
            }
        }
    }

    cout << "Sum of word values: " << sum << endl;

    return 0;
}
