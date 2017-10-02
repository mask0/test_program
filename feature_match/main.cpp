#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"


#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv){
  Mat image = imread(argv[1]);
  
  Ptr<FastFeatureDetector> detectorFAST = FastFeatureDetector::create();
  Ptr<xfeatures2d::SIFT>detectorSIFT = xfeatures2d::SIFT::create();

  vector<KeyPoint> fast_keypoint1, fast_keypoint2;
  Mat fast_descriptor1, fast_descriptor2;

  detectorFAST->detect(image, fast_keypoint1);
  detectorSIFT->compute(image, fast_keypoint1, fast_descriptor1);

  //camera open
  VideoCapture cap("video.avi");  
  cap.open(1);
  if (!cap.isOpened()) {
    std::cout << "cannot find a camera." << std::endl;
    waitKey(5000);
    return -1;
  }

  Mat camera;
  while(1){
    cap >> camera;
      detectorFAST->detect(camera, fast_keypoint2);
      detectorSIFT->compute(camera, fast_keypoint2, fast_descriptor2);

      Ptr<DescriptorMatcher> fast_matcher = DescriptorMatcher::create("BruteForce");
      //vector<DMatch> fast_match;
      //fast_matcher->match(fast_descriptor1, fast_descriptor2, fast_match);

      vector<vector<DMatch> > fast_match;
      fast_matcher->knnMatch(fast_descriptor1, fast_descriptor2, fast_match, 1);
      
      Mat fast_dst;
      drawMatches(image, fast_keypoint1, camera, fast_keypoint2, fast_match, fast_dst);
      imshow("fast_match", fast_dst);

      int key = waitKey(1);
      if(key == 113){ break;}   
  }

  destroyAllWindows();
  return 0;
}
