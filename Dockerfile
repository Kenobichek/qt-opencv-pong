# ===== Stage 1: Build =====
FROM ubuntu:22.04 AS build

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential cmake qtbase5-dev libopencv-dev libgl1-mesa-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app

RUN mkdir build && cd build && cmake .. && make -j$(nproc)

# ===== Stage 2: Runtime =====
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    libqt5widgets5 libopencv-dev libgl1-mesa-glx \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=build /app/build/CameraPingPong /app/qt_opencv_camera

CMD ["./qt_opencv_camera"]
