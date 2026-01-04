# 🛠️ IT Tools Collection

<div align="center">

![Tools](https://img.shields.io/badge/Tools-2-blue?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows)
![Status](https://img.shields.io/badge/Status-Active-success?style=for-the-badge)

<br>

**A powerful collection of IT security and utility tools built with C++**

*Designed for developers, security enthusiasts, and IT professionals*

<br>

> ⚡ **This repository is actively maintained — more tools are being added regularly!** ⚡

---

### 🚀 Quick Navigation

[🔐 Password Strength Analyzer](#-password-strength-analyzer) • [🎲 Token Generator](#-token-generator) • [📦 Installation](#-installation) • [🔮 Coming Soon](#-coming-soon)

---

</div>

<br>

## 📋 Tools Overview

<table>
<tr>
<td width="50%" valign="top">

### [🔐 Password Strength Analyzer](#-password-strength-analyzer)

Evaluate password security in **real-time** with entropy calculation, pattern detection, and comprehensive scoring.

**Highlights:**
- ⚡ Live analysis as you type
- 📊 Entropy-based scoring
- 🔍 Pattern & sequence detection
- 🎭 Password masking toggle

</td>
<td width="50%" valign="top">

### [🎲 Token Generator](#-token-generator)

Generate **cryptographically-informed** random tokens with fully customizable character sets.

**Highlights:**
- 🎛️ 5 customizable options
- 📏 Adjustable length
- 🚫 Ambiguous char filtering
- ♻️ Instant regeneration

</td>
</tr>
</table>

---

<br>

# 🔐 Password Strength Analyzer

Real-time password security evaluation at your fingertips — type and see!

<br>

## 📖 What Does It Do?

The **Password Strength Analyzer** is an interactive console application that evaluates your password's security **in real-time**. Every keystroke triggers an instant analysis, providing immediate feedback on:

- ✅ Character composition
- ✅ Entropy (randomness measure)
- ✅ Common vulnerability patterns
- ✅ Overall security score

<br>

## 🎯 Features at a Glance

<table>
<tr>
<td>⌨️</td>
<td><b>Real-Time Analysis</b></td>
<td>Instant feedback with every keystroke</td>
</tr>
<tr>
<td>🔢</td>
<td><b>Entropy Calculation</b></td>
<td>Information theory-based randomness measurement</td>
</tr>
<tr>
<td>📋</td>
<td><b>7-Point Checklist</b></td>
<td>Visual requirement validation</td>
</tr>
<tr>
<td>🎭</td>
<td><b>Mask Toggle</b></td>
<td>Show/hide password with TAB</td>
</tr>
<tr>
<td>🚨</td>
<td><b>Pattern Detection</b></td>
<td>Catches repeated chars & common sequences</td>
</tr>
<tr>
<td>📊</td>
<td><b>Security Score</b></td>
<td>0-100 score for quick assessment</td>
</tr>
</table>

<br>

## 🖥️ Live Preview

```
================================================
          PASSWORD STRENGTH ANALYZER
================================================
Password: MyP@ssw0rd█
-------------------------------------------------
REQUIREMENTS: 
[OK] Lowercase Letters        ✓
[OK] Uppercase Letters        ✓
[OK] Numbers                  ✓
[OK] Symbols                  ✓
[OK] Minimum 8 characters     ✓
[OK] No repeated characters   ✓
[OK] No common sequences      ✓
-------------------------------------------------
Entropy: 65 bits
Score:   50 / 100
================================================
 [ESC] Quit | [TAB] Hide | [BKSP] Delete
```

<br>

## 🎮 Controls

<div align="center">

| Key | Action | Description |
|:---:|:------:|:------------|
| `Any Key` | ➕ Add | Add character to password |
| `BACKSPACE` | ⬅️ Delete | Remove last character |
| `TAB` | 👁️ Toggle | Show/Hide password |
| `ESC` | 🚪 Exit | Quit the application |

</div>

<br>

## 🧮 How Scoring Works

### Step 1: Calculate Character Pool

The analyzer determines available characters based on what you've used:

| Character Type | Pool Size | Characters                          |
|----------------|-----------|-------------------------------------|
| Lowercase      | 26        | abcdefghijklmnopqrstuvwxyz          |
| Uppercase      | 26        | ABCDEFGHIJKLMNOPQRSTUVWXYZ          |
| Digits         | 10        | 0123456789                          |
| Symbols        | 32        | !@#$%^&*()_+-=[]{}|;':",.<>?        |


### Step 2: Calculate Raw Entropy

```
📐 Formula: Entropy = Length × log₂(Pool Size)
```

**Example:**
> Password: `MyP@ss123` (Length: 9)
> Pool: 26 + 26 + 10 + 32 = 94 characters
> Entropy: 9 × log₂(94) ≈ 59 bits

### Step 3: Apply Penalties

| Bad Pattern Detected          | Penalty    |
|------------------------------|------------|
| 🔄 3+ repeated characters    | -15 bits   |
| 📝 Common sequences found    | -25 bits   |


### Step 4: Calculate Final Score

```
📊 Score = min(100, (Adjusted Entropy ÷ 128) × 100)
```

<br>

## 🚨 Detected Bad Patterns

<details>
<summary><b>Click to see all detected sequences</b></summary>

<br>

The analyzer scans for these weak patterns (case-insensitive):

| Category | Patterns |
|----------|----------|
| **Numeric Sequences** | `123`, `234`, `345`, `456`, `567`, `678`, `789` |
| **Alphabetic** | `abc` |
| **Keyboard Patterns** | `qwerty`, `asdf` |
| **Common Words** | `password` |

</details>

<br>

## 🏗️ Code Architecture

```cpp
class StrengthAnalyser
{
public:
    struct AnalysisResult
    {
        // 📏 Metrics
        int length;           // Password length
        int poolsize;         // Character pool size
        double entropy;       // Calculated entropy (bits)
        int score;            // Final score (0-100)
        
        // ✅ Character Checks
        bool hasLower;        // Contains a-z
        bool hasUpper;        // Contains A-Z
        bool hasDigit;        // Contains 0-9
        bool hasSymbol;       // Contains symbols
        
        // 📋 Requirement Checks
        bool hasLength;       // Length >= 8
        bool hasRepeats;      // Has bad repeats (aaa)
        bool hasSequence;     // Has bad sequences (123)
    };

    // 🔍 Analysis Methods
    bool checkhasRepeats(string password);    // Detect 3+ consecutive repeats
    bool checkhasSequence(string password);   // Detect common patterns
    AnalysisResult analyze(string password);  // Main analysis engine
};
```

<br>

## 📊 Strength Level Guide

| Score | Level | Entropy | Recommendation |
|:-----:|:-----:|:-------:|:---------------|
| 0-20 | 🔴 **Very Weak** | 0-25 bits | Don't use this! |
| 21-40 | 🟠 **Weak** | 26-50 bits | Needs improvement |
| 41-60 | 🟡 **Fair** | 51-75 bits | Acceptable for low-risk |
| 61-80 | 🟢 **Strong** | 76-100 bits | Good for most uses |
| 81-100 | 💪 **Very Strong** | 101-128+ bits | Excellent security! |

---

<br>

# 🎲 Token Generator

Generate secure random tokens instantly with fully customizable options!

<br>

## 📖 What Does It Do?

The **Token Generator** creates random, secure tokens perfect for:

- 🔑 API Keys
- 🔐 Strong Passwords
- 🎫 Session Tokens
- 🆔 Unique Identifiers
- 🔒 Secret Keys

<br>

## 🎯 Features at a Glance

<table>
<tr>
<td>🎛️</td>
<td><b>5 Toggle Options</b></td>
<td>Full control over character sets</td>
</tr>
<tr>
<td>📏</td>
<td><b>Custom Length</b></td>
<td>Any length you need</td>
</tr>
<tr>
<td>🚫</td>
<td><b>Ambiguous Filter</b></td>
<td>Exclude confusing characters</td>
</tr>
<tr>
<td>♻️</td>
<td><b>Instant Refresh</b></td>
<td>New token with one keypress</td>
</tr>
<tr>
<td>🎨</td>
<td><b>Color Coded</b></td>
<td>Visual ON/OFF states</td>
</tr>
</table>

<br>

## 🖥️ Live Preview

```
=======================================
            TOKEN GENERATOR
=======================================
Controls: Press keys [1] to [5] to toggle
          Press [L] to change length

[1] UpperCase   : [ON]  🟢
[2] LowerCase   : [ON]  🟢
[3] Numbers     : [ON]  🟢
[4] Symbols     : [ON]  🟢
[5] No Ambiguous: [OFF] 🔴

Length           : 16
---------------------------------------
GENERATED TOKEN: aB3$kL9@mNpQ2&xZ

Press [R]efresh or [Q]uit.
```

<br>

## 🎮 Controls

<div align="center">

| Key | Action | Description |
|:---:|:------:|:------------|
| `1` | 🔤 Toggle | Uppercase letters ON/OFF |
| `2` | 🔡 Toggle | Lowercase letters ON/OFF |
| `3` | 🔢 Toggle | Numbers ON/OFF |
| `4` | 🔣 Toggle | Symbols ON/OFF |
| `5` | 🚫 Toggle | Exclude ambiguous chars |
| `L` | 📏 Length | Set custom token length |
| `R` | ♻️ Refresh | Generate new token |
| `Q` | 🚪 Quit | Exit the application |

</div>

<br>

## 🔤 Character Sets

<table>
<tr>
<th>Category</th>
<th>Characters</th>
<th>Count</th>
</tr>
<tr>
<td>🔠 <b>Uppercase</b></td>
<td><code>ABCDEFGHIJKLMNOPQRSTUVWXYZ</code></td>
<td align="center">26</td>
</tr>
<tr>
<td>🔡 <b>Lowercase</b></td>
<td><code>abcdefghijklmnopqrstuvwxyz</code></td>
<td align="center">26</td>
</tr>
<tr>
<td>🔢 <b>Numbers</b></td>
<td><code>0123456789</code></td>
<td align="center">10</td>
</tr>
<tr>
<td>🔣 <b>Symbols</b></td>
<td><code>!@#$%&?</code></td>
<td align="center">7</td>
</tr>
</table>

<br>

## 🚫 Ambiguous Characters

When **"No Ambiguous"** is enabled, these confusing characters are excluded:

<div align="center">

```
┌─────────────────────────────────────────────┐
│                                             │
│     0 (zero)  ←→  O (letter O)              │
│     1 (one)   ←→  l (lowercase L)           │
│               ←→  I (uppercase i)           │
│                                             │
│     Excluded: 0, O, I, l, 1                 │
│                                             │
└─────────────────────────────────────────────┘
```

</div>

> 💡 **Use Case:** Enable this when tokens need to be read/typed manually to avoid confusion!

<br>

## 🏗️ Code Architecture

```cpp
class TokenGenerator
{
private:
    // ⚙️ Configuration
    int length;               // Token length (default: 16)
    bool includeUpper;        // A-Z (default: true)
    bool includeLower;        // a-z (default: true)
    bool includeNumbers;      // 0-9 (default: true)
    bool includeSymbols;      // !@#$%&? (default: true)
    bool excludeAmbiguous;    // Filter 0OIl1 (default: false)

    // 📚 Character Libraries
    const string UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string LOWER = "abcdefghijklmnopqrstuvwxyz";
    const string NUMS  = "0123456789";
    const string SYM   = "!@#$%&?";
    const string AMBIGUOUS = "0OIl1";

public:
    // 🔧 Getters & Toggles
    bool getUpper();          void toggleUpper();
    bool getLower();          void toggleLower();
    bool getNumbers();        void toggleNumbers();
    bool getSymbols();        void toggleSymbols();
    bool getAmbiguous();      void toggleAmbiguous();
    int getLength();          void setLength(int l);
    
    // 🎲 Generation
    string generate();        // Create random token
};
```

<br>

# 📦 Installation

## Prerequisites

<table>
<tr>
<td>🖥️</td>
<td><b>Platform</b></td>
<td>Windows OS (uses Windows API)</td>
</tr>
<tr>
<td>⚙️</td>
<td><b>Compiler</b></td>
<td>C++11 or later (MinGW / MSVC)</td>
</tr>
<tr>
<td>📚</td>
<td><b>Dependencies</b></td>
<td>Windows.h, conio.h (included with Windows)</td>
</tr>
</table>

<br>

## 🔨 Compilation

### Using g++ (MinGW)

```bash
# Clone the repository
git clone https://github.com/yourusername/IT-Tools.git
cd IT-Tools

# Compile Password Strength Analyzer
g++ -o PasswordStrengthAnalyzer.exe PasswordStrengthAnalyzer.cpp

# Compile Token Generator
g++ -o TokenGenerator.exe TokenGenerator.cpp
```

### Using MSVC (Visual Studio)

```bash
# Compile Password Strength Analyzer
cl PasswordStrengthAnalyzer.cpp

# Compile Token Generator
cl TokenGenerator.cpp
```

<br>

## ▶️ Running

```bash
# Run Password Strength Analyzer
./PasswordStrengthAnalyzer.exe

# Run Token Generator  
./TokenGenerator.exe
```

---

<br>

# 📁 Project Structure

```
IT-Tools/
│
├── 📄 README.md                       # You are here!
│
├── 🔐 PasswordStrengthAnalyzer.cpp    # Password analysis tool
│
├── 🎲 TokenGenerator.cpp              # Token generation tool
│
└── 🔮 (more tools coming soon...)
```

---

<br>

# 🔮 Coming Soon

<div align="center">

> **🚧 This repository is under active development! 🚧**

</div>

<br>

### Planned Tools

| Status | Tool | Description |
|:------:|:-----|:------------|
| 📋 | **Hash Generator** | MD5, SHA-1, SHA-256, SHA-512 |
| 📋 | **Base64 Encoder/Decoder** | Encode and decode Base64 strings |
| 📋 | **UUID Generator** | Generate unique identifiers |
| 📋 | **File Checksum Validator** | Verify file integrity |
| 📋 | **Network Scanner** | Scan local network devices |
| 📋 | **Port Scanner** | Check open ports on hosts |
| 📋 | **Encryption Tool** | AES/DES encryption & decryption |
| 📋 | **System Info Tool** | Display system information |
| 📋 | **JSON Formatter** | Pretty print JSON data |
| 📋 | **Regex Tester** | Test regular expressions |

<br>

> 💡 **Have a suggestion?** Open an issue and let us know what tools you'd like to see!

---

<br>
