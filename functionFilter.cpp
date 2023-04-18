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


void makeGray(Image& img) {
    cv::Mat mat = ImageToMat(img);
    if (mat.empty()) {
        cout << "Could not open or find the image" << endl;
        return;
    }
    int width = mat.cols / 5;
    vector<Scalar> filter_colors = {
        Scalar(255, 0, 0),   // blue filter
        Scalar(0, 255, 0),   // green filter
        Scalar(0, 0, 255),   // red filter
        Scalar(0, 255, 255), // yellow filter
        Scalar(255, 0, 255)  // purple filter
    };
    Mat combined(mat.rows, mat.cols, mat.type(), Scalar(0, 0, 0));
    for (int i = 0; i < 5; i++) {
        vector<Point> pts(4);
        pts[0] = Point(i * width, 0);
        pts[1] = Point((i + 1) * width, 0);
        pts[2] = Point((i + 1) * width, mat.rows);
        pts[3] = Point(i * width, mat.rows);
        Mat mask(mat.size(), CV_8UC1, Scalar(0));
        fillConvexPoly(mask, pts, Scalar(255));
        Mat roi(mat.size(), mat.type(), filter_colors[i]);
        mat.copyTo(roi, mask);
        applyFilter(roi, filter_colors[i]);
        roi.copyTo(combined, mask);
    }
    img = MatToImage(combined);
}
void makeGray(cv::Mat& mat) {
    if (mat.empty()) {
        cout << "Could not open or find the image" << endl;
        return;
    }
    int width = mat.cols / 5;
    vector<Scalar> filter_colors = {
        Scalar(255, 0, 0),   // blue filter
        Scalar(0, 255, 0),   // green filter
        Scalar(0, 0, 255),   // red filter
        Scalar(0, 255, 255), // yellow filter
        Scalar(255, 0, 255)  // purple filter
    };
    Mat combined(mat.rows, mat.cols, mat.type(), Scalar(0, 0, 0));
    for (int i = 0; i < 5; i++) {
        vector<Point> pts(4);
        pts[0] = Point(i * width, 0);
        pts[1] = Point((i + 1) * width, 0);
        pts[2] = Point((i + 1) * width, mat.rows);
        pts[3] = Point(i * width, mat.rows);
        Mat mask(mat.size(), CV_8UC1, Scalar(0));
        fillConvexPoly(mask, pts, Scalar(255));
        Mat roi(mat.size(), mat.type(), filter_colors[i]);
        mat.copyTo(roi, mask);
        applyFilter(roi, filter_colors[i]);
        roi.copyTo(combined, mask);
    }
      mat=combined;
}


void redBlue(Image& img) {
    cv::Mat mat = ImageToMat(img);
    if (mat.empty()) {
        cout << "Could not open or find the image" << endl;
        return;
    }
    double stretch_factor = 2.5;
    double compression_factor = 0.7;
    Point2f source[4] = {
        Point2f(0, 0),
        Point2f(mat.cols, 0),
        Point2f(0, mat.rows),
        Point2f(mat.cols, mat.rows)
    };
    Point2f destination[4] = {
        Point2f(0, 0),
        Point2f(mat.cols * stretch_factor, 0),
        Point2f(0, mat.rows * compression_factor),
        Point2f( mat.cols * stretch_factor, mat.rows * compression_factor)
    };
    Mat transform_matrix = getPerspectiveTransform(source, destination);  // sarqenq 3x3 matric warpi 3rd paranetri hamar
    Mat modified_img;
    warpPerspective(mat, modified_img, transform_matrix, Size(mat.cols * stretch_factor, mat.rows*compression_factor));
     img = MatToImage(modified_img);
}

void redBlue(cv::Mat& mat) {
    if (mat.empty()) {
        cout << "Could not open or find the image" << endl;
        return;
    }
    double stretch_factor = 2.5;
    double compression_factor = 0.7;
    Point2f source[4] = {
        Point2f(0, 0),
        Point2f(mat.cols, 0),
        Point2f(0, mat.rows),
        Point2f(mat.cols, mat.rows)
    };
    Point2f destination[4] = {
        Point2f(0, 0),
        Point2f(mat.cols * stretch_factor, 0),
        Point2f(0, mat.rows * compression_factor),
        Point2f( mat.cols * stretch_factor, mat.rows * compression_factor)
    };
    Mat transform_matrix = getPerspectiveTransform(source, destination);  // sarqenq 3x3 matric warpi 3rd paranetri hamar
    Mat modified_img;
    warpPerspective(mat, modified_img, transform_matrix, Size(mat.cols * stretch_factor, mat.rows*compression_factor));
    mat=modified_img;
}

// void redBlue(Image& img) {
//     cv::Mat mat = ImageToMat(img);
//     if (mat.empty()) {
//         cout << "Could not open or find the image" << endl;
//         return;
//     }
//     double stretch_factor = 3.5;
//     double compression_factor = 0.7;
//     Point2f source[4] = {
//         Point2f(0, 0),
//         Point2f(mat.cols, 0),
//         Point2f(0, mat.rows),
//         Point2f(mat.cols, mat.rows)
//     };
//     Point2f destination[4] = {
//         Point2f(0, 0),
//         Point2f(mat.cols * stretch_factor, 0),
//         Point2f(0, mat.rows * compression_factor),
//         Point2f( mat.cols * stretch_factor, mat.rows * compression_factor)
//     };
//     Mat transform_matrix = getPerspectiveTransform(source, destination);  // sarqenq 3x3 matric warpi 3rd paranetri hamar
//     Mat modified_img;
//     warpPerspective(mat, modified_img, transform_matrix, Size(mat.cols * stretch_factor, mat.rows*compression_factor));
//     img = MatToImage(mat);
// }
// void redBlue(cv::Mat& mat) {
//     if (mat.empty()) {
//         cout << "Could not open or find the image" << endl;
//         return;
//     }
//     double stretch_factor = 3.5;
//     double compression_factor = 0.7;
//     Point2f source[4] = {
//         Point2f(0, 0),
//         Point2f(mat.cols, 0),
//         Point2f(0, mat.rows),
//         Point2f(mat.cols, mat.rows)
//     };
//     Point2f destination[4] = {
//         Point2f(0, 0),
//         Point2f(mat.cols * stretch_factor, 0),
//         Point2f(0, mat.rows * compression_factor),
//         Point2f( mat.cols * stretch_factor, mat.rows * compression_factor)
//     };
//     Mat transform_matrix = getPerspectiveTransform(source, destination);  // sarqenq 3x3 matric warpi 3rd paranetri hamar
//     Mat modified_img;
//     warpPerspective(mat, modified_img, transform_matrix, Size(mat.cols * stretch_factor, mat.rows*compression_factor));
// }
  
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
