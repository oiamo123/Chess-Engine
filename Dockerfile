FROM ubuntu:22.04 AS build
WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    && rm -rf /var/lib/apt/lists/*

COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Debug
RUN cmake --build build