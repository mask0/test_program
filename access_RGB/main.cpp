/*-----------------------------
 * moudle : get point for RGB value
 *
 *  author : Takashi Higasa
 *  date   : 2017/07/07
------------------------------*/

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

struct mouseParam{
  int x;
  int y;
  int event;
  int flags;
};

void CallBackFunc(int eventType, int x, int y, int flags, void* userdata){
  mouseParam *ptr = static_cast<mouseParam*> (userdata);
  ptr->x = x;
  ptr->y = y;
  ptr->event = eventType;
  ptr->flags = flags;
}
    


int main(void){
  mouseParam mouseEvent;
  
  Mat input_image =imread("lena.png");
  String showing_name ="input";

  imshow(showing_name, input_image);

  setMouseCallback(showing_name, CallBackFunc, &mouseEvent);
  while(1){
    waitKey(1);
    if(mouseEvent.event == EVENT_MOUSEMOVE){
      Vec3b bgr = input_image.at<Vec3b>(mouseEvent.x, mouseEvent.y);
      printf("%d, %d, %d\n", bgr[0], bgr[1],bgr[2]);
    }

    else if(mouseEvent.event == EVENT_RBUTTONDOWN){
      break;
    }
  }
  return 0;
}
