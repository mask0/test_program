#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace cv;

int face_num =0;

Mat detectFaceInImage(Mat &image, string &cascade_file){
  CascadeClassifier cascade;
  cascade.load(cascade_file);

  vector<Rect> faces;
  cascade.detectMultiScale(image, faces, 1.1, 3, 0, Size(20, 20));

  for(int i =0; i < faces.size(); i++){
    rectangle(image, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y+faces[i]. height), Scalar(0, 200, 0), 1, CV_AA);
    face_num++;
  }
  
  return image;
}

void IntToString(char *str, int number){
  sprintf(str, "%d", number);
}
int main(int argc, char const *argv[]){
  Mat image = imread(argv[1]);
  string filename = argv[2];
  char people[] = "people";
  char sNum[32], str;
  
  Mat detectFaceImage = detectFaceInImage(image, filename);

  //input number of people for image.
  IntToString(sNum, face_num);
  strcat(sNum, people);
  putText(detectFaceImage, sNum, Point(50, 50), FONT_HERSHEY_TRIPLEX, 1, Scalar(255,255,255), 1, CV_AA);

  imshow("detect_face", detectFaceImage);
  waitKey(0);

  return 0;
}
