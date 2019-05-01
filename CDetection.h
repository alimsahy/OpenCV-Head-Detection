//
// Created by Alimsah YILDIRIM on 5/1/19.
//

#ifndef FACE_CDETECTION_H
#define FACE_CDETECTION_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class CDetection
{
	private:
			vector<Rect> m_faces;
			CascadeClassifier m_classifier;
			VideoCapture m_capture;

			int m_detectedFaceCount;
			float m_scalingFactor;
			string m_windowName;

			Mat m_faceMask;
			Mat m_frame;
			Mat m_frameGray;
			Mat m_frameROI;
			Mat m_grayMaskSmall;
			Mat m_grayMaskSmallThresh;
			Mat m_grayMaskSmallThreshInv;
			Mat m_faceMaskSmall;
			Mat m_maskedFace;
			Mat m_maskedFrame;

	public:
			CDetection(const string &windowName);
			void processFrame();
			void processFrame(VideoCapture &capture);
			void setClassifier(int classifierType);
			void setFacemask(const string &mask);
			void setScalingFactor(const float &factor);
			void setSource(int source, const string &sourceAddress = nullptr);

			enum ClassifierType
			{
				FrontalFace,
				FrontalFace2
			};

			enum SourceType
			{
				Webcam,
				File
			};
};

#endif //FACE_CDETECTION_H
