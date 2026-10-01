#! /bin/bash

LDFLAGS=" -lglfw -lvulkan -ldl -lpthread -lm"

g++ -o build/main -g src/main.cpp src/extern/glad.c $LDFLAGS
