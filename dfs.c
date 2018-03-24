/* This code is a slightly changed version of the code of Chapter 11
of the book
"Data Structures and Program Design in C" by
R. Kruse, C. L. Tondo and B. Leung */
#include <stdio.h>
#include <stdlib.h>
#include "GraphTypes.h"


/* global variable visited */
Boolean visited[MAXVERTEX];
Vertex start[MAXVERTEX];
Vertex end[MAXVERTEX];
Node *Head;
int clock,push;


/*
Scans the count, and then the adjacency as follows.
For every vertex, the vertexes that are connected with it are scanned, with a white space between them, and -1 when finished.
For example this adjacency list:
__
|0|->1->3
|1|->2->3->4
|2|->3
|3|
|4|->0
should be written like this:

5
1 3 -1
2 3 4 -1
3 -1
-1
0 -1

*/
void ScanGraphAdjList(Graph *G){
	int count,firsttime;
	Vertex v,w;
	Edge *new, *prev;
	scanf("%d",&count);
	G->n=count;
	for(v=0 ; v<count ; v++)
		G->firstedge[v]=NULL;
	for(v=0 ; v<count ; v++){
		firsttime=1;
		while(1){
			scanf("%d",&w);

			if(w==-1) break;
			if(w>=count){
				printf("Wrong Input\n");
				exit(1);
			}
			new=malloc(sizeof(Edge));
			new->endpoint=w;
			new->nextedge=NULL;
			if(firsttime){
				G->firstedge[v]=new;
				prev=G->firstedge[v];
				firsttime=0;
			}else{
				prev->nextedge=new;
				prev=prev->nextedge;
				
			}
		}
	}
}


void Push(Vertex v)
{
	Node *new;
	new=malloc(sizeof(Node));
	new->v=v;
	new->next=Head;
	Head=new;
}

/*Returns the last item of the stack,and deletes it*/
Vertex Pop(void){
	Node *tmp=Head;
	Vertex rtrn=Head->v;
	Head=Head->next;
	free(tmp);
	return rtrn;
}


void Connect(Graph *G,Vertex v,Vertex w)
{
	Edge *lastedge, *new;

	new=malloc(sizeof(Edge));
	new->endpoint=w;
	new->nextedge=NULL;
	
	if(G->firstedge[v]==NULL)
		G->firstedge[v]=new;
	else{
		lastedge=G->firstedge[v];
		while(lastedge->nextedge!=NULL)
			lastedge=lastedge->nextedge;
		lastedge->nextedge=new;
	}
}

Graph Transpose(Graph G)
{
	Graph Gt;
	Vertex v,w;
	Edge *curedge;

	Gt.n=G.n;
	for(v=0 ; v<G.n ; v++)
		Gt.firstedge[v]=NULL;
	for (v=0; v < G.n; v++){
		curedge=G.firstedge[v];
		while(curedge){
			w=curedge->endpoint;
			Connect(&Gt,w,v);
			curedge=curedge->nextedge;
		}
	}
	return Gt;
}

void Noop(Vertex x){

}

/* Traverse: recursive traversal of a graph
   Pre: v is a vertex of graph G
   Post: The depth first traversal, using function Visit, has been
   completed for v and for all vertices adjacent to v.
   Uses: Traverse recursively, Visit */
void Traverse(Graph G, Vertex v, void (*Visit)(Vertex))
{
  start[v]=clock++;

  Vertex w;
  Edge *curedge;

  visited[v]=TRUE;
  Visit(v);

  curedge=G.firstedge[v];      /* curedge is a pointer to the first edge (v,_) of V */
  while (curedge){
    w=curedge->endpoint;        /* w is a successor of v and (v,w) is the current edge */
    if (!visited[w]) Traverse(G, w, Visit);
    curedge=curedge->nextedge;  /*curedge is a pointer to the next edge (v,_) of V */
  }
  if(push) Push(v);
  end[v]=clock++;
}

/* DepthFirst: depth-first traversal of a graph
   Pre: The graph G has been created.
   Post: The function Visit has been performed at each vertex of G in depth-first order
   Uses: Function Traverse produces the recursive depth-first order */
void SSC(Graph G, void (*Visit)(Vertex))
{
  clock=0;
  Vertex v;
  free(Head);
  Head=NULL;
  push=1; 

  /*	DFS	*/
  for (v=0; v < G.n; v++)
    visited[v]=FALSE;
  for (v=0; v < G.n; v++)
    if (!visited[v])  Traverse(G, v, Noop);

  Graph Gt=Transpose(G);

  for (v=0; v < G.n; v++)
    visited[v]=FALSE;
  push=0;
  while(Head!=NULL){	/*While stack is not empty*/
	v=Pop();
	if(visited[v]==FALSE){
		printf("{ ",v);
		Traverse(Gt, v, Visit);
		printf("}\n");
	}
  }
 
}

void PrintStack()
{
	Node *temp=Head;
	while(temp!=NULL){
		printf("%d\t",temp->v);
		temp=temp->next;
	}

}

/* PrintElement: prints the value of its parameter x */
void PrintElement(Vertex x)
{
  printf("%d ", x);
}

