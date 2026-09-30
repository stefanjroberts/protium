#! /bin/bash

LDFLAGS=" -lglfw -lvulkan -ldl -lpthread -lm"

g++ -o build/main -g src/main.cpp $LDFLAGS
