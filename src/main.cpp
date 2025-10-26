#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QImage>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char *argv[])
{
    std::cout << "Hello, Qt123!" << std::endl;
    QApplication app(argc, argv);

    QLabel label;
    label.setWindowTitle("Camera-Controlled Ping Pong");
    label.resize(640, 480);
    label.show();

    // Получаем индекс камеры из аргументов (по умолчанию 0)
    int cam_index = 0;
    if (argc > 1) cam_index = std::atoi(argv[1]);

    // Используем V4L2, чтобы точно открывать камеры в Linux/Docker
    VideoCapture cap(cam_index, cv::CAP_V4L2);
    if (!cap.isOpened()) {
        label.setText("Error: Cannot open camera " + QString::number(cam_index));
        return app.exec();
    }

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        Mat frame;
        cap >> frame;
        if (frame.empty()) return;

        cvtColor(frame, frame, COLOR_BGR2RGB);

        QImage img((const unsigned char*)(frame.data),
                   frame.cols, frame.rows,
                   frame.step, QImage::Format_RGB888);

        label.setPixmap(QPixmap::fromImage(img).scaled(label.size(),
                              Qt::KeepAspectRatio, Qt::SmoothTransformation));
    });

    timer.start(30);
    return app.exec();
}
