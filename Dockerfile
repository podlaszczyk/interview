FROM ubuntu:latest
LABEL authors="podlaszczyk"
ARG LLVM_TOOLS_VERSION=17

RUN apt-get update \
    && apt-get install -y  \
    cmake ninja-build build-essential python3 python3-pip wget lsb-release wget software-properties-common gnupg

# Adding given LLVM version repository to apt
RUN wget https://apt.llvm.org/llvm.sh  \
    && chmod +x llvm.sh \
    && ./llvm.sh ${LLVM_TOOLS_VERSION} \
    && apt update && apt install -y clang-tidy-${LLVM_TOOLS_VERSION} clang-format-${LLVM_TOOLS_VERSION} \
    && rm llvm.sh \
    && ln -s /usr/bin/clang-format-17 /usr/bin/clang-format \
    && ln -s /usr/bin/clang-tidy-17 /usr/bin/clang-tidy

RUN pip3 install conan==1.62.0 \
     && conan profile new default --detect \
     && conan profile update settings.compiler.libcxx=libstdc++11 default