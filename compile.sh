#!/bin/bash
clang++ -std=c++17 -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -o bin/main src/main.cpp src/Button.cpp src/Engine.cpp -I
bin/main