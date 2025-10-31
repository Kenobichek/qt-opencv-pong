#!/usr/bin/env bash
set -e

IMAGE_NAME="camera-ping-pong"
PROJECT_DIR="$(pwd)"

echo "Running tests inside container..."

docker run --rm \
  -v "$PROJECT_DIR":/app \
  -w /app \
  $IMAGE_NAME \
  bash -c "mkdir -p build && cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build --parallel \$(nproc) && ctest --output-on-failure --test-dir build"
