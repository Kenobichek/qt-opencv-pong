#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QImage>
#include <QPixmap>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    int camIndex = (argc > 1) ? std::stoi(argv[1]) : 0;
    VideoCapture cap(camIndex);
    if (!cap.isOpened()) {
        qDebug("Failed to open camera");
        return -1;
    }

    QLabel label;
    label.setWindowTitle("Camera Pong: Hand as Paddles");
    label.resize(640, 480);
    label.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        Mat frame;
        cap >> frame;
        if (frame.empty()) return;

        flip(frame, frame, 1);

        // === 1. Цветовая маска кожи ===
        Mat ycrcb, mask;
        cvtColor(frame, ycrcb, COLOR_BGR2YCrCb);
        inRange(ycrcb, Scalar(0,133,77), Scalar(255,173,127), mask);

        // === 2. Морфология для очистки ===
        morphologyEx(mask, mask, MORPH_OPEN, Mat(), Point(-1,-1), 2);
        morphologyEx(mask, mask, MORPH_CLOSE, Mat(), Point(-1,-1), 2);

        // === 3. Поиск контуров ===
        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // === 4. Фильтрация по положению (только края) ===
        vector<Rect> hands;
        int width = frame.cols;
        for (auto& c : contours) {
            double area = contourArea(c);
            if (area < 5000) continue; // игнорируем шум

            Rect box = boundingRect(c);
            float cx = box.x + box.width / 2.0f;

            float ratio = (float)box.height / box.width;

            bool left = cx < width * 0.25;
            bool right = cx > width * 0.75;
            if (!left && !right) continue;
            if (ratio < 1.0 || ratio > 4.0) continue;
            if (box.width < 40 || box.height < 60) continue;

            hands.push_back(box);
        }

        // === 5. Оставляем максимум 2 контуры (по одному на сторону) ===
        if (hands.size() > 2) {
            // выберем самые крупные
            sort(hands.begin(), hands.end(),
                [](const Rect& a, const Rect& b){ return a.area() > b.area(); });
            hands.resize(2);
        }

        // === 6. Отрисовка ===
        for (auto& h : hands) {
            rectangle(frame, h, Scalar(0,255,0), 2);
        }

        putText(frame, "Detected hands: " + to_string(hands.size()),
                Point(10,30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255,255,255), 2);

        // === 7. Показ в Qt ===
        cvtColor(frame, frame, COLOR_BGR2RGB);
        QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        label.setPixmap(QPixmap::fromImage(qimg).scaled(label.size(), Qt::KeepAspectRatio));
    });

    timer.start(30);
    return app.exec();
}