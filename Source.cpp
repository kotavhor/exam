#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <cstring> 

void readDelimiters(const char* filename, std::string& delimiters) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::getline(file, delimiters);
        file.close();
    }
    else {
        throw "Ошибка при открытии файла для чтения разделителей.\n";
    }
}

std::string readText(const char* filename) {
    std::ifstream file(filename);
    std::string line, text = "";

    if (!file.is_open()) {
        throw "Ошибка при открытии файла для чтения текста.\n";
    }

    std::getline(file, line); 

    while (std::getline(file, line)) {
        text += line + '\n';
    }

    file.close();
    return text;
}

char* convertToCharArray(const std::string& text) {
    char* charArray = new char[text.length() + 1];
    strcpy_s(charArray, text.length() + 1, text.c_str()); 
    return charArray;
}

void replaceDelimiters(char* text, const std::string& delimiters) {
    for (int i = 0; text[i] != '\0'; i++) {
        for (char delim : delimiters) {
            if (text[i] == delim) {
                text[i] = ' ';
                break;
            }
        }
    }
}

bool isDigitsOnly(const std::string& word) {
    if (word.empty()) return false;

    size_t start = 0;
    if (word[0] == '-') {
        if (word.length() == 1) return false; 
        start = 1;
    }

    for (size_t i = start; i < word.length(); ++i) {
        if (!isdigit(word[i])) return false;
    }
    return true;
}


int32_t countDigits(int32_t number) {
    if (number == 0) return 1;
    int32_t digits = 0;
    while (number < 1) {
        number /= 10;
        ++digits;
    }
    return digits;
}

void extractNumbers(char* text) {
    std::stringstream ss(text);
    std::string word;

    const int MAX_NUMBERS = 1000;
    int numbers[MAX_NUMBERS];
    int count = 0;

    while (ss >> word) {
        if (isDigitsOnly(word)) {
            if (count < MAX_NUMBERS) {
                numbers[count++] = std::stoi(word);
            }
        }
    }

    if (count == 0) {
        std::cout << "Числа не найдены.\n";
    }
    else {
        std::cout << "Найденные числа:\n";
        for (int i = 0; i < count; ++i) {
            std::cout << numbers[i] << " ";
        }
        std::cout << std::endl;
    }

    int32_t sorted[MAX_NUMBERS];
    for (int32_t i = 0; i < count; ++i) {
        sorted[i] = numbers[i];
    }

    for (int32_t i = 0; i < count - 1; ++i) {
        for (int32_t j = i + 1; j < count; ++j) {
            if (countDigits(sorted[i]) > countDigits(sorted[j])) {
                std::swap(sorted[i], sorted[j]);
            }
        }
    }
    std::cout << "Числа по количеству цифр:\n";
    for (int32_t i = 0; i < count; ++i) {
        std::cout << sorted[i] << " ";
    }
    std::cout << std::endl;

}

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        const char* filename = "file.txt";

        std::string delimiters;
        readDelimiters(filename, delimiters);

        std::string text = readText(filename);

        char* textBuffer = convertToCharArray(text);

        replaceDelimiters(textBuffer, delimiters);

        extractNumbers(textBuffer);

        delete[] textBuffer;
    }
    catch (const char* msg) {
        std::cout << msg;
    }

    return 0;
}

