//
// Created by Alimsah YILDIRIM on 5/1/19.
//

#include "CDetection.h"

CDetection::CDetection(const string &windowName)
{
	this->m_windowName = windowName;
	namedWindow(this->m_windowName);
}

void CDetection::processFrame()
{
	VideoCapture capture(0);
	capture.set(CV_CAP_PROP_FPS, 30);
	while (true)
	{
		capture >> this->m_frame;

		resize(this->m_frame, this->m_frame, Size(1000, 700), this->m_scalingFactor, this->m_scalingFactor, INTER_AREA);

		cvtColor(this->m_frame, this->m_frameGray, COLOR_BGR2GRAY);
		equalizeHist(this->m_frameGray, this->m_frameGray);
		this->m_classifier.detectMultiScale(this->m_frameGray, this->m_faces, 1.2, 9, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for (auto &face: this->m_faces)
		{
			this->m_detectedFaceCount = this->m_faces.size();

			Rect faceRect(face.x, face.y + 10, face.width, face.height);

			int x = face.x - int(0.0 * face.width);
			int y = face.y - int(0.0 * face.height);
			int w = int(1.0 * face.width);
			int h = int(1.0 * face.height);

			this->m_frameROI = this->m_frame(Rect(x, y, w, h));
			resize(this->m_faceMask, this->m_faceMaskSmall, Size(w, h));
			cvtColor(this->m_faceMaskSmall, this->m_grayMaskSmall, COLOR_BGR2GRAY);
			threshold(this->m_grayMaskSmall, this->m_grayMaskSmallThresh, 230, 255, THRESH_BINARY_INV);
			bitwise_not(this->m_grayMaskSmallThresh, this->m_grayMaskSmallThreshInv);
			bitwise_and(this->m_faceMaskSmall, this->m_faceMaskSmall, this->m_maskedFace, this->m_grayMaskSmallThresh);
			bitwise_and(this->m_frameROI, this->m_frameROI, this->m_maskedFrame, this->m_grayMaskSmallThreshInv);

			if (x > 0 && y > 0 && x + w < this->m_frame.cols && y + h < this->m_frame.rows)
			{
				add(this->m_maskedFace, this->m_maskedFrame, this->m_frame(Rect(x, y, w, h)));
			}
		}
		imshow(this->m_windowName, this->m_frame);
		waitKey(1);
	}
}

void CDetection::processFrame(VideoCapture &capture)
{
	while (true)
	{
		capture >> this->m_frame;

		resize(this->m_frame, this->m_frame, Size(1000, 700), this->m_scalingFactor, this->m_scalingFactor, INTER_AREA);

		cvtColor(this->m_frame, this->m_frameGray, COLOR_BGR2GRAY);
		equalizeHist(this->m_frameGray, this->m_frameGray);
		this->m_classifier.detectMultiScale(this->m_frameGray, this->m_faces, 1.2, 9, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for (auto &face: this->m_faces)
		{
			Rect faceRect(face.x, face.y + 10, face.width, face.height);

			int x = face.x - int(0.0 * face.width);
			int y = face.y - int(0.0 * face.height);
			int w = int(1.0 * face.width);
			int h = int(1.0 * face.height);

			this->m_frameROI = this->m_frame(Rect(x, y, w, h));
			resize(this->m_faceMask, this->m_faceMaskSmall, Size(w, h));
			cvtColor(this->m_faceMaskSmall, this->m_grayMaskSmall, COLOR_BGR2GRAY);
			threshold(this->m_grayMaskSmall, this->m_grayMaskSmallThresh, 230, 255, THRESH_BINARY_INV);
			bitwise_not(this->m_grayMaskSmallThresh, this->m_grayMaskSmallThreshInv);
			bitwise_and(this->m_faceMaskSmall, this->m_faceMaskSmall, this->m_maskedFace, this->m_grayMaskSmallThresh);
			bitwise_and(this->m_frameROI, this->m_frameROI, this->m_maskedFrame, this->m_grayMaskSmallThreshInv);

			if (x > 0 && y > 0 && x + w < this->m_frame.cols && y + h < this->m_frame.rows)
			{
				add(this->m_maskedFace, this->m_maskedFrame, this->m_frame(Rect(x, y, w, h)));
			}
		}
		imshow(this->m_windowName, this->m_frame);
		waitKey(1);
	}
}

void CDetection::setSource(int source, const string &sourceAddress)
{
	switch (source)
	{

	}
}

void CDetection::setClassifier(int classifier)
{
	switch (classifier)
	{
		case CDetection::ClassifierType::FrontalFace:
		{
			this->m_classifier.load("haarcascade_frontalface_default.xml");
			break;
		}
		case CDetection::ClassifierType ::FrontalFace2:
		{
			this->m_classifier.load("haarcascade_frontalface_alt2.xml");
			break;
		}
		default:
		{
			this->m_classifier.load("haarcascade_frontalface.xml");
			break;
		}
	}
}

void CDetection::setFacemask(const string &mask)
{
	this->m_faceMask = imread(mask);
}

void CDetection::setScalingFactor(const float &factor)
{

}
