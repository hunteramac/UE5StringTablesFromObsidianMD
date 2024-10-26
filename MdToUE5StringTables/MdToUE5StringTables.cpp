// MdToUE5StringTables.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ostream>
#include "MdToCSV.h"

int main()
{
    // Learning only
    std::filesystem::path curPath = std::filesystem::current_path().string();
    // Should be arguments from command line
    
    std::filesystem::path pathToDirectory = "D:/dev/UE5StringTablesFromObsidianMD/TestMdToUE5StringTable/TestFilesDirectory/TwoPortrayalFiles";
    //std::filesystem::path pathToDirectory = "C:/Users/hunter/OneDrive/[Vault] Game Dev/Spec/C2077/A_Friends_Last_Text";

    //std::filesystem::path pathToDirectory = "../TestMdToUE5StringTable/TestFilesDirectory/TwoPortrayalFiles";
    //std::filesystem::path pathToOutputCSV = "../TestMdToUE5StringTable/TestFilesDirectory/ScriptOutput/ST_portrayals.md";

    // Make path to csv file (with name)
    std::filesystem::path pathToOutputCSV = "D:/dev/UE5StringTablesFromObsidianMD/TestMdToUE5StringTable/TestFilesDirectory/ScriptOutput";
    std::filesystem::path csvName = "ST_portrayals.csv";
    pathToOutputCSV /= csvName;

    std::cout << "Getting Portrayal File paths\n";
    std::vector<std::filesystem::path> resultPortrayalFilePaths = GetPortrayalMDFilePaths(pathToDirectory);

    std::string result = "";

    for (const auto path : resultPortrayalFilePaths) {
        result.append(MdPortrayalFileToCSV(path) + "\n");
    }

    // Make CSV file
    std::ofstream csvFile;
    csvFile.open(pathToOutputCSV.c_str(), std::ofstream::trunc); // if file exists, overwrite
    csvFile << "Key,SourceString\n";
    csvFile << result;
    csvFile.close();
    
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
