/**
 * UnweightedGraph Class
 * Stub written by Sorrachai Yingchareonthawornchai, 29 OCT 2014
 * Completed by Yiming Li
 */
#include "UnweightedGraph.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <array>

using namespace std;

UnweightedGraph::UnweightedGraph(const string& t)
{
	 //You may add any construction to your private attribute.
	ifstream in(t);
	if(!in.is_open()) {
		cerr << "cannot open file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	string line;
	while(getline(in,line)) {
		istringstream iss(line);
		int v;
		list<int> list_temp;
		while( iss >> v) {
			list_temp.push_back(v);
		}
		adj_list.push_back(list_temp);
	}
	//build a v*v matrix and map the edges between the vertices
	vector<int> empty_vec;
	for (unsigned int i = 0; i < adj_list.size(); i++){
		matrix.push_back(empty_vec);
		for (unsigned int j = 0; j < adj_list.size(); j++){
			this->matrix[i].push_back(0);
		}
	}
	for (unsigned int v = 0; v < adj_list.size(); v++){
		for (auto e = adj_list[v].begin(); e != adj_list[v].end(); e++){
			matrix[v][*e] = 1;
		}
	}
}

void UnweightedGraph::DisplayInfo() const{
	cout << "Adjacency list of the graph \n";
	auto printItem = [](const list<int>& alist) {
		copy(begin(alist),end(alist), ostream_iterator<int>(cout, " "));
		cout << endl;
	};
	for_each(begin(adj_list),end(adj_list), printItem);
}

bool UnweightedGraph::IsConnected() const {
	//Creat a one-dimensional matrix to store boolean for eah vertices.
	//If it is connected, it is false, it not it is true.
	vector<bool> temp;
	for (unsigned int i = 0; i < adj_list.size(); i++){
		temp.push_back(false);
	}
	//Go through the adj_list check all the edges between vertives. 
	//If a vertice has been connected, change the correspoding bool value
	//in the matrix turn to be true.
	for (auto v = adj_list.begin(); v != adj_list.end(); v++){
		list<int> edges = *v;
		for (auto e = edges.begin(); e != edges.end(); e++){
			temp[*e] = true;
		}
	}
	//Check the matrix, if found a false value in it, then it means all the 
	//vertices are not connected together, so return false. Otherwise, return 
	//true.
	for (auto b = temp.begin(); b != temp.end(); b++){
		if (*b == false){
			return false;
		}
	}
	return true; 
}

bool UnweightedGraph::IsEulerian() const {
	//Check if the graph is connected
	if (this->IsConnected()){
		//Check each size of edges of each vertices is even
		for (auto v = adj_list.begin(); v != adj_list.end(); v++){
			//If not, return false
			if (v->size() % 2 != 0){
				return false;
			}
		}
		//If all the vertices has even edges, return true
		return true;
	}
	return false;
}

list<int> UnweightedGraph::FindEulerianCycle() const {
	//Make a copy of the matrix
	vector<vector<int>> matrix_copy = matrix;
	//Make a copy of the adj_list
	vector<list<int>> list_copy = adj_list;
	//Make two cycle list, one is for current cycle, the other one is
	//for the whole cycle
	list<int> final_cycle, current_cycle;
	//from, to, start to track the vertices
	unsigned int from, to, start;
	//While the matrix still has valid edges in it, find the first valid
	//edge in it and start to track how it travel. After traveling each 
	//vertices, make the corresdponding edge to be zero.
	while (!VectorEmpty(matrix_copy, from, to)){
		start = from;
		current_cycle.push_back(from);
		current_cycle.push_back(to);
		matrix_copy[from][to] = 0;
		matrix_copy[to][from] = 0;
		from = to;
		//Check if it travel back to the start point, if not, keep travel and
		//track the route, and cancel the edges
		while (start != to){
			to = list_copy[from].front();
			list_copy[from].pop_front();
			while (matrix_copy[from][to] == 0 && !list_copy[from].empty()){
				to = list_copy[from].front();	
				list_copy[from].pop_front();
			}
			current_cycle.push_back(to);
			matrix_copy[from][to] = 0;
			matrix_copy[to][from] = 0;
			from = to;
		}
		//After it finish the current cycle, merge it with the final cycle.
		Merge(final_cycle, current_cycle);
	}
	return final_cycle;
}

bool UnweightedGraph::VerifyEulerCycle(const list<int>& cycle) const {
	//Make a copy of the matrix
	vector<vector<int>> matrix_copy = matrix;
	//Make a copy of the cycle
	list<int> cycle_copy = cycle;
	//Unsigned int from, to to trach the route of the travel
	unsigned int from, to;
	//Follow the cycle and go through the whole route. In the end, call
	//VectorEmpty function to check if the matric still has valid edge
	//And return the result.
	from = cycle_copy.front();
	cycle_copy.pop_front();
	while (!cycle_copy.empty()){
		to = cycle_copy.front();
		cycle_copy.pop_front();
		matrix_copy[from][to] = 0;
		matrix_copy[to][from] = 0;
		from = to;
	}
	return VectorEmpty(matrix_copy, from, to);
}


//Check if the matrix is empty without any valid edges in it.
bool UnweightedGraph::VectorEmpty(vector<vector<int>> v, unsigned int& x, unsigned int& y) const{
	//Go through the whole matrix, if one of item is 1, whcih means has a valid
	//edge. Then return false. If it go through the whole matrix without meeting 
	//any valid edge, which mean all the edge has been visited. Then return true.
	for (unsigned int i = 0; i < v.size(); i++){
		for (unsigned int j = 0; j < v[i].size(); j++){
			if (v[i][j] == 1){
				x = i;
				y = j;
				return false;
			}
		}
	}
	return true;
}


//Merge list2 into list1 at correct location and erase the list2
void UnweightedGraph::Merge(std::list<int>& list1, std::list<int>& list2) const{
	//If list1 is empty, then copy list2 directly into list1
	if (list1.empty()){
		list1 = list2;
	}
	//If list1 is not empty, then find the correct location for the cycle 
	//in list2 and move it into list1.
	else{
		for (auto v = list1.begin(); v != list1.end(); v++){
			if (*v == list2.front()){
				list2.pop_back();
				list1.splice(v, list2);
			}
		}
	}
	//Erase list2 to empty.
	list2.clear();
}
