#include "pch.h"

#include <vector>
#include <filesystem>
#include "../MdToUE5StringTables/MdToCSV.h"

TEST(MdToCSV, takesPathToFileOutputsContentsToCSV1) {
	// ARRANGE - Setup filepath to Portrayal File
	// 
	// Used to determine where test code was running
	//std::string curPath = std::filesystem::current_path().string();
	std::filesystem::path PortrayalFile = "../../../TestMdToUE5StringTable/TestFilesDirectory/TwoPortrayalFiles/p_text1.md";
	
	// ACT - Read premade p_text1.md from testing directory (top level)

	std::string result = ObsidianMdFileContentsToCSV(PortrayalFile);
	// ASSERT - Result matches expected write to csv file
	std::string ExpectedCsvParse = "\"p_text1\",\"It was a dark and stormy night.\"";
	EXPECT_EQ(result, ExpectedCsvParse);
}

TEST(MdToCSV, takesPathToFileOutputsContentsToCSV2) {
	// ARRANGE - Setup filepath to Portrayal File
	std::filesystem::path PortrayalFile = "../../../TestMdToUE5StringTable/TestFilesDirectory/TwoPortrayalFiles/p_text2.md";

	// ACT - Read premade p_text1.md from testing directory (top level)

	std::string result = ObsidianMdFileContentsToCSV(PortrayalFile);
	// ASSERT - Result matches expected write to csv file

	std::string ExpectedCsvParse = "\"p_text2\",\"The fog rolling across the night city skyline shrouded the skyscrapers in gloom.\"";
	EXPECT_EQ(result, ExpectedCsvParse);
}

TEST(MdToCSV, inputFileHasObsidianTag) {
	// ARRANGE
	std::string convert = "#dummyTag #dummyTag2 \nIt Was a dark and stormy night.\n Snoopy.";
	
	std::string expect = "It Was a dark and stormy night.\n Snoopy.";

	std::string result = RemoveObsidianEditorMarkdown(convert);

	EXPECT_EQ(result, expect);
}

TEST(MdToCSV, inputFileHasObsidianTagV2) {
	// ARRANGE
	std::string convert = "---\ntags:  - statePortrayal\n---\nIt Was a dark and stormy night.\n Snoopy.";

	std::string expect = "It Was a dark and stormy night.\n Snoopy.";

	std::string result = RemoveObsidianEditorMarkdown(convert);

	EXPECT_EQ(result, expect);
}

TEST(CheckObsidianTag, V2Tags1) {
	// ARRANGE
	std::string contents = "---\ntags:  - statePortrayal\n---\nIt Was a dark and stormy night.\n Snoopy.";

	bool expect = true;

	bool result = hasObsidianTagV2("statePortrayal", contents);

	EXPECT_EQ(result, expect);
}

TEST(CheckObsidianTag, TagNotPresent2) {
	// ARRANGE
	std::string contents = "---\ntags:  - wrongTag\n---\nIt Was a dark and stormy night.\n Snoopy.";

	bool expect = false;

	bool result = hasObsidianTagV2("statePortrayal", contents);

	EXPECT_EQ(result, expect);
}


TEST(TestGetFileContents, doesntThrowIfPathInvalid) {
	// ARRANGE
	std::filesystem::path PortrayalFile = "invalid/Path/";

	// ACT
	std::optional<std::string> result = GetFileContents(PortrayalFile);
	
	EXPECT_FALSE(result.has_value());
}

TEST(TestConvertPortrayalToCSVForm, inputFileHasQoutes) {
	// ARRANGE
	std::filesystem::path PortrayalFile = "../../../TestMdToUE5StringTable/TestFilesDirectory/ParsingToCSV/quotes/p_text1.md";
	std::filesystem::path ExpectFile = "../../../TestMdToUE5StringTable/TestFilesDirectory/ParsingToCSV/quotes/expect.md";

	std::optional<std::string> fileContents = GetFileContents(PortrayalFile);
	ASSERT_TRUE(fileContents.has_value());

	std::optional<std::string> expect = GetFileContents(ExpectFile);
	ASSERT_TRUE(expect.has_value());

	// ACT
	std::string result = GetCsvFormatString(fileContents.value());

	EXPECT_EQ(result, expect.value());
}

#include "gmock/gmock-matchers.h"

TEST(TestGetPortrayalFiles, test1) {
	// Arrange
	// Path to obsidian vault game design scene folder
	std::filesystem::path pathToDirectory = "../../../TestMdToUE5StringTable/TestFilesDirectory/TwoPortrayalFiles";
	std::filesystem::path PortrayalFile1 = "../../../TestMdToUE5StringTable/TestFilesDirectory/TwoPortrayalFiles/p_text1.md";
	std::filesystem::path PortrayalFile2 = "../../../TestMdToUE5StringTable/TestFilesDirectory/TwoPortrayalFiles/p_text2.md";

	// ACT
	std::vector<std::filesystem::path> resultPortrayalFilePaths = GetMDFilePathsWithFileNamePrefix("p_", pathToDirectory);
	
	std::vector<std::filesystem::path> expect{ PortrayalFile1, PortrayalFile2 };
	EXPECT_EQ(resultPortrayalFilePaths,expect);
}

TEST(TestGetPortrayalFiles, OneFileInDirectory) {
	// Arrange
	// Path to obsidian vault game design scene folder
	std::filesystem::path pathToDirectory = "../../../TestMdToUE5StringTable/TestFilesDirectory/Simple";
	std::filesystem::path PortrayalFile1 = "../../../TestMdToUE5StringTable/TestFilesDirectory/Simple/p_text1.md";

	// ACT
	std::vector<std::filesystem::path> resultPortrayalFilePaths = GetMDFilePathsWithFileNamePrefix("p_", pathToDirectory);

	std::vector<std::filesystem::path> expect{ PortrayalFile1};
	EXPECT_EQ(resultPortrayalFilePaths, expect);
}

TEST(TestGetPortrayalFiles, TwoFilesInDirectoryOnlyOnePortrayal) {
	// Arrange
	// Path to obsidian vault game design scene folder
	std::filesystem::path pathToDirectory = "../../../TestMdToUE5StringTable/TestFilesDirectory/2Files_1Portrayal";
	std::filesystem::path PortrayalFile1 = "../../../TestMdToUE5StringTable/TestFilesDirectory/2Files_1Portrayal/p_text1.md";

	// ACT
	std::vector<std::filesystem::path> resultPortrayalFilePaths = GetMDFilePathsWithFileNamePrefix("p_", pathToDirectory);

	std::vector<std::filesystem::path> expect{ PortrayalFile1 };
	EXPECT_EQ(resultPortrayalFilePaths, expect);
}

TEST(TestGetPortrayalFiles, PortrayalInSubdirectory) {
	// Arrange
	// Path to obsidian vault game design scene folder
	std::filesystem::path pathToDirectory = "../../../TestMdToUE5StringTable/TestFilesDirectory/Subdirectories1";
	std::filesystem::path PortrayalFile1 = "../../../TestMdToUE5StringTable/TestFilesDirectory/Subdirectories1/portrayals/p_text1.md";

	// ACT
	std::vector<std::filesystem::path> resultPortrayalFilePaths = GetMDFilePathsWithFileNamePrefix("p_", pathToDirectory);

	std::vector<std::filesystem::path> expect{ PortrayalFile1 };
	EXPECT_EQ(resultPortrayalFilePaths, expect);
}