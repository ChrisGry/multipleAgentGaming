//#include <iostream>
//#include "evgame.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
using namespace std;

//	static const int SIZE=100;///important!! range of rand is 0-32767,size can not be too large!!! number of nodes?
//	static const int NMAX=SIZE-1;               //degree of nodes
//	static const int tmplen=SIZE*NMAX;               //=totalvector array

static const int M =3;//BA网络中初始点的个数

class NodeAdj
{
private:
public:

	 int Size,iSide;///important!! range of rand is 0-32767,size can not be too large!!! number of nodes?
    double dSide;

	NodeAdj(int nettype,int neighbors);
	~NodeAdj();//	VNode *p;

	double Nratio;// node ratio  √‹∂»
	double Mv; //move ratio
	int MplBuld();
	
	int Mpl2adj();
	int mixbuld();
	int beeLat();
	int latbuld(int neighbors);
    int BAnetbuld();
	int movbuld(double movr);
	//vector<vector<int> > vLmatrix;
	vector<vector<double> > vLaxis;
	vector<vector<int> > vLadjmx;
int AdjPrint();
int Mplmove();
};

   


