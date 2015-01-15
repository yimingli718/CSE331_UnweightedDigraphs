/**
 * UnweightedGraph Class
 * Interface written by Sorrachai Yingchareonthawornchai, 29 OCT 2014
 * Completed by Yiming Li
 */
#ifndef UnweightedGraph_H
#define UnweightedGraph_H
#include <string>
#include <list>
#include <vector>

class UnweightedGraph
{
	public:
	UnweightedGraph(const std::string& t);
	
	void DisplayInfo() const;
	bool IsConnected() const;
	bool IsEulerian() const;
	
	std::list<int> FindEulerianCycle () const;
	bool VerifyEulerCycle(const std::list<int>& cycle) const;
	
	//helper function
	//Check if the matrix is empty or not, and pass the first valid edge to x,y
	bool VectorEmpty(std::vector<std::vector<int>> v, unsigned int& x, unsigned int& y) const;
	//Merge list2 to list1 and erase list2.
	void Merge(std::list<int>& list1, std::list<int>& list2) const;

	private:
	std::vector<std::list<int>> adj_list;
	std::vector<std::vector<int>> matrix;
	//Add any attribute or method that can help complete your implementation
};
#endif
