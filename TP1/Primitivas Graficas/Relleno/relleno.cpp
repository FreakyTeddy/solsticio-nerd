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
	
	//TODO: HARCODEOOOO
	//std::cout << lower.y << std::endl;
	if(lower.y<WINDOW_HEIGHT && lower.y>0)
		insertEdge(edges[lower.y], edge);
	else if(lower.y>WINDOW_HEIGHT)
		insertEdge(edges[WINDOW_HEIGHT-1], edge);
	else
		insertEdge(edges[0], edge);
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
				makeEdgeRec(v2, v1, yPrev, edge, edges);
		} else {
		//	std::cout << "HORIZONTALES" << std::endl;
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
	
	while(p1 && p1->next) {
		p2= p1->next;
	     
	  for(int i= p1->xIntersect; i<p2->xIntersect; i++)
			glVertex2i(i, scan);
	     
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
		
	active= new Edge();
	active->next= NULL;
	
	for(int scan= 0; scan < WINDOW_HEIGHT; scan++) {
		
		buildActiveList(scan, active, edges);

		if(active->next) {
			fillScan(scan, active);
			updateActiveList(scan, active);
			resortActiveList(active);
		}
	}
	
	delete active;
}
