#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>


// could return an option std::string, not crash on read
std::optional<std::string> GetFileContents(std::filesystem::path path);
std::string MdFileContentsToCSV(std::filesystem::path PortrayalPath);
bool fileNameHasPrefix(std::string portrayalFilePrefix, std::filesystem::directory_entry entry);
std::vector<std::filesystem::path> GetMDFilePathsWithFileNamePrefix(std::string prefix, std::filesystem::path searchDir);
std::string GetCsvFormatString(std::string portrayalFileContents);
std::string replaceSubstring(std::string input, std::string replace, std::string replaceWith);