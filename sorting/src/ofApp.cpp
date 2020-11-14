#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::update() {
	span = 5 * factor;
	if (button)
	{
		if (bool_bubble_sort == 1)
		{
			bubble_sort(&array[0]);
		}
		if (bool_selection_sort == 1)
		{
			selection_sort(&array[0]);
		}
		if (bool_insertion_sort)
		{
			insertion_sort(&array[0]);
		}
		if (bool_merge_sort)
		{
			merge_sort(&array[0]);
		}
		if (test)
		{
			test = animate->moveTo(&array[10], array[0].xpos);
		}
	}
	
	if (intField > 0 && intField != number)
	{
			number = intField;
			setup();
	}

}


//--------------------------------------------------------------
void ofApp::draw()
{
	 
	if (menu)
	{
		font.drawString(st[5], (ofGetWidth() / 2 - font.stringWidth(st[5]) / 2),40);
		gui.setPosition(ofGetWidth() / 2 - gui.getWidth() / 2,42);
		gui.draw();
		
		for(int i=0;i<3;i++)
			font.drawString(st[i], (ofGetWidth()/2-font.stringWidth(st[i])/2),(4+i)*40);
	}
	else
	{
		gui2.draw();
		font.drawString(st[3], (ofGetWidth() / 2 - font.stringWidth(st[4]) / 2),170);
		font.drawString(st[4], (ofGetWidth() / 2 - font.stringWidth(st[4]) / 2), 210);
		for (int i = 0; i < number; i++)
		{
			if (i == setColor[0] || i == setColor[1] || i == setColor[2])
				ofSetColor(242, 60, 112);
			else
				ofSetColor(145, 224, 215);
			ofDrawRectangle(array[i].pos, array[i].size.x, array[i].size.y);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == '1' && menu)
	{
		menu = 0;
		bool_bubble_sort = 1;
	}
	if (key == '2' && menu)
	{
		menu = 0;
		bool_selection_sort = 1;
	}
	if (key == '3' && menu)
	{
		menu = 0;
		bool_insertion_sort = 1;
	}
	if (key == '4' && menu)
	{
		menu = 0;
		bool_merge_sort = 1;
	}
	else if (key == 'r' && menu!=1)
	{
		shuffle();
	}
	else if (key == 'm')
	{
		setup();
		menu = 1;
		bool_selection_sort = bool_bubble_sort = bool_insertion_sort = 0;
	}
	else if (key == 'p' && menu)
	{
		menu = 0;
		test = 1;
	}
}