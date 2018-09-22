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
	
	double Game(double dg,double dr);//���岩��  ��ֹģʽ 
	int Gameas(double dg);//�첽ģʽ�µĲ���
	double Gamemob(double dg,double dr);
	int Gameasmob(double dg);
	int Pfpmob();
	int ruleupdate(double dg,double dr);  //���¹��� 
	//����ģ�¹��� ,�� ruleupdate��ѡ����� 
	int imitdyns(double dg,double dr); 
	int imitmaxs();
	int imitrands();
	int imitgas();
	int imitdynas(double b);
	int imitmaxas();
	int imitrandas();                     //
	int imitgaas();
	int imitSkipLearns();//1��ѧϰ 
	int imitMoreSkipLearns();//����ѧϰ 
	int imitSkipLearnDyns(double dg,double dr);//replicator�����µĶ���ѧϰ
	int imitProbabilityLearnsUC(double dg,double dr);
	int imitProbabilityLearnsDY(double dg,double dr);
  
	int imitrandomdys(double b);
	double getpayoff();
	int Infoprint();
	double getCratioas();
    void setSpecialNode ();
    bool probability(double dg,double dr,int ,int ); //compute probability
	
	vector<vector<unsigned> > GameHistory; //������ʷ 
	vector<vector<double> > Pfmx; //payoff ���� 
	vector<vector<int> > Strategy; //���� 
	vector<vector<int> > MidStrategy; //�м���Ա��� 
	vector<double> Fitness; //������Ӧ�� 
	vector<vector<int> > GameCountmx;	//��������
    vector<bool> LMflag;//LMflagΪ�жϵ��Ƿ��ж���ѧϰ����

    const vector<vector<int> > &vLadj; //�ڽӾ��� 
    double LearnAbilityRate;//���������ı���
    int learnStep;//����ѧϰ�Ĳ��� 
    int moreThan;//��Ӧ�ڵ�������ڼ����ھ�����ʱ��ȡѧϰ���� ,��ϸ˵����evgame.h 
	int Randnode;//�첽ģʽ�²��õ�������ɵĵ��±� 
	int Gsize, GAMETYPE, MEM, MEMLEN,GLOOP,nImitType,nSyncType;//game loops in one generation
	//int ILOOP;// I loop times in main  rerun the whole sytem repeat times
	//int JLOOP;//k loop times in main ,Gene algrithm generations
private:
};

