#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>
#include <string>

int main(){

    cv::VideoCapture cap(1);

    for(;;){
        cv::Mat src,srcGray,blurred,canny,thresh,hsv,filtered,cont,done;
        std::vector< std::vector<cv::Point> > contours;
        std::vector< std::vector<cv::Point> > ThreshContours;
        std::vector<cv::Vec4i> heirarchy;
        cap>>src;
        //src = cv::imread("/home/chinmaya/Desktop/balls1.jpg");
        cv::resize(src,src,cv::Size(640,480));

        //Uses thresh or filtering
        //cv::cvtColor(src,src,CV_BGR2GRAY);
        //cv::blur(src,blurred,cv::Size(49,51));
        //cv::threshold(blurred,thresh,150,255,CV_THRESH_BINARY);
        //filtered = thresh;
        hsv = src.clone();
        cv::cvtColor(src,srcGray,CV_BGR2GRAY);
        //Uses HSV for filtering
        cv::cvtColor(src,hsv,CV_BGR2HSV);
        cv::blur(hsv,blurred,cv::Size(13,13));

        cv::inRange(hsv,cv::Scalar(34,23,181),cv::Scalar(48,218,255),filtered);

        cv::threshold(srcGray,thresh,221,255,CV_THRESH_BINARY);

        done = src.clone();

        cv::findContours(thresh,ThreshContours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE,cv::Point(0,0));

        cv::drawContours(done,ThreshContours,-1,cv::Scalar(0,0,0),-1);


        std::vector<cv::Point> largest;





        cv::findContours(filtered,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE,cv::Point(0,0));
        cont = cv::Mat::zeros(filtered.size(),CV_8UC1);
        cv::drawContours(cont,contours,-1,cv::Scalar(255,255,255),1);


        std::vector< std::vector<cv::Point> > contours_poly( contours.size() );
        std::vector<cv::Rect> boundRect( contours.size() );
        std::vector<cv::Point2f> center( contours.size() );
        std::vector<float> radius( contours.size() );


        for( int i = 0; i < contours.size(); i++ ){
            cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( cv::Mat(contours_poly[i]) );
            cv::minEnclosingCircle( (cv::Mat)contours_poly[i], center[i],radius[i]);
        }





        std::string text;

        for( int i = 0; i< contours.size(); i++ ){
            if(cv::contourArea(contours[i])>650)
            cv::rectangle( done, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(255,255,255),2 );
            text = std::to_string(i);
            //cv::putText(done,)
        }





        int circles = contours.size()-1;


        //show original
        cv::namedWindow("Original");
        cv::imshow("Original",src);

        //show HSV
        //cv::namedWindow("HSV");
        //cv::imshow("HSV",hsv);

        //show blurred
       // cv::namedWindow("blurred");
        //cv::imshow("blurred",blurred);

        //show filtered
        cv::namedWindow("filtered");
        cv::imshow("filtered",filtered);

        //show contours
        cv::namedWindow("contours");
        cv::imshow("contours",cont);

        //show end img
        cv::namedWindow("end");
        cv::imshow("end",done);



        cv::namedWindow("thresh");
        cv::imshow("thresh",thresh);
        /*cv::imwrite("/home/chinmaya/Desktop/thresh.jpg",thresh);
        cv::imwrite("/home/chinmaya/Desktop/src.jpg",src);
        cv::imwrite("/home/chinmaya/Desktop/filtered.jpg",filtered);
        cv::imwrite("/home/chinmaya/Desktop/done.jpg",done);*/
        //cv::imwrite("/home/chinmaya/Desktop/cont.jpg",cont);
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
cv::VideoCapture cap(1);
for(;;){
 //src = imread("/home/chinmaya/Desktop/balls2.jpg",1);
 cap>>src;
 //cv::resize(src,src,cv::Size(720,1080));
 imshow(window_name,src);
 setMouseCallback( window_name, onMouse, 0 );
 waitKey(20);
 }
}*/

