# Camera Ping Pong

## Requirements
- Docker installed
- X server running (for GUI)
- At least one webcam connected

## Build & Run

### 1. Clone
```bash
git clone git@github.com:Kenobichek/qt-opencv-pong.git
cd qt-opencv-pong
```

### 2. Build Docker image
```bash
docker build -t camera-ping-pong .
```

### 3. Run
```bash
./run.sh
```