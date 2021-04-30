#include <iostream>
#include <cstdlib>
#include "ProcessFile.h"

using namespace std;

int displayMenu() 
{ 
	int choice; 
	cout << "\nPlease enter a numerical value for your choice\n" << endl; 
	cout << "1:Geographic Locations of units" << endl;
	cout << "2:Total distance of unit" << endl;
	cout << "3:Exit" << endl; 
	cin  >>  choice; 
	return choice; 
}
	


int main(int argc, char** argv) 
{	
	ProcessFile processFile; 
	int menuChoice = displayMenu(); 
	
	while (menuChoice != 3){ 
		
		//Allows user to enter in the range and displays the names of the units that are within the distance 
		//of any other unit. E.g. If the user enters 10 kilometers, then the app prints the units that are within 
		//5 Km of each other. 
		if(menuChoice == 1){
			int range; 
			cout << "\nHow many kilometers are between units?" << endl; 
			cin >> range; 
			processFile.displayUnitRange(range);
			menuChoice = displayMenu(); 
		
		}
	
		//Allows the user to enter or pick a unit ID. Outputs the total distance traveled by that unit over all the 
		//timeframes
		if(menuChoice == 2){
			string choice; 		
			//Get units to display 
			cout << "\nEnter the name of the unit" << endl;
			processFile.displayUnitList(); 			
			cin >> choice; 
			processFile.displayUnitTotal(choice);  
			menuChoice = displayMenu(); 
		
		}	
	
		else { 
			cout << "\nIncorrect menu value" << endl;
			menuChoice = displayMenu(); 
		}
	} 
	
	//Come up with a cool name	
	cout << "\nThank you for using this application" << endl;  

	return 0;
}

