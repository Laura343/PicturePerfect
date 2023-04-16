#include "frameCapture.h"

void Camera::startCamera()
{
    m_cap.open(0); 
}

void Camera::endCamera()
{
    m_cap.release();
}

Image Camera::captureImage(int filterNumber)
{
    m_cap >> frame;
    cv::flip(frame, frame, 1);
    switch(filterNumber)
    {
        case 1:
            Zerno(frame);
            break;
        case 2:
            makeGray(frame);
            break;
        case 3:
            redBlue(frame);
            break;
    }
    return MatToImage(frame);
}

Image Camera::captureOriginalImage()
{
    cv::Mat original;
    m_cap>>original;
    cv::flip(original, original, 1);
    return MatToImage(original);
}