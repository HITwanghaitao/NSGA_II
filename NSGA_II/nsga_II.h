#pragma once
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

struct Node
{
	vector<double> X = vector<double>(2);
	vector<double> Y = vector<double>(2);
	int flag;
	int np = 0;
	vector<double> S;
};

class NSGA
{
public:
	vector<Node> Population;
	int N = 100;
	vector<vector<double>> F;
	void Initialization();
	void Sort();
	bool compare(Node node1,Node node2);

};
vector<double> function(vector<double> x);