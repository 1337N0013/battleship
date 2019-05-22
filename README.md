# Battleship

Final project for CMSC 21

## Downloading the Project

`cd` into the folder where you want to put Battleship, then enter
```
git clone https://github.com/1337N0013/battleship
```
This should create a folder named `battleship` into the current folder.

You can then `cd` into the `battleship` folder.

## Compiling

While in the `battleship` folder, type
```
make
```
into your console. This creates a `main` binary inside `bin/` and `.o` files inside `obj/`.

You can then run the binary with
```
./bin/main
```

## Cleaning Compiled Files

To remove the compiled files, type
```
make clean
```
Sometimes things (usually font loading) result in segfaults. Try using this and recompiling before moving on.

## TODO

- [ ] Clean up Button.h
- [x] Figure out how to call functions using the buttons
- [x] Create a scene system (main menu, options, the game itself, etc.)
- [x] Game logic