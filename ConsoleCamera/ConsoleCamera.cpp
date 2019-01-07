#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;

int main()
{
	int count = 0;
	cv::Size patternsize(12, 7);
	cv::VideoCapture cap(0);
	std::vector<cv::Point2f> corners;
	if (!cap.isOpened())
	{
		cout << "camera open failed" << endl;
		return 0;
	}


	cv::Mat frame1;
	cv::Mat gray_img;
	cv::namedWindow("raw image", 1);
	cv::namedWindow("gray image", 1);

	cap >> frame1;


	if (cap.isOpened())
	{
		cout << "camera image size : " << frame1.cols << "x" << frame1.rows << endl;
	}

	while (1)
	{
		cap >> frame1;
		cv::cvtColor(frame1, gray_img, cv::COLOR_BGR2GRAY);
		cv::imshow("raw image", frame1);
		//cv::imshow("gray image", gray_img);
		char ch = cv::waitKey(1);

		if (ch == 32)
		{
			//원하는 명령을 입력
			bool found = cv::findChessboardCorners(gray_img, patternsize, corners, cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE);
			if (found)
			{
				cv::drawChessboardCorners(gray_img, patternsize, cv::Mat(corners), found);
				imshow("gray image", gray_img);
				ostringstream name;
				name << "testImg_" << count << ".bmp";
				count++;
				if (imwrite(name.str(), frame1))
					cout << "chess board found and save the raw image, press any key to continue" << endl;
				else
					cout << "chess board found, but not saved. press any key to continue" << endl;

			}
			else
				cout << "chess board not found, press any key to continue" << endl;
			
			cv::waitKey(0);
		}

		if (ch == 27) break;
	}

	return 0;

}