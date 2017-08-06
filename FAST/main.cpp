#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv){
  //camera open
  VideoCapture cap("video.avi");  
  cap.open(1);
  if (!cap.isOpened()) {
    std::cout << "cannot find a camera." << std::endl;
    waitKey(5000);
    return -1;
  }

  Mat frame;
  while(1){
    cap >> frame;
    vector<KeyPoint> points;
    Ptr < FastFeatureDetector>fast = FastFeatureDetector::create();
    fast->detect(frame, points);

    Mat image_fast;
    drawKeypoints(frame, points, image_fast, Scalar(0, 0, 255));
    imshow("fast", image_fast);

    int key = waitKey(1);
    if(key == 113){
      break;
    }
  }
  destroyAllWindows();
  return 0;
}
