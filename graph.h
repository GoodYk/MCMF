/****************************************************************************
///
///  Copyright (c) GoodYk
///  All rights reserved.
///
///  @file                  graph.h
///  @author                GoodYk
///  @e-mail                yaokun@hust.edu.cn
****************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H


#include <vector>
#include <unordered_map>


using namespace std;

class Graph
{
public:

	struct Edge
	{
		int from;
		int to;
		int cap;
		long long cost;

		int initCap;
		long long initCost;
		Edge *reverseEdge;
		bool isReturnEdge;

		Edge(int from, int to, int cap, long long cost, bool isReturnEdge)
		{
			this->from = from;
			this->to = to;
			this->cap = cap;
			this->cost = cost;

			this->initCap = cap;
			this->initCost = cost;
			this->isReturnEdge = isReturnEdge;
		}

		void setCap(int cap) { this->cap = cap; }
		void setCost(long long cost) { this->cost = cost; }

		void setReverseEdge(Edge *reverseEdge)
		{
			this->reverseEdge = reverseEdge;
		}

		//for net vertex and super sink
		void initEdge()
		{
			initEdgeCap();
			initEdgeCost();
		}

		void initEdgeCap() { cap = initCap; }
		void initEdgeCost() { cost = initCost; }

	};

	Graph();

	Graph(const Graph & graph);
	
	~Graph();

	Graph & operator = (const Graph & graph);

	/**
	 * @brief  set source of the Graph
	 * @param [in] source: the index of source 
	 */
	void setSource(int source);


	/**
	 * @brief  get source index 
	 */
	int getSource();

	/**
	* @brief  set sink of the Graph
	* @param [in] sink: the index of sink
	*/
	void setSink(int sink);

	/**
	* @brief  get sink index
	*/
	int getSink();


	/**
	* @brief  set the number of vertices  
	*/
	void setVNum(int vNum);

	/**
	* @brief  get vertex number
	*/
	int getVNum();

	/**
	* @brief  insert directed edge into the Graph
	* @param  [in] from: the beginning vertex of edge
	* @param  [in] to: the ending vertex of edge
	* @param  [in] cap: the capacity of edge
	* @param  [in] cost: the cost of edge
	*/
	void insertDirEdge(int from, int to, int cap, long long cost);

	/**
	* @brief  insert undirected edge into the Graph
	* @param  [in] left: one vertex of edge
	* @param  [in] right: the other one vertex of edge
	* @param  [in] cap: the capacity of edge
	* @param  [in] cost: the cost of edge
	*/
	void insertUnDirEdge(int left, int right, int cap, long long cost);

	/**
	* @brief  calculate the max flow and the min cost under max flow
	*/
	void calMinCostMaxFlow();

	/**
	 * @brief  get the min cost      
	 * @return the min cost
	 */
	long long getMinCost();

	/**
	* @brief  get the max cost
	* @return the max cost
	*/
	int getMaxFlow();

	/**
	 * @brief  initialize the graph after set vertex number
	 */
	void init();

protected:
	
	vector<vector<Edge *>>  adjVec;

	long long minCost;
	int maxFlow;

	int vNum;
	int source;
	int sink;
	
private:
	vector<bool> known;
	long long unitFlowCost;

	void clearAdjVec();
	bool relabel();
	int augment(int source, int flow);
	Edge * insertEdge(int from, int to, int cap, long long cost, bool isReturnEdge = false);

};
 

#endif // GRAPH_H