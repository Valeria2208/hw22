//
//  main.cpp
//  hw22
//
//  Created by Valeria Dudinova on 08.12.2024.
//

#include <iostream>

using namespace std;

// Функція для перевірки валідності HTML
bool validateHTML(const char* htmlContent)
{
    const char* tags[100];
    int top = -1;

    const char* pos = htmlContent;

    while (*pos != '\0')
    {
        // Шукаємо початок тегу
        const char* startTag = strchr(pos, '<');
        if (!startTag) break;

        const char* endTag = strchr(startTag, '>');
        if (!endTag) {
            cout << "Eror: not found closing symbol '>'." << endl;
            return false;
        }

        // Визначаємо довжину тегу
        int tagLength = endTag - startTag - 1;
        if (tagLength <= 0) {
            cout << "Error: empty tag." << endl;
            return false;
        }

        // Перевіряємо, чи є тег закриваючим
        if (*(startTag + 1) == '/') {
            // Закриваючий тег
            if (top == -1) {
                cout << "Error: closing tag </" << string(startTag + 2, tagLength - 1) << "> не має пари." << endl;
                return false;
            }

            const char* openingTag = tags[top--]; // Знімаємо тег з "стека"
            if (strncmp(openingTag, startTag + 2, tagLength - 1) != 0) {
                cout << "Error: tag </" << string(startTag + 2, tagLength - 1) << "> does not match an open tag." << endl;
                return false;
            }
        } else {
            // Відкриваючий тег
            if (top == 99) {
                cout << "error: too many nested tags." << endl;
                return false;
            }

            tags[++top] = startTag + 1; // Додаємо в "стек"
        }

        pos = endTag + 1; // Переходимо до наступної частини
    }

    // Перевіряємо, чи залишилися незакриті теги
    if (top != -1) {
        cout << "Error: Unclosed tags left." << endl;
        return false;
    }

    cout << "The HTML file is valid." << endl;
    return true;
}

int main() {
    // Введення HTML-коду від користувача
    cout << "Enter the HTML code (one line): ";
    char htmlContent[1000];
    cin.getline(htmlContent, 1000);

    // Викликаємо функцію валідації
    validateHTML(htmlContent);

    return 0;
}

