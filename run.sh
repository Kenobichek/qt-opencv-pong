#!/usr/bin/env bash
set -e

if [ -z "$DISPLAY" ]; then
  echo "DISPLAY is not set. Run this from a graphical session."
  exit 1
fi

VIDEO_DEVS=$(ls /dev/video* 2>/dev/null)
if [ -z "$VIDEO_DEVS" ]; then
  echo "No /dev/videoX devices found."
  exit 1
fi

DEVICES=""
for dev in $VIDEO_DEVS; do
  DEVICES="$DEVICES --device=$dev:$dev"
done

xhost +local:docker >/dev/null 2>&1 || true

docker run --rm \
  $DEVICES \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
  qt-cam-pong "$@"

xhost -local:docker >/dev/null 2>&1 || true
