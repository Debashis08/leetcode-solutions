#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <filesystem>

namespace fs = std::filesystem;

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
    std::string GetTestDataFilePath(const fs::path& sourcePath, const fs::path& sourceDir, const fs::path& testDataDir)
    {
        fs::path relativePath = fs::relative(sourcePath, sourceDir);
        fs::path testCasePath = testDataDir / relativePath;
        testCasePath.replace_extension(".txt");
        return testCasePath.string();
    }

    std::vector<TestCase> LoadTestCases(const std::string& testCaseFilePath)
    {
        std::ifstream inputFile(testCaseFilePath);
        std::vector<TestCase> testCases;
        if (!inputFile) return testCases;

        std::string line;
        while (std::getline(inputFile, line))
        {
            if (line.find("Test Case") != std::string::npos)
            {
                TestCase testCase;
                std::getline(inputFile, line); // "Input:"
                std::ostringstream ossInput;
                while (std::getline(inputFile, line) && line.find("Output:") == std::string::npos)
                {
                    ossInput << line << '\n';
                }
                testCase.inputBlock = ossInput.str();

                std::ostringstream ossOutput;
                while (std::getline(inputFile, line) && !line.empty())
                {
                    ossOutput << line << '\n';
                }
                testCase.expectedOutputBlock = ossOutput.str();

                testCases.push_back(testCase);
            }
        }

        return testCases;
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
    Helper helper;
    bool isAnyTestFailed = false;

    int totalTests = 0;
    int passedTests = 0;
    int failedTests = 0;
    int skippedTests = 0;

    fs::path scriptDir;

    #ifdef _WIN32
        scriptDir = fs::current_path();  // fallback for Windows
    #else
        scriptDir = fs::canonical("/proc/self/exe").parent_path();  // works for Linux (GitHub Actions)
    #endif

    fs::path rootDir = scriptDir.parent_path();
    fs::path sourceDir = rootDir / "src";
    fs::path testDataDir = rootDir / "tests";

    if (!fs::exists(sourceDir))
    {
        std::cerr << "Source directory not found: " << sourceDir << "\n";
        return 1;
    }

    for (const auto& entry : fs::recursive_directory_iterator(sourceDir))
    {
        if (entry.path().extension() == ".cpp" || entry.path().extension() == ".cc")
        {
            std::string sourcePath = entry.path().string();
            std::string testCasePath = helper.GetTestDataFilePath(entry.path(), sourceDir, testDataDir);

            std::cout << "\nTesting: " << fs::relative(entry.path(), sourceDir).string() << "\n";

            std::string compileCommand = "g++ \"" + sourcePath + "\" -o " EXECUTABLE_NAME " 2> compile_errors.txt";
            if (std::system(compileCommand.c_str()) != 0)
            {
                std::cerr << "Compilation failed for: " << sourcePath << "\n";
                skippedTests++;
                continue;
            }

            std::vector<TestCase> testCases = helper.LoadTestCases(testCasePath);
            if (testCases.empty())
            {
                std::cerr << "No test cases found for: " << testCasePath << "\n";
                skippedTests++;
                continue;
            }

            for (size_t i = 0; i < testCases.size(); i++)
            {
                totalTests++;

                std::ofstream in("temp_input.txt");
                in << testCases[i].inputBlock;
                in.close();

                std::string runCommand = std::string(EXECUTABLE_NAME) + " < temp_input.txt > temp_output.txt";
                std::system(runCommand.c_str());

                std::ifstream out("temp_output.txt");
                std::ostringstream oss;
                std::string line;
                while (std::getline(out, line))
                {
                    oss << line << '\n';
                }
                std::string expected = helper.Trim(testCases[i].expectedOutputBlock);
                std::string actual = helper.Trim(oss.str());

                if (expected == actual)
                {
                    std::cout << "Test Case " << (i + 1) << ": " << COLOR_GREEN_BOLD << "Passed" << COLOR_RESET << '\n';
                    passedTests++;
                }
                else
                {
                    std::cout << "Test Case " << (i + 1) << ": " << COLOR_RED_BOLD << "Failed" << COLOR_RESET << '\n';
                    std::cout << "Expected:\n" << expected << "\n";
                    std::cout << "Got:\n" << actual << "\n";
                    failedTests++;
                    isAnyTestFailed = true;
                }
            }

            std::remove("temp_input.txt");
            std::remove("temp_output.txt");
            std::remove("solution_test_exec.exe");
        }
    }

    // Print summary report
    std::cout << "\nTest Summary\n";
    std::cout << "Total Tests   : " << totalTests << "\n";
    std::cout << "Passed        : " << (passedTests > 0 ? COLOR_GREEN_BOLD : COLOR_RESET) << passedTests << COLOR_RESET << "\n";
    std::cout << "Failed        : " << (failedTests > 0 ? COLOR_RED_BOLD : COLOR_RESET) << failedTests << COLOR_RESET << "\n";
    std::cout << "Skipped       : " << skippedTests << "\n";

    return isAnyTestFailed ? 1 : 0;
}
