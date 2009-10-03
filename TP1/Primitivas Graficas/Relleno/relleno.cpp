#include "relleno.h"

void Relleno::insertEdge(Edge* list, Edge* edge) {
	
	Edge *p, *q= list;
	p= q->next;
	
	while(p) {
		if(edge->xIntersect < p->xIntersect)
			p= NULL;
		else {
			q= p;
			p= p->next;
		}	
	}
	edge->next= q->next;
	q->next= edge;
}

int Relleno::yNext(int k, int cnt, dcPt* pts) {
	
	int j;
	
	if((k+1) > (cnt-1))
		j= 0;
	else
		j= k+1;
	
	while(pts[k].y == pts[j].y) {
		if((j+1) > (cnt-1))
			j= 0;
		else
			j++;
	}
	return pts[j].y;
}

void Relleno::makeEdgeRec(dcPt lower, dcPt upper, int yComp, Edge* edge, Edge* edges[]) {
	
	edge->dxPerScan= (float) (upper.x - lower.x) / (upper.y - lower.y);
	edge->xIntersect= lower.x;
	
	if(upper.y < yComp)
		edge->yUpper= upper.y - 1;
	else
		edge->yUpper= upper.y;
	
	insertEdge(edges[lower.y], edge);
}

void Relleno::buildEdgeList(int cnt, dcPt* pts, Edge* edges[]) {
	
	Edge *edge;
	dcPt v1, v2;
	int yPrev= pts[cnt-2].y;
	
	v1.x= pts[cnt-1].x;
	v1.y= pts[cnt-1].y;
	
	for(int i= 0; i<cnt; i++) {
		v2= pts[i];
		if(v1.y != v2.y) { //No lineas horizontales
			edge= new Edge();
			
			if(v1.y < v2.y)  //Creciente
				makeEdgeRec(v1, v2, yNext(i, cnt, pts), edge, edges);
			else	//Decreciente
				makeEdgeRec(v1, v2, yPrev, edge, edges);
		}
		yPrev= v1.y;
		v1= v2;
	}
}

void Relleno::buildActiveList(int scan, Edge* active, Edge* edges[]) {
	
	Edge *p, *q;
	
	p= edges[scan]->next;
	while(p) {
		q= p->next;
		insertEdge(active, p);
		p= q;
	}
}

void Relleno::fillScan(int scan, Edge* active) {

	Edge *p1, *p2;
	p1= active->next;
	
	while(p1) {
		p2= p1->next;

		std::cout << "p1->xIntersect: " << p1->xIntersect << std::endl;
		std::cout << "p2->xIntersect: " << p2->xIntersect << std::endl;
		
		for(int i= p1->xIntersect; i<p2->xIntersect; i++) {
			std::cout << "Pinto: i,scan" << std::endl;
			glVertex2i((int) i, scan);
		}
		p1= p2->next;
	}
	
}

void Relleno::deleteAfter(Edge* q) {
	
	Edge* p= q->next;
	q->next= p->next;
	
	delete p;
}

void Relleno::updateActiveList(int scan, Edge* active) {
	
	Edge* q= active, *p= active->next;
	
	while(p) {
		if(scan >= p->yUpper) {
			p= p->next;
			deleteAfter(q);
		} else {
			p->xIntersect= p->xIntersect + p->dxPerScan;
			q= p;
			p= p->next;
		}	
	}
}

void Relleno::resortActiveList(Edge* active) {
	
	Edge* q, *p= active->next;
	active->next= NULL;
	
	while(p) {
		q= p->next;
		insertEdge(active, p);
		p= q;
	}
}

void Relleno::scanLine(int cnt, dcPt* pts) {
	
	Edge *edges[WINDOW_HEIGHT], *active;
	
	for(int i=0; i < WINDOW_HEIGHT; i++) {
		edges[i]= new Edge();
		edges[i]->next= NULL; 
	} 
	
	buildEdgeList(cnt, pts, edges);
	
	std::cout << "Paso buildEdgeList" << std::endl;
	
	active= new Edge();
	active->next= NULL;
	
	for(int scan= 0; scan < WINDOW_HEIGHT; scan++) {
		
		buildActiveList(scan, active, edges);
		std::cout << "Paso buildActiveList" << std::endl;

		if(active->next) {

			std::cout << "Tengo next" << std::endl;

			fillScan(scan, active);
			updateActiveList(scan, active);
			resortActiveList(active);
		}
		
		std::cout << "Scan:" << scan << std::endl;
		std::cout << "WINDOW_HEIGHT:" << WINDOW_HEIGHT << std::endl;
	}
	
	//TODO: liberar
}