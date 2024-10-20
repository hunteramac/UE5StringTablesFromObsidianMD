#include "pch.h"

#include <filesystem>
#include "../MdToUE5StringTables/MdToCSV.h"

TEST(MdToCSV, HighLevelSimple1) {
	// ARRANGE - Setup filepath to Portrayal File
	std::filesystem::path PortrayalFile = "D:\\dev\\TestMdToUE5StringTable\\TestFilesDirectory\\p_text1.md";

	// ACT - Read premade p_text1.md from testing directory (top level)

	std::string result = MdPortrayalFileToCSV(PortrayalFile);
	// ASSERT - Result matches expected write to csv file

	std::string ExpectedCsvParse = "\"p_text1\",\"It was a dark and stormy knight\"";
	EXPECT_EQ(ExpectedCsvParse, result);
}