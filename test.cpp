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

static int lookup[256];

int main()
{



    for (char c : vowels) {
        lookup[(unsigned char)c] = 2;
    }

    for (char c : consonants) {
        lookup[(unsigned char) c] = 1;
    }

    std::cout << "static int lookup[256] = {";
    for (int i = 0; i < 256; i++) {
        std::cout << lookup[i] << ",";
    }
    std::cout << std::endl;

    return 0;
}