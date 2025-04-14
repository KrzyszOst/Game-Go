# 🕹️ Console-Based Go Game 🧱

This is a university project developed for the **Basics of Computer Programming** course.  
The task was to implement a simple terminal game in C++ — and I chose **Go (Baduk/Weiqi)**, a classic strategic board game.

## 🚀 Features

- 🎮 **Fully Playable Console Game** — Navigate and place stones with keyboard input  
- 🧠 **Rules Implemented** — Capturing mechanics, suicide prevention, handicap mode  
- 📁 **Save & Load System** — Save your board state and continue later  
- ⚙️ **Custom Board Sizes** — Choose standard 9x9, 13x13, 19x19 or define your own size  
- 💡 **Text-Based UI** — Uses `conio2.h` for cursor positioning and color output

## 🧱 How It Works

- Use **arrow keys** to move the cursor  
- Press `i` to place a stone  
- Use `s` to save, `l` to load, and `n` to start a new game  
- `h` enables handicap mode (white starts at 6.5 points), `g` disables it  
- Press `q` to quit

## 🔧 Installation & Run

Make sure you are using **Windows with a C++ compiler** that supports the `conio2` library.

```bash
git clone https://github.com/yourusername/go-console-game.git
cd go-console-game
g++ project.cpp conio2.cpp -o go-game -std=c++11
./go-game
