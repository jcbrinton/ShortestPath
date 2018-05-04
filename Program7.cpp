// Program7.cpp : Defines the entry point for the console application.
/* Joseph Brinton
CS 2420 Section 3
Program 7 Graph - Practice creating, traversing, and finding shortest paths in a directed graph
12/9/2017
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <stack>
#include "Graph.h"

#include <iomanip>


using namespace std;
using std::setw;

int main()		// Main function starts here
{
	cout << "Joseph Brinton" << endl << "CS 2420, Section 003" << endl << "Program 7 - Graph" << endl;

	Graph h;
	std::vector<string> symboltable;
	ifstream inputFile;
	string fileName;
	cout << "Please enter the name of data file: ";
	cin >> fileName;
	inputFile.open(fileName.c_str());
	if (inputFile.fail())
	{
		cout << "Error opening " << fileName << "\n";
		char c;
		cin >> c;
		cin.get();
		return 1;
	}

	
	string departure, destination; 
	int mile, cost;

	int i = 0;
	int j =0;

	cout << setw(11) << std::left << "Direct Flights" << endl;
	cout << setw(11) << std::left << "Source" << setw(11) << std::left << "Dest" << setw(11) << std::left << "Mileage" << setw(11) << std::left << "Cost" << endl;
	cout << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << endl;


	while (!inputFile.eof())  //read file to create airport table
	{
		inputFile >> departure >> destination >> mile >> cost;
		i = h.insert(symboltable, departure);
		j = h.insert(symboltable, destination);
	}

	sort(symboltable.begin(), symboltable.end()); // sorts airport table into alphabetical order

	//initialize matrices
	int size = symboltable.size();
	int infinity = 5000;
	std::vector <std::vector<int> > miles(size, std::vector<int>(size, infinity));
	std::vector <std::vector<int> > costs(size, std::vector<int>(size, infinity));

	inputFile.clear();
	inputFile.seekg(0, inputFile.beg);

	while (!inputFile.eof())  //reads file to insert values into matrices
	{
		inputFile >> departure >> destination >> mile >> cost; 
		i = h.insert(symboltable, departure);
		j = h.insert(symboltable,  destination);
		miles[i][j] = mile; 
		costs[i][j] = cost; 
		
	}
	inputFile.close();

	// prints Direct Flights report
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (costs[i][j] != 5000)
				cout << setw(11) << std::left << symboltable[i] << setw(11) << std::left << symboltable[j] << setw(11) << std::left << miles[i][j] << setw(1) << std::left <<"$"<< setw(10) << std::left <<costs[i][j] << endl;
		}
	}

	string airport;

	//loop to prompt for airport
	while (airport != "quit") {
		cout << "Please enter the name of the airport you will depart from:(Type 'quit' to exit) ";
		cin >> airport;
		int airportNumber = h.find(symboltable, airport);
		airportNumber;
		if (airportNumber >= 0) {

			std::vector<int> d = costs[airportNumber];

			std::vector<int> p = costs[airportNumber];
			std::list<int> L;
			std::list<int> RS;
			RS.push_back(airportNumber);

			int dsize = d.size();

			for (int j = 0; j < dsize; j++) {
			
					if (d[j] == 5000) {
						p[j] = -1;
					}
					else {
						p[j] = airportNumber;
						L.push_back(j);
					}
			}


			std::vector<int> dprime = d;

			//loop for shortest path algorithm
		while (!L.empty())
			{


				int dnumber = min_element(dprime.begin(), dprime.end()) - dprime.begin();

				dprime[dnumber] = 5000;

				L.remove(dnumber);


				for (int j = 0; j < dsize; j++) {
					
					bool inL = std::find(L.begin(), L.end(), j) != L.end();
					bool inRS = std::find(RS.begin(), RS.end(), j) != RS.end();

				
					if ((d[j] > (d[dnumber] + costs[dnumber][j])) && !inRS && costs[dnumber][j] !=5000) {

						d[j] = d[dnumber] + costs[dnumber][j];
						dprime[j] = d[dnumber] + costs[dnumber][j];
						p[j] = dnumber; 
						RS.push_back(dnumber);
						if (!inL) {
							L.push_back(j);
							

						}
					}
					
				}


			}


			cout <<  endl;
			cout << setw(11) << std::left << "Best Price Report" << endl;
			cout << setw(44) << std::left << " " << setw(44) << std::left << "Connecting Flight Information" << endl;
			cout << setw(11) << std::left << "Source" << setw(11) << std::left << "Dest" << setw(11) << std::left << "Cost" << setw(11) << std::left << "Mileage" << setw(11) << std::left << "Source" << setw(11) << std::left << "Dest" << setw(11) << std::left << "Cost" << setw(11) << std::left << "Mileage" << endl;
			cout << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << endl;

			int psize = p.size();

			// constructs flight paths from p vector
			for (int j = 0; j < psize; j++) {   

				int totalcosts = 0;
				int totalmileage = 0;

				if (p[j] >= 0) {

					std::stack<int> flightpath;

					int route = p[j];
					int c = j;
					while (route >= 0) {
						totalmileage = totalmileage + miles[route][c];
						totalcosts = totalcosts + costs[route][c];

						flightpath.push(route);
						c = p[c];
							route = p[route];
					}

					while (!flightpath.empty()) {
						int nextcity= j;
						int city = flightpath.top();
						flightpath.pop();
						if (!flightpath.empty()) {
							nextcity = flightpath.top();
						}
						if (airportNumber == city) {
							cout << setw(11) << std::left << airport << setw(11) << std::left << symboltable[j] << setw(1) << std::left << "$" << setw(10) << std::left << totalcosts << setw(11) << std::left << totalmileage << setw(11) << std::left << symboltable[city] << setw(11) << std::left << symboltable[nextcity] << setw(1) << std::left << "$" << setw(10) << std::left << costs[city][nextcity] << setw(11) << std::left << miles[city][nextcity] << endl;

						}
						else {
							cout << setw(44) << std::left << "" << setw(11) << std::left << symboltable[city] << setw(11) << std::left << symboltable[nextcity] << setw(1) << std::left << "$" << setw(10) << std::left << costs[city][nextcity] << setw(11) << std::left << miles[city][nextcity] << endl;

						}

					}
					cout << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << setw(11) << std::left << "---------" << endl;

				}
				}

			cin.clear();
			cin.ignore(10000, '\n');
				cout << "Press ENTER when done viewing report...";
			while (cin.get() != '\n') {}

			}
			else if(airport != "quit"){
				cout << "Not a valid airport abbreviation. Try again." << endl;
			}

		}
	

	char c;
	cin >> c;
	cin.get();
	return 0;
}