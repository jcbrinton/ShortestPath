#include "Graph.h"
#include <iomanip>
#include <string>
#include <vector>

using namespace std;
using std::setw;
Graph::Graph() //  Constructor
{
	
}

Graph::~Graph() //  Destructor
{

}

//   inserts unique airports names and returns the # given to it
int Graph::insert(std::vector<std::string>& symboltable, std::string airport) {
	int value = 0;
	bool added = false;
	for(value; value<symboltable.size(); value++){
		if (symboltable[value] == airport) {
			added = true;
			break;
		}
	}
	if(!added) {
		symboltable.push_back(airport);
	}
	
	return value;
}

//   finds if airports name is in symboltable and returns its position
int Graph::find(std::vector<std::string>& symboltable, std::string airport) {
	int value = 0;
	bool found = false;
	for (value; value<symboltable.size(); value++) {
		if (symboltable[value] == airport) {
			found = true;
			break;
		}
	}
	if (found) {
		return value;
	}
	else {
		return -1;
	}
}





