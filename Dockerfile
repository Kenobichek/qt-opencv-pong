FROM gcc:latest

WORKDIR /app

COPY src/main.cpp .

RUN apt-get update && apt-get install -y gdb \
    && g++ -g -O0 -o app main.cpp \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

CMD ["./app"]
