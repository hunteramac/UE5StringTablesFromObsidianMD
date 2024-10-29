// MdToUE5StringTables.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ostream>
#include "MdToCSV.h"

void MdWithPrefixContentsToCSV(std::string prefix, std::filesystem::path pathToDirectory, std::filesystem::path pathToOutputCSV) {


    std::vector<std::filesystem::path> resultPortrayalFilePaths = GetMDFilePathsWithFileNamePrefix(prefix, pathToDirectory);

    std::string result = "";

    for (const auto path : resultPortrayalFilePaths) {
        result.append(MdFileContentsToCSV(path) + "\n");
    }

    // Make CSV file
    std::ofstream csvFile;
    csvFile.open(pathToOutputCSV.c_str(), std::ofstream::trunc); // if file exists, overwrite
    csvFile << "Key,SourceString\n";
    csvFile << result;
    csvFile.close();
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "Must provide input and output file paths, 1.Path to Obsidian Vault design directory 2.Path to output the csv (path+filename)";
        return -1;
    }

     // Continue

    std::filesystem::path pathToDirectory = argv[1];
    std::filesystem::path pathToOutputCSV = argv[2];

    std::filesystem::path pathToOutputPortrayalCSV = pathToOutputCSV / "ST_portrayals.csv";
    std::filesystem::path pathToOutputDeclarationCSV = pathToOutputCSV / "ST_declarations.csv";

    std::cout << "Getting Portrayal Files\n";
    MdWithPrefixContentsToCSV("p_", pathToDirectory, pathToOutputPortrayalCSV);

    std::cout << "Getting Action Declaration Files\n";
    MdWithPrefixContentsToCSV("d_", pathToDirectory, pathToOutputDeclarationCSV);

    // Success
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
