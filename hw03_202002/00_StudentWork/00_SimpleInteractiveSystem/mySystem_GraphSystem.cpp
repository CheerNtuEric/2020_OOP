//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2020/05/01
//
#include <iostream>
#include "mySystem_GraphSystem.h"
#include <time.h>
#include <math.h>
#define PI 3.1415926535

using namespace std;

int Param::GRAPH_MAX_NUM_NODES = 10000;
int Param::GRAPH_MAX_NUM_EDGES = 10000;
double Param::GRAPH_NODE_RADIUS = 1;
int RandomCircle = 24;
GRAPH_SYSTEM::GRAPH_SYSTEM( )
{
    mFlgAutoNodeDeletion = false;
	initMemorySpace();
    createDefaultGraph();
    //
    // Implement your own stuff
    //
}

void GRAPH_SYSTEM::reset( )
{
    stopAutoNodeDeletion();
    mPassiveSelectedNode = 0;
    mSelectedNode = 0;
    //
    // Implement your own stuff
    //
	for(int i = 0 ; i < mMaxNumEdges ; i++)
		mFreeNodeArr[i] = i;
	for(int i = 0 ; i < mMaxNumNodes ; i++)
		mFreeEdgeArr[i] =i;
	mCurNumFreeEdges = mMaxNumEdges;
	mCurNumFreeNodes = mMaxNumNodes;

	mCurNumActiveNodes = 0;
	mCurNumActiveEdges = 0;
}

void GRAPH_SYSTEM::initMemorySpace()
{
	 mMaxNumNodes = Param::GRAPH_MAX_NUM_NODES = 10000;
	 mMaxNumEdges = Param::GRAPH_MAX_NUM_EDGES = 10000;

	 mPool_Edges = new GRAPH_EDGE[mMaxNumEdges];
	 mPool_Nodes = new GRAPH_NODE[mMaxNumNodes];
		 //
		for(int i = 0 ; i < mMaxNumNodes ; i++)
			mPool_Nodes[i].id = i;
		for(int i = 0 ; i < mMaxNumEdges ; i++)
			mPool_Edges[i].id = i;
		//

	mFreeNodeArr = new int [mMaxNumNodes];
	mFreeEdgeArr = new int [mMaxNumNodes];
	mCurNumFreeEdges = 0;
	mCurNumFreeNodes = 0;
	//
	mActiveNodeArr = new int [mMaxNumNodes];
	mActiveEdgeArr = new int [mMaxNumEdges];
	mCurNumActiveNodes = 0;
	mCurNumActiveEdges = 0;
	reset();
}

void GRAPH_SYSTEM::createDefaultGraph( )
{
    reset( );
    //
    // Implement your own stuff
    //
	int v0 = addNode(0.0, 0.0, 0.0, Param::GRAPH_NODE_RADIUS);
	int v1 = addNode(10.0, 0.0, 0.0, Param::GRAPH_NODE_RADIUS);
	int v2 = addNode(10.0, 0.0, 10.0, Param::GRAPH_NODE_RADIUS);
	addEdge(v0, v1);
	addEdge(v0, v2);
}

void GRAPH_SYSTEM::createRandomGraph_DoubleCircles(int n)
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 15; // radius
    float d = 10; // layer distance
    float offset_x = 15.;
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
	int *inner,*outer;
	inner = new int[n];
	outer = new int [n];
	for( int i =0; i < n; i++  ){
		float x = cos(2*PI*i/n);
		float z = sin(2*PI*i/n);
		inner[i] = addNode(x*r+offset_x, 0.0, z*r+offset_z);
		outer[i] = addNode(x*(r+d)+offset_x, 0.0, z*(r+d)+offset_z);
	}
	//addEdge
	for(int i = 0, num = 0 ; i < n ; i++){
		num = rand()%3-1;
		addEdge(inner[i], outer[i+num]);
	}
}

void GRAPH_SYSTEM::createNet_Circular( int n, int num_layers )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 15.;
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
	num_layers++;
	int *prev, *now;
	prev = new int[num_layers];
	now = new int [num_layers];
	int i =0 , j =0;
	for( i =0; i < n; i++  ){
		float x = 1*cos(2*PI*i/n);
		float z = 1*sin(2*PI*i/n);
		for( j = 0 ; j< num_layers ; j++){
		 now[j] = addNode(offset_x + x*r*(j+1), 0.0, offset_z + z*r*(j+1));	
		 if(j!=0)
			 addEdge(now[j],now[j-1]);
		 if(j<num_layers-1 &&  i!= 0)
			 addEdge(prev[j],now[j]);
		 prev[j] = now[j];
		}	
	}
	for(int k = 0; k < num_layers ; k++){
		now[k] = addNode(offset_x + 1*r*(k+1), 0.0, offset_z );
		if(k <num_layers-1)
			addEdge(prev[k],now[k]);
	}
}
void GRAPH_SYSTEM::createNet_Square( int n, int num_layers )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 5.;
    float offset_z = 5.;
    //
    // Implement your own stuff
    //
	int rownode[20][20];

	//prevRownode = new int *[num_layers];
	for(int j =0 ; j < num_layers ; j++){
		for(int i = 0; i<num_layers ; i++){
				if(i < ( (num_layers-n)/2 ) || i >= (num_layers+n)/2 || ( j < ( (num_layers-n)/2 ) || j >= (num_layers+n)/2) )
					rownode[j][i] = addNode(i*d, 0.0, j*d );
				else
					rownode[j][i] = NULL;
		}
	}

	for( int j =0 ; j < num_layers-1 ; j++){
		for( int i = 0; i<num_layers-1 ; i++){
				if(i < ( (num_layers-n)/2 -1) || i >= (num_layers+n)/2 || j < ( (num_layers-n)/2 ) || j >= (num_layers+n)/2 ){
					if(rownode[j][i] != NULL){
					addEdge(rownode[j][i], rownode[j][i+1]);
					}
					if(j == num_layers-2)
						addEdge(rownode[j+1][i], rownode[j+1][i+1]);
					/*else if(j == num_layers-1)
						addEdge(rownode[j][i], rownode[j+1][i]);*/
				}
		}
	}
	for( int j =0 ; j < num_layers-1 ; j++){
		for( int i = 0; i< num_layers ; i++){
				if(i < ( (num_layers-n)/2 ) || i >= (num_layers+n)/2 || j < ( (num_layers-n)/2-1 ) || j >= (num_layers+n)/2 ){
					if(rownode[j][i] != NULL){
					addEdge(rownode[j][i], rownode[j+1][i]);
					}
					if(j == num_layers-2)
						addEdge(rownode[j+1][i], rownode[j+1][i]);
				}
		}
	}
}

void GRAPH_SYSTEM::createNet_RadialCircular( int n ) {

    reset( );

    float offset_x = 15.0;
    float offset_z = 15.0;

    float r = 15; // radius
    //
    // Implement your own stuff
    //    
	int v0 = addNode(offset_x,0.0,offset_z);
	for(int i = 0; i<n; i++){
		float x = r*cos(2*PI*i/n);
		float z = r*sin(2*PI*i/n);
		int v1 = addNode(x+offset_x,0.0,z+offset_z);
		addEdge(v0,v1);
	}
}
/*
int mMaxNumNodes;
	int mMaxNumEdges;
	//
	int *mFreeNodeArr;
	int *mFreeEdgeArr;
	int mCurNumFreeNodes;
	int mCurNumFreeEdges;

	int *mActiveNodeArr;
	int *mActiveEdgeArr;
	int mCurNumActiveNodes;
	int mCurNumActiveEdges;
	*/
GRAPH_NODE *GRAPH_SYSTEM::getFreeNode()
{
	GRAPH_NODE *node = 0;
	if(mCurNumFreeNodes<=0) return node;
	--mCurNumFreeNodes;
	int nodeIndex = mFreeNodeArr[mCurNumFreeNodes];
	node = &mPool_Nodes[nodeIndex];

	node->dynamicID = mCurNumActiveNodes;
	mActiveNodeArr[mCurNumActiveNodes] = nodeIndex;
	++mCurNumActiveNodes;
	node->edgeID.clear();
	return node;
}
GRAPH_EDGE *GRAPH_SYSTEM::getFreeEdge()
{
	GRAPH_EDGE *edge = 0;
	if(mCurNumFreeEdges<=0) return edge;
	--mCurNumFreeEdges;
	int edgeIndex = mFreeEdgeArr[mCurNumFreeEdges];
	edge = &mPool_Edges[edgeIndex];

	edge->dynamicID = mCurNumActiveEdges;
	mActiveEdgeArr[mCurNumActiveEdges] = edgeIndex;
	++mCurNumActiveEdges;
	edge->nodeID[0] = -1;
	edge->nodeID[1] = -1;
	return edge;
}
// return node id
int GRAPH_SYSTEM::addNode( float x, float y, float z, float r )
{
    //
    // Implement your own stuff
    //  
	GRAPH_NODE *node = getFreeNode();
	if(!node) return -1;
	node->p.x = x;
	node->p.y = y;
	node->p.z = z;
	node->r = r;
    return node->id;
}

// return edge id
int GRAPH_SYSTEM::addEdge( int nodeID_0, int nodeID_1 )
{
    //
    // Implement your own stuff
    //  
	GRAPH_EDGE *edge = getFreeEdge();
	if(!edge) return -1;
	edge->nodeID[0] = nodeID_0;
	edge->nodeID[1] = nodeID_1;
    return edge->id;
}

void GRAPH_SYSTEM::askForInput( )
{
    //
    // Implement your own stuff
    // 
	cout << "GRAPH_SYSTEM" << endl;
    cout << "Key usage:" << endl;
    cout << "1: create a default graph" << endl;
    cout << "2: create a graph with 10x10 nodes. Connect the consecutive nodes horizontally" << endl;
    cout << "3: create a graph with 10x10 nodes. Connect the consecutive nodes vertically" << endl;
    cout << "4: create a graph with 10x10 nodes. Create 10 randomly generated edges" << endl;
    cout << "5: create a graph with 10x10 nodes. Create 10 randomly generated edges attached at a random node" << endl;
    cout << "Delete: delete a node and all the edges attached at it" << endl;
    cout << "Spacebar: unselect the selected node" << endl;
    cout << " " << endl;
    cout << "Use the mouse to select nodes and add edges" << endl;
    cout << "Click the left button to select/unselect or create an edge" << endl;
    cout << " " << endl;
    cout << "A selected node is highlighted as red." << endl;

}

GRAPH_NODE *GRAPH_SYSTEM::findNearestNode( double x, double z, double &cur_distance2 ) const
{   
    GRAPH_NODE *n = 0;
    
    //
    // Implement your own stuff
    // 
    cur_distance2 = -1;
    int End =getNumOfNodes( );
    //int End =1000;
    for(int i = 0 ; i<End ; i++){
        GRAPH_NODE *TEMP = &mPool_Nodes[i];
        double dx = TEMP ->p.x - x;
        double dz = TEMP ->p.z - z;
        double d2 = dx*dx + dz*dz;
        if(cur_distance2 < 0.0 ||d2 <cur_distance2)
        {   cur_distance2 = d2;
            n = TEMP;
        }   
    }
    
    return n;
    
}

//
// compute mSelectedNode
//
void GRAPH_SYSTEM::clickAt(double x, double z)
{   
    //
    // Implement your own stuff
    //
    //int End =getNumOfNodes( );
    double cur_distance2;
    GRAPH_NODE *n = findNearestNode(x ,z ,cur_distance2);
    //to add edge and cancel the same node if you select it twice 
    if(n == 0){
        mSelectedNode = 0;
        return;
    }
    if(cur_distance2 > n->r * n->r)
        {
            mSelectedNode = 0;
            return;
        }
    if(mSelectedNode == n)
        {   
            mSelectedNode = 0;
            return;
        }
    if (mSelectedNode != 0)
        {
            addEdge(mSelectedNode->id, n->id);
            //mSelectedNode = 0;
            return;
        }
     mSelectedNode = n;
}

void GRAPH_SYSTEM::deleteNode( int nodeID ) {
    //
    // Implement your own stuff
    //
    GRAPH_EDGE *m;
    GRAPH_NODE *n;
    int i = 0;
    while( i< getNumOfEdges() ){
        if(mPool_Edges[i].nodeID[0] == nodeID || mPool_Edges[i].nodeID[1] == nodeID ){
            m = mPool_Edges;
            delete m;
            mCurNumActiveEdges;
            mCurNumFreeEdges++;
        }
        else 
             i++;
    }
    for(i = 0 ; i <getNumOfNodes() ; i++){
        if(mPool_Nodes[i].id == nodeID)
            {
                n = mPool_Nodes;
                delete n;
                mCurNumActiveNodes;
                mCurNumFreeNodes++;
                break;
            }
    }
}

void GRAPH_SYSTEM::deleteSelectedNode( ) {
    //
    // Implement your own stuff
    // 
    if(mSelectedNode == 0)
        return;
    deleteNode(mSelectedNode->id);
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;
}

bool GRAPH_SYSTEM::isSelectedNode( ) const
{
    //
    if(mSelectedNode != 0)
        return true;
    //
    // Implement your own stuff
    // 
    return false;
}

void GRAPH_SYSTEM::getInfoOfSelectedPoint( double &r, vector3 &p ) const
{   if(isSelectedNode() == false) return;
     r = mSelectedNode->r;
     p = mSelectedNode->p;
    //
    // Implement your own stuff
    // 
}



void GRAPH_SYSTEM::handleKeyPressedEvent( unsigned char key )
{
    
    switch( key ) {
    case 127: // delete
        mFlgAutoNodeDeletion = false;
        deleteSelectedNode( );
        break;
    case '1':
        mFlgAutoNodeDeletion = false;
        createDefaultGraph( );
        mSelectedNode = 0;
        break;
    case '2':
        mFlgAutoNodeDeletion = false;
        createNet_Circular(12, 3);
        mSelectedNode = 0;

        break;
    case '3':
        mFlgAutoNodeDeletion = false;
        createNet_Square(3, 11); // you can modify this
        mSelectedNode = 0;

        break;
    case '4':
        mFlgAutoNodeDeletion = false;
        createNet_RadialCircular(24);
        mSelectedNode = 0;

        break;
    case '5':
        mFlgAutoNodeDeletion = false;
        createRandomGraph_DoubleCircles(RandomCircle);
        mSelectedNode = 0;

        break;

    case ' ':
        mFlgAutoNodeDeletion = false;
        mSelectedNode = 0;
        break;
    case 'g':
        mFlgAutoNodeDeletion = !mFlgAutoNodeDeletion;
        break;
	case '<':
		mFlgAutoNodeDeletion = false;
		RandomCircle--;
		if(RandomCircle < 3) RandomCircle = 3;
        createRandomGraph_DoubleCircles(RandomCircle);
        mSelectedNode = 0;
        break;
	case '>':
		mFlgAutoNodeDeletion = false;
		RandomCircle++;
		if(RandomCircle > 36) RandomCircle = 36;
        createRandomGraph_DoubleCircles(RandomCircle);
        mSelectedNode = 0;
        break;
    }
}

void GRAPH_SYSTEM::handlePassiveMouseEvent( double x, double z )
{
    double cur_d2;
    GRAPH_NODE *n = findNearestNode( x, z, cur_d2 );
    if ( n == 0 ) return;
    if ( cur_d2 > n->r*n->r ) {
        mPassiveSelectedNode = 0;
        return;
    }
    mPassiveSelectedNode = n;
}

//
// get the number of nodes
//
int GRAPH_SYSTEM::getNumOfNodes( ) const
{
    //
    // Implement your own stuff
    // 
    return mCurNumActiveNodes;
}

void GRAPH_SYSTEM::getNodeInfo( int nodeIndex, double &r, vector3 &p ) const
{
    //
    // Implement your own stuff
    // 
	int nodeID = mActiveNodeArr[nodeIndex];
	const GRAPH_NODE *node= &mPool_Nodes[nodeID];
	r = node->r;
	p = node->p;
}

//
// return the number of edges
//
int GRAPH_SYSTEM::getNumOfEdges( ) const
{
    //
    // Implement your own stuff
    // 
    return mCurNumActiveEdges;
}

//
// an edge should have two nodes: index 0 and index 1
// return the position of node with nodeIndex
//
vector3 GRAPH_SYSTEM::getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const
{
    vector3 p;
    //
    // Implement your own stuff
    // 
	int id = mActiveEdgeArr[edgeIndex];
	const GRAPH_EDGE *edge= &mPool_Edges[id];

	int vertexID = edge->nodeID[nodeIndex];
	p = mPool_Nodes[vertexID].p;
	return p;
}

void GRAPH_SYSTEM::stopAutoNodeDeletion()
{
    mFlgAutoNodeDeletion = false;
}

//
// For every frame, update( ) function is called.
// 
//
void GRAPH_SYSTEM::update( )
{
    if (!mFlgAutoNodeDeletion) {
     
        return;
    }
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;

    Sleep(250);
    //
    //
    // Implement your own stuff
    // 

}