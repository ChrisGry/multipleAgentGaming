//#include "network.h"
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
//#include"globev.h"
#include "evgame.h"



class GAgame
{
	//DATA  OF GAGAME
public:

	GAgame( int gamet,int imitt,int synct,int steps, const vector<vector<int> > &vTemp);
	~GAgame();
	int Strtinit();
	int Hstinit(double rt=0.5);
	int Fitinit();
	
	double Game(double dg,double dr);//具体博弈  静止模式 
	int Gameas(double dg);//异步模式下的博弈
	double Gamemob(double dg,double dr);
	int Gameasmob(double dg);
	int Pfpmob();
	int ruleupdate(double dg,double dr);  //更新规则 
	//各类模仿规则 ,由 ruleupdate来选择调用 
	int imitdyns(double dg,double dr); 
	int imitmaxs();
	int imitrands();
	int imitgas();
	int imitdynas(double b);
	int imitmaxas();
	int imitrandas();                     //
	int imitgaas();
	int imitSkipLearns();//1跳学习 
	int imitMoreSkipLearns();//多跳学习 
	int imitSkipLearnDyns(double dg,double dr);//replicator规则下的多跳学习
	int imitProbabilityLearnsUC(double dg,double dr);
	int imitProbabilityLearnsDY(double dg,double dr);
  
	int imitrandomdys(double b);
	double getpayoff();
	int Infoprint();
	double getCratioas();
    void setSpecialNode ();
    bool probability(double dg,double dr,int ,int ); //compute probability
	
	vector<vector<unsigned> > GameHistory; //博弈历史 
	vector<vector<double> > Pfmx; //payoff 矩阵 
	vector<vector<int> > Strategy; //策略 
	vector<vector<int> > MidStrategy; //中间策略保存 
	vector<double> Fitness; //计算适应度 
	vector<vector<int> > GameCountmx;	//博弈轮数
    vector<bool> LMflag;//LMflag为判断点是否有额外学习能力

    const vector<vector<int> > &vLadj; //邻接矩阵 
    double LearnAbilityRate;//调节特殊点的比例
    int learnStep;//多跳学习的步数 
    int moreThan;//对应节点收益高于几个邻居收益时获取学习能力 ,详细说明看evgame.h 
	int Randnode;//异步模式下才用的随机生成的点下标 
	int Gsize, GAMETYPE, MEM, MEMLEN,GLOOP,nImitType,nSyncType;//game loops in one generation
	//int ILOOP;// I loop times in main  rerun the whole sytem repeat times
	//int JLOOP;//k loop times in main ,Gene algrithm generations
private:
};

