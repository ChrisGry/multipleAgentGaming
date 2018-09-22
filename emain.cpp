#include "evgame.h"
int main(int argc,char **argv)
{
	//MIX = 10
	//EG2X2 = 24
	//IGA = 33
	//SYNC = 40
	//M0 = 0, M1 = 1, M2 = 2
	{Evgame egm0(beeLAT,PD,IMSL,SYNC,step0,LearnRate1_0,closeMoreThanFunc,6);}
    {Evgame egm1(beeLAT,PD,IMSL,SYNC,step1,LearnRate1_0,closeMoreThanFunc,6);}
    {Evgame egm0(beeLAT,PD,IMSL,SYNC,step2,LearnRate1_0,closeMoreThanFunc,6);}
    {Evgame egm1(beeLAT,PD,IMSL,SYNC,step3,LearnRate1_0,closeMoreThanFunc,6);}
    {Evgame egm0(beeLAT,PD,IMSL,SYNC,step4,LearnRate1_0,closeMoreThanFunc,6);}
    {Evgame egm1(beeLAT,PD,IMSL,SYNC,step5,LearnRate1_0,closeMoreThanFunc,6);}
    {Evgame egm0(beeLAT,PD,IMSL,SYNC,step6,LearnRate1_0,closeMoreThanFunc,6);}
    {Evgame egm1(beeLAT,PD,IMSL,SYNC,step7,LearnRate1_0,closeMoreThanFunc,6);}
    {Evgame egm0(beeLAT,PD,IMSL,SYNC,step8,LearnRate1_0,closeMoreThanFunc,6);}
//    {Evgame egm2(BA,PD,IPDY,SYNC,M0,LearnRate0_6,closeMoreThanFunc);}
//	{Evgame egm3(BA,PD,IPDY,SYNC,M0,LearnRate0_9,closeMoreThanFunc);}//replicatorÏÂµÄ2ÌøÑ§Ï° 
//	{Evgame egm0(LAT,PD,IMX,SYNC,M0);}//egm1(LAT,SD,M1
//	{Evgame egm0(LAT,EG2X2,IDY,SYNC,M0);}//egm1(LAT,SD,M1
//	{Evgame egm0(MIX,EG2X2,IGA,SYNC,M3);}//egm1(LAT,SD,M1
//	{Evgame egm0(MIX,GEN,IGA,SYNC,M3);}//egm1(LAT,SD,M1
//	{Evgame egm0(MIX,SD,IGA,SYNC,M1);}//egm1(LAT,SD,M1
//	{Evgame egm0(MIX,SH,IGA,SYNC,M1);}//egm1(LAT,SD,M1

//	{Evgame egm0(MIX,SH,IMX,SYNC,M1,&argc,&argv);}//egm1(LAT,SD,M1
return 0;
}
