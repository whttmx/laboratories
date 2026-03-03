```cpp
#include <iostream>
#include <fstream>
#include <cstring>
#include <clocale>

using namespace std;

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool is_english_letter(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return (uc >= 65 && uc <= 90) || (uc >= 97 && uc <= 122);
}

bool is_russian_letter(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return (uc >= 192 && uc <= 223) || (uc >= 224 && uc <= 255) || uc == 168 || uc == 184;
}

bool is_letter(char c) {
    return is_english_letter(c) || is_russian_letter(c);
}

bool is_letter_or_digit(char c) {
    return is_letter(c) || is_digit(c);
}

char to_lower_char(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    if (uc >= 65 && uc <= 90)
        return uc + 32;
    if (uc >= 192 && uc <= 223) {
        if (uc == 168)
            return 184;
        return uc + 32;
    }
    if (uc == 168)
        return 184;
    return c;
}

const char* vowels = "аеёиоуъыьэюя";
const char* consonants = "бвгджзйклмнпрстфхцчшщ";

bool is_vowel(char c) {
    for (int i = 0; vowels[i] != '\0'; ++i)
        if (vowels[i] == c) return true;
    return false;
}

bool is_consonant(char c) {
    for (int i = 0; consonants[i] != '\0'; ++i)
        if (consonants[i] == c) return true;
    return false;
}

void print_table() {
    cout << "Таблица символов и их кодов (в десятичной системе):\n\n";

    cout << "Английские заглавные:\n";
    for (char c = 'A'; c <= 'Z'; ++c)
        cout << c << " - " << (int)c << "\n";

    cout << "\nАнглийские строчные:\n";
    for (char c = 'a'; c <= 'z'; ++c)
        cout << c << " - " << (int)c << "\n";

    cout << "\nЦифры:\n";
    for (char c = '0'; c <= '9'; ++c)
        cout << c << " - " << (int)c << "\n";

    const char* punct = ".,!?;:-()\"'";
    cout << "\nЗнаки препинания:\n";
    for (int i = 0; punct[i] != '\0'; ++i)
        cout << punct[i] << " - " << (int)punct[i] << "\n";

    const char* rus_upper = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    cout << "\nРусские заглавные:\n";
    for (int i = 0; rus_upper[i] != '\0'; ++i)
        cout << rus_upper[i] << " - " << (int)(unsigned char)rus_upper[i] << "\n";

    const char* rus_lower = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    cout << "\nРусские строчные:\n";
    for (int i = 0; rus_lower[i] != '\0'; ++i)
        cout << rus_lower[i] << " - " << (int)(unsigned char)rus_lower[i] << "\n";
}

void task1() {
    const int MAX_LEN = 101;
    char str[MAX_LEN];
    cout << "Введите строку (не более 100 символов): ";
    cin.getline(str, MAX_LEN);

    const char punct[] = ".,!?;:-()\"'";
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; ++i) {
        bool is_punct = false;
        for (int k = 0; punct[k] != '\0'; ++k) {
            if (str[i] == punct[k]) {
                is_punct = true;
                break;
            }
        }
        if (!is_punct) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
    cout << "Результат: " << str << endl;
}

void process_word(char* word, int len, char words[][256], int& word_count, int lengths[]) {
    while (len > 0 && !is_letter(word[len-1])) {
        --len;
    }
    if (len == 0) return;

    for (int i = 0; i < len; ++i) {
        word[i] = to_lower_char(word[i]);
    }
    word[len] = '\0';

    int v = 0, c = 0;
    for (int i = 0; i < len; ++i) {
        if (is_vowel(word[i]))
            ++v;
        else if (is_consonant(word[i]))
            ++c;
    }
    if (v != c) return;

    for (int i = 0; i < word_count; ++i) {
        if (strcmp(words[i], word) == 0)
            return;
    }

    strcpy(words[word_count], word);
    lengths[word_count] = len;
    ++word_count;
}

void task2() {

    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Ошибка: не удалось открыть input.txt\n";
        return;
    }
    int N;
    fin >> N;
    fin.close();
    if (N <= 0) {
        cerr << "Ошибка: N должно быть положительным числом\n";
        return;
    }

    ifstream ftext("text.txt");
    if (!ftext) {
        cerr << "Ошибка: не удалось открыть text.txt\n";
        return;
    }

    const int MAX_WORDS = 1000;
    const int WORD_LEN = 256;
    char words[MAX_WORDS][WORD_LEN];
    int lengths[MAX_WORDS];
    int word_count = 0;

    char ch;
    char buffer[WORD_LEN];
    int buf_len = 0;
    bool in_word = false;

    while (ftext.get(ch)) {
        if (is_letter_or_digit(ch)) {
            if (!in_word) {
                in_word = true;
                buf_len = 0;
                buffer[buf_len++] = ch;
            } else {
                if (buf_len < WORD_LEN - 1)
                    buffer[buf_len++] = ch;
            }
        } else if (ch == '-') {
            if (in_word) {
                if (buf_len < WORD_LEN - 1)
                    buffer[buf_len++] = ch;
            }
        } else {
            if (in_word) {
                process_word(buffer, buf_len, words, word_count, lengths);
                in_word = false;
            }
        }
    }
    if (in_word) {
        process_word(buffer, buf_len, words, word_count, lengths);
    }
    ftext.close();

    for (int i = 0; i < word_count - 1; ++i) {
        for (int j = i + 1; j < word_count; ++j) {
            if (lengths[i] < lengths[j]) {
                int tmp_len = lengths[i];
                lengths[i] = lengths[j];
                lengths[j] = tmp_len;
                char tmp_word[WORD_LEN];
                strcpy(tmp_word, words[i]);
                strcpy(words[i], words[j]);
                strcpy(words[j], tmp_word);
            }
        }
    }

    ofstream fout("result.txt");
    if (!fout) {
        cerr << "Ошибка: не удалось создать result.txt\n";
        return;
    }
    int count = (word_count < N) ? word_count : N;
    for (int i = 0; i < count; ++i) {
        fout << words[i] << endl;
    }
    fout.close();
    cout << "Результат записан в result.txt\n";
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    cout << "=== Пункт 0 ===\n";
    print_table();

    cout << "\n=== Задача 1 ===\n";
    task1();

    cout << "\n=== Задача 2 ===\n";
    task2();

    return 0;
}
