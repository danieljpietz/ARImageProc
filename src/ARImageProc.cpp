#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

#define DELAY_CAPTION (1500)
#define DELAY_BLUR (100)
#define MAX_KERNEL_LENGTH (8)
std::vector<Point> FilterLowest(std::vector<Point> input);
int main(int argc, char const *argv[]) {

    Mat image = imread("TestImages/Camera_Center.png");
    // Create Matrices (make sure there is an image in input!)
    Mat input = image;
    Mat channel[3];
    Mat resultImg;
    // The actual splitting.
    split(input, channel);

    Mat im = channel[2];
    Mat blurred = im;


      // threshold the image with gray value of 100
     Mat binImg;
     threshold(blurred, binImg, 1, 255, THRESH_BINARY);

      // find the contours
      vector<vector<Point>> contours;
      vector<Vec4i> hierarchy;
      findContours(binImg, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

      if(contours.size() <= 0)
      {
          printf("no contours found");
          return 0;
      }
      // filter the contours
      vector<vector<Point>> filteredBlobs;
      vector<Rect> obstacleBoxes;

      Mat centers = Mat::zeros(0,2,CV_64FC1);
      for(int i = 0; i < contours.size(); i++) {
          filteredBlobs.push_back(contours[i]);
          obstacleBoxes.insert(obstacleBoxes.end(),boundingRect(contours[i]));
      }
      drawContours(blurred, filteredBlobs, -1, Scalar(255,255,255), FILLED, 8);
      imshow("B", blurred);
      waitKey(0);
      return 0;
}

std::vector<Point> FilterLowest(std::vector<Point> input) {
    using namespace std;
    vector<Point> retVal;
    vector<int> maxIndex;
    vector<int> maxValue;
    int i;
    for (i = 0; i < input.size(); i++) {
       vector<int>::iterator index = find(maxIndex.begin(), maxIndex.end(), input[i].x); //Find the x value if it is in the maxIndex Vector
       if (index == maxIndex.end()) {
         maxIndex.insert(maxIndex.end(), input[i].x);
         maxValue.insert(maxValue.end(), input[i].y);
       }
       else if(input[i].y > maxValue[distance(maxValue.begin(),index)]){
         maxValue.insert(index, input[i].y);
       }
    }
    for (i = 0; i < maxIndex.size(); i++) {
      Point p = Point(maxIndex[i], maxValue[i]);
      retVal.insert(retVal.end(), p);
    }
    return retVal;
}

double localizeObstacle() {
    //Car-Relative Camera Positions
    //Left Cam: (-1, 0.5, 0.5) m
    //Center Cam: (0, 0.5, 0.5) m
    //Right Cam: (1, 0.5, 0.5) m
    //Camera Focal Lengthsm 5mm
    //Camera Sensor Widths: 20mm
    //Camera Image Width 540px
    

    return 0;
}
