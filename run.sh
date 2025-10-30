#!/usr/bin/env bash
set -e

xhost +local:docker

VIDEO_DEVS=$(ls /dev/video* 2>/dev/null)
DEVICES=""
for dev in $VIDEO_DEVS; do
  DEVICES="$DEVICES --device=$dev:$dev"
done

docker run --rm \
  -e DISPLAY=$DISPLAY \
  -e XDG_RUNTIME_DIR=/tmp/runtime-root \
  $DEVICES \
  -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
  camera-ping-pong

xhost -local:docker
