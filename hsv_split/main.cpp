#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"

#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char* argv[]){
  //camera open
  VideoCapture cap("video.avi");  
  cap.open(1);
  if (!cap.isOpened()) {
    std::cout << "cannot find a camera." << std::endl;
    waitKey(5000);
    return -1;
  }

  Mat camera, hsv;
  vector<Mat> hsv_split;
  while(1){
    cap >> camera;
    cvtColor(camera, hsv, CV_BGR2HSV);

    split(hsv, hsv_split);                     //[0]:h, [1]:s,[2]:v

    imshow("input", camera);
    imshow("Hue", hsv_split[0]);
    imshow("Saturation", hsv_split[1]);
    imshow("Value", hsv_split[2]);

    int key = waitKey(1);
    if(key == 113){
      imwrite("input.png", camera);
      imwrite("Hue.png", hsv_split[0]);
      imwrite("Saturation.png", hsv_split[1]);
      imwrite("Value.png", hsv_split[2]);

      break;
    }   
  }
  destroyAllWindows();
}
