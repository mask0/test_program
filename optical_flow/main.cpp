#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;
using namespace cv::superres;

int main(int argc, const char** argv){

  // add your file name
  VideoCapture cap("yourFile.mp4");
 
  Mat flow, frame;
  // some faster than mat image container
  UMat  flowUmat, prevgray;

  while(1){
    bool Is = cap.grab();
    if (Is == false) {
      // if video capture failed
      cout << "Video Capture Fail" << endl;
      break;
    }
    else {
      Mat img;
      Mat original;

      // capture frame from video file
      cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);
      resize(img, img, Size(640, 480));

      // save original for later
      img.copyTo(original);

      // just make current frame gray
      cvtColor(img, img, COLOR_BGR2GRAY);
  

      // For all optical flow you need a sequence of images.. Or at least 2 of them. Previous                           //and current frame
      //if there is no current frame
      // go to this part and fill previous frame
      //else {
      // img.copyTo(prevgray);
      //   }
      // if previous frame is not empty.. There is a picture of previous frame. Do some                                  //optical flow alg. 

      if (prevgray.empty() == false ) {

	// calculate optical flow 
	calcOpticalFlowFarneback(prevgray, img, flowUmat, 0.5, 10, 24, 2, 5, 1.2, 0);
	// copy Umat container to standard Mat
	flowUmat.copyTo(flow);

	for (int y = 0; y < original.rows; y += 10) {
	  for (int x = 0; x < original.cols; x += 10){
	      // get the flow from y, x position * 10 for better visibility
	      const Point2f flowatxy = flow.at<Point2f>(y, x) * 10;
	      // draw line at flow direction
	      line(original, Point(x, y), Point(cvRound(x + flowatxy.x), cvRound(y + flowatxy.y)), Scalar(255,0,0), 2);
	      // draw initial point
	      circle(original, Point(x, y), 1, Scalar(0, 0, 0), -1);
   	    }
	}
   
	// draw the results
	namedWindow("result", WINDOW_AUTOSIZE);
	imshow("result", original);
    
	// fill previous image again
	img.copyTo(prevgray);
      }
      else {
	// fill previous image in case prevgray.empty() == true
	img.copyTo(prevgray);
      }
   
      int key = waitKey(1);
      if(key == 113){ break;}   

    }
  }
}
