#pragma once

#include "ofMain.h"
#include "ofConstants.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void drawValueWindow();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void onButtonPress(ofxDatGuiButtonEvent e);
		void clearPath();
		void clearLast();
		void viewValues();
		void saveFile();
		void loadImage();
		
	private: 
		ofPath path;
		ofPolyline polyPath;
		vector<ofPolyline> paths;
		float drawLine;
		float fading;
		bool drawing = true;

		ofImage backgroundImage;

		ofxDatGui gui;
		ofxDatGui opt;
		ofxDatGui bgImageGui;

		ofxDatGuiTextInput* valueEdit;
		ofxDatGuiTextInput* delimEdit;
		ofxDatGuiTextInput* parenEdit;
		ofxDatGuiTextInput* parenCloseEdit;
		ofxDatGuiTextInput* filenameEdit;
		ofxDatGuiTextInput* imageFilenameEdit;

		bool showValues = false;
		bool backgroundLoaded = false;
		string values;
		string delim = ",";
		string paren = "{";
		string parenClose = "}";



		vector<ofColor> colors = { ofColor::aliceBlue,
			ofColor::antiqueWhite, ofColor::azure,
			ofColor::azure, ofColor::bisque };
};
