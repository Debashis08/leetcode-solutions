#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

// Helper function to format the folder name (e.g., 0000-0099)
string getFolderName(int problemId)
{
	int lower = (problemId / 100) * 100;
	int upper = lower + 99;

	stringstream ss;
	ss << setfill('0') << setw(4) << lower << "-"
		<< setfill('0') << setw(4) << upper;
	return ss.str();
}

// Helper function to copy file contents
bool copyTemplate(const string& sourcePath, const string& destPath)
{
	ifstream source(sourcePath, ios::binary);
	if (!source) {
		cerr << "[ERROR] Could not open template file: " << sourcePath << "\n";
		return false;
	}

	ofstream dest(destPath, ios::binary);
	if (!dest) {
		cerr << "[ERROR] Could not create destination file: " << destPath << "\n";
		return false;
	}

	dest << source.rdbuf();
	return true;
}

int main()
{
	cout << "Code and Tests File Generator\n";

	int problemId;
	cout << "Enter Problem ID: ";
	if (!(cin >> problemId))
	{
		cerr << "[ERROR] Invalid input. Please enter a number.\n";
		return 1;
	}

	string folderName = getFolderName(problemId);
	string problemName = to_string(problemId);

	// Define target directories
	fs::path srcDir = fs::path("src") / folderName;
	fs::path testDir = fs::path("tests") / folderName;

	// Define target files
	fs::path cppFile = srcDir / (problemName + ".cpp");
	fs::path txtFile = testDir / (problemName + ".txt");

	// 1. Create directories if they don't exist
	try
	{
		fs::create_directories(srcDir);
		fs::create_directories(testDir);
	}
	catch (const fs::filesystem_error& e)
	{
		cerr << "[ERROR] Failed to create directories: " << e.what() << "\n";
		return 1;
	}

	// 2. Check if files already exist to prevent accidental overwriting
	if (fs::exists(cppFile) || fs::exists(txtFile))
	{
		cout << "[WARNING] Files for Problem " << problemId << " already exist!\n";
		cout << "Overwrite? (y/n): ";
		char choice;
		cin >> choice;
		if (choice != 'y' && choice != 'Y')
		{
			cout << "Operation aborted.\n";
			return 0;
		}
	}

	// 3. Copy templates
	bool cppSuccess = copyTemplate("template.cpp", cppFile.string());
	bool txtSuccess = copyTemplate("template.txt", txtFile.string());

	// 4. Output results
	if (cppSuccess && txtSuccess)
	{
		cout << "[SUCCESS] Files generated successfully!\n";
		cout << "Source : " << cppFile.string() << "\n";
		cout << "Test   : " << txtFile.string() << "\n";
	}
	else
	{
		cout << "[FAILED] Make sure 'template.cpp' and 'template.txt' exist in the root directory.\n";
	}

	return 0;
}