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
  Mat clone = image.clone();
  Mat gray_image, img_threshold;  
  cvtColor(image, gray_image, CV_BGR2GRAY);
  threshold(gray_image, img_threshold, 0, 255, THRESH_BINARY | THRESH_OTSU);
  
  Ptr<FastFeatureDetector> detectorFAST = FastFeatureDetector::create();
  Ptr<xfeatures2d::SIFT>detectorSIFT = xfeatures2d::SIFT::create();

  vector<KeyPoint> fast_keypoint, sift_keypoint;
  detectorFAST->detect(gray_image, fast_keypoint);
  detectorSIFT->detect(gray_image, sift_keypoint);

  Mat fast_image,sift_image, surf_image, akaze_image;
  drawKeypoints(gray_image, fast_keypoint, fast_image, Scalar(0, 255, 0), DrawMatchesFlags::DEFAULT);
  drawKeypoints(gray_image, sift_keypoint, sift_image, Scalar(0, 255, 0), DrawMatchesFlags::DEFAULT);

  imshow("FAST", fast_image);
  imshow("SIFT", sift_image);
  //imwrite("FAST.png", fast_image);
  //imwrite("SIFT.png", sift_image);

  /*------------ matching_sample(sift) -----------------*/
  vector<KeyPoint> sift_keypoint1, sift_keypoint2;
  detectorSIFT->detect(image, sift_keypoint1);

  Mat sift_descriptor1, sift_descriptor2;
  detectorSIFT->compute(image, sift_keypoint1, sift_descriptor1);

    //camera open
  VideoCapture cap("video.avi");  
  cap.open(1);
  if (!cap.isOpened()) {
    std::cout << "cannot find a camera." << std::endl;
    waitKey(5000);
    return -1;
  }

  Mat camera, gray_camera;
  while(1){
    cap >> camera;
      cvtColor(camera, gray_camera, CV_BGR2GRAY);
      detectorSIFT->detect(gray_camera, sift_keypoint2);
      detectorSIFT->compute(gray_camera, sift_keypoint2, sift_descriptor2);

      Ptr<DescriptorMatcher> sift_matcher = DescriptorMatcher::create("BruteForce");
      vector<DMatch> sift_match;
      sift_matcher->match(sift_descriptor1, sift_descriptor2, sift_match);

      //vector<vector<DMatch> > sift_match2;
      //sift_matcher->match(sift_descriptor1, sift_descriptor2, sift_match2, 2);
      
      Mat sift_dst;
      drawMatches(gray_image, sift_keypoint1, gray_camera, sift_keypoint2, sift_match, sift_dst);
      imshow("sift_match", sift_dst);

      int key = waitKey(1);
      if(key == 113){ break;}   
  }

  destroyAllWindows();
  return 0;
}
