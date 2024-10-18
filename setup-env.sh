#!/bin/bash
docker build --tag 'riscv-tools' --file Dockerfile .
docker run -v ./gem5:/home/gem5 riscv-tools sh setup-gem5.sh
