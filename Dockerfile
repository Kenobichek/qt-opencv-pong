# ===== Stage 1: Build =====
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential cmake git qtbase5-dev libqt5widgets5 \
    libopencv-dev libgl1-mesa-glx \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app

# ===== Stage 2: Runtime =====

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug \
 && cmake --build build --parallel $(nproc)

WORKDIR /app/build

CMD ["./CameraPingPong"]
