#include "graph.h"

#include <iostream>
#include <fstream>
#include <string>
#include "ctime"

using namespace std;
void main(int argc, char *argv[])
{
	Graph graph;

	ifstream file;
	
	for (int i = 1; i < argc; ++i)
	{
		file.open(argv[i], ios::in);

		if (!file)
		{
			cout << "Error opening " << argv[i] << " for input" << endl;
			exit(-1);
		}

		string str;

		int vNum;
		getline(file, str);
		sscanf_s(str.c_str(), "%d", &vNum);

		graph.setVNum(vNum);
		graph.init();

		int source;
		int sink;
		getline(file, str);
		getline(file, str);
		sscanf_s(str.c_str(), "%d %d", &source, &sink);

		graph.setSource(source);
		graph.setSink(sink);

		int from;
		int to;
		int cap;
		long long cost;
		getline(file, str);
		while (getline(file, str))
		{
			sscanf_s(str.c_str(), "%d %d %d %lld", &from, &to, &cap, &cost);
			graph.insertUnDirEdge(from, to, cap, cost);
		}


		auto startTime = clock();
		graph.calMinCostMaxFlow();
		auto endTime = clock();

		auto time = 1.0 * (endTime - startTime) / CLOCKS_PER_SEC * 1000.0;


		cout << "File: " << argv[i] << endl;
		cout << "\tMaxFlow: " << graph.getMaxFlow() << endl;
		cout << "\tMinCost: " << graph.getMinCost() <<endl;
		cout << "\tSpentTime: " << time << "ms" << endl;

		file.close();
	}
	
	cin.get();

}