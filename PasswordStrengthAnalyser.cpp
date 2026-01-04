#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <conio.h>

using namespace std;

class StrengthAnalyser
{
public:
    struct AnalysisResult
    {
        int length;
        int poolsize;
        double entropy;
        int score;

        bool hasLower;
        bool hasUpper;
        bool hasDigit;
        bool hasSymbol;
        bool hasLength;
        bool hasRepeats;
        bool hasSequence;
    };

    bool checkhasRepeats(string password)
    {
        int count = 1;
        int limit = 3;

        for (int i = 1; i < password.length(); i++)
        {
            if (password[i] == password[i - 1])
                count++;
            else
                count = 1;

            if (count >= limit)
                return true;
        }

        return false;
    }

    bool checkhasSequence(string password)
    {
        vector<string> badSequences = {"123", "234", "345", "456", "567", "678", "789", "abc", "qwerty", "asdf", "password"};

        string lowerpass = "";
        for (char c : password)
        {
            lowerpass += tolower(c);
        }

        for (string word : badSequences)
        {
            if (lowerpass.find(word) != string::npos)
                return true;
        }
        return false;
    }

    AnalysisResult analyze(string password)
    {
        AnalysisResult res;
        res.length = password.length();
        res.hasLower = false;
        res.hasUpper = false;
        res.hasDigit = false;
        res.hasSymbol = false;
        res.hasLength = res.length >= 8;
        res.hasRepeats = checkhasRepeats(password);
        res.hasSequence = checkhasSequence(password);

        for (char c : password)
        {
            if (islower(c))
                res.hasLower = true;
            else if (isupper(c))
                res.hasUpper = true;
            else if (isdigit(c))
                res.hasDigit = true;
            else
                res.hasSymbol = true;
        }

        int pool = 0;
        if (res.hasLower)
            pool += 26;
        if (res.hasUpper)
            pool += 26;
        if (res.hasDigit)
            pool += 26;
        if (res.hasSymbol)
            pool += 32;

        res.poolsize = pool;

        double rawEntropy = 0.0;
        if (res.poolsize > 0)
            rawEntropy = res.length * log2(res.poolsize);

        double penalty = 0.0;
        if (res.hasRepeats)
            penalty += 15;
        if (res.hasSequence)
            penalty += 25;

        res.entropy = max(0.0, rawEntropy - penalty);

        res.score = min(100, (int)((res.entropy / 128.0) * 100));

        return res;
    }
};

void setConsoleColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printChecklist(string label, bool condition)
{
    if (condition)
    {
        setConsoleColor(10);
        cout << "[OK] ";
    }
    else
    {
        setConsoleColor(8);
        cout << "[  ] ";
    }
    setConsoleColor(7);
    cout << label << endl;
}

int main()
{
    StrengthAnalyser analyzer;
    string inputPass;
    bool running = true;
    bool masked = false;

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);

    while (running)
    {
        system("cls");
        StrengthAnalyser::AnalysisResult res = analyzer.analyze(inputPass);

        cout << "================================================\n";
        cout << "          PASSWORD STRENGTH ANALYZER\n";
        cout << "================================================\n";
        cout << "Password: ";
        setConsoleColor(14);
        if (masked)
            cout << string(inputPass.length(), '*') << endl;
        else
            cout << inputPass << endl;
        setConsoleColor(7);
        cout << "-------------------------------------------------\n";
        cout << "REQUIREMENTS: \n";
        printChecklist("Lowercase Letters", res.hasLower);
        printChecklist("Uppercase Letters", res.hasUpper);
        printChecklist("Numbers", res.hasDigit);
        printChecklist("Symbols", res.hasSymbol);
        printChecklist("Minimum 8 characters", res.hasLength);
        printChecklist("No repeated characters", !res.hasRepeats);
        printChecklist("No common sequences", !res.hasSequence);
        cout << "-------------------------------------------------\n";
        cout << "Entropy: " << (int)res.entropy << " bits" << endl;
        cout << "Score:   " << res.score << " / 100" << endl;
        cout << "================================================\n";
        cout << " [ESC] Quit | [TAB] " << (masked ? "Show " : "Hide ") << "| [BKSP] Delete";

        char key = _getch();
        if (key == 27)
            running = false;
        else if (key == 8)
        {
            if (!inputPass.empty())
                inputPass.pop_back();
        }
        else if (key == 9)
        {
            masked = !masked;
        }
        else if (key >= 32 && key <= 126)
        {
            inputPass += key;
        }
    }
    return 0;
}