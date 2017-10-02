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
  Ptr<xfeatures2d::SURF>detectorSURF = xfeatures2d::SURF::create();
  Ptr<AKAZE> detectorAKAZE = AKAZE::create();

  vector<KeyPoint> fast_keypoint, sift_keypoint, surf_keypoint, akaze_keypoint;
  detectorFAST->detect(image, fast_keypoint);
  detectorSIFT->detect(image, sift_keypoint);
  detectorSURF->detect(image, surf_keypoint);
  detectorAKAZE->detect(img_threshold, akaze_keypoint);

  Mat fast_image,sift_image, surf_image, akaze_image;
  drawKeypoints(image, fast_keypoint, fast_image, Scalar(0, 255, 0), DrawMatchesFlags::DEFAULT);
  drawKeypoints(image, sift_keypoint, sift_image, Scalar(0, 255, 0), DrawMatchesFlags::DEFAULT);
  drawKeypoints(image, surf_keypoint, surf_image, Scalar(0, 255, 0), DrawMatchesFlags::DEFAULT);
  drawKeypoints(image, akaze_keypoint, akaze_image, Scalar(0, 255, 0), DrawMatchesFlags::DEFAULT);
  imshow("FAST", fast_image);
  imshow("SIFT", sift_image);
  imshow("SURF", surf_image);
  imshow("AKAZE", akaze_image);


  /*------------ matching_sample(sift) -----------------*/
  vector<KeyPoint> sift_keypoint1, sift_keypoint2;
  detectorSIFT->detect(image, sift_keypoint1);
  detectorSIFT->detect(image, sift_keypoint2);
  Mat sift_descriptor1, sift_descriptor2;
  detectorSIFT->compute(image, sift_keypoint1, sift_descriptor1);
  detectorSIFT->compute(clone, sift_keypoint2, sift_descriptor2);

  Ptr<DescriptorMatcher> sift_matcher = DescriptorMatcher::create("BruteForce");
  vector<DMatch> sift_match;
  sift_matcher->match(sift_descriptor1, sift_descriptor2, sift_match);
  
  Mat sift_dst;
  drawMatches(image, sift_keypoint1, clone, sift_keypoint2, sift_match, sift_dst);
  imshow("sift_match", sift_dst);

  imwrite("FAST.png", fast_image);
  imwrite("SIFT.png", sift_image);
  imwrite("SURF.png", surf_image);
  imwrite("AKAZE.png", akaze_image);
  imwrite("match.png", sift_dst);

  waitKey(0);
  return 0;
}
