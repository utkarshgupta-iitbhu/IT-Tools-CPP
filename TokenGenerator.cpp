#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <windows.h>
#include <conio.h>

using namespace std;

class TokenGenerator
{
private:
    int length;
    bool includeUpper;
    bool includeLower;
    bool includeNumbers;
    bool includeSymbols;
    bool excludeAmbiguous;

    const string UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string LOWER = "abcdefghijklmnopqrstuvwxyz";
    const string NUMS = "0123456789";
    const string SYM = "!@#$%&?";
    // AMBIGUOUS CHARACTERS
    const string AMBIGUOUS = "0OIl1";

public:
    TokenGenerator(int l = 16) : length(l), includeLower(true), includeUpper(true), includeNumbers(true), includeSymbols(true), excludeAmbiguous(false) {}

    bool getUpper() { return includeUpper; }
    bool getLower() { return includeLower; }
    bool getNumbers() { return includeNumbers; }
    bool getSymbols() { return includeSymbols; }
    bool getAmbiguous() { return excludeAmbiguous; }
    int getLength() { return length; }

    void setLength(int l) { length = l; }
    void toggleUpper() { includeUpper = !includeUpper; }
    void toggleLower() { includeLower = !includeLower; }
    void toggleNumbers() { includeNumbers = !includeNumbers; }
    void toggleSymbols() { includeSymbols = !includeSymbols; }
    void toggleAmbiguous() { excludeAmbiguous = !excludeAmbiguous; }

    string generate()
    {
        string pool = "";
        string result = "";

        if (includeLower)
            pool = pool + LOWER;
        if (includeUpper)
            pool = pool + UPPER;
        if (includeNumbers)
            pool = pool + NUMS;
        if (includeSymbols)
            pool = pool + SYM;

        if (excludeAmbiguous && !pool.empty())
        {
            string filteredPool = "";
            for (char c : pool)
            {
                if (AMBIGUOUS.find(c) == string::npos)
                    filteredPool = filteredPool + c;
            }

            pool = filteredPool;
        }

        if (pool.empty())
        {
            return "Error: You must select at least one character type!";
        }

        while (result.size() < length)
        {
            int pos = rand() % pool.size();
            result = result + pool[pos];
        }

        return result;
    }
};

void setConsoleColor(int color)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, color);
}

void printToggleState(bool state)
{
    if (state)
    {
        setConsoleColor(10);
        cout << "[ON]\n";
    }
    else
    {
        setConsoleColor(12);
        cout << "[OFF]\n";
    }
    setConsoleColor(7);
}

int main()
{
    srand(time(NULL));
    TokenGenerator gen;
    bool running = true;
    string currentToken = gen.generate();

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);

    while (running)
    {
        system("cls");
        cout << "=======================================\n";
        cout << "            TOKEN GENERATOR\n";
        cout << "=======================================\n";
        cout << "Controls: Press keys [1] to [5] to toggle\n";
        cout << "          Press [L] to change length\n\n";

        cout << "[1] UpperCase   : ";
        printToggleState(gen.getUpper());
        cout << "[2] LowerCase   : ";
        printToggleState(gen.getLower());
        cout << "[3] Numbers     : ";
        printToggleState(gen.getNumbers());
        cout << "[4] Symbols     : ";
        printToggleState(gen.getSymbols());
        cout << "[5] No Ambiguous: ";
        printToggleState(gen.getAmbiguous());

        cout << "\nLength           : ";
        cout << gen.getLength();
        cout << endl;

        cout << "---------------------------------------\n";
        cout << "GENERATED TOKEN: " << currentToken << endl;
        cout << endl
             << "Press [R]efresh or [Q]uit." << endl;

        char key = _getch();
        bool settingsChanged = false;

        switch (tolower(key))
        {
        case '1':
            gen.toggleUpper();
            settingsChanged = true;
            break;
        case '2':
            gen.toggleLower();
            settingsChanged = true;
            break;
        case '3':
            gen.toggleNumbers();
            settingsChanged = true;
            break;
        case '4':
            gen.toggleSymbols();
            settingsChanged = true;
            break;
        case '5':
            gen.toggleAmbiguous();
            settingsChanged = true;
            break;

        case 'l':
            info.bVisible = TRUE;
            SetConsoleCursorInfo(consoleHandle, &info);
            cout << "\nEnter new length: ";
            int newlength;
            cin >> newlength;
            gen.setLength(newlength);
            break;
        case 'r':
            settingsChanged = true;
            break;
        case 'q':
            running = false;
            break;
        }
        if (settingsChanged)
            currentToken = gen.generate();
    }
}