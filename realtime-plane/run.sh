#!/bin/bash
if [ -d "build" ]; then 
    cd build
    cmake ..
    make
    if [ -d "Simulator" ]; then 
        ./Simulator
    fi
else
    echo "build folder doesn't exist"
fi
