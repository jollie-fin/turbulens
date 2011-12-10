#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>


IplImage * ContrastBrightness(IplImage *src, int Contrast, int Brightness);
 
int main (int argc, char** argv)
{
	// OpenCV data structure for handle to the cam
	CvCapture* vidObj;
 
	// This captures from the default cam
	vidObj = cvCaptureFromCAM(CV_CAP_ANY);
        if (!vidObj) return 1;
//        cvSetCaptureProperty(vidObj, CV_CAP_PROP_FPS, 50.0);

 
	while (!cvGrabFrame(vidObj)) {
                printf ("coucou\n");
		// Just wait while first frame is grabbed
	}
 
	// Creating structures to hold the captured and processed frames
	IplImage *grabbedImg, *grayImg, *diffImg, *oldgrabbedImg, *showImage, *thresImage;
 
	// Retrieve the captured frame
	grabbedImg = cvRetrieveFrame(vidObj);
	// Allocate memory for the image structure which will hold the processed frame
	oldgrabbedImg = cvCreateImage(cvSize(grabbedImg->width, grabbedImg->height), grabbedImg->depth, grabbedImg->nChannels);
	diffImg = cvCreateImage(cvSize(grabbedImg->width, grabbedImg->height), grabbedImg->depth, grabbedImg->nChannels);
	grayImg = cvCreateImage(cvSize(grabbedImg->width, grabbedImg->height), IPL_DEPTH_8U, 1);
	showImage = cvCreateImage(cvSize(grabbedImg->width, grabbedImg->height), IPL_DEPTH_8U, 1);
	thresImage = cvCreateImage(cvSize(grabbedImg->width, grabbedImg->height), IPL_DEPTH_8U, 1);
 
	// Create a Window to show the captured stream
	cvNamedWindow("CapturedImage", CV_WINDOW_AUTOSIZE); 
	cvMoveWindow("CapturedImage", 00, 100);
 
	// Create a Window to show the processed stream
	cvNamedWindow("ModifiedImage", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("ModifiedImage", 640, 100);
 
        int i=0;
  	// Loop until Esc key is pressed
	while(1) {
 
		// This function is used to grab the frame from camera + retrieve the image from it
		/*grabbedImg = cvQueryFrame(vidObj);

                cvAbsDiff(grabbedImg, oldgrabbedImg, diffImg);
 
		// Convert the captured frame to Grayscale
		cvCvtColor(diffImg, grayImg, CV_RGB2GRAY);
 
//                cvBlur( CV_BLUR, 3 );  //  I like to blur before taking the difference image to reduce camera noise
                cvThreshold( grayImg, thresImage, atoi(argv[1]), 255, CV_THRESH_BINARY );


                for( int y=0; y<showImage->height; y++ ) {
                        unsigned char* ptr = (unsigned char*) (
                        showImage->imageData + y * showImage->widthStep
                        );
                        unsigned char* ptr2 = (unsigned char*) (
                        thresImage->imageData + y * thresImage->widthStep
                        );
                        for( int x=0; x<showImage->width; x++ ) {
                                //unsigned a = (unsigned) ptr[x] * 254 / 256 + ptr2[x];
                                unsigned a = (unsigned) 4*ptr2[x];
                                ptr[x] = (unsigned) (a>255)?255:a;
                                // use +1 for saturation, +0 for hue
                        }
                }

//                if (i++%2==0)
                {
               		// Display the processed frame in second Window
		        cvShowImage("ModifiedImage", showImage);
		        // Display the captured frame in first Window
		        cvShowImage("CapturedImage", grabbedImg);
                }
                cvCopy(grabbedImg,oldgrabbedImg);*/
                printf("%d\n",grabbedImg->widthStep);

 		// Exit on esc key
		if( cvWaitKey( 2 ) == 27 ) 
			break;
 	}
 
	cvWaitKey(0);
 
	return -1;
}

