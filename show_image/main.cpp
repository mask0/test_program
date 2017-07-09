#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace cv;
// 画像表示
int main(int argc, char* argv[]){

  Mat image =imread("lena.png");
  cvNamedWindow("lena", CV_WINDOW_AUTOSIZE);

  imshow("lena", image);
  // キー入力待ち
  cvWaitKey(0);
  cvDestroyWindow("lena");
  return 0;
}

