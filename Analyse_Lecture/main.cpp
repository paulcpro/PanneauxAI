#include "opencv2/objdetect/objdetect.hpp"
#include <string.h>
#include <opencv2/ml/ml.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include <string.h>
#include <opencv2/ml/ml.hpp>

using namespace std;
using namespace cv;

std::vector<cv::Rect> getRedObjects(cv::Mat image);
vector<Mat> detectAndDisplaySpeedLimit( Mat frame );
void trainDigitClassifier();
string getDigits(Mat image);
vector<Mat> loadAllImage();
int getSpeedLimit(string speed);

//path of the haar cascade files
String speed_signs_cascade = "/Users/giuliopettenuzzo/Desktop/cascade_classifiers/speed_limit_cascade.xml";

CascadeClassifier speed_limit_cascade;

int main(int argc, char** argv)
{
    //train the classifier for digit recognition, this require a manually train, read the report for more details
    trainDigitClassifier();

    cv::Mat sceneImage;

    vector<Mat> allImages = loadAllImage();

    for(int i = 0;i<=allImages.size();i++){
        sceneImage = allImages[i];

        //load the haar cascade files
        if( !speed_limit_cascade.load( speed_signs_cascade ) ){ printf("--(!)Error loading\n"); return -1; };

        Mat scene = sceneImage.clone();

        //detect the red objects
        std::vector<cv::Rect> allObj = getRedObjects(scene);

        //use the three cascade classifier for each object detected by the getRedObjects() method
        for(int j = 0;j<allObj.size();j++){
            Mat img = sceneImage(Rect(allObj[j]));
            vector<Mat> speedLitmitVec = detectAndDisplaySpeedLimit(img);
            if(speedLitmitVec.size()>0){
                Rect box = allObj[j];
                for(int i = 0; i<speedLitmitVec.size();i++){
                    //get speed limit and skatch it in the image
                    int digit = getSpeedLimit(getDigits(speedLitmitVec[i]));
                    if(digit > 0){
                        Point point = box.tl();
                        point.y = point.y + 30;
                        cv::putText(sceneImage,
                                    "SPEED LIMIT " + to_string(digit),
                                    point,
                                    cv::FONT_HERSHEY_COMPLEX_SMALL,
                                    0.7,
                                    cv::Scalar(0,255,0),
                                    1,
                                    cv::CV__CAP_PROP_LATEST);
                    }
                }
            }
        }
        imshow("currentobj",sceneImage);
        waitKey(0);
    }
}

/*
 *  detect the red object in the image given in the param,
 *  return a vector containing all the Rect of the red objects
 */
std::vector<cv::Rect> getRedObjects(cv::Mat image)
{
    Mat3b res = image.clone();
    std::vector<cv::Rect> result;

    cvtColor(image, image, COLOR_BGR2HSV);

    Mat1b mask1, mask2;
    //ranges of red color
    inRange(image, Scalar(0, 70, 50), Scalar(10, 255, 255), mask1);
    inRange(image, Scalar(170, 70, 50), Scalar(180, 255, 255), mask2);

    Mat1b mask = mask1 | mask2;
    Mat nonZeroCoordinates;
    vector<Point> pts;

    findNonZero(mask, pts);
    for (int i = 0; i < nonZeroCoordinates.total(); i++ ) {
        cout << "Zero#" << i << ": " << nonZeroCoordinates.at<Point>(i).x << ", " << nonZeroCoordinates.at<Point>(i).y << endl;
    }

    int th_distance = 2; // radius tolerance

     // Apply partition
     // All pixels within the radius tolerance distance will belong to the same class (same label)
    vector<int> labels;

     // With lambda function (require C++11)
    int th2 = th_distance * th_distance;
    int n_labels = partition(pts, labels, [th2](const Point& lhs, const Point& rhs) {
        return ((lhs.x - rhs.x)*(lhs.x - rhs.x) + (lhs.y - rhs.y)*(lhs.y - rhs.y)) < th2;
    });

     // You can save all points in the same class in a vector (one for each class), just like findContours
    vector<vector<Point>> contours(n_labels);
    for (int i = 0; i < pts.size(); ++i){
        contours[labels[i]].push_back(pts[i]);
    }

     // Get bounding boxes
    vector<Rect> boxes;
    for (int i = 0; i < contours.size(); ++i)
    {
        Rect box = boundingRect(contours[i]);
        if(contours[i].size()>500){//prima era 1000
            boxes.push_back(box);

            Rect enlarged_box = box + Size(100,100);
            enlarged_box -= Point(30,30);

            if(enlarged_box.x<0){
                enlarged_box.x = 0;
            }
            if(enlarged_box.y<0){
                enlarged_box.y = 0;
            }
            if(enlarged_box.height + enlarged_box.y > res.rows){
                enlarged_box.height = res.rows - enlarged_box.y;
            }
            if(enlarged_box.width + enlarged_box.x > res.cols){
                enlarged_box.width = res.cols - enlarged_box.x;
            }

            Mat img = res(Rect(enlarged_box));
            result.push_back(enlarged_box);
        }
     }
     Rect largest_box = *max_element(boxes.begin(), boxes.end(), [](const Rect& lhs, const Rect& rhs) {
         return lhs.area() < rhs.area();
     });

    //draw the rects in case you want to see them
     for(int j=0;j<=boxes.size();j++){
         if(boxes[j].area() > largest_box.area()/3){
             rectangle(res, boxes[j], Scalar(0, 0, 255));

             Rect enlarged_box = boxes[j] + Size(20,20);
             enlarged_box -= Point(10,10);

             rectangle(res, enlarged_box, Scalar(0, 255, 0));
         }
     }

     rectangle(res, largest_box, Scalar(0, 0, 255));

     Rect enlarged_box = largest_box + Size(20,20);
     enlarged_box -= Point(10,10);

     rectangle(res, enlarged_box, Scalar(0, 255, 0));

     return result;
}


/*
 *  code for detect the speed limit sign , it draws a circle around the speed limit signs
 */
vector<Mat> detectAndDisplaySpeedLimit( Mat frame )
{
    std::vector<Rect> signs;
    vector<Mat> result;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    //normalizes the brightness and increases the contrast of the image
    equalizeHist( frame_gray, frame_gray );

    //-- Detect signs
    speed_limit_cascade.detectMultiScale( frame_gray, signs, 1.1, 3, 0| CASCADE_SCALE_IMAGE, Size(30, 30) );
    cout << speed_limit_cascade.getFeatureType();

    for( size_t i = 0; i < signs.size(); i++ )
    {
        Point center( signs[i].x + signs[i].width*0.5, signs[i].y + signs[i].height*0.5 );
        ellipse( frame, center, Size( signs[i].width*0.5, signs[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );


        Mat resultImage = frame(Rect(center.x - signs[i].width*0.5,center.y - signs[i].height*0.5,signs[i].width,signs[i].height));
        result.push_back(resultImage);
    }
    return result;
}

/*
 *  train the classifier for digit recognition, this could be done only one time, this method save the result in a file and
 *  it can be used in the next executions
 *  in order to train user must enter manually the corrisponding digit that the program shows, press space if the red box is just a point (false positive)
 */
void trainDigitClassifier(){
    Mat thr,gray,con;

    //A partir de l'image on va entrainer notre donnée
    Mat src = imread("C:/Resources/PanneauxAI/trainDigit.png", 1);

    cvtColor(src,gray,COLOR_BGR2GRAY);

    //Récupère les contour
    threshold(gray,thr,125,255,THRESH_BINARY_INV);


    imshow("ci",thr);
    waitKey(0);
    thr.copyTo(con);

    // Create sample and label data
    vector< vector <Point> > contours; // Vector for storing contour
    vector< Vec4i > hierarchy;
    Mat sample;
    Mat response_array;
    //Bug utiliser RETR_CCOMP  au lieu de CV_RETR_CCOMP
    findContours( con, contours, hierarchy,RETR_CCOMP, CHAIN_APPROX_SIMPLE ); //Find contour

    for( int i = 0; i< contours.size(); i=hierarchy[i][0] ) // iterate through first hierarchy level contours
    {
        Rect r= boundingRect(contours[i]); //Find bounding rect for each contour
        rectangle(src,Point(r.x,r.y), Point(r.x+r.width,r.y+r.height), Scalar(0,0,255),2,8,0);
        Mat ROI = thr(r); //Crop the image
        Mat tmp1, tmp2;
        resize(ROI,tmp1, Size(10,10), 0,0,INTER_LINEAR ); //resize to 10X10
        tmp1.convertTo(tmp2,CV_32FC1); //convert to float

        imshow("src",src);

        int c=waitKey(0); // Read corresponding label for contour from keyoard
        c-=0x30;     // Convert ascii to intiger value
        response_array.push_back(c); // Store label to a mat
        rectangle(src,Point(r.x,r.y), Point(r.x+r.width,r.y+r.height), Scalar(0,255,0),2,8,0);
        sample.push_back(tmp2.reshape(1,1)); // Store  sample data
    }

    // Store the data to file
    Mat response,tmp;
    tmp=response_array.reshape(1,1); //make continuous
    tmp.convertTo(response,CV_32FC1); // Convert  to float

    FileStorage Data("TrainingData.yml",FileStorage::WRITE); // Store the sample data in a file
    Data << "data" << sample;
    Data.release();

    FileStorage Label("LabelData.yml",FileStorage::WRITE); // Store the label data in a file
    Label << "label" << response;
    Label.release();
    cout<<"Training and Label data created successfully....!! "<<endl;

    imshow("src",src);
    waitKey(0);

}

/*
 *  get digit from the image given in param, using the classifier trained before
 */
string getDigits(Mat image)
{
    Mat thr1,gray1,con1;
    Mat src1 = image.clone();
    cvtColor(src1,gray1,COLOR_BGR2GRAY);
    threshold(gray1,thr1,125,255,THRESH_BINARY_INV); // Threshold to create input
    thr1.copyTo(con1);


    // Read stored sample and label for training
    Mat sample1;
    Mat response1,tmp1;
    FileStorage Data1("TrainingData.yml",FileStorage::READ); // Read traing data to a Mat
    Data1["data"] >> sample1;
    Data1.release();

    FileStorage Label1("LabelData.yml",FileStorage::READ); // Read label data to a Mat
    Label1["label"] >> response1;
    Label1.release();


    Ptr<ml::KNearest>  knn(ml::KNearest::create());

    knn->train(sample1, ml::ROW_SAMPLE,response1); // Train with sample and responses
    cout<<"Training compleated.....!!"<<endl;

    vector< vector <Point> > contours1; // Vector for storing contour
    vector< Vec4i > hierarchy1;

    //Create input sample by contour finding and cropping
    //utiliser CHAIN_APPROX_SIMPLE au lieu de CV_CHAIN_APPROX_SIMPLE
    findContours( con1, contours1, hierarchy1,RETR_CCOMP, CHAIN_APPROX_SIMPLE );
    Mat dst1(src1.rows,src1.cols,CV_8UC3,Scalar::all(0));
    string result;

    for( int i = 0; i< contours1.size(); i=hierarchy1[i][0] ) // iterate through each contour for first hierarchy level .
    {
        Rect r= boundingRect(contours1[i]);
        Mat ROI = thr1(r);
        Mat tmp1, tmp2;
        resize(ROI,tmp1, Size(10,10), 0,0,INTER_LINEAR );
        tmp1.convertTo(tmp2,CV_32FC1);
        Mat bestLabels;
        float p=knn -> findNearest(tmp2.reshape(1,1),4, bestLabels);
        char name[4];
        sprintf(name,"%d",(int)p);
        cout << "num = " << (int)p;
        result = result + to_string((int)p);

        putText( dst1,name,Point(r.x,r.y+r.height) ,0,1, Scalar(0, 255, 0), 2, 8 );
    }

    imwrite("dest.jpg",dst1);
    return  result ;
}
/*
 *  from the digits detected, it returns a speed limit if it is detected correctly, -1 otherwise
 */
int getSpeedLimit(string numbers){
    if ((numbers.find("30") != std::string::npos) || (numbers.find("03") != std::string::npos)) {
        return 30;
    }
    if ((numbers.find("50") != std::string::npos) || (numbers.find("05") != std::string::npos)) {
        return 50;
    }
    if ((numbers.find("80") != std::string::npos) || (numbers.find("08") != std::string::npos)) {
        return 80;
    }
    if ((numbers.find("70") != std::string::npos) || (numbers.find("07") != std::string::npos)) {
        return 70;
    }
    if ((numbers.find("90") != std::string::npos) || (numbers.find("09") != std::string::npos)) {
        return 90;
    }
    if ((numbers.find("100") != std::string::npos) || (numbers.find("001") != std::string::npos)) {
        return 100;
    }
    if ((numbers.find("130") != std::string::npos) || (numbers.find("031") != std::string::npos)) {
        return 130;
    }
    return -1;
}

/*
 *  load all the image in the file with the path hard coded below
 */
vector<Mat> loadAllImage(){
    vector<cv::String> fn;
    glob("/Users/giuliopettenuzzo/Desktop/T1/dataset/*.jpg", fn, false);

    vector<Mat> images;
    size_t count = fn.size(); //number of png files in images folder
    for (size_t i=0; i<count; i++)
        images.push_back(imread(fn[i]));
    return images;
}
