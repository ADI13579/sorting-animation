#include "ofApp.h"

int ofApp::get_max()
{
	int temp = pow(2, nodes);
	if (temp > 1000)
		temp = 999;
	while (array[temp] == -1)
	{
		temp--;
	}
	return temp;
}
void ofApp::insert(int input, int index)
{
	if (index < 1000)
	{
		if (array[index] == -1)
		{
			nodes++;
			array[index] = input;
			max_index = get_max();
			return;
		}
		else if (input > array[index])
			insert(input, 2 * index + 1);
		else if (input < array[index])
			insert(input, 2 * index);
		else if (array[index] == input)
		{
			exists= index;
			return;
		}
	}
}

int ofApp::search(int input, int pos,int *search_pos)
{
	if (pos < 500)
	{
		if (input == -1)
			return -1;
		else if (input > array[pos])
			search(input, 2 * pos + 1,search_pos);
		else if (input < array[pos])
			search(input, 2 * pos,search_pos);
		else if (array[pos] == input)
		{
			*search_pos=pos;
		}
	}
}


void ofApp::remove(int input)
{
	int search_pos=0,temp=0,insertedat=0;
	search(input, 1,&search_pos);
	if (search_pos!= -1 && search_pos!=0 && search_pos<500);
	{
		nodes--;
		if (array[2 * search_pos] == -1 && array[2 * search_pos + 1] == -1)
			array[search_pos] = -1;
		else if (array[2 * search_pos] != -1 && array[2 * search_pos + 1] != -1)
		{
			temp = 2 * search_pos + 1;
			while (array[2 * temp] != -1)
			{
				temp*=2;
			}
			
			int copy = array[temp];
			remove(array[temp]);
			array[search_pos] = copy;
		}
		else if (array[2 * search_pos] == -1 && array[2 * search_pos + 1] != -1)
		{
			array[search_pos] = array[2 * search_pos + 1];
			array[2 * search_pos + 1] = -1;

			for (int i = search_pos * 2 + 2; i <=max_index; i++)
			{
				if (array[i] != -1)
				{
					insert(array[i], 1);
					array[i] = -1;
				}
			}
		}
		else if (array[2 * search_pos] != -1 && array[2 * search_pos + 1] == -1)
		{
			array[search_pos] = array[2 * search_pos];
			array[2 * search_pos] = -1;
			for (int i = 2*search_pos; i <= max_index; i++)
			{
				if (array[i] != -1)
				{
					insert(array[i], 1);
					array[i] = -1;
				}
			}
		}
		max_index = get_max();
	}
	search_pos = exists = -1;
}
//--------------------------------------------------------------
void ofApp::setup(){
	for (int i = 0; i < 1000; i++)
		array[i] = -1;
	
	pos_array[0] = -1;

	for (int i = 1; i < 8; i++)
	{
		for (int j = pow(2, i - 1),k=1; j < pow(2, i); j++,k+=2)
		{
			pos_array[j]=k*ofGetWidth()/ (pow(2,i));
		}
	}


	index = nodes=max_index=0;
	input = -1;

	panel.setup();
	panel.add(input.setup("Enter Data", input));
	panel.add(searchButton.setup("Press to search", searchButton));
	panel.add(insertButton.setup("Press to insert", insertButton));
	panel.add(removeButton.setup("Press to remove", removeButton));

	insertButton = removeButton = 0;


	insert(47, 1);
	insert(24, 1);
	insert(21, 1);
	insert(25, 1);
	insert(48, 1);
	insert(49, 1);
}

//--------------------------------------------------------------
void ofApp::update(){
	int insertedat;
	index = 1;
	if ((insertButton || searchButton || removeButton) && input == -1)
		removeButton = insertButton = removeButton = 0;
	else if (insertButton && input!=-1)
	{
		search_pos=exists = -1;
		insert(input,1);
		removeButton=searchButton=insertButton = 0;
		if (exists == -1)
			searchButton = 1;
	}
	else if (removeButton && input!=-1)
	{
		search_pos =exists= -1;
		remove(input);
		insertButton=searchButton=removeButton = 0;
		input = -1;
	}
	else if(searchButton && input!=-1)
	{
		search_pos =exists= -1;
		search(input, 1, &search_pos);
		insertButton=searchButton=searchButton = 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	panel.draw();
	
	int k = 1;
	
	for (int i = 1; i <= max_index; i++)
	{
		if (array[2 * i] != -1)
		{
			ofDrawLine(ofVec2f(pos_array[i], k * 100), ofVec2f(pos_array[2 * i], (k + 1) * 100));
		}
		if (array[2 * i+1] != -1)
		{
			ofDrawLine(ofVec2f(pos_array[i], k * 100), ofVec2f(pos_array[2 * i+1], (k + 1) * 100));
		}
		if (array[i] != -1)
		{
			if (search_pos == i)
				ofSetColor(117, 216, 136);
			else if (exists == i)
				ofSetColor(209,56,89);
			else
				ofSetColor(163, 119, 147);

			ofDrawCircle(ofVec2f(pos_array[i], k * 100), 50);
			ofSetColor(0, 0, 0);
			ofDrawBitmapString(array[i], pos_array[i]-12, k * 100);
		}
		if (i == pow(2, k) - 1)
		{
			k++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'r')
		setup();
}