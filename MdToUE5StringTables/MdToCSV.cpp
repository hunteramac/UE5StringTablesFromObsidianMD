#include "MdToCSV.h"

std::string RemoveObsidianEditorMarkdown(std::string input) {
	//Search for tags at the TOP of the file and remove them
	size_t pos = input.find("#");
	
	// is tag at start of the file?
	if (pos == 0) {
		size_t newLine = input.find('\n');
		// Erase the line between pos and newline -> first line is all tags is assumed
		input.erase(pos, newLine+1);
		return input;
	}

	// check for --- version of obsidian tags, and remove.
	size_t pos2 = input.find("---\n");
	if (pos2 == 0) {
		input.erase(0, pos2+4);
		size_t pos3 = input.find("---\n");

		input.erase(0, pos3+4);

		return input;
	}
	return input;
}

bool hasObsidianTagV2(std::string tag, std::string contents) {
	// check for --- version of obsidian tags, and remove.
	size_t pos2 = contents.find("---\n");
	if (pos2 == 0) {
		contents.erase(0, pos2 + 4);
		size_t pos3 = contents.find("---\n");

		contents.erase(pos3, std::string::npos); //clear all remaining

		// check if tag is present now only frontmatter leftover
		size_t findTagResult = contents.find(tag);
		// https://cplusplus.com/reference/string/string/find/
		if (findTagResult != std::string::npos) {
			return true;
		}
	}
	return false;
}

std::vector<std::filesystem::path> GetMDFilePathsWithFileNamePrefix(std::string prefix, std::filesystem::path searchDir) {
	std::vector<std::filesystem::path> result;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(searchDir)) {
		//check if is a portrayal file
		if (fileNameHasPrefix(prefix, entry)) {
			result.push_back(entry.path());
		}
	}

	return result;
}

std::vector<std::filesystem::path> GetMDFilePathsWithObsidianTag(std::string tag, std::filesystem::path searchDir) {
	std::vector<std::filesystem::path> result;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(searchDir)) {
		//check if is a portrayal file

		//get file contents to check tag
		std::optional<std::string> contents = GetFileContents(entry);
		
		bool hasTag = false;

		if (contents.has_value()) {
			// check if tag present
			hasTag = hasObsidianTagV2(tag, contents.value());
		}
		
		// if tag matched, then push the entry
		if (hasTag) {
			result.push_back(entry.path());
		}
	}

	return result;
}




bool fileNameHasPrefix(std::string portrayalFilePrefix, std::filesystem::directory_entry entry) {
	std::filesystem::path temp = entry.path();

	if (temp.extension() != ".md")
		return false;

	if (temp.filename().string().starts_with(portrayalFilePrefix))
		return true;

	return false;
}

std::string ObsidianMdFileContentsToCSV(std::filesystem::path PortrayalPath) {
	//Get filename without extension for CSV
	std::string portrayalFileName = PortrayalPath.stem().string();

	std::optional<std::string> result = GetFileContents(PortrayalPath);
	if (result.has_value()) {
		
		std::string removedObsidianSpecificMarkdown = RemoveObsidianEditorMarkdown(result.value());

		std::string converted = GetCsvFormatString(removedObsidianSpecificMarkdown);

		if(removedObsidianSpecificMarkdown=="" || removedObsidianSpecificMarkdown == "\0\0\0")
			return "\"" + portrayalFileName + "\",\"" + portrayalFileName + "\"";

		return "\"" + portrayalFileName + "\",\"" + converted + "\"";
	}
	else {
		// Do something better in next TDD itteration
		return "error, catch this";
	}
}

// could return an option std::string, not crash on read
std::optional<std::string> GetFileContents(std::filesystem::path path) {
	if (!std::filesystem::exists(path)) {
		return std::nullopt;
	}
	// File read
	std::ifstream in;
	in.open(path.c_str(), std::ifstream::in);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	else {
		return std::nullopt;
	}
}

std::string GetCsvFormatString(std::string portrayalFileContents) {
	std::string converted = portrayalFileContents;

	// convert " to \" In C++ means \\\"\"
	converted = replaceSubstring(converted, "\"", "\\\"\"");

	return converted;
}

std::string replaceSubstring(std::string input , std::string replace, std::string replaceWith) {
	size_t pos = input.find(replace);
	while (pos != std::string::npos) {
		input.replace(pos, replace.size(), replaceWith);
		pos = input.find(replace, pos + replaceWith.size());
	}

	return input;
}