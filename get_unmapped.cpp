#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_set>

using Names = std::unordered_set < std::string >;

void parse_sam (char *file_name, Names &names) {
	std::ifstream infile(file_name);
	std::string line, name;
	if (! infile.good()) {
		std::cerr << "Error, SAM file name '" << file_name << "' cannot be opened.\n";
		exit(EXIT_FAILURE);
	}
	while (std::getline(infile, line)) {
		std::istringstream iss(line);
		if (!(iss >> name)) {
			std::cerr << "Error, line '" << line << "' does not look like a SAM line.\n";
			exit(EXIT_FAILURE);
		}
		names.insert(name);
	}
}

void parse_fastq (char *file_name, Names &names) {
	std::ifstream infile(file_name);
	std::string line, name;
	bool keep;
	if (! infile.good()) {
		std::cerr << "Error, FASTQ file name '" << file_name << "' cannot be opened.\n";
		exit(EXIT_FAILURE);
	}
	while (true) {
		if (std::getline(infile, line)) {
			std::istringstream iss(line);
			if (!(iss >> name)) {
				std::cerr << "Error, line '" << line << "' does not look like a FASTQ line.\n";
				exit(EXIT_FAILURE);
			}
			name = name.substr(1);
			keep = (names.find(name) == names.end());
			if (keep) {
				std::cout << line << '\n';
			}
		}
		else return;
		std::getline(infile, line);
		if (keep) {
			std::cout << line << '\n';
		}
		std::getline(infile, line);
		if (keep) {
			std::cout << line << '\n';
		}
		std::getline(infile, line);
		if (keep) {
			std::cout << line << '\n';
		}
	}
}

int main (int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: get_unmapped input_SAM input_FASTQ > output_FASTQ\n";
		exit(EXIT_FAILURE);
	}
	Names names;
	std::cerr << "Reading SAM file...\n";
	parse_sam(argv[1], names);
	std::cerr << "Reading FASTQ file...\n";
	parse_fastq(argv[2], names);
	std::cerr << "Done.\n";
	return EXIT_SUCCESS;
}
