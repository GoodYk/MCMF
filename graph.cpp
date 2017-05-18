/****************************************************************************
///
///  Copyright (c) GoodYk
///  All rights reserved.
///
///  @file                  graph.h
///  @author                GoodYk
///  @e-mail                yaokun@hust.edu.cn
****************************************************************************/

#include "graph.h"

#include <limits.h>
#include <algorithm>
#include <string>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))



Graph::Graph()
{

}



Graph::Graph(const Graph & graph)
{
	operator = (graph);
}

Graph::~Graph()
{
	for (auto edgeVec : adjVec)
	{
		for (auto edge : edgeVec)
		{
			delete edge;
		}
	}
}

Graph & Graph::operator = (const Graph & graph)
{
	if (this != &graph)
	{
		vNum = graph.vNum;
		known = graph.known;

		minCost = graph.minCost;
		maxFlow = graph.maxFlow;

		source = graph.source;
		sink = graph.sink;

		unitFlowCost = graph.unitFlowCost;

		adjVec.resize(vNum);

		for (auto edgeVec : graph.adjVec)
		{
			for (auto edge : edgeVec)
			{
				Edge * tempEdge = new Edge(*edge);
				adjVec[tempEdge->from].push_back(tempEdge);
			}
		}
	}

	return *this;
}

void Graph::setSource(int source)
{
	this->source = source;
}

int Graph::getSource()
{
	return source;
}

void Graph::setSink(int sink)
{
	this->sink = sink;
}

int Graph::getSink()
{
	return sink;
}

void Graph::setVNum(int vNum)
{
	this->vNum = vNum;
}

int Graph::getVNum()
{
	return vNum;
}

void Graph::calMinCostMaxFlow()
{
	minCost = 0;
	maxFlow = 0;
	unitFlowCost = 0;

	do
	{
		known.assign(vNum, false);
		while (augment(source, INT_MAX) > 0)
		{
			known.assign(vNum, false);
		}
	} while (relabel());
}

long long Graph::getMinCost()
{
	return minCost;
}

int Graph::getMaxFlow()
{
	return maxFlow;
}

void Graph::init()
{
	clearAdjVec();
	adjVec.resize(vNum);
	known.assign(vNum, false);
}

void Graph::clearAdjVec()
{
	for (auto edgeVec : adjVec)
	{
		for (auto edge : edgeVec)
		{
			delete edge;
			edge = nullptr;
		}
	}

	adjVec.clear();
	
}

bool Graph::relabel()
{
	long long tempCost = LLONG_MAX;

	for (int i = 0; i < vNum; ++i)
	{
		if (known[i])
		{
			for (auto edge : adjVec[i])
			{
				if (edge->cap > 0 && !known[edge->to] && edge->cost < tempCost)
				{
					tempCost = edge->cost;
				}
			}
		}
	}

	if (tempCost == LLONG_MAX)
	{
		return false;
	}

	for (int i = 0; i < vNum; ++i)
	{
		if (known[i])
		{
			for (auto edge : adjVec[i])
			{
				edge->cost -= tempCost;
				edge->reverseEdge->cost += tempCost;
			}
		}
	}

	unitFlowCost += tempCost;
	return true;
}

int Graph::augment(int source, int flow)
{
	if (source == sink)
	{
		minCost += unitFlowCost * flow;
		maxFlow += flow;
		return flow;
	}

	known[source] = true;

	int leftFlow = flow;
	int tempFlow;
	for (auto edge : adjVec[source])
	{
		if (edge->cap > 0 && edge->cost == 0 && !known[edge->to])
		{
			tempFlow = augment(edge->to, MIN(edge->cap, leftFlow));

			edge->cap -= tempFlow;
			edge->reverseEdge->cap += tempFlow;
			leftFlow -= tempFlow;
			if (leftFlow <= 0)
			{
				return flow;
			}
			if (tempFlow > 0)
			{
				break;
			}
		}
	}
	return flow - leftFlow;
}

Graph::Edge * Graph::insertEdge(int from, int to, int cap, long long cost, bool isReturnEdge /*= false*/)
{
	Edge * edge = new Edge(from, to, cap, cost, isReturnEdge);
	adjVec[from].push_back(edge);
	return edge;
}

void Graph::insertDirEdge(int from, int to, int cap, long long cost)
{
	Edge * edge = insertEdge(from, to, cap, cost);
	Edge * returnEdge = insertEdge(to, from, 0, -cost, true);
	edge->reverseEdge = returnEdge;
	returnEdge->reverseEdge = edge;
}

void Graph::insertUnDirEdge(int left, int right, int cap, long long cost)
{
	insertDirEdge(left, right, cap, cost);
	insertDirEdge(right, left, cap, cost);
}