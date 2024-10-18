FROM ubuntu:noble

WORKDIR /home/

RUN apt update
RUN apt -y upgrade
RUN apt install -y autoconf automake autotools-dev bc bison build-essential cmake curl flex gawk git gperf libexpat-dev libglib2.0-dev libgmp-dev libgoogle-perftools-dev libmpc-dev libmpfr-dev libprotobuf-dev libprotoc-dev libslirp-dev libtool m4 ninja-build patchutils protobuf-compiler pre-commit mypy python-is-python3 python3 python3-dev python3-pip python3-venv scons texinfo zlib1g zlib1g-dev

ENV RISCV=/opt/riscv
ENV PATH=$PATH:$RISCV/bin

ARG TOOLCHAIN_VERSION=2024.04.12
RUN    git clone https://github.com/riscv/riscv-gnu-toolchain -b ${TOOLCHAIN_VERSION} \
    && cd riscv-gnu-toolchain                            \
    && ./configure --prefix=$RISCV --enable-multilib     \
    && make -j`nproc`                                    \
    && cd ..                                             \
    && rm -rf riscv-gnu-toolchain

COPY setup-gem5.sh /home/setup-gem5.sh  
