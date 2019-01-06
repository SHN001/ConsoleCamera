#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;

int main()
{

	cv::VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cout << "camera open failed" << endl;
		return 0;
	}


	cv::Mat frame1;
	cv::namedWindow("raw image", 1);

	cap >> frame1;

	if (cap.isOpened())
	{
		cout << "camera image size : " << frame1.cols << "x" << frame1.rows << endl;
	}

	while (1)
	{
		cap >> frame1;
		cv::imshow("raw image", frame1);


		if (cv::waitKey(1) == 32)
		{
			//원하는 명령을 입력
			cv::imwrite("testImg.bmp", frame1);
			cout << "image saved" << endl;
		}

		if (cv::waitKey(1) == 27) break;
	}

	return 0;

}