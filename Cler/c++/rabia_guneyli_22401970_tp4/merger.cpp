#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
using namespace std;

class FileMerger {
private:
    string inputDir;   // Directory where the text files are located
    string outputFile; // Output file where merged content will be written

public:
    // Constructor to initialize input directory and output file
    FileMerger(const string& inputDirectory, const string& outputFileName)
        : inputDir(inputDirectory), outputFile(outputFileName) {}

    // Method to list all files in the directory
    vector<string> listFilesInDirectory() {
        vector<string> fileNames;
        namespace fs = std::filesystem;

        for (const auto& entry : fs::directory_iterator(inputDir)) {
            if (fs::is_regular_file(entry.status())) {
                fileNames.push_back(entry.path().filename().string()); // Add only regular files
            }
        }

        return fileNames;
    }

    // Method to merge files
    void merge() {
        vector<string> fileNames = listFilesInDirectory();
        ofstream mergedFile(outputFile); // Create or overwrite the output file

        if (mergedFile.is_open()) {
            for (const auto& inputFile : fileNames) {
                ifstream inputFileStream(inputDir + "/" + inputFile); // Open each input file for reading

                if (inputFileStream.is_open()) {
                    string line; // Declare a string to store each line of text

                    while (getline(inputFileStream, line)) { // Read each line from the input file
                        mergedFile << line << "\n"; // Write each line to the merged file
                    }

                    inputFileStream.close(); // Close the input file
                } else {
                    cerr << "Failed to open input file: " << inputFile << endl; // Display an error message if file opening failed
                }
            }

            mergedFile.close(); // Close the merged file
            cout << "\nFiles merged successfully into " << outputFile << endl; // Display a success message
        } else {
            cerr << "Failed to create or open the merged output file." << endl;
        }
    }
};

int main() {
    string inputDir;
    cout << "Enter the full directory path: ";
    cin >> inputDir;

    string outputFile = "merged_output.txt";

    // Create FileMerger instance
    FileMerger merger(inputDir, outputFile);

    // List files in directory
    vector<string> files = merger.listFilesInDirectory();

    // Merge files
    merger.merge();

    // Display files found in the directory
    cout << "\nFiles found in directory:" << endl;
    for (const auto& file : files) {
        cout << file << endl;
    }

    return 0;
}
