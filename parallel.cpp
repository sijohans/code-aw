#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <thread>

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

void processWords(const set<string>& words, int& partialSum) {
    for (const string& word : words) {
        // Process the word here
        partialSum += calculateWordValue2(word);
    }
}

int main() {
    ifstream inputFile("../loTSoFWOrds.txt.txt");

    if (!inputFile) {
        cerr << "Failed to open input file!" << endl;
        return 1;
    }

    map<int, set<string>> wordsByLength;

    string word;
    while (inputFile >> word) {
        wordsByLength[word.length()].insert(word);
    }

    inputFile.close();

    int sum = 0;

    // Create and start threads for parallel processing
    vector<thread> threads;
    for (const auto& entry : wordsByLength) {
        const set<string>& words = entry.second;
        if (words.size() > 2) {
            threads.emplace_back(processWords, ref(words), ref(sum));
        }
    }

    // Wait for all threads to finish
    for (thread& t : threads) {
        t.join();
    }

    cout << "Sum of word values: " << sum << endl;

    return 0;
}
