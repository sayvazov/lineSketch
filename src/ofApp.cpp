#include "ofApp.h"

//Some Helper Functions


//--------------------------------------------------------------
void ofApp::setup(){
	drawLine = 0.0;
	fading = false;
	
	ofSetWindowShape(1920, 1080);

	gui = ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	opt = ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	bgImageGui = ofxDatGui(ofxDatGuiAnchor::BOTTOM_RIGHT);

	auto updateValue = gui.addButton("Update Values");
	updateValue->setLabelAlignment(ofxDatGuiAlignment::CENTER);

	valueEdit = gui.addTextInput("Point Array is ");
	valueEdit->setName("Value");

	auto saveButton = gui.addButton("Save to File");
	saveButton->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	auto clearBut = gui.addButton("Clear");
	clearBut->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	auto clearLastBut = gui.addButton("Clear Last");
	clearLastBut->setLabelAlignment(ofxDatGuiAlignment::CENTER);

	delimEdit = opt.addTextInput("The Deliminator is ");
	delimEdit->setText (",");
	delimEdit->setWidth(400, 300);

	filenameEdit = opt.addTextInput("File to edit is ");
	filenameEdit->setText("image.txt");
	filenameEdit->setWidth(400, 300);

	parenEdit = opt.addTextInput("The opening bracket is ");
	parenEdit->setText("{");

	parenCloseEdit = opt.addTextInput("The closing bracket is ");
	parenCloseEdit->setText("}");

	imageFilenameEdit = bgImageGui.addTextInput("Load Background Image from ");
	imageFilenameEdit->setText("background.jpg");

	auto loadImageButton = bgImageGui.addButton("Load Background Image");


	gui.addFooter();
	opt.addFooter();
	opt.getFooter()->setLabelWhenCollapsed("Expand General Options");
	opt.getFooter()->setLabelWhenExpanded("Collapse General Options");
	opt.collapse();
	bgImageGui.addFooter();
	bgImageGui.getFooter()->setLabelWhenCollapsed("Expand Background Options");
	bgImageGui.getFooter()->setLabelWhenExpanded("Collapse Background Options");
	bgImageGui.collapse();

	gui.onButtonEvent(this, &ofApp::onButtonPress);
	bgImageGui.onButtonEvent(this, &ofApp::onButtonPress);
}

//--------------------------------------------------------------
void ofApp::update(){
	if (fading && drawLine > 0)
	{
		drawLine -= 0.01;
	}
	else if (!fading)
	{
		drawLine = 1.0;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofClear(ofColor(0));
	if (backgroundLoaded)
	{
		ofSetColor(255, 127);
		backgroundImage.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
	int grayVal = 0;
	if (drawLine > 0.01)
	{
		grayVal = (int)(MIN(drawLine, 1.0) * 255);
		ofSetColor(255, 255, 255, grayVal);
		//polyPath.draw();
		//path.draw();
		
		for (auto i = 0; i < paths.size(); i++)
		{
			ofColor col = colors[i%colors.size()];
			col.a = grayVal;
			ofSetColor(col);
			//ofColor::set(colors[i]);
			paths[i].draw();
		}
	}
	else
	{
		paths.clear();
		//polyPath.clear();
		//path.clear();
		viewValues();
	}
	
}

void ofApp::drawValueWindow()
{

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	//polyPath.addVertex(x, y);
	//path.lineTo(x, y);
	if (drawing)
	{
		paths[paths.size() - 1].addVertex(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	ofPoint pressPos = ofPoint(x, y);
	vector <ofRectangle> guiRects;
	guiRects.push_back(ofRectangle(
		gui.getPosition(), gui.getWidth(), gui.getHeight()));
	guiRects.push_back(ofRectangle(
		opt.getPosition(), opt.getWidth(), opt.getHeight()));
	guiRects.push_back(ofRectangle(
		bgImageGui.getPosition(), bgImageGui.getWidth(), bgImageGui.getHeight()));
	drawing = true;
	for (auto rec = guiRects.begin(); rec < guiRects.end(); rec++)
	{
		if (rec->inside(pressPos))
		{
			drawing = false;
		}
	}

	if (drawing)
	{
		//polyPath.clear();
		//polyPath.addVertex(x, y);
		//path.newSubPath();
		//path.moveTo(x, y);
		ofPolyline* newLine = new ofPolyline();
		newLine->addVertex(x, y);
		paths.push_back( *newLine);
		fading = false;
	}
	
}

void ofApp::onButtonPress(ofxDatGuiButtonEvent e)
{
	if (e.target->is("Clear"))
		clearPath();
	if (e.target->is("Clear Last"))
		clearLast();
	if (e.target->is("Update Values"))
		viewValues();
	if (e.target->is("Save to File"))
		saveFile();
	if (e.target->is("Load Background Image"))
		loadImage();
}





void ofApp::clearPath()
{
	fading = true;
}

void ofApp::clearLast()
{
	paths.pop_back();
}

void ofApp::viewValues()
{
	delim      =      delimEdit->getText();
	paren      =      parenEdit->getText();
	parenClose = parenCloseEdit->getText();

	showValues = true;
	values = paren;
	//std::vector<ofPoint> vertices = polyPath.getVertices();
	for (auto curPath = paths.begin(); curPath < paths.end(); curPath++)
	{
		vector<ofPoint> vertices= curPath->getVertices();
		if (curPath > paths.begin())
		{
			values += "\n{";

		}
		for (auto i = vertices.begin(); i < vertices.end(); i++)
		{
			if (i != vertices.begin())
				values += delim;
			values += paren + ofToString(i->x) + delim + ofToString(i->y) + parenClose;

		}
		values += parenClose;
		valueEdit->setText(values.substr(0, 30) + "...");
		if (vertices.size() == 0)
		{
			valueEdit->setText("");
		}
		
		
		
	}
}

void ofApp::saveFile()
{
	ofBuffer buf = ofBuffer();
	buf.append(values);
	ofFile file(filenameEdit->getText(), ofFile::ReadWrite);
	if (!file.exists()){
		file.create();
	}
	file.writeFromBuffer(buf);
	file.close();


}

void ofApp::loadImage()
{
	if (backgroundImage.load(imageFilenameEdit->getText()))
	{
		backgroundLoaded = true;
	}
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
