#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Graph {  	// Graph class definition
public:
	Graph();
	int insert(std::vector<std::string>& abbrev, std::string airport);
	int find(std::vector<std::string>& abbrev, std::string airport);
	~Graph();
};