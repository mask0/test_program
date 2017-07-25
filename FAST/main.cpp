#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv){
    Mat input_image =imread("lena.png");
    vector<KeyPoint> points;
    Ptr < FastFeatureDetector>fast = FastFeatureDetector::create();
    fast->detect(input_image, points);

    Mat image_fast;
    drawKeypoints(input_image, points, image_fast, Scalar(0, 0, 255));
    imshow("fast", image_fast);
    waitKey(0);
    destroyAllWindows();

    return 0;
}
