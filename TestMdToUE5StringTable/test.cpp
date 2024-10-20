#include "pch.h"

#include <vector>
#include <filesystem>
#include "../MdToUE5StringTables/MdToCSV.h"

TEST(MdToCSV, takesPathToFileOutputsContentsToCSV1) {
	// ARRANGE - Setup filepath to Portrayal File
	// 
	// Used to determine where test code was running
	//std::string curPath = std::filesystem::current_path().string();
	std::filesystem::path PortrayalFile = "../../../TestMdToUE5StringTable/TestFilesDirectory/p_text1.md";
	
	// ACT - Read premade p_text1.md from testing directory (top level)

	std::string result = MdPortrayalFileToCSV(PortrayalFile);
	// ASSERT - Result matches expected write to csv file
	std::string ExpectedCsvParse = "\"p_text1\",\"It was a dark and stormy night.\"";
	EXPECT_EQ(result, ExpectedCsvParse);
}

TEST(MdToCSV, takesPathToFileOutputsContentsToCSV2) {
	// ARRANGE - Setup filepath to Portrayal File
	std::filesystem::path PortrayalFile = "../../../TestMdToUE5StringTable/TestFilesDirectory/p_text2.md";

	// ACT - Read premade p_text1.md from testing directory (top level)

	std::string result = MdPortrayalFileToCSV(PortrayalFile);
	// ASSERT - Result matches expected write to csv file

	std::string ExpectedCsvParse = "\"p_text2\",\"The fog rolling across the night city skyline shrouded the skyscrapers in gloom.\"";
	EXPECT_EQ(result, ExpectedCsvParse);
}

#include "gmock/gmock-matchers.h"

TEST(TestGetPortrayalFiles, test1) {
	// Arrange
	// Path to obsidian vault game design scene folder
	std::filesystem::path pathToDirectory = "../../../TestMdToUE5StringTable/TestFilesDirectory";
	std::filesystem::path PortrayalFile1 = "../../../TestMdToUE5StringTable/TestFilesDirectory/p_text1.md";
	std::filesystem::path PortrayalFile2 = "../../../TestMdToUE5StringTable/TestFilesDirectory/p_text2.md";

	// ACT
	std::vector<std::filesystem::path> resultPortrayalFilePaths = GetPortrayalFiles(pathToDirectory);
	
	std::vector<std::filesystem::path> expect{ PortrayalFile1, PortrayalFile2 };
	EXPECT_EQ(resultPortrayalFilePaths,expect);
}