FROM ubuntu:16.04

RUN apt-get update && apt-get install -y --no-install-recommends \
  perl binutils make build-essential flex bison ncurses-dev \
  gcc-arm-linux-gnueabi binutils-arm-linux-gnueabi bc \
  device-tree-compiler

WORKDIR /src

