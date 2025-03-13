FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    cmake \
    vim \
    git \
    g++23 \
    && rm -rf /var/lib/apt/lists/*

RUN git config --global --add safe.directory /app/build/_deps/catch2-src

COPY . /app

WORKDIR /app/build