#! /bin/bash

LDFLAGS=" -lglfw -lvulkan -ldl -lpthread -lm"
INTERNALSOURCE=" src/main.cpp"
EXTERNALSOURCE=" src/extern/glad.c "

g++ -o build/main -g $INTERNALSOURCE $EXTERNALSOURCE $LDFLAGS
