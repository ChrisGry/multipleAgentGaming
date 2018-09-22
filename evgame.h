#ifndef EVG
#define EVG
#define egX 11
#define egY 1

#include "macro.h"
//#include "mpi.h"
const int ILOOP=100; // I loop times in main  rerun the whole sytem repeat times
const int JLOOP=1000; //k loop times in main ,Gene algrithm generations

#include <omp.h>
#define MIX 10
#define LAT 11
#define BA 12
#define beeLAT 13

#define G2X2 20
#define PD 21
#define SD 22
#define SH 23
#define EG2X2 24
#define GEN 25

#define IMX 30
#define IRD 31
#define IDY 32
#define IGA 33
#define ISL 34
#define IMSL 35
#define ISLD 36
#define IPUC 37
#define IPDY 38

#define SYNC 40
#define ASYNC 41

#define HSKP 50
#define HS25 51
#define HS50 52
#define HS75 53

#define LearnRate1_0 0
#define LearnRate0_3 1
#define LearnRate0_6 2
#define LearnRate0_9 3

#define closeMoreThanFunc -1
#define moreThan0 0
#define moreThan1 1
#define moreThan2 2
#define moreThan3 3
#define moreThan4 4
//moreThan0 ��ʾֻ��������Ͳŷ���������4���ʾ��߲ŷ�������
 
#define step0 0
#define step1 1
#define step2 2
#define step3 3
#define step4 4
#define step5 5
#define step6 6
#define step7 7
#define step8 8
#define step9 9
#define step10 10

#ifndef LINUX
	#include "direct.h"
	#include "io.h"
#endif
#include <fstream>

#include <vector>
using namespace std;

#ifndef TTTT
#define TTTT 10

#endif
class Evgame
{

//	double mcr[ILOOP][egX][egY][JLOOP];
	double  mst[ILOOP][egX][egY][16];//��Ų���	
//	double stdcr[egX][egY][JLOOP];
//	double mfg[ILOOP][egX][egY][4096];
	double tpf[ILOOP][egX][egY];//��� ����

//	double smcr[egX][egY][JLOOP];
	double smst[egX][egY][16];//���ĳһ�ֵĲ��� 
//	double smfg[egX][egY][4096];
	double stpf[egX][egY];//��� ĳһ������

	vector<vector<vector<vector<double> > > > mcr;//��ź�����ʷ
	vector<vector<vector<double> > > smcr;//���ĳһ�ֺ�����ʷ
	vector<vector<vector<vector<double> > > > mfg;//��Ų��Եķֲ�
	vector<vector<vector<double> > > smfg;//���ĳһ�ֲ��Եķֲ�
	vector<vector<vector<double> > > stdcr;//ͳ�� ƫ��

/*
	double mpicr[ILOOP][JLOOP];
	int mpimst[16];
	double mpifg[64];
	double mpipf[ILOOP];
*/
	int tsize,ttmplen;
	char fhead[30];
	int nettype,gametype,imittype,synctype,mem,netsize,moreThanFuncType,stepCount;
	int LearnRateType;//���������ı���
	int dataproc();
	int  crhp();
	int fchmp();
   int histp();
    int pfp();
public:
	Evgame(int nett,int gamet,int imitt,int synct,int step,int LearnAbilityRateType,int moreThanType,int neighbors);
	//~eVgame();
	int evgm(int neighbor);
	int evgmmb();

	int writefile();

	
};

#endif
