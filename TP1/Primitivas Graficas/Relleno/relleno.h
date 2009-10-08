#ifndef RELLENO_H_
#define RELLENO_H_

#include <iostream>
#include "GL/glut.h"
#include "../../Constantes.h"

struct dcPt {
	int x;
	int y;
};

class Relleno {
	
	private:
		struct Edge {
			int yUpper;
			float xIntersect; 
			float dxPerScan;
			struct Edge* next;
		};	

		void insertEdge(Edge* list, Edge* edge);
		int yNext(int k, int cnt, dcPt* pts);
		void makeEdgeRec(dcPt lower, dcPt upper, int yComp, Edge* edge, Edge* edges[]);
		void buildEdgeList(int cnt, dcPt* pts, Edge* edges[]);
		void buildActiveList(int scan, Edge* active, Edge* edges[]);
		void fillScan(int scan, Edge* active);
		void deleteAfter(Edge* q);
		void updateActiveList(int scan, Edge* active);
		void resortActiveList(Edge* active);
	
	public:
		void scanLine(int cnt, dcPt* pts);
};

#endif /*RELLENO_H_*/
