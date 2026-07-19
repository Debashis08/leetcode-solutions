#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>

#ifdef _WIN32
#define EXECUTABLE_NAME "solution_test_exec.exe"
#else
#define EXECUTABLE_NAME "./solution_test_exec"
#endif

#define COLOR_GREEN_BOLD "\033[1;32m"
#define COLOR_RED_BOLD "\033[1;31m"
#define COLOR_RESET "\033[0m"

class TestCase
{
public:
    std::string inputBlock;
    std::string expectedOutputBlock;
};

class Helper
{
public:
    // Calculates the folder bucket (e.g., 3658 -> "3600-3699")
    std::string GetFolderName(int problemId)
    {
        int lower = (problemId / 100) * 100;
        int upper = lower + 99;

        std::ostringstream ss;
        ss << std::setfill('0') << std::setw(4) << lower << "-"
            << std::setfill('0') << std::setw(4) << upper;
        return ss.str();
    }

    std::string Trim(std::string s)
    {
        while (!s.empty() && (s.back() == '\n' || s.back() == '\r' || s.back() == ' '))
        {
            s.pop_back();
        }
        return s;
    }
};

int main()
{
    bool isAnyTestFailed = false;
    int problemId;

    std::cout << "Enter Problem ID: ";
    if (!(std::cin >> problemId))
    {
        std::cerr << COLOR_RED_BOLD << "[ERROR] Invalid input. Please enter a numeric ID." << COLOR_RESET << "\n";
        return 1;
    }

    Helper helper;
    std::string folderName = helper.GetFolderName(problemId);
    std::string problemName = std::to_string(problemId);

    // Automatically construct paths based on the repository structure
    // Using '/' works cross-platform for standard libraries and g++
    std::string sourceFilePath = "src/" + folderName + "/" + problemName + ".cpp";
    std::string testCaseFilePath = "tests/" + folderName + "/" + problemName + ".txt";

    std::cout << "Targeting Source: " << sourceFilePath << "\n";
    std::cout << "Targeting Tests : " << testCaseFilePath << "\n\n";

    // Check if the test case file actually exists before attempting compilation
    std::ifstream inputFile(testCaseFilePath);
    if (!inputFile)
    {
        std::cerr << COLOR_RED_BOLD << "[ERROR] Failed to open test case file: " << testCaseFilePath << COLOR_RESET << "\n";
        return 1;
    }

    // Compile the source code
    std::string compileCommand = "g++ -std=c++20 \"" + sourceFilePath + "\" -o " EXECUTABLE_NAME " 2> compile_errors.txt";
    int compileResult = std::system(compileCommand.c_str());

    if (compileResult != 0)
    {
        std::cerr << COLOR_RED_BOLD << "Compilation failed. See compile_errors.txt" << COLOR_RESET << "\n";
        return 1;
    }

    std::vector<TestCase> testCases;
    std::string line;

    while (std::getline(inputFile, line))
    {
        if (line.find("Test Case") != std::string::npos)
        {
            TestCase testCase;

            // Read Input block
            std::getline(inputFile, line); // "Input:"
            std::ostringstream ossInput;
            while (std::getline(inputFile, line) && line.find("Output:") == std::string::npos)
            {
                ossInput << line << '\n';
            }
            testCase.inputBlock = ossInput.str();

            // Read Output block
            std::ostringstream ossOutput;
            while (std::getline(inputFile, line) && !line.empty())
            {
                ossOutput << line << '\n';
            }
            testCase.expectedOutputBlock = ossOutput.str();

            testCases.push_back(testCase);
        }
    }
    inputFile.close();

    if (testCases.empty())
    {
        std::cout << "[WARNING] No test cases found in the file.\n";
    }

    // Execute each test case
    for (size_t i = 0; i < testCases.size(); i++)
    {
        std::string inputFileName = "temp_input.txt";
        std::string outputFileName = "temp_output.txt";

        std::ofstream tempInput(inputFileName);
        tempInput << testCases[i].inputBlock;
        tempInput.close();

        std::string runCommand = std::string(EXECUTABLE_NAME) + " < " + inputFileName + " > " + outputFileName;
        std::system(runCommand.c_str());

        std::ifstream outputFile(outputFileName);
        std::ostringstream ossActual;
        while (std::getline(outputFile, line))
        {
            ossActual << line << '\n';
        }
        outputFile.close();

        std::string expected = helper.Trim(testCases[i].expectedOutputBlock);
        std::string actual = helper.Trim(ossActual.str());

        if (expected == actual)
        {
            std::cout << "Test Case " << (i + 1) << ": " << COLOR_GREEN_BOLD << "Passed" << COLOR_RESET << '\n';
        }
        else
        {
            std::cout << "Test Case " << (i + 1) << ": " << COLOR_RED_BOLD << "Failed" << COLOR_RESET << '\n';
            std::cout << "Expected:\n" << expected << "\n";
            std::cout << "Got:\n" << actual << "\n";
            isAnyTestFailed = true;
        }
    }

    // Clean up
    std::remove("temp_input.txt");
    std::remove("temp_output.txt");
    std::remove("solution_test_exec.exe");
    std::remove("solution_test_exec"); // Linux cleanup just in case

    return isAnyTestFailed ? 1 : 0;
}