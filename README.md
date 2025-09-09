🎯 Description

"Game Roulette" is a C program that helps gamers randomly select a game from their personal library. Users can add, remove, and view games, then spin the roulette to let fate decide their next gaming session!
✨ Features

    Random Game Selection: Fair random selection using time-based seeding

    Game Library Management: Add, remove, and view your game collection

    Animated Selection: Visual feedback with spinning animation

    File Persistence: Games are saved between sessions

    Directory Management: Automatically creates necessary folders

    Windows Compatibility: Designed for Windows systems

🚀 How to Use

    Compile the program

    Run the executable

    Add your games to the library

    Spin the roulette to randomly select a game

    Enjoy your chosen game!

🛠️ Compilation

Compile using any C compiler (tested on Windows):
bash

gcc -o game_roulette roulette.c

📋 Requirements

    Windows OS (uses Windows-specific headers)

    C compiler (GCC or MinGW recommended)

    Standard C library

🎮 Functions

    menu() - Displays the main menu

    roulette() - Randomly selects and displays a game

    add_Game() - Adds a new game to the library

    remove_Game() - Removes a game from the library

    show_Games() - Displays all games in the library

    read_Int() - Reads integer input

    read_Name() - Reads string input

📝 Note

This version is specifically designed for Windows systems. For Linux/Mac compatibility, the Windows-specific headers and functions would need to be adapted.
