# Battleship

Final project for CMSC 21

## Downloading the Project

`cd` into the folder where you want to put Battleship, then enter
```
git clone https://github.com/1337N0013/battleship.git
```
This should create a folder named `battleship` into the current folder. You can then `cd` into the `battleship` folder.

## Dependencies

Make sure `make` is installed on your system. There should be tutorials online for Windows systems if you're using MinGW.

## Compiling

While in the `battleship` folder, enter
```
make
```
into your console. This creates a `battleship` binary at the directory root and `.o` files inside `obj/`.
On Windows systems, you might have to create the `obj/` folder yourself.

You can then run the binary with on MacOS or Linux systems.
```
./battleship
```

If you're on a Windows system, enter
```
battleship.exe
```
or simply double click it.

## Cleaning Compiled Files

To remove the compiled files, type
```
make clean
```
Sometimes things result in segfaults. Try using this and recompiling before moving on.
On Windows systems, you might have to delete `battleship.exe` and `obj/` yourself.
