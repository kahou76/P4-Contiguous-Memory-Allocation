#!/bin/bash

# Compile memory.c
gcc memory.c -o memory

# Run the resulting executable
./memory <<EOF
R script.txt
E
EOF

# Clean up
rm memory
