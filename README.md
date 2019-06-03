# Battleship

Final project for CMSC 21

## Downloading the Project

`cd` into the folder where you want to put Battleship, then enter
```
git clone https://github.com/1337N0013/battleship.git
```
This should create a folder named `battleship` into the current folder. You can then `cd` into the `battleship` folder.

## Dependencies

Make sure SFML is installed correctly on your system. SFML can be downloaded from [here.](https://www.sfml-dev.org/download.php)
There are tutorials on how to install it on the website.

Also make sure `make` is installed on your system. There should be tutorials online for Windows systems if you're using MinGW.

## Compiling

While in the `battleship` folder, type
```
make
```
into your console. This creates a `main` binary inside `bin/` and `.o` files inside `obj/`.
On Windows systems, you'll have to create the `bin/` and `obj/` folders yourself.

You can then run the binary with
```
./bin/main
```
or
```
\bin\main
```
on Windows systems.

## Cleaning Compiled Files

To remove the compiled files, type
```
make clean
```
Sometimes things result in segfaults. Try using this and recompiling before moving on.
On Windows systems, you'll have to delete the files inside `bin/` and `obj/` yourself.