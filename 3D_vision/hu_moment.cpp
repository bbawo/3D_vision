#include <opencv2/highgui/highgui.hpp> 
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <unistd.h>

using namespace cv;

// Include file for every supported opencv function
void output(Mat img1, Mat img2)
{
    //parameters of sliding window
    int w_rows = img2.rows;
    int w_cols = img2.cols;

    //step of each window
    int stepslide = 5;

    Point coordinates;
    coordinates.x = 0;
    coordinates.y = 0;

    double least_dist = 10000.00;
    double distance;

    for ( int row = 0; row <= img1.rows - w_rows; row+= stepslide)
    {
        for ( int col = 0; col <= img1.cols - w_cols; col+=stepslide)
        {
           //slide over original image and create template samples
           Rect windows(col, row, w_cols, w_rows);
           Mat result = img1(windows);
           
           distance = matchShapes(img2, result, CONTOURS_MATCH_I2, 0);

           if (distance < least_dist)
           {
               least_dist = distance;
               coordinates.x = col;
               coordinates.y = row;

           }

        }
    }
    
    std::cout << "coordinates: " << coordinates.x << ", " <<  coordinates.y << ", " <<  img2.cols << ", " << img2.rows << std::endl;
    rectangle(img1, coordinates,Point( coordinates.x + w_cols , coordinates.y + w_rows ), Scalar(255, 0, 0), 1, 8, 0);
    namedWindow( "window", WINDOW_AUTOSIZE );
    imshow("window", img1);
    waitKey( 0 );
    destroyWindow( "window" );

}

int main()
{
    Mat img_original = imread("StarMap.png", IMREAD_GRAYSCALE);
    Mat img_cropped  = imread("Small_area.png", IMREAD_GRAYSCALE);
    threshold(img_original, img_original, 128, 255, THRESH_BINARY);
    threshold(img_cropped, img_cropped, 128, 255, THRESH_BINARY);

    if( img_original.empty() || img_cropped.empty() ) 
    {
        std::cout << "File error!" <<std::endl;
        return -1;
    }
    std::cout << "images read successfully...." << std::endl;
    output(img_original, img_cropped);
    std::cout << "program finished!" << std::endl;

    return 0;
}


