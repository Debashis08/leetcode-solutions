#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstdio>

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
    std::string GetTestDataFolderPath(std::string filePath, const std::string& source, const std::string& target)
    {
        size_t pos = filePath.find(source);
        if (pos != std::string::npos)
        {
            filePath.replace(pos, source.length(), target);
        }
        return filePath;
    }

    std::string ChangeExtensionToTxt(const std::string& filepath)
    {
        size_t dotPos = filepath.find_last_of('.');
        if (dotPos == std::string::npos)
        {
            return filepath + ".txt";
        }
        return filepath.substr(0, dotPos) + ".txt";
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
    std::string sourceFilePath;
    std::cout << "Enter full path to the C++ source file (.cpp): ";
    std::getline(std::cin, sourceFilePath);

    // Derive test case file path
    Helper helper;
    std::string testCaseFilePath = helper.GetTestDataFolderPath(sourceFilePath, "src\\", "tests\\");
    testCaseFilePath = helper.ChangeExtensionToTxt(testCaseFilePath);

    // Compile the source code
    std::string compileCommand = "g++ \"" + sourceFilePath + "\" -o " EXECUTABLE_NAME " 2> compile_errors.txt";
    int compileResult = std::system(compileCommand.c_str());

    if (compileResult != 0)
    {
        std::cerr << "Compilation failed. See compile_errors.txt\n";
        return 1;
    }

    std::ifstream inputFile(testCaseFilePath);
    if (!inputFile)
    {
        std::cerr << "Failed to open test case file: " << testCaseFilePath << "\n";
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

    // Execute each test case
    for (size_t i = 0; i < testCases.size(); i++)
    {
        std::string inputFileName = "temp_input.txt";
        std::string outputFileName = "temp_output.txt";

        std::ofstream inputFile(inputFileName);
        inputFile << testCases[i].inputBlock;
        inputFile.close();

        std::string runCommand = std::string(EXECUTABLE_NAME) + " < " + inputFileName + " > " + outputFileName;
        std::system(runCommand.c_str());

        std::ifstream outputFile(outputFileName);
        std::ostringstream ossActual;
        while (std::getline(outputFile, line))
        {
            ossActual << line << '\n';
        }

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
        }
    }

    // Clean up
    std::remove("temp_input.txt");
    std::remove("temp_output.txt");
    std::remove("solution_test_exec.exe");

    return 0;
}
