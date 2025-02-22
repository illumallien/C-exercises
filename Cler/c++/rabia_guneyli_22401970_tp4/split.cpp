#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;

class FileSplitter {
private:
    string inputFile;   // Input file name
    string outputPrefix; // Output file prefix

public:
    // Constructor to initialize input file and output file prefix
    FileSplitter(const string& inputFileName, const string& outputFilePrefix)
        : inputFile(inputFileName), outputPrefix(outputFilePrefix) {}

    void split() {
        int chunkSize = 250; // Size of each chunk in bytes
        ifstream inFile(inputFile, ios::binary); // Open input file in binary mode

        if (!inFile.is_open()) {
            cerr << "Error: Unable to open input file: " << inputFile << endl;
            return;
        }

        size_t fileSize = filesystem::file_size(inputFile); // Get file size
        int partNumber = 1;
        char buffer[250]; // Temporary buffer to store chunk data

        while (inFile) {
            inFile.read(buffer, chunkSize); // Read up to chunkSize bytes
            streamsize bytesRead = inFile.gcount(); // Get the number of bytes read

            if (bytesRead > 0) {
                string outputFileName = outputPrefix + "_" + to_string(partNumber);
                ofstream outFile(outputFileName, ios::binary);

                if (!outFile.is_open()) {
                    cerr << "Error: Unable to create output file: " << outputFileName << endl;
                    return;
                }

                outFile.write(buffer, bytesRead); // Write chunk to output file
                outFile.close();
                partNumber++;
            }
        }

        inFile.close();
        cout << "File splitting completed. " << partNumber - 1 << " parts created." << endl;
    }
};

int main() {
    string inputFile;

    cout << "Enter the file name to split:" << endl;
    cin >> inputFile;

    FileSplitter fileSplitter(inputFile, "out");
    fileSplitter.split();

    return 0;
}
