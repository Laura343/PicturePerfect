#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include "imageToMat.h"
#include "functionFilter.h"

class Camera
{
public:
    void startCamera();

    void endCamera();

    Image captureImage(int filterNumber);

    Image captureOriginalImage();
private:
    cv::Mat original;
    cv::VideoCapture m_cap;
};

