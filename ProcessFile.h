
//Rachel Festervand 
//April 20,2021 

#ifndef PROCESSFILE_H
#define PROCESSFILE_H
#include <string> 
#include <list>
#include <iostream>

using namespace std; 

class ProcessFile {
    
public:
    ProcessFile();
    virtual ~ProcessFile();
    void displayUnitList(); 
    void displayUnitRange(int); 
    void displayUnitTotal(string); 
    
private:
    struct Location{
        string name; 
        double lat; 
        double lon;
        void print()const{
            cout << name << ":" << lat << " " << lon << " ";}         
    }; 
    
    list<Location> units;
    
    double calculateDistance(double,double,double,double); 
    double toRad(double); 
    
};

#endif /* PROCESSFILE_H */

