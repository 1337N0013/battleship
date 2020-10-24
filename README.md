# Battleship

Final project for CMSC 21

## Downloading the Project

`cd` into the folder where you want to put Battleship, then enter

```
$ git clone https://github.com/1337N0013/battleship.git
```

This should create a folder named `battleship` into the current folder. You can then `cd` into the `battleship` folder.

## Dependencies

You'll need the following tools to build the game:

- CMake
- Ninja

## Compiling

In `battleship`, create a `build` folder, then `cd` into it.

```shell
$ mkdir build
$ cd build
```

If you have CMake and Ninja properly installed, you can enter the following commands to build the game.

```shell
$ cmake -G Ninja ..
$ ninja
```

When it's done compiling, you can run the game with:

```shell
$ ./battleship
```

Or if you're on Windows:

```shell
> battleship.exe
```
