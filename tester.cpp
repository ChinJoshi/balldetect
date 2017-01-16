#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


int main(){

    cv::VideoCapture cap(0);

    for(;;){
        cv::Mat src,blurred,canny,thresh,hsv,filtered,cont,done;
        std::vector< std::vector<cv::Point> > contours; //contour vector
        std::vector<cv::Vec4i> heirarchy;
        cap>>src;
        //src = cv::imread("/home/chinmaya/Desktop/balls1.jpg");
        //cv::resize(src,src,cv::Size(720,1080));

        //Uses thresh or filtering
        /*cv::cvtColor(src,src,CV_BGR2GRAY);
        cv::blur(src,blurred,cv::Size(49,51));
        cv::threshold(blurred,thresh,150,255,CV_THRESH_BINARY);
        filtered = thresh;*/

        //Uses HSV for filtering
        cv::cvtColor(src,hsv,CV_BGR2HSV);
        cv::blur(hsv,blurred,cv::Size(9,9));
        cv::inRange(blurred,cv::Scalar(30,75,100),cv::Scalar(100,160,255),filtered);

        //Finding and drawing contours
        cv::findContours(filtered,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE,cv::Point(0,0));
        cont = cv::Mat::zeros(filtered.size(),CV_8UC1);
        cv::drawContours(cont,contours,-1,cv::Scalar(255,255,255),1);
        //cv::HoughCircles(cont,foundCircles,CV_HOUGH_GRADIENT,1,1,100,200,0,0);

        std::vector< std::vector<cv::Point> > contours_poly( contours.size() );
        std::vector<cv::Rect> boundRect( contours.size() );
        std::vector<cv::Point2f> center( contours.size() );
        std::vector<float> radius( contours.size() );

        //find
        for( int i = 0; i < contours.size(); i++ ){
            cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( cv::Mat(contours_poly[i]) );
            cv::minEnclosingCircle( (cv::Mat)contours_poly[i], center[i],radius[i]);
        }

        done = src.clone();

        for( int i = 0; i< contours.size(); i++ ){
            cv::rectangle( done, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(255,255,255),2 );
        }
    //show original
        cv::namedWindow("Original");
        cv::imshow("Original",src);

        //show HSV
        cv::namedWindow("HSV");
        cv::imshow("HSV",hsv);

        //show blurred
        cv::namedWindow("blurred");
        cv::imshow("blurred",blurred);

        //show filtered
        cv::namedWindow("filtered");
        cv::imshow("filtered",filtered);

        //show contours
        cv::namedWindow("contours");
        cv::imshow("contours",cont);

        //show end img
        cv::namedWindow("end");
        cv::imshow("end",done);

        cv::waitKey(30);
    }

    return 0;
}







//Code below is for finding HSV values
/*
using namespace cv;
using namespace std;
char window_name[30] = "HSV Segmentation";
Mat src;

static void onMouse( int event, int x, int y, int f, void* ){
 Mat image=src.clone();
 Vec3b rgb=image.at<Vec3b>(y,x);
 int B=rgb.val[0];
 int G=rgb.val[1];
 int R=rgb.val[2];

  Mat HSV;
  Mat RGB=image(Rect(x,y,1,1));
  cvtColor(RGB, HSV,CV_BGR2HSV);

    Vec3b hsv=HSV.at<Vec3b>(0,0);
    int H=hsv.val[0];
    int S=hsv.val[1];
    int V=hsv.val[2];

    char name[30];
    sprintf(name,"B=%d",B);
    putText(image,name, Point(150,40) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,255,0), 2,8,false );

    sprintf(name,"G=%d",G);
    putText(image,name, Point(150,80) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,255,0), 2,8,false );

    sprintf(name,"R=%d",R);
    putText(image,name, Point(150,120) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,255,0), 2,8,false );

    sprintf(name,"H=%d",H);
    putText(image,name, Point(25,40) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,255,0), 2,8,false );

    sprintf(name,"S=%d",S);
    putText(image,name, Point(25,80) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,255,0), 2,8,false );

    sprintf(name,"V=%d",V);
    putText(image,name, Point(25,120) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,255,0), 2,8,false );

    sprintf(name,"X=%d",x);
    putText(image,name, Point(25,300) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,0,255), 2,8,false );

    sprintf(name,"Y=%d",y);
    putText(image,name, Point(25,340) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,0,255), 2,8,false );

 //imwrite("hsv.jpg",image);
 imshow( window_name, image );
}



int main(){
 src = imread("/home/chinmaya/Desktop/balls2.jpg",1);
 cv::resize(src,src,cv::Size(720,1080));
 imshow(window_name,src);
 setMouseCallback( window_name, onMouse, 0 );
 waitKey();
 }

*/
