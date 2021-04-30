//Rachel Festervand 
// April 20, 2021
//This project takes in an XML file, processes the file.
//First feature checks Geographic location within distance of each other. 
//Second feature prints the total distance of the unit. 

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <list>
#include "ProcessFile.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <cmath>

#define pi 3.14159265358979323846

using namespace std; 
using namespace rapidxml;


ProcessFile::ProcessFile() 
{
}


ProcessFile::~ProcessFile()
{
}


//GROUP FEATURE 
//Displays the list of units, hard coded from the xml file
//could have processed them from the xml code with UnitId
void ProcessFile::displayUnitList() 
{ 
	cout << "\n UNIT LIST\n" << endl; 
	cout << "11/1/A/1-1IN " << " 12/1/A/1-1IN" << " 13/1/A/1-1IN" << endl; 
	cout << "14/1/A/1-1IN" << " 1/1/A/1-1IN" << " 2/1/A/1-1IN" << " 3/1/A/1-1IN" << endl; 
	cout << "4/1/A/1-1IN" << " 22/2/A/1-1IN" << " 23/2/A/1-1IN" << " 24/2/A/1-1IN" << endl; 
	cout << "1/2/A/1-1IN" << " 2/2/A/1-1IN" << " 3/2/A/1-1IN" << " 4/2/A/1-1IN" << endl; 
	cout << "31/3/A/1-1IN" << " 32/3/A/1-1I" << " 33/3/A/1-1IN" << " 34/3/A/1-1IN" << endl;
	cout << "4/3/A/1-1IN" << "HVT" << "RM01" << "RM02" << "Militia_0" << "Militia_1" << endl; 
	cout << "Militia_2" << "Militia_3" << "Militia_4" << endl; 

	
}
//Displays the unit total. Left some error checking code, commented it out to make app cleaner
void ProcessFile::displayUnitTotal(string unit)
{ 
	
	double lat1,long1,lat2,long2,lat3,long3;  
	lat1 =0; long1 =0; lat2 = 0; long2 = 0; lat3 = 0; long3 = 0; 
	
	
	xml_document<> doc;
	xml_node<> * rootNode = NULL;
	
	ifstream theFile ("testMessage.xml");
	/*if(!theFile.is_open())
		cout << "Error opening file" << endl; 
	else 
		cout << "Success opening file" << endl; */
	
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
   
	 // Parse the buffer
	doc.parse<0>(&buffer[0]);   
	//cout<<&buffer[0]<<endl;
	
	rootNode = doc.first_node("TimeFrame");
	//Just to verify it got the root
	/*if(rootNode == NULL)
		cout << "Did not get root" << endl; 
	else 
		cout << rootNode->name() << endl; */
	
	
	// Iterate over the unit nodes
	for (xml_node<> * unitNode = rootNode->first_node("Unit"); unitNode; unitNode = unitNode->next_sibling()){ 
		if(unitNode->first_node("UnitID")->value() == unit){ 
			xml_node<> * locNode = unitNode->first_node("Location"); 
			if(lat1 == 0 ){ 
				lat1 = atoi(locNode->first_node("lg:Lat")->value());
				long1 = atoi(locNode->first_node("lg:Lon")->value());
			}
			else if(lat1 != 0 && lat2 == 0){ 
				lat2 = atoi(locNode->first_node("lg:Lat")->value());
				long2 = atoi(locNode->first_node("lg:Lon")->value());
			}
			else { 
				lat3 = atoi(locNode->first_node("lg:Lat")->value());
				long3 = atoi(locNode->first_node("lg:Lon")->value());
			} 
			 
		}
	}
	
	int point1,point2; 
	point1 = calculateDistance(lat1,long1,lat2,long2); 
	point2 = calculateDistance(lat2,long2,lat3,long3); 
	int distance = point1 + point2; 
	cout << "/n" << unit << " traveled " << distance << " kms" << endl; 
	
}




//TOTAL DISTANCE FEATURE
//Displays the units that are in range 
void ProcessFile::displayUnitRange(int range) 
{ 
	cout << "UNITS WITHIN " << range << " KM" << endl; 
	xml_document<> doc;
	xml_node<> * rootNode = NULL;
	
	ifstream theFile ("testMessage.xml");
	/*if(!theFile.is_open())
		cout << "Error opening file" << endl; 
	else 
		cout << "Success opening file" << endl; */
	
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
   
	 // Parse the buffer
	doc.parse<0>(&buffer[0]);   
	//cout<<&buffer[0]<<endl;
	
	rootNode = doc.first_node("TimeFrame");
	//Just to verify it got the root
	if(rootNode == NULL)
		cout << "Did not get root" << endl; 
	else 
		cout << rootNode->name() << endl; 
	
		
	// Iterate over the unit nodes to get names and locations
	
	for (xml_node<> * unitNode = rootNode->first_node("Unit"); unitNode; unitNode = unitNode->next_sibling()){ 
		string name; 
		double lat, lon; 
		Location loc; 
		loc.name = unitNode->first_node("UnitID")->value(); 		
		xml_node<> * locNode = unitNode->first_node("Location");
		xml_node<> * latNode = locNode->first_node("lg:Lat");
		xml_node<> * lonNode = locNode->first_node("lg:Lon");
		cout << lonNode->value() << latNode->value(); 
		loc.lat = atoi(latNode->value()); 
		loc.lon = atoi(lonNode->value()); 	 
		units.push_back(loc); 	
		
	}
	
	
	//Iterate over the list and check for units within the range 
	double lat1,long1,lat2,long2;
	lat1 =0; long1 =0; lat2 = 0; long2 = 0;
	string name1,name2;
	list<Location>::iterator i = units.begin(); 
	list<Location>::iterator j = units.begin();
	
	
	for(i = units.begin();i != units.end();++i){  
		for(j= units.begin();j != units.end();++j){ 
		
			if(lat1 == 0){ //first one to be compared 
				lat1 = i->lat; 
				long1 = i->lon;
				name1 = i->name; 
				
			}
			else {			
				lat2 = j->lat; 
				long2 = j->lon;
				name2 = j->name;
				if(j == units.end())
					lat1 = 0; 
			}
			double distance = calculateDistance(lat1,long1,lat2,long2); 
			if(distance <= range){				
				cout << name1 << " and " << name2 << endl;
			} 
		} 
	}	
	
}



double ProcessFile::calculateDistance(double lat1, double long1, double lat2, double long2) {
	double dist;
	dist = sin(toRad(lat1)) * sin(toRad(lat2)) + cos(toRad(lat1)) * cos(toRad(lat2)) * cos(toRad(long1 - long2));
	dist = acos(dist);
	//dist = (6371 * pi * dist) / 180;
	dist = 6371 * dist;
	return dist;
}

double ProcessFile::toRad(double degree) {
	return degree/180 * pi;
}



