#!/usr/bin/env bash
set -e

IMAGE_NAME="camera-ping-pong"
PROJECT_DIR="$(pwd)"

xhost +local:docker

VIDEO_DEVS=$(ls /dev/video* 2>/dev/null)
DEVICES=""
for dev in $VIDEO_DEVS; do
  DEVICES="$DEVICES --device=$dev:$dev"
done

docker run --rm \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
  -v "$PROJECT_DIR":/app \
  -w /app \
  $DEVICES \
  $IMAGE_NAME \
  bash -c "mkdir -p build && cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build --parallel \$(nproc) && ./build/CameraPingPong"

xhost -local:docker
