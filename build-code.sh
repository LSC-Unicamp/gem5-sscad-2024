#!/bin/bash

# Build the multiplication
riscv64-unknown-elf-gcc -O3 code/naive-multiply.c -o code/naive-multiply.riscv
riscv64-unknown-elf-gcc -O3 code/naive-multiply-big.c -o code/naive-multiply-big.riscv -Igem5/include -Lgem5/util/m5/build/riscv/out -lm5
riscv64-unknown-elf-gcc -O3 code/matrix-multiply.c -o code/matrix-multiply.riscv
riscv64-unknown-elf-gcc -O3 code/matrix-multiply-big.c -o code/matrix-multiply-big.riscv -I./gem5/include -Lgem5/util/m5/build/riscv/out -lm5

# objdump the code
riscv64-unknown-elf-objdump -d code/naive-multiply.riscv > code/naive-multiply.dump
riscv64-unknown-elf-objdump -d code/matrix-multiply.riscv > code/matrix-multiply.dump


# Simulate
# from sscad folder run
# ./gem5/build/RISCV/gem5.opt se-mode-atomic.py naive-multiply.riscv
# Take a look at the generated m5out file
