#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <shlobj.h>
#include <filesystem>

using namespace std;

string xorEncryptDecrypt(const string& text, char key) {
    string output = text;

    for (size_t i = 0; i < text.size(); i++) {
        output[i] = text[i] ^ key;
    }

    return output;
}

int main() {
    int choice;
    string text;
    char key;

    cout << "Choose an option:\n";
    cout << "1. Decrypt text\n";
    cout << "2. Encrypt text\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "Enter text to decrypt (in hexadecimal format): ";
        getline(cin, text);
        cout << "Enter key (one character): ";
        cin >> key;

        string decryptedText;
        for (size_t i = 0; i < text.length(); i += 2) {
            string byteString = text.substr(i, 2);
            char byte = (char)(stoi(byteString, nullptr, 16));
            decryptedText += byte;
        }

        string finalDecryptedText = xorEncryptDecrypt(decryptedText, key);
        cout << "Decrypted text: " << finalDecryptedText << endl;

    }
    else if (choice == 2) {
        cout << "Enter text to encrypt: ";
        getline(cin, text);
        cout << "Enter key (one character): ";
        cin >> key;

        // Шифруем текст
        string cipherText = xorEncryptDecrypt(text, key);
        cout << "Encrypted text (hex): ";
        for (char c : cipherText) {
            cout << hex << (int)c;
        }
        cout << endl;
        char saveOption;
        cout << "Do you want to save the key and encrypted text to a file on the desktop? (y/n): ";
        cin >> saveOption;

        if (saveOption == 'y' || saveOption == 'Y') {
            char path[MAX_PATH];
            if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path))) {
                string desktopPath = string(path) + "\\encrypted_data.txt";
                cout << "Path to save file: " << desktopPath << endl;
                ofstream outFile(desktopPath);
                if (outFile.is_open()) {
                    outFile << "Key: " << key << endl;
                    outFile << "Encrypted text (hex): ";
                    for (char c : cipherText) {
                        outFile << hex << (int)c;
                    }
                    outFile << endl;
                    outFile.close();
                    cout << "Data saved to " << desktopPath << endl;
                }
                else {
                    cout << "Error opening file for writing." << endl;
                }
            }
            else {
                cout << "Error getting desktop path." << endl;
            }
        }
    }
    else {
        cout << "Invalid choice. Please enter 1 or 2." << endl;
    }

    return 0;
}