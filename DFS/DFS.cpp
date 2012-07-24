// DFS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <exception>
#include <iostream>
#include <queue>
#include <string.h>
#include <string>
#include <functional>

#define NIL 0
static const int MAXNODES = 100;

class Graph {
public:
	class NodeWrapper;

	static const int WHITE = 0;
	static const int GREY = 1;
	static const int BLACK = 2;

private:
	struct Node {
		int data;
		Node* next[MAXNODES];
		int weight[MAXNODES];

		int numEdges;

		int color;
		Node* parent;
		int dfsIn;
		int dfsOut;
		int dist;

		Node(): color(WHITE), numEdges(0), dfsIn(0), dfsOut(0) {
			for (int i = 0; i < MAXNODES; i++) {
				next[i] = NIL;
				weight[i] = 0;
			}
		}

		void relaxAll() {
			if (dist == -1) {
				return;
			}
			for (int i = 0; i < numEdges; i++) {
				if(dist + weight[i] < next[i]->dist || next[i]->dist == -1) {
					next[i]->dist = dist + weight[i];
					next[i]->parent = this;
				}
			}
		}

	};

	Node vertices[MAXNODES];
	int numNodes;
	int dfsTimer;

public:
	typedef Node* GraphNode;

	Graph(): numNodes(0), dfsTimer(0) {
	}

	GraphNode add(int data_) {
		GraphNode node = vertices + numNodes++;
		node->data = data_;
		return node;
	}

	void connect(GraphNode n1, GraphNode n2, int w = 0) {
		n1->next[n1->numEdges] = n2;
		n1->weight[n1->numEdges++] = w;
	}

	void DFS() {
		int i = 0;
		for (i = 0; i < numNodes; i++) {
			vertices[i].color = WHITE;
			vertices[i].dfsIn = -1;
			vertices[i].dfsOut = -1;
			vertices[i].parent = NIL;
		}
		for (i = 0; i < numNodes; i++) {
			DFSvisit(vertices + i);
		}
	}

	void DFSprint(std::ostream& out) {
		int i = 0;
		for (i = 0; i < numNodes; i++) {
			out << "data: " << vertices[i].data;
			if (vertices[i].parent == NIL) {
				out << " parent : " << "None";
			} else {
				out << " parent : " << vertices[i].parent->data;
			}
			out << " dfsIn : " << vertices[i].dfsIn;
			out << " dfsOut: " << vertices[i].dfsOut;
			out << '\n';
		}
	}

	void minSourcePrint(std::ostream& out) {
		int i = 0;
		for (i = 0; i < numNodes; i++) {
			out << "data: " << vertices[i].data;
			if (vertices[i].parent == NIL) {
				out << " parent : " << "None";
			} else {
				out << " parent : " << vertices[i].parent->data;
			}
			out << " dist : " << vertices[i].dist;
			out << '\n';
		}
		out << '\n';
	}

	void DFSvisit (GraphNode node) {
		if (node->color != WHITE) {
			return;
		}
		node->color = GREY;
		node->dfsIn = dfsTimer++;
		for (int i = 0; i < node->numEdges; i++) {
			GraphNode child = node->next[i];
			if (child->color != WHITE) {
				continue;
			}
			child->parent = node;
			DFSvisit(child);
		}
		node->color = BLACK;
		node->dfsOut = dfsTimer++;
	}

	void BFS(GraphNode node) {
		int i = 0;
		for (i = 0; i < numNodes; i++) {
			vertices[i].color = WHITE;
			vertices[i].dfsIn = -1;
			vertices[i].dfsOut = -1;
			vertices[i].parent = NIL;
		}

		for (i = 0; i < numNodes; i++) {
			DFSvisit(vertices + i);
		}
	}

	class NodeWrapper {
	public:
		Node* node;

		friend bool operator==(const NodeWrapper& n1, const NodeWrapper& n2) {
			return (n1.node->dist == n2.node->dist);
		}

		friend bool operator!=(const NodeWrapper& n1, const NodeWrapper& n2) {
			return !(n1 == n2);
		}

		friend bool operator>(const NodeWrapper& n1, const NodeWrapper& n2) {
			if (n1.node->dist == n2.node->dist) {
				return false;
			}
			if (n1.node->dist == -1) {
				return false;
			}
			if (n2.node->dist == -1) {
				return true;
			}
			return (n2.node->dist > n1.node->dist);
		}

		friend bool operator>=(const NodeWrapper& n1, const NodeWrapper& n2) {
			return (n1 > n2 || n1 == n2);
		}

		friend bool operator<=(const NodeWrapper& n1, const NodeWrapper& n2) {
			return (!(n1 > n2));
		}

		friend bool operator<(const NodeWrapper& n1, const NodeWrapper& n2) {
			return (n1 <= n2 && n1 != n2);
		}
	};

	void Dijkstra(GraphNode node) {
		std::priority_queue<NodeWrapper> queue;

		int i = 0;
		for (i = 0; i < numNodes; i++) {
			vertices[i].dist = -1;
			vertices[i].parent = NIL;
		}

		node->dist = 0;
		node->parent = NIL;

		for (i = 0; i < numNodes; i++) {
			NodeWrapper* nw = new NodeWrapper();
			nw->node = vertices + i;
			queue.push(*nw);
		}

		while (!queue.empty()) {
			//minSourcePrint(std::cout);
			NodeWrapper& nw = queue.top(); 
			Node* node1 = nw.node;
			node1->relaxAll();
			queue.pop();
		}
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	Graph foo;
	Graph::GraphNode node0 = foo.add(0);
	Graph::GraphNode node1 = foo.add(1);
	Graph::GraphNode node2 = foo.add(2);
	Graph::GraphNode node3 = foo.add(3);
	Graph::GraphNode node4 = foo.add(4);

	foo.connect(node0,node1,10);
	foo.connect(node0,node2,5);
	foo.connect(node1,node2,2);
	foo.connect(node2,node1,3);
	foo.connect(node1,node3,1);
	foo.connect(node2,node3,9);
	foo.connect(node2,node4,2);
	foo.connect(node3,node4,4);
	foo.connect(node4,node0,7);
	foo.connect(node4,node3,6);

	//foo.DFS();
	//foo.DFSprint(std::cout);
	//std::cout << '\n' << '\n';

	//foo.BFS();
	//foo.BFSprint(std::cout);
	//std::cout << '\n' << '\n';

	foo.Dijkstra(node0);
	foo.minSourcePrint(std::cout);
	std::cout << '\n' << '\n';

	exit(0);
}
