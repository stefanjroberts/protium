#! /bin/bash

LDFLAGS=" -lglfw -lvulkan -ldl -lpthread -lm"

g++ -o bin/main -g src/main.cpp $LDFLAGS
