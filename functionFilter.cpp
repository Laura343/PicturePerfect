#include "functionFilter.h"

using namespace cv;
using namespace std;

void Zerno(Image& img){
    cv::Mat mat=ImageToMat(img);
    if (mat.empty())
    {
        std::cout << "Could not open or find the image" << std::endl;
        return;
    }
    cv::Mat noise = cv::Mat::zeros(mat.size(), mat.type());
    randn(noise, cv::Scalar::all(0), cv::Scalar::all(50)); // mean=0, SD=50
    mat+=noise;

    img=MatToImage(mat);
}

void Zerno(cv::Mat& mat){
    if (mat.empty())
    {
        std::cout << "Could not open or find the image" << std::endl;
        return;
    }
    cv::Mat noise = cv::Mat::zeros(mat.size(), mat.type());
    randn(noise, cv::Scalar::all(0), cv::Scalar::all(50)); // mean=0, SD=50
    mat+=noise;
}

void applyFilter(Mat& image, Scalar color)
{
    Mat filter(image.size(), image.type(), color);
    addWeighted(image, 0.5, filter, 0.5, 0, image);
}


void makeGray(Image& img ){
    cv::Mat mat=ImageToMat(img);
    if (mat.empty())
    {
        cout << "Could not open or find the image" << endl;
    }
    time_t now = time(0);
    struct tm tstruct;
    char text[80];
    tstruct = *localtime(&now);
    strftime(text, sizeof(text), "%Y-%m-%d %X", &tstruct);
    string date_time = text;
    Scalar brightness = mean(mat);
    int font = FONT_HERSHEY_SIMPLEX; //tareri dzev
    double font_scale = 2.0; //tarachap
    Scalar font_color;
    if (brightness[0] < 127) {
        font_color = Scalar(255, 255, 255);
    } else {
        font_color = Scalar(0, 0, 0);
    }
    int font_thickness = 2;
    Size text_size = getTextSize(date_time, font, font_scale, font_thickness, nullptr);
    Point text_pos(mat.cols - text_size.width - 10, mat.rows - text_size.height - 10);
    putText(mat, date_time, text_pos, font, font_scale, font_color, font_thickness);
    img=MatToImage(mat);
}


void makeGray(cv::Mat& mat ){

    if (mat.empty())
    {
        cout << "Could not open or find the image" << endl;
    }
    time_t now = time(0);
    struct tm tstruct;
    char text[80];
    tstruct = *localtime(&now);
    strftime(text, sizeof(text), "%Y-%m-%d %X", &tstruct);
    string date_time = text;
    Scalar brightness = mean(mat);
    int font = FONT_HERSHEY_SIMPLEX; //tareri dzev
    double font_scale = 2.0; //tarachap
    Scalar font_color;
    if (brightness[0] < 127) {
        font_color = Scalar(255, 255, 255);
    } else {
        font_color = Scalar(0, 0, 0);
    }
    int font_thickness = 2;
    Size text_size = getTextSize(date_time, font, font_scale, font_thickness, nullptr);
    Point text_pos(mat.cols - text_size.width - 10, mat.rows - text_size.height - 10);
    putText(mat, date_time, text_pos, font, font_scale, font_color, font_thickness);
   
} 

void redBlue(Image& img ){
    cv::Mat mat=ImageToMat(img);

    if (mat.empty())
    {
        cout << "Could not open or find the image" << endl;
    }

  int width = mat.cols / 5;
  for (int i = 0; i < 5; i++) {
    vector<Point> pts(4);
    int width = mat.cols / 5;
    pts[0] = Point(i * width, 0);
    pts[1] = Point((i + 1) * width, 0);
    pts[2] = Point((i + 1) * width, mat.rows);
    pts[3] = Point(i * width, mat.rows);

    Mat mask(mat.size(), CV_8UC1, Scalar(0));
    fillConvexPoly(mask, pts, Scalar(255));

    Mat roi;
    mat.copyTo(roi, mask);
    Scalar color;
    switch (i) {
        case 0: // blue filter
            color = Scalar(255, 0, 0);
            break;
        case 1: // green filter
            color = Scalar(0, 255, 0);
            break;
        case 2: // red filter
            color = Scalar(0, 0, 255);
            break;
        case 3: // yellow filter
            color = Scalar(0, 255, 255);
            break;
        case 4: // purple filter
            color = Scalar(255, 0, 255);
            break;
    }
    applyFilter(roi, color);
    roi.copyTo(mat, mask);
}

    Mat combined(mat.rows, mat.cols * 2, mat.type());
    mat.copyTo(combined(Rect(0, 0, mat.cols, mat.rows)));

    img=MatToImage(combined);
}


void redBlue(cv::Mat& mat ){
   

    if (mat.empty())
    {
        cout << "Could not open or find the image" << endl;
    }

  int width = mat.cols / 5;
  for (int i = 0; i < 5; i++) {
    vector<Point> pts(4);
    int width = mat.cols / 5;
    pts[0] = Point(i * width, 0);
    pts[1] = Point((i + 1) * width, 0);
    pts[2] = Point((i + 1) * width, mat.rows);
    pts[3] = Point(i * width, mat.rows);

    Mat mask(mat.size(), CV_8UC1, Scalar(0));
    fillConvexPoly(mask, pts, Scalar(255));

    Mat roi;
    mat.copyTo(roi, mask);
    Scalar color;
    switch (i) {
        case 0: // blue filter
            color = Scalar(255, 0, 0);
            break;
        case 1: // green filter
            color = Scalar(0, 255, 0);
            break;
        case 2: // red filter
            color = Scalar(0, 0, 255);
            break;
        case 3: // yellow filter
            color = Scalar(0, 255, 255);
            break;
        case 4: // purple filter
            color = Scalar(255, 0, 255);
            break;
    }
    applyFilter(roi, color);
    roi.copyTo(mat, mask);
}

    Mat combined(mat.rows, mat.cols * 2, mat.type());
    mat.copyTo(combined(Rect(0, 0, mat.cols, mat.rows)));

    mat=combined;
}     
// void makeGray(Image& img){
//     cv::Mat mat=ImageToMat(img);
//     if (mat.empty())
//     {
//         std::cout << "Could not open or find the image" << std::endl;
//         return;
//     }
//     cv::cvtColor(mat, mat, 6);
//     img=MatToImage(mat);
// }

// void makeGray(cv::Mat& image){
//     if (image.empty())
//     {
//         std::cout << "Could not open or find the image" << std::endl;
//         return;
//     }
//     cv::cvtColor(image, image, 6);
// } 

// void redBlue(Image& img){
//     cv::Mat mat=ImageToMat(img);
//     if (mat.empty())
//     {
//         std::cout << "Could not open or find the image" << std::endl;
//         return;
//     }
//     cv::Mat left_half = mat(cv::Rect(0, 0, mat.cols / 2, mat.rows));
//     cv::Mat right_half = mat(cv::Rect(mat.cols / 2, 0, mat.cols / 2, mat.rows));
//     cv::Mat blue_filter = cv::Mat::zeros(left_half.size(), left_half.type());
//     blue_filter.setTo(cv::Vec3b(225, 0, 0));
//     cv::Mat red_filter = cv::Mat::zeros(right_half.size(), right_half.type());
//     red_filter.setTo(cv::Vec3b(0, 0, 225));
//     cv::Mat blue_image;
//     addWeighted(left_half, 0.5, blue_filter, 0.5, 0.0, blue_image);
//     cv::Mat red_image;
//     addWeighted(right_half, 0.5, red_filter, 0.5, 0.0, red_image);
//     cv::Mat output_image(mat.size(), mat.type());
//     cv::Mat left_roi(output_image, cv::Rect(0, 0, mat.cols / 2, mat.rows));
//     blue_image.copyTo(left_roi);
//     cv::Mat right_roi(output_image, cv::Rect(mat.cols / 2, 0, mat.cols / 2, mat.rows));
//     red_image.copyTo(right_roi);
//     img=MatToImage(output_image);

// }

// void redBlue(cv::Mat& mat){
//     if (mat.empty())
//     {
//         std::cout << "Could not open or find the image" << std::endl;
//         return;
//     }
//     cv::Mat left_half = mat(cv::Rect(0, 0, mat.cols / 2, mat.rows));
//     cv::Mat right_half = mat(cv::Rect(mat.cols / 2, 0, mat.cols / 2, mat.rows));
//     cv::Mat blue_filter = cv::Mat::zeros(left_half.size(), left_half.type());
//     blue_filter.setTo(cv::Vec3b(225, 0, 0));
//     cv::Mat red_filter = cv::Mat::zeros(right_half.size(), right_half.type());
//     red_filter.setTo(cv::Vec3b(0, 0, 225));
//     cv::Mat blue_image;
//     addWeighted(left_half, 0.5, blue_filter, 0.5, 0.0, blue_image);
//     cv::Mat red_image;
//     addWeighted(right_half, 0.5, red_filter, 0.5, 0.0, red_image);
//     cv::Mat output_image(mat.size(), mat.type());
//     cv::Mat left_roi(output_image, cv::Rect(0, 0, mat.cols / 2, mat.rows));
//     blue_image.copyTo(left_roi);
//     cv::Mat right_roi(output_image, cv::Rect(mat.cols / 2, 0, mat.cols / 2, mat.rows));
//     red_image.copyTo(right_roi);
//     mat=output_image;
// }
