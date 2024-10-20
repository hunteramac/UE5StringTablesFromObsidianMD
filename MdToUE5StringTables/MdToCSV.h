#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>


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
	}else{
		return std::nullopt;
	}
}

std::string MdPortrayalFileToCSV(std::filesystem::path PortrayalPath) {
	//Get filename without extension for CSV
	std::string portrayalFileName = PortrayalPath.stem().string();

	std::optional<std::string> result = GetFileContents(PortrayalPath);
	if (result.has_value()) {
		return "\"" + portrayalFileName + "\",\"" + result.value() + "\"";
	}
	else{
		// Do something better in next TDD itteration
		return "error, catch this";
	}
}

std::vector<std::filesystem::path> GetPortrayalFiles(std::filesystem::path searchDir) {
	std::vector<std::filesystem::path> result;

	return result;
}