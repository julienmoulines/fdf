#include <opencv2/opencv.hpp>

int main() {apt-get install libopencv-dev
    cv::VideoCapture cap(0);  // Ouvre la webcam (0 est l'ID de la webcam par défaut)

    if (!cap.isOpened()) {
        std::cerr << "Erreur : Impossible d'ouvrir la webcam." << std::endl;
        return -1;
    }

    cv::Mat frame;
    cv::namedWindow("Webcam", cv::WINDOW_NORMAL);
    cv::resizeWindow("Webcam", 640, 480);

    while (true) {
        cap >> frame;  // Capture un frame de la webcam

        if (frame.empty()) {
            std::cerr << "Erreur : Frame vide." << std::endl;
            break;
        }

        cv::rectangle(frame, cv::Point(100, 100), cv::Point(200, 200), cv::Scalar(255, 255, 255), -1);  // Carré blanc
        cv::imshow("Webcam", frame);

        int key = cv::waitKey(10);
        if (key == 27)  // Appuyez sur la touche Échap pour quitter
            break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
