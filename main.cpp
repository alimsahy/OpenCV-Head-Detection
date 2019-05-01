//
// Created by Alimsah YILDIRIM on 5/1/19.
//

#include "CDetection.h"

int main()
{
	CDetection detection("Face Detection");

	detection.setScalingFactor(0.50);
	detection.setFacemask("mask.png");
	detection.setClassifier(detection.FrontalFace2);
	detection.processFrame();
	waitKey(1);
	return 1;
}
