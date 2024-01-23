#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <Windows.h>
#include <filesystem>

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#pragma warning(disable : 4996)

int wingetInstall() {
    std::cout << "WARNING! IF YOU GET AN ERROR, TRY TO INSTALL WITH ANOTHER METHOD! \n";
    std::string userInput1;
    std::cout << "Continue? (Y/N): ";
    std::cin >> userInput1;

    if (userInput1 == "Y" || userInput1 == "Yes" || userInput1 == "y") {
        std::string themeName;
        std::cout << "Enter theme name (e.g., blue-owl): ";
        std::cin >> themeName;

        std::string installCommand = "oh-my-posh init pwsh --config 'https://raw.githubusercontent.com/JanDeDobbeleer/oh-my-posh/main/themes/" + themeName + ".omp.json' | Invoke-Expression";

        system("powershell winget install JanDeDobbeleer.OhMyPosh -s winget");
        system("oh-my-posh font install --user CascadiaCode");
        system("powershell New-Item -Path $PROFILE -Type File -Force");
        std::ifstream inputFile("$PROFILE");

        if (inputFile.is_open()) {
            std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
            inputFile.close();

            content = installCommand;

            std::ofstream outputFile("$PROFILE");
            outputFile << content;
            outputFile.close();

            std::cout << "Success" << std::endl;
        }
        else {
            std::cout << "Failed to edit PowerShell Profile" << std::endl;
        }
    }
    else if (userInput1 == "N" || userInput1 == "No" || userInput1 == "n") {
        std::cout << "Exiting..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        exit(0);
    }
    else {
        std::cout << "Invalid input. Please enter Y or N." << std::endl;
    }
    return 0;
}

int manualInstall() {
    std::string userInput2;
    std::cout << "Do you want to install? (Y/N): ";
    std::cin >> userInput2;

    if (userInput2 == "Y" || userInput2 == "Yes" || userInput2 == "y") {
        std::string themeName;
        std::cout << "Enter theme name (e.g., blue-owl): ";
        std::cin >> themeName;

        std::string installCommand = "oh-my-posh init pwsh --config 'https://raw.githubusercontent.com/JanDeDobbeleer/oh-my-posh/main/themes/" + themeName + ".omp.json' | Invoke-Expression";

        system("powershell Set-ExecutionPolicy Bypass -Scope Process -Force; Invoke-Expression ((New-Object System.Net.WebClient).DownloadString('https://ohmyposh.dev/install.ps1'))");
        system("oh-my-posh font install --user CascadiaCode");
        system("powershell New-Item -Path $PROFILE -Type File -Force");
        std::ifstream inputFile("$PROFILE");

        if (inputFile.is_open()) {
            std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
            inputFile.close();

            content = installCommand;

            std::ofstream outputFile("$PROFILE");
            outputFile << content;
            outputFile.close();

            std::cout << "Success" << std::endl;
        }
        else {
            std::cout << "Failed to edit PowerShell Profile" << std::endl;
        }
    }
    else if (userInput2 == "N" || userInput2 == "No" || userInput2 == "n") {
        std::cout << "Exiting..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        exit;
    }
    else {
        std::cout << "Invalid input. Please enter Y or N." << std::endl;
    }
    return 0;
}

std::string getUsername() {
    char* username;
    size_t len;
    errno_t err = _dupenv_s(&username, &len, "USERPROFILE");
    return std::string(username);
}


bool doesDirectoryExist(const std::string& path) {
    std::filesystem::path p(path);
    return std::filesystem::exists(p) && std::filesystem::is_directory(p);
}

int main() {
    std::string username = getUsername();
    std::string path = "C:\\Users\\" + username + "\\AppData\\Local\\Programs\\oh-my-posh\\bin";

    if (doesDirectoryExist(path)) {
        std::cout << "Oh-My-Posh is installed." << std::endl;
        exit;
    }

    std::string userInput;
    std::cout << "Do you want to install using WinGet? (Y/N): ";
    std::cin >> userInput;

    if (userInput == "Y" || userInput == "Yes" || userInput == "y") {
        system("cls");
        wingetInstall();
    }
    else if (userInput == "N" || userInput == "No" || userInput == "n") {
        std::cout << "Installing with other method..." << std::endl;
        system("cls");
        manualInstall();
    }
    else {
        std::cout << "Invalid input. Please enter Y or N." << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    return 0;
}
