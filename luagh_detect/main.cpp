#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace cv;

#define N (4)

int main(int argc, char **argv){
  VideoCapture cap(1);

  if (!cap.isOpened()) {
    std::cout << "cannot find a camera." << std::endl;
    waitKey(5000);
    return -1;
  }
  
  Mat frame, result, img_dst;

  vector<string> file_tmp;
  file_tmp.push_back("right_eye.png");
  file_tmp.push_back("left_eye.png");
  file_tmp.push_back("left_mouth.png");
  file_tmp.push_back("right_mouth.png");

  Mat img_tmp[N];
  Point max_pt[N];

  for(int i = 0; i < N; i++){
    img_tmp[i] = imread(file_tmp[i], 1);
    }
  
  while(1){
    cap >> frame;
    img_dst = frame.clone();

    for(int i =0; i<N; i++){
      matchTemplate(frame, img_tmp[i], result, TM_CCORR_NORMED);
      minMaxLoc(result, NULL, NULL, NULL, &max_pt[i]);
      Rect r(max_pt[i].x, max_pt[i].y, img_tmp[i].cols, img_tmp[i].rows);
      rectangle(img_dst, r.tl(), r.br(), Scalar(255, 0, 255), 2);
    }

    Rect r(max_pt[0].x + img_tmp[0].rows/2, max_pt[0].y + img_tmp[0].cols/2, max_pt[1].x-max_pt[0].x, max_pt[3].y-max_pt[0].y);
    rectangle(img_dst, r.tl(), r.br(), Scalar(255, 255, 255), 2);

    double width = saturate_cast<double>(max_pt[1].x - max_pt[0].x);
    double height = saturate_cast<double>(max_pt[3].y - max_pt[0].y);
    double ratio = width / height;
    cerr << ratio << endl;

    putText(img_dst, format("%5.3lf", ratio), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2, LINE_AA);

    imshow("frame", img_dst);


    int key = waitKey(1);
    if(key == 113){
      break;
    }
  }
}
