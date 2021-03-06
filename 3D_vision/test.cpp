#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// Global Variables
Mat img; Mat templ; Mat result;
char* image_window = "Source Image";
char* result_window = "Result window";

int match_method = CV_TM_SQDIFF;

/// Function Headers
void MatchingMethod( int, void* );

//main
int main( int argc, char** argv )
{
  /// Load image and template
  img = imread( argv[1], 1 );
  templ = imread( argv[2], 1 );

  /// Create windows
  namedWindow( image_window, WINDOW_AUTOSIZE );
  namedWindow( result_window, WINDOW_AUTOSIZE );

  MatchingMethod( 0, 0 );

  waitKey(0);
  return 0;
}


void MatchingMethod( int, void* )
{
  /// Source image to display
  Mat img_display;
  img.copyTo( img_display );

  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_cols, result_rows, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( img, templ, result, match_method );
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

 
  matchLoc = minLoc; 

  //print coordinates
  cout <<"x, y, w, h : " << matchLoc.x << ", "<< matchLoc.y
    << ", " << templ.cols <<", " << templ.rows << endl;

  /// Show me what you got
  rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar(0, 128, 0), 2, 8, 0 );
  rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar(0, 128, 0), 2, 8, 0 );

  imshow( image_window, img_display );
  imshow( result_window, result );

  return;
}
