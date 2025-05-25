#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string rle_compress(const string& input) {
    string result;
    int n = input.length();
    for (int i = 0; i < n;) {
        char c = input[i];
        int count = 1;
        while (i + count < n && input[i + count] == c) count++;
        result += c + to_string(count);
        i += count;
    }
    return result;
}

void compress_file(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile, ios::binary);
    if (!in) {
        cerr << "Error opening input file\n";
        return;
    }

    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    string compressed = rle_compress(content);

    ofstream out(outputFile, ios::binary);
    if (!out) {
        cerr << "Error opening output file\n";
        return;
    }

    out << compressed;
    out.close();
}

int main() {
    string inputFile = "input.txt";
    string outputFile = "compressed.txt";

    compress_file(inputFile, outputFile);

    cout << "Compression done!\n";
    return 0;
}
