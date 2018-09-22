#include <queue>
#include <string.h>
#include "ga.h"
#include<time.h>
using namespace std;
//const int sum=2*step*(step+1);
//extern vector<vector<int> >  vLadjmx;

int GAgame::ruleupdate(double dg, double dr)//
{
	if(nSyncType==SYNC)      //SYNC=40
	{
		switch(nImitType)
		{
		case 30: imitmaxs();break;    //unconditional imitation
		case 31: imitrands();break;    // Ëæ»úÑ§Ï°ÁÚ¾Ó 
		case 32: imitdyns(dg,dr);break;// replicator dynamic 
		case 33: imitgas();break;       //ÒÅ´«Ëã·¨
		case 34: setSpecialNode();imitSkipLearns();break; //ÏÈÉèÖÃÒ»¶¨±ÈÀıµÄÌØÊâµã£¬¿ªÊ¼1ÌøÑ§Ï° 
		case 35: setSpecialNode();imitMoreSkipLearns();break;//Í¬ÉÏ£¬µ«ÊÇ¶àÌøÑ§Ï°ÄÜÁ¦¿ÉÒÔÔÚºêÖĞÉèÖÃ 
		case 36: setSpecialNode();imitSkipLearnDyns(dg,dr);break; //¼ÓdyµÄÎª replicator dynamic£¬²»¼ÓµÄÄ¬ÈÏÎª unconditional
		case 37: setSpecialNode();imitProbabilityLearnsUC(dg,dr);break;//¸ÅÂÊÑ§Ï°£¬¸ÅÂÊÔÚºêÖĞÉèÖÃ 
		case 38: setSpecialNode();imitProbabilityLearnsDY(dg,dr);break;
		default: exit(331);
		}	
	}
	else
	{
		switch(nImitType)
		{
		case 30: imitmaxas();break;
		case 31: imitrandas();break;
		case 32: imitdynas(dg);break;
		case 33: imitgaas();break;
		default: exit(332);
		}	
	}
return 0;
}

void GAgame::setSpecialNode (){//set special nodes to make them have another ability 
    int i,temp;
    int LMnum=Gsize*LearnAbilityRate;
    vector<int> input;
    LMflag.resize(Gsize);
    //Èç¹û¸ÅÂÊÎª1£¬ÔòÖ±½Ó¸³Öµ£¬·ñÔò½øĞĞËæ»úÑ¡È¡
	if(LMnum==Gsize) {
		for (i = 0; i < Gsize; i++) LMflag[i]=1;
	}else{
		for (i = 0; i < Gsize; i++){
        	input.push_back(i);
        	LMflag[i]=0;//LMflagÊı×éÓÃÀ´ÅĞ¶ÏµãÊÇ·ñÓĞ¶îÍâÑ§Ï°ÄÜÁ¦
        }
    	for (i = 0; i < LMnum; i++){
    		srand((unsigned)time(NULL));
        	temp = rand()%input.size();
        	LMflag[input[temp]]=1;
        	input.erase(input.begin()+temp);
    	}
	}
}

//compute the probability with Fitness then return YES or NO
bool GAgame::probability(double dg,double dr,int max,int origin){
     double pp,transrt,tt,maxp,minp,rr,gg,mx1,mx2,mn1,mn2;
     int i,j,k,maxk; 
     srand((unsigned)time(NULL));
     pp=Fitness[max]-Fitness[origin];
	  if(pp>0)
	  {
			(vLadj[origin].size()>vLadj[max].size())?maxk=(int)vLadj[origin].size():maxk=(int)vLadj[max].size();

			if(GAMETYPE!=20&&GAMETYPE!=24)//G2X2 20;EG2X2 24
				transrt=pp/((dg+1)*maxk);    //(b*maxk);
		//		transrt=pp/(dg+1);    //(b*maxk);  //before 130614
			else if(GAMETYPE==20) //not  changed 130614
			{
				maxp=(1>dg)?1:dg;
				minp=(dr<1)?dr-1:0;
				transrt=pp/((maxp-minp)*maxk);  //change 130809  before is pp/(maxp-minp)
			}		
			else  //130809  gametype 24
			{	
               	rr=(dr*10-4)*1.0/2;            //S     -2-5  14 samples
               	gg=(dg*10-2)*1.0/2;              //T   -1-6  14 samples
					
				if(rr>1) 
				{
					mx1=rr;
					mn1=1; 
				}
				else
				{
					mx1=1;
					mn1=rr; 
				}
					
				if(gg>0) 
				{
					mx2=gg;
					mn2=0;
				} 
				else
				{
					mx2=0;
					mn2=gg;
				}

				maxp=(mx1>mx2)?mx1:mx2;
				minp=(mn1<mn2)?mn1:mn2;
				transrt=pp/((maxp-minp)*maxk);
			//printf("/ntransrt%lf pp %lf  maxk %d,maxp %lf ,minp %lf,",transrt,pp,maxk,maxp,minp);
			//getchar();
			}


			tt=double(rand()%100)/100;
			if(tt<transrt)
            return 1;
            else return 0;
		}
		else return 0;
}

int GAgame::imitrandas()// now not ga  2011 2 11
{
	//printf("Gene1 ");
	int max,i,j,k;
	double pp;

//		do
//		{i=rand()%Gsize;
//		}while (vLadjmx[i].size()==0)
		
		i=Randnode;	
		j=rand()%vLadj[i].size();   //vLadjÅ’â„¢Â¡â„Î©â€Ã¦Ã¿â€™Ã› 
		k=vLadj[i][j];

		pp=Fitness[k]-Fitness[i];   //FitnessÂ±Â»Ã€ËšÂ±Ã¦â€¦ÃŒÂµÆ’Â¥Ã›Ã¦Ã•â€”ÃŸÅ“âˆÃ€ËšÂµÆ’â‰¤ï¬‚Â¬â€˜ 
		pp>0?max=k:max=i;
		for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
		{	
			Strategy[i][j]=Strategy[max][j];////////////////////////////??????????????????Strategyâ€°âˆ«Ã¥ÃÂªÂ¥Ã‚ÃªÃ«ÃˆÃ¡Ã¨
			if (rand()%100<1) 
				Strategy[i][j]=1-Strategy[i][j];
			if(Strategy[i][j]>1)  
			{
				printf("strategy wrong at genetic algrithm  %d  %d\n",i,j);   //genetic algrithmÃˆÃ…Ã³â€°Âºâ€ ÃÃ†Ã³ÃŠâ‰¥Ã¯
				exit (65);
			}
		}
	return 0;
}

int GAgame::imitrands()
{
	int max,i,j,k;
	double pp;

	for(i=0;i<Gsize;i++)//For each NODE,we need to do SELECTION,CROSSOVER,AND MUTATION
	{
		if(vLadj[i].size()==0) 
		{   
			for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
				MidStrategy[i][j]=Strategy[i][j];////////////////////////////??????????????????
			continue;
		}
		//	if(vLadj[i].size()==0) continue;
		j=rand()%(int)vLadj[i].size();
		k=vLadj[i][j];
		pp=Fitness[k]-Fitness[i];

		pp>0?max=k:max=i;
		
		for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
		{	
			MidStrategy[i][j]=Strategy[max][j];////////////////////////////??????????????????
		}
	}//END OF for(i<Gsize)

	for(i=0;i<Gsize;i++) 
		for(j=0;j<MEMLEN;j++)
	    { 
	    	Strategy[i][j]=MidStrategy[i][j];
	//	    if (rand()%100<1) Strategy[i][j]=1-Strategy[i][j];
			if(Strategy[i][j]>1)  
			{
				printf("strategy wrong at geneticalgrithm  %d  %d\n",i,j);
				exit (66);
			}
	    }
	return 0;
}


int GAgame::imitdyns(double dg,double dr)
{
	int max,i,j,k;
	for(i=0;i<Gsize;i++)//For each NODE,we need to do SELECTION,CROSSOVER,AND MUTATION
	{
		if(vLadj[i].size()==0) 
		{   
			for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
				MidStrategy[i][j]=Strategy[i][j];//////
			continue;
		}

		j=rand()%(int)vLadj[i].size();
		k=vLadj[i][j];
		max=i;
		
		if(probability(dg,dr,k,i))
	    max=k;

		for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
		{	
			MidStrategy[i][j]=Strategy[max][j];////////////////////////////??????????????????
		}
	}//END OF for(i<Gsize)
		
	for(i=0;i<Gsize;i++)
		for(j=0;j<MEMLEN;j++)
		{
			Strategy[i][j]=MidStrategy[i][j];
// mutation=0 130609	
			if (rand()%100<1) 
				Strategy[i][j]=1-Strategy[i][j];
		}
//getchar();
   	return 0;
} 

int GAgame::imitSkipLearns(){//ÎŞÌõ¼şÏÂµÄ1ÌøÑ§Ï°£¬Ö»Ğ´1Ìø£¬ÎªÁË¿ÉÒÔÒ»´Î¶àÔËĞĞ
    srand((unsigned)time(NULL));
    int max,i,j,k,p,temp,temp1; 
	for(i=0;i<Gsize;i++)
	{
	  if(vLadj[i].size()==0)
        {
            for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
                MidStrategy[i][j]=Strategy[i][j];////////////////
            continue;
        }
      max=i;
      
	  if(LMflag[i]==1) {
	    for(j=0;j<(int)vLadj[i].size();j++)
        {
			temp=vLadj[i][j];
			for(k=0;k<(int)vLadj[temp].size();k++)
			{
               if (Fitness[max]<Fitness[vLadj[temp][k]])
                max=k;
            }
			if (Fitness[max]<Fitness[temp])
                max=temp;
        } 
      }else{
         for(j=0;j<(int)vLadj[i].size();j++)
        {
			k=vLadj[i][j];
			if (Fitness[max]<Fitness[k])
                max=k;
        }
      }

        for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
             MidStrategy[i][j]=Strategy[max][j];/////
    }//END OF for(i<Gsize)  


    for(i=0;i<Gsize;i++) 
	{
		for(j=0;j<MEMLEN;j++)
        {	
        	Strategy[i][j]=MidStrategy[i][j];
			
			if (rand()%100<1) 
				Strategy[i][j]=1-Strategy[i][j];
            		
            if(Strategy[i][j]>1)
            {
            	printf("strategy wrong at geneticalgrithm %d %d\n",i,j);
                exit (0);
            }
        }
//	printf("%d%d%d%d\t",Strategy[i][0],Strategy[i][1],Strategy[i][2],Strategy[i][3] );
	}
//getchar();
  //	printf(" imitmaxs over  ");
	return 0;
}

int GAgame::imitMoreSkipLearns(){
    int max,i,j,p,k,temp,temp1;
    srand((unsigned)time(NULL));
	for(i=0;i<Gsize;i++)
	{
        if(vLadj[i].size()==0)
        {
            for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
                MidStrategy[i][j]=Strategy[i][j];
            continue;
        }
        max=i;
        
    	int tempCount=0;
    	bool sFlag=1;
    	//½öÔÚ¾§¸ñÍøÂçÖĞÉúĞ§£¬Èç¹ûÔÚÆäËûÍøÂçÏÂÒª¹Ø±Õ¸Ã¹¦ÄÜ£¬²»È»ÓĞÎ´Öª´íÎó 
	    if(moreThan!=-1){
	    	for(j=0;j<(int)vLadj[i].size();j++)
	      		if(Fitness[i]>Fitness[vLadj[i][j]])
	           		tempCount++;
	        if(moreThan==0){
	        	tempCount==moreThan?sFlag=1:sFlag=0;
	        }else tempCount>=moreThan?sFlag=1:sFlag=0;
	    }
	
    if(LMflag[i]==1&&sFlag&&learnStep>0) {//LMflagÎªÅĞ¶Ïµã½ÚÊÇ·ñÓĞ¶îÍâÑ§Ï°ÄÜÁ¦
	    int tmpStep=learnStep;
        vector<int> numArray;//´æËùÓĞ¿ÉÑ§Ï°·¶Î§ÄÚµÄÁÚ¾Ó±àºÅ
        bool flag[Gsize];//ÅĞ¶ÏÊÇ·ñÒÑ¾­Ìí¼Ó¹ı£¬Ìí¼ÓÁËÎª1
        memset(flag,0,sizeof(flag));
        flag[i]=1;//µ±Ç°½Úµã±íÊ¾ÒÑÌí¼Ó
        for(temp=0;temp<(int)vLadj[i].size();temp++){
            numArray.push_back(vLadj[i][temp]);
            flag[vLadj[i][temp]]=1;
        }
        int begin = 0;//Ã¿´ÎÑ­»·¼ÓÁÚ¾ÓµÄ¿ªÊ¼µã£¬³õÊ¼Îª0ÏÂ±ê
        while(tmpStep--){
        	int tmpLoop = (int)numArray.size();//ÒòÎªnumArrayµÄ´óĞ¡ÔÚÑ­»·ÖĞ»á±ä»¯£¬µÄÏÈÌáÈ¡³öÀ´
            for(temp=begin;temp<tmpLoop;temp++)
              for(temp1=0;temp1<(int)vLadj[numArray[temp]].size();temp1++){
              	if(flag[vLadj[numArray[temp]][temp1]]==0){
              		numArray.push_back(vLadj[numArray[temp]][temp1]);
            		flag[vLadj[numArray[temp]][temp1]]=1;
              	}
            }
            begin = tmpLoop;//ĞŞ¸ÄÆğÊ¼ÏÂ±ê
        }//while end±íÊ¾·¶Î§ÄÚµÄ¶¼¼Ó½øÈ¥ÁË
       for(j=0;j<(int)numArray.size();j++)
             if (Fitness[max]<Fitness[numArray[j]])
             	max=numArray[j];
   }else{
      for(j=0;j<(int)vLadj[i].size();j++){
			k=vLadj[i][j];
			if (Fitness[max]<Fitness[k])
                max=k;
        	}
   		}
         
        for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
             MidStrategy[i][j]=Strategy[max][j];/////
    }//END OF for(i<Gsize)  


    for(i=0;i<Gsize;i++) 
	{
		for(j=0;j<MEMLEN;j++)
        {	
        	Strategy[i][j]=MidStrategy[i][j];
			
			if (rand()%100<1) 
				Strategy[i][j]=1-Strategy[i][j];
            		
            if(Strategy[i][j]>1)
            {
            	printf("strategy wrong at geneticalgrithm %d %d\n",i,j);
                exit (0);
            }
        }
//	printf("%d%d%d%d\t",Strategy[i][0],Strategy[i][1],Strategy[i][2],Strategy[i][3] );
	}
//getchar();
//	printf(" imitmaxs over  ");
	return 0;
} 

int GAgame::imitSkipLearnDyns(double dg,double dr){
    int max,i,j,k,temp,temp1;
    srand((unsigned)time(NULL));
	for(i=0;i<Gsize;i++)
	{
	    if(vLadj[i].size()==0) 
		{   
			for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
				MidStrategy[i][j]=Strategy[i][j];////////////////////////////??????????????????
			continue;
		}
	  max=i;
	  
	  int tempCount=0;
      bool sFlag=1;
    	//½öÔÚ¾§¸ñÍøÂçÖĞÉúĞ§£¬Èç¹ûÔÚÆäËûÍøÂçÏÂÒª¹Ø±Õ¸Ã¹¦ÄÜ£¬²»È»ÓĞÎ´Öª´íÎó 
	    if(moreThan!=-1){
	    	printf("enter!\n"); 
	    	for(j=0;j<(int)vLadj[i].size();j++)
	      		if(Fitness[i]>Fitness[vLadj[i][j]])
	           		tempCount++;
	        if(moreThan==0){
	        	tempCount==moreThan?sFlag=1:sFlag=0;
	        }else tempCount>=moreThan?sFlag=1:sFlag=0;
	    }
	  
	  if(LMflag[i]==1&&sFlag&&learnStep>0){
	    int tmpStep=learnStep;
        vector<int> numArray;//´æËùÓĞ¿ÉÑ§Ï°·¶Î§ÄÚµÄÁÚ¾Ó±àºÅ
        bool flag[Gsize];//ÅĞ¶ÏÊÇ·ñÒÑ¾­Ìí¼Ó¹ı£¬Ìí¼ÓÁËÎª1
        memset(flag,0,sizeof(flag));
        flag[i]=1;//µ±Ç°½Úµã±íÊ¾ÒÑÌí¼Ó
        for(temp=0;temp<(int)vLadj[i].size();temp++){
            numArray.push_back(vLadj[i][temp]);
            flag[vLadj[i][temp]]=1;
        }
        int begin = 0;//Ã¿´ÎÑ­»·¼ÓÁÚ¾ÓµÄ¿ªÊ¼µã£¬³õÊ¼Îª0ÏÂ±ê
        while(tmpStep--){
        	int tmpLoop = (int)numArray.size();//ÒòÎªnumArrayµÄ´óĞ¡ÔÚÑ­»·ÖĞ»á±ä»¯£¬µÄÏÈÌáÈ¡³öÀ´
            for(temp=begin;temp<tmpLoop;temp++)
              for(temp1=0;temp1<(int)vLadj[numArray[temp]].size();temp1++){
              	if(flag[vLadj[numArray[temp]][temp1]]==0){
              		numArray.push_back(vLadj[numArray[temp]][temp1]);
            		flag[vLadj[numArray[temp]][temp1]]=1;
              	}
            }
            begin = tmpLoop;//ĞŞ¸ÄÆğÊ¼ÏÂ±ê
        }//while end±íÊ¾·¶Î§ÄÚµÄ¶¼¼Ó½øÈ¥ÁË
        
        k = numArray[rand()%numArray.size()];//Ëæ»úÈ¡Ò»¸öÁÚ¾Ó
     }else{
        j=rand()%(int)vLadj[i].size();
		k=vLadj[i][j];
        }
        
    if(probability(dg,dr,k,i))
	    max=k;

	for(j=0;j<MEMLEN;j++) MidStrategy[i][j]=Strategy[max][j];
    }//END OF for(i<Gsize)
        
	
	for(i=0;i<Gsize;i++)//
		for(j=0;j<MEMLEN;j++)
		{
			Strategy[i][j]=MidStrategy[i][j];
// mutation=0 130609	
			if (rand()%100<1) 
				Strategy[i][j]=1-Strategy[i][j];
		}
    return 0;
}

int GAgame::imitProbabilityLearnsDY(double dg,double dr){
    int max,i,j,k,temp,temp1;
    srand((unsigned)time(NULL));
	for(i=0;i<Gsize;i++)
	{
        if(vLadj[i].size()==0)
        {
            for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
                MidStrategy[i][j]=Strategy[i][j];////////////////////////////??????????????????
            continue;
        }
        max=i;
      
    if(LMflag[i]==1&&learnStep>0) {
	    int tmpStep=learnStep;
        vector<int> numArray;//´æËùÓĞ¿ÉÑ§Ï°·¶Î§ÄÚµÄÁÚ¾Ó±àºÅ
        bool flag[Gsize];//ÅĞ¶ÏÊÇ·ñÒÑ¾­Ìí¼Ó¹ı£¬Ìí¼ÓÁËÎª1
        memset(flag,0,sizeof(flag));
        flag[i]=1;//µ±Ç°½Úµã±íÊ¾ÒÑÌí¼Ó
        for(temp=0;temp<(int)vLadj[i].size();temp++){
            numArray.push_back(vLadj[i][temp]);
            flag[vLadj[i][temp]]=1;
        }
        int begin = 0;//Ã¿´ÎÑ­»·¼ÓÁÚ¾ÓµÄ¿ªÊ¼µã£¬³õÊ¼Îª0ÏÂ±ê
        while(tmpStep--){
        	int tmpLoop = (int)numArray.size();//ÒòÎªnumArrayµÄ´óĞ¡ÔÚÑ­»·ÖĞ»á±ä»¯£¬µÄÏÈÌáÈ¡³öÀ´
            for(temp=begin;temp<tmpLoop;temp++)
              for(temp1=0;temp1<(int)vLadj[numArray[temp]].size();temp1++){
              	if(flag[vLadj[numArray[temp]][temp1]]==0){
              		numArray.push_back(vLadj[numArray[temp]][temp1]);
            		flag[vLadj[numArray[temp]][temp1]]=1;
              	}
            }
            begin = tmpLoop;//ĞŞ¸ÄÆğÊ¼ÏÂ±ê
        }//while end±íÊ¾·¶Î§ÄÚµÄ¶¼¼Ó½øÈ¥ÁË
        k = numArray[rand()%numArray.size()];//Ëæ»úÑ¡Ò»¸öÁÚ¾Ó
     }else{
        j=rand()%(int)vLadj[i].size();
		k=vLadj[i][j];
        }
        
        if(probability(dg,dr,k,i))
	    max=k;
  
        for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
             MidStrategy[i][j]=Strategy[max][j];///////
    }//END OF for(i<Gsize)  


    for(i=0;i<Gsize;i++) 
	{
		for(j=0;j<MEMLEN;j++)
        {	
        	Strategy[i][j]=MidStrategy[i][j];
			
			if (rand()%100<1) 
				Strategy[i][j]=1-Strategy[i][j];
            		
            if(Strategy[i][j]>1)
            {
            	printf("strategy wrong at geneticalgrithm %d %d\n",i,j);
                exit (0);
            }
        }
	}
	return 0;
}

int GAgame::imitProbabilityLearnsUC(double dg,double dr){
    int max,i,j,k,temp,temp1;
	for(i=0;i<Gsize;i++)
	{
        if(vLadj[i].size()==0)
        {
            for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
                MidStrategy[i][j]=Strategy[i][j];////////////////////////////??????????????????
            continue;
        }
        max=i;
	
    if(LMflag[i]==1&&learnStep>0) {
	    int tmpStep=learnStep;
        vector<int> numArray;//´æËùÓĞ¿ÉÑ§Ï°·¶Î§ÄÚµÄÁÚ¾Ó±àºÅ
        bool flag[Gsize];//ÅĞ¶ÏÊÇ·ñÒÑ¾­Ìí¼Ó¹ı£¬Ìí¼ÓÁËÎª1
        memset(flag,0,sizeof(flag));
        flag[i]=1;//µ±Ç°½Úµã±íÊ¾ÒÑÌí¼Ó
        for(temp=0;temp<(int)vLadj[i].size();temp++){
            numArray.push_back(vLadj[i][temp]);
            flag[vLadj[i][temp]]=1;
        }
		int begin = 0;//Ã¿´ÎÑ­»·¼ÓÁÚ¾ÓµÄ¿ªÊ¼µã£¬³õÊ¼Îª0ÏÂ±ê
        while(tmpStep--){
        	int tmpLoop = (int)numArray.size();//ÒòÎªnumArrayµÄ´óĞ¡ÔÚÑ­»·ÖĞ»á±ä»¯£¬µÄÏÈÌáÈ¡³öÀ´
            for(temp=begin;temp<tmpLoop;temp++)
              for(temp1=0;temp1<(int)vLadj[numArray[temp]].size();temp1++){
              	if(flag[vLadj[numArray[temp]][temp1]]==0){
              		numArray.push_back(vLadj[numArray[temp]][temp1]);
            		flag[vLadj[numArray[temp]][temp1]]=1;
              	}
            }
            begin = tmpLoop;//ĞŞ¸ÄÆğÊ¼ÏÂ±ê
        }//while end±íÊ¾·¶Î§ÄÚµÄ¶¼¼Ó½øÈ¥ÁË
       for(j=0;j<numArray.size();j++)
             if (Fitness[max]<Fitness[numArray[j]])
             	max=numArray[j];
   }else{
      for(j=0;j<(int)vLadj[i].size();j++){
			k=vLadj[i][j];
			if (Fitness[max]<Fitness[k])
                max=k;
        	}
        }
         
    for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
        MidStrategy[i][j]=Strategy[max][j];/////
    }//END OF for(i<Gsize)  


    for(i=0;i<Gsize;i++) 
	{
		for(j=0;j<MEMLEN;j++)
        {	
        	Strategy[i][j]=MidStrategy[i][j];
			
			if (rand()%100<1) //±äÒì 
				Strategy[i][j]=1-Strategy[i][j];
            		
            if(Strategy[i][j]>1)
            {
            	printf("strategy wrong at geneticalgrithm %d %d\n",i,j);
                exit (0);
            }
        }
//	printf("%d%d%d%d\t",Strategy[i][0],Strategy[i][1],Strategy[i][2],Strategy[i][3] );
	}
//getchar();
//	printf(" imitmaxs over  ");
	return 0;
}

int GAgame::imitdynas(double b)
{
	int max,maxk,i,j,k;
	double pp,transrt,tt;
	
	i=Randnode;
	j=rand()%(int)vLadj[i].size();
	k=vLadj[i][j];
	pp=Fitness[k]-Fitness[i];
	max=i;
	
	if(pp>0)
	{
//		(vLadj[i].size()-vLadj[k].size())>0?maxk=(int)vLadj[i].size():maxk=(int)vLadj[k].size();
		transrt=pp/(b+1); // (b*maxk);
		tt=double(rand()%100)/100;
		if(tt<transrt) 
		{	
			max=k;
			for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
			{
				Strategy[i][j]=Strategy[max][j];////////////////////////////??????????????????
				if (rand()%100<1) 
					Strategy[i][j]=1-Strategy[i][j];	
			}
	//		printf("strategy transferr transrt %lf %lf",transrt,tt);
		}
	}

	 return 0;
}


int GAgame::imitgas()/////only for well mixed network
{
///////////////////////////////////////////////////
/*
	int max,maxk,i,j,k,tmp;
	double pp,transrt,tt,fitsum=0,jj,kk;
	for(i=0;i<Gsize;i++)
		for(j=0;j<MEMLEN;j++)
			MidStrategy[i][j]=Strategy[i][j];

	vector<int> tsort;
	vector<double> tfit;

	tsort.resize(Gsize,0);
	tfit.resize(Gsize,0);
	for(i=0;i<Gsize;i++) 
		{
			tsort[i]=i;
			fitsum=fitsum+Fitness[i];
		}

	for(i=0;i<Gsize;i++)
		for(j=i;j<Gsize;j++)
			if(Fitness[i]>Fitness[j])
			{
				tmp=tsort[i];
				tsort[i]=tsort[j];
				tsort[j]=tmp;	
			}

	tfit[0]=Fitness[tsort[0]]/fitsum;
	for(i=1;i<Gsize;i++)
		tfit[i]=tfit[i-1]+Fitness[tsort[i]]/fitsum;


	int n1,n2;
	for(i=0;i<Gsize;i++)//For each NODE,we need to do SELECTION,CROSSOVER,AND MUTATION
		{
			if(vLadj[i].size()==0)
				continue;
			
			//j=rand()%(int)vLadj[i].size();
			//k=vLadj[i][j];
			//pp=Fitness[k]-Fitness[i];
			
			jj=1.0*(rand()%10000)/10000;
			kk=1.0*(rand()%10000)/10000;
			for(j=0;j<Gsize;j++)
				if(tfit[j]>jj)
				{
					 n1=tsort[j];
					break;
				}
			for(j=0;j<Gsize;j++)
				if(tfit[j]>kk)
				{
					 n2=tsort[j];
					break;
				}

						

			
			{//cross
				if(rand()%2)
				{	for(j=0;j<MEMLEN/2;j++)
					MidStrategy[i][j]=Strategy[n1][j];
	//				for(j=MEMLEN/2;j<MEMLEN;j++)
	//				MidStrategy[i][j]=Strategy[n2][j];
				}
				else
				{//	for(j=0;j<MEMLEN/2;j++)
				//	MidStrategy[i][j]=Strategy[n2][j];
					for(j=MEMLEN/2;j<MEMLEN;j++)
					MidStrategy[i][j]=Strategy[n1][j];
				}
			}
		}//END OF for(i<Gsize)


		for(i=0;i<Gsize;i++) for(j=0;j<MEMLEN;j++)
			{ Strategy[i][j]=MidStrategy[i][j];
							  if (rand()%100<1) Strategy[i][j]=1-Strategy[i][j];
			}
	 return 0;

//////////////////////////////////////////////////
//
*/
    int max,maxk,i,j,k;
    double pp,transrt,tt;
    
    for(i=0;i<Gsize;i++)
        for(j=0;j<MEMLEN;j++)
            MidStrategy[i][j]=Strategy[i][j];

    for(i=0;i<Gsize;i++)//For each NODE,we need to do SELECTION,CROSSOVER,AND MUTATION
    {
        if(vLadj[i].size()==0)
            continue;

        j=rand()%(int)vLadj[i].size();
        k=vLadj[i][j];
        pp=Fitness[k]-Fitness[i];

        if(pp>0)
        {
            if(rand()%2)
                for(j=0;j<MEMLEN/2;j++)
                    MidStrategy[i][j]=Strategy[k][j];
            else
                for(j=MEMLEN/2;j<MEMLEN;j++)
                    MidStrategy[i][j]=Strategy[k][j];
        }
    }//END OF for(i<Gsize)

    for(i=0;i<Gsize;i++) 
        for(j=0;j<MEMLEN;j++)
        { 
            Strategy[i][j]=MidStrategy[i][j];
            if (rand()%100<1) 
            	Strategy[i][j]=1-Strategy[i][j];
        }
        
    return 0;
}

int GAgame::imitgaas()
{ 
	return 0;
}

int GAgame::imitmaxas()// now not ga  2011 2 11
{
    int i,j,k,max;
	i=Randnode; 
	max=i;
//			if(vLadj[i].size()==0) continue;
    for(j=0;j<(int)vLadj[i].size();j++)
    {
		k=vLadj[i][j];
		if (Fitness[max]<Fitness[k])
            max=k;
    }
	for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
	{
		Strategy[i][j]=Strategy[max][j];////////////////////////////??????????????????
 		if (rand()%100<1) 
 			Strategy[i][j]=1-Strategy[i][j];
	
	}

//	printf(" imitmaxs over  ");
     return 0;
}

int GAgame::imitmaxs()
{
    int i,j,k,max;
//printf("  imitmaxs  ");
	for(i=0;i<Gsize;i++)//For each NODE,we need to do SELECTION,CROSSOVER,AND MUTATION
    {
        max=i;
		if(vLadj[i].size()==0) 
		{   
			for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
				MidStrategy[i][j]=Strategy[i][j];////////////////////////////??????????????????
			continue;
		}
	//		if(vLadj[i].size()==0) continue;
        for(j=0;j<(int)vLadj[i].size();j++)
        {
			k=vLadj[i][j];
			if (Fitness[max]<Fitness[k])
                max=k;
        }
		
		for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
             MidStrategy[i][j]=Strategy[max][j];////////////////////////////??????????????????
    }//END OF for(i<Gsize)
//printf("\nstrategt ga \n");
    for(i=0;i<Gsize;i++) 
	{
		for(j=0;j<MEMLEN;j++)
        {	
        	Strategy[i][j]=MidStrategy[i][j];
			
			if (rand()%100<1) 
				Strategy[i][j]=1-Strategy[i][j];
            		
            if(Strategy[i][j]>1)
            {
            	printf("strategy wrong at geneticalgrithm %d %d\n",i,j);
                exit (0);
            }
        }
//	printf("%d%d%d%d\t",Strategy[i][0],Strategy[i][1],Strategy[i][2],Strategy[i][3] );
	}
//getchar();
//	printf(" imitmaxs over  ");
	return 0;
}

double GAgame::getpayoff()// Â â€™â€œÃŠ Âºâˆ†Ã€â€Â£Â¨Â»Â°âˆËœÃ·Ã·âˆ†Î©Ã¦Ë˜Â£Â¨â‰¤Â©ï¬Æ’Â¥Å’Â ËÂ£Â¨Â»âˆ«ÃƒÃ‚âˆË†Â Ë
{
	int i;
	double payoff=0;
	
	if(Gsize>100)
	{
		for(i=0;i<Gsize;i++)
		{
			if(vLadj[i].size()>0)
				payoff=payoff+Fitness[i];
		}
		payoff=payoff/(Gsize*200*JLOOP);		
	}
	else
	{
		for(i=0;i<Gsize;i++)
		{
			if(vLadj[i].size()>0)
				payoff=payoff+Fitness[i]/vLadj[i].size();

		}
		payoff=payoff/Gsize;
	}
	return payoff;
}

int GAgame::Strtinit()//âˆË†ÃƒÃ‚â‰¤ï¬‚Â¬â€˜â‰¥Ä±Â ÂºÂªÃ˜
{
	int i,k;
	
	for(i=0;i<Gsize;i++)
		for(k=0;k<MEMLEN;k++)////////////////////////////////////////memlength///////////////
		{
			Strategy[i][k]=(unsigned short)(rand()%2);
		//	cout<<Strategy[i][k]<<"\t";
		//	if(Strategy[i][k]>1) {printf("strategy wrong at Strategy init i %d k %d\n",i,k); exit (0);}
		}
	return 0;
}

int GAgame::Infoprint()//Â¥Ãšâ€Â°â€œÂªâ€“Â©â€“â‰ˆÅ“Â¢
{
	int i,j,k;
	for(i=0;i<Gsize;i++)
	{
		printf("\t node %d ",i);
		for(k=0;k<MEMLEN;k++)////////////////////////////////////////memlength///////////////
		{
			printf(" %d ",Strategy[i][k]);
		//	if(Strategy[i][k]>1) {printf("strategy wrong at Strategy init i %d k %d\n",i,k); exit (0);}
		}
	}
	printf("\n");
	for(i=0;i<Gsize;i++)
	{
		printf("\t %d  %lf ",i,Fitness[i]);
	}
/*	for(i=0;i<Gsize;i++)
	{
		printf("\n %d ",i);
		for(j=0;j<vLadj[i].size();j++)
		printf("%lf ",Pfmx[i][vLadj[i][j]]);
	}	
*/
	printf("history\n");
	for (i=0;i<Gsize;i++)
		for(j=0;j<vLadj[i].size();j++)
			printf("%d %d %d\t",i,vLadj[i][j],(GameHistory[i][vLadj[i][j]])%2);

	return 0;
}

int GAgame::Hstinit(double rt)//â‰¤Â©ï¬Æ’Â¿Ë™Â âˆ‘â‰¥Ä±Â ÂºÂªÃ˜Â£Â¨Ã·Ëœâ€œâ„¢âˆ‚â€˜â€â€“ÂºÂ«â€œâ€°Â«ÃˆÃ¸Ë†
{
	int i,j,k,ans1,ans2;
	for(i=0;i<Gsize;i++)
		for(k=i+1;k<Gsize;k++)//Some values are meaningless
		{
			for(j=0;j<MEM;j++)////////////////////////////////////////memlength///////////////
			{
				if(rand()%100/100.00<rt)//50%ÂµÆ’ÂºâˆÂ¬Â  
					ans1=1;
				else 
					ans1=0;

				if(rand()%100/100.00<rt)
					ans2=1;
				else 
					ans2=0;

				GameHistory[i][k]=(GameHistory[i][k]<<2);    //Ã‚âˆ‘Â¶ÃÃŸÂªâ€°âˆÂ§â€°Î©Ã§
				GameHistory[i][k]=GameHistory[i][k]+ans1*2+ans2;

				GameHistory[k][i]=(GameHistory[k][i]<<2);
				GameHistory[k][i]=GameHistory[k][i]+ans2*2+ans1;
			}
		}
	return 0;
}

int GAgame::Fitinit()//
{
	Fitness.assign(Gsize,0.0);
	Pfmx.assign(Gsize, vector<double>(Gsize,0.0));
	GameCountmx.assign(Gsize, vector<int>(Gsize,0));
	return 0;
}

GAgame::GAgame( int gamet,int imitt,int synct,int steps,const vector<vector<int> > &vTemp):vLadj(vTemp)//Ï€Ï€â€˜Ãâˆ«Ã˜Â ËÂ£Â¨Î©Â´Ã•Â¯Â¬ÃÎ©Â·Ï€Ï€Ã•Â®Ï€ËvTempÂ¥Â´Ï€ËÂ¿Â¥
{
//	vLadj=vTemp;
	Gsize=(int)vLadj.size();
	GAMETYPE=gamet;
	nImitType=imitt;
	nSyncType=synct;
	MEM=0;     //  printf("ga ok0");
	learnStep=steps;
	
	switch(MEM)
	{
	case 0: MEMLEN=1,GLOOP=1;break;
	case 1: MEMLEN=4,GLOOP=20;break;//if(synctype==41)GLOOP=8;
	case 2: MEMLEN=16,GLOOP=40;break;//if(synctype==41)GLOOP=32;
	case 3: MEMLEN=64,GLOOP=80;break;//if(synctype==41)GLOOP=32;
	case 4: MEMLEN=256,GLOOP=100;break;//if(synctype==41)GLOOP=32;
	case 5: MEMLEN=1024,GLOOP=200;break;//if(synctype==41)GLOOP=32;
	case 6: MEMLEN=4096,GLOOP=200;break;//if(synctype==41)GLOOP=32;
	
	default:exit(24);
	}
 //      printf("ga ok");

	Strategy.resize(Gsize,vector<int>(MEMLEN));
	MidStrategy.resize(Gsize,vector<int>(MEMLEN,0));
	GameHistory.resize(Gsize,vector<unsigned>(Gsize));
	Pfmx.resize(Gsize,vector<double>(Gsize,0.0));
	Fitness.resize(Gsize,0);
 //   cout<<Strategy[1][1]<<" ";
	GameCountmx.resize(Gsize,vector<int>(Gsize,0));
	Strtinit();

	Hstinit(0.5);
}

GAgame::~GAgame()
{	
}

double GAgame::Game(double dg,double dr)//Determine the fitness of each strategyÃ¦ï¬‚ÃƒÃ‚â‰¤Â©ï¬Æ’  Ã¦â‰¤Ã·Ï€Æ’Â£Â Î©  
{
//	printf("  Game dg ");
	double incomeMatrix[2][2], C_Ratio;
	int m,n,i,j,node1,node2;
	int strategy1,strategy2;
	int StrategyCount[2]={0,0};

    switch(GAMETYPE)
    {
    case 20:
        //for 2x2 incomeMatrix, the subscript variable have the opposite meaning of game stratege,in game 0 means betray,1 means cooperate.
        incomeMatrix[0][0]=1;                 //R
        incomeMatrix[0][1]=dr-1;             //S -1~1
        incomeMatrix[1][0]=dg;              //T   0~2  dg gr 0-2
        incomeMatrix[1][1]=0;                //P
        break;
    case 21:   // pd game
        incomeMatrix[0][0]=1.0;                 //R             dg 0-1
        incomeMatrix[0][1]=0.0;            //S
        incomeMatrix[1][0]=dg+1.0;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 22:   // SD
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=1.0-dg;            //S
        incomeMatrix[1][0]=1.0+dg;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 23:   //SH
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=-dg;            //S
        incomeMatrix[1][0]=dg;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 24:   //great2x2              dg dr 0-1.5
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=(dr*10-4)*1.0/2;            //S     -2-5  14 samples
        incomeMatrix[1][0]=(dg*10-2)*1.0/2;              //T   -1-6  14 samples
        incomeMatrix[1][1]=0.0;                //P
        break;
	case 25: //general
		incomeMatrix[0][0]=1.0;
        incomeMatrix[0][1]=dg;            //S
        incomeMatrix[1][0]=dr;              //T
        incomeMatrix[1][1]=0.0;                //P
		break;
	 
    default: exit(29);
    }
//	Fitinit();
//	Hstinit();

    
		for(i=0;i<GLOOP;i++)
		{
			for( m=0;m<(int)vLadj.size();m++)
				for( n=0;n<(int)vLadj[m].size();n++)
				{
					node1=m;
					node2=vLadj[m][n];
	//				cout <<GameHistory[node1][node2]<< "    gamehistory"<<endl;
					strategy1=Strategy[node1][GameHistory[node1][node2]%MEMLEN];//////////////memlenghth////////////////////////
					strategy2=Strategy[node2][GameHistory[node2][node1]%MEMLEN];//////////////memlenghth////////////////////////

					Pfmx[node1][node2]=Pfmx[node1][node2]+incomeMatrix[1-strategy1][1-strategy2];
					Pfmx[node2][node1]=Pfmx[node2][node1]+incomeMatrix[1-strategy2][1-strategy1];
//					Fitness[node1]=Fitness[node1]+incomeMatrix[1-strategy1][1-strategy2];
//					Fitness[node2]=Fitness[node2]+incomeMatrix[1-strategy2][1-strategy1];
					StrategyCount[strategy1]++;
					StrategyCount[strategy2]++;

					GameHistory[node1][node2]=(GameHistory[node1][node2]<<2);
					GameHistory[node1][node2]=GameHistory[node1][node2]+strategy1*2+strategy2;
					GameHistory[node2][node1]=(GameHistory[node2][node1]<<2);
					GameHistory[node2][node1]=GameHistory[node2][node1]+strategy2*2+strategy1;
				}
		}
		
		for(i=0;i<Gsize;i++)
			for(j=0;j<vLadj[i].size();j++)
				Pfmx[i][vLadj[i][j]]/=(2*GLOOP);//previous' /2'  //conside 2 times count for one game in vladjmx
		
		for(i=0;i<Gsize;i++)
		{
			Fitness[i]=0;
			for(j=0;j<vLadj[i].size();j++)
				Fitness[i]=Fitness[i]+Pfmx[i][vLadj[i][j]];
	//		if (vLadj[i].size()>0) Fitness[i]=Fitness[i]/vLadj[i].size();   //(GLOOP*2); 130614
		}	

//	for(i=0;i<Gsize;i++)
//	if (vLadj[i].size()>0) Fitness[i]=Fitness[i]/(GLOOP*2);////conside the degree effection
	
    
	C_Ratio=(double)StrategyCount[1]/(StrategyCount[0]+StrategyCount[1]);
//cout <<C_Ratio<<endl;
//	printf(" game dg over  ");
	return C_Ratio;
}




double GAgame::Gamemob(double dg,double dr)//Determine the fitness of each strategyâ€œâˆ†âˆ‚Ã˜Æ’Â£Â Î©Å“Â¬ÂµÆ’â‰¤Â©ï¬Æ’
{
//	printf("  Game dg ");
	double incomeMatrix[2][2], C_Ratio;
	int m,n,i,j,node1,node2;
	int strategy1,strategy2;
	int StrategyCount[2]={0,0};

    switch(GAMETYPE)
    {
    case 20:
        //for 2x2 incomeMatrix, the subscript variable have the opposite meaning of game stratege,in game 0 means betray,1 means cooperate.
        incomeMatrix[0][0]=1;                 //R
        incomeMatrix[0][1]=dr-1;             //S -1~1
        incomeMatrix[1][0]=dg;              //T   0~2  dg gr 0-2
        incomeMatrix[1][1]=0;                //P
        break;
    case 21:   // pd game
        incomeMatrix[0][0]=1.0;                 //R             dg 0-1
        incomeMatrix[0][1]=0.0;            //S
        incomeMatrix[1][0]=dg+1.0;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 22:   // SD
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=1.0-dg;            //S
        incomeMatrix[1][0]=1.0+dg;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 23:   //SH
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=-dg;            //S
        incomeMatrix[1][0]=dg;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 24:   //great2x2
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=(dr*10-4)*1.0/2;            //S     -2-5  14 samples
        incomeMatrix[1][0]=(dg*10-2)*1.0/2;              //T   -1-6  14 samples
        incomeMatrix[1][1]=0.0;                //P
        break;
    default: exit(25);
    }


	for( m=0;m<(int)vLadj.size();m++)
		for( n=0;n<(int)vLadj[m].size();n++)
		{
			node1=m;
			node2=vLadj[m][n];
	//		cout <<GameHistory[node1][node2]<< "    gamehistory"<<endl;
			strategy1=Strategy[node1][GameHistory[node1][node2]%MEMLEN];//////////////memlenghth////////////////////////
			strategy2=Strategy[node2][GameHistory[node2][node1]%MEMLEN];//////////////memlenghth////////////////////////

			Pfmx[node1][node2]=Pfmx[node1][node2]+incomeMatrix[1-strategy1][1-strategy2];
			Pfmx[node2][node1]=Pfmx[node2][node1]+incomeMatrix[1-strategy2][1-strategy1];
//			Fitness[node1]=Fitness[node1]+incomeMatrix[1-strategy1][1-strategy2];
//			Fitness[node2]=Fitness[node2]+incomeMatrix[1-strategy2][1-strategy1];
			GameCountmx[node1][node2]++;
			GameCountmx[node2][node1]++;
			StrategyCount[strategy1]++;
			StrategyCount[strategy2]++;

			GameHistory[node1][node2]=(GameHistory[node1][node2]<<2);
			GameHistory[node1][node2]=GameHistory[node1][node2]+strategy1*2+strategy2;
			GameHistory[node2][node1]=(GameHistory[node2][node1]<<2);
			GameHistory[node2][node1]=GameHistory[node2][node1]+strategy2*2+strategy1;
		}
			
	C_Ratio=(double)StrategyCount[1]/(StrategyCount[0]+StrategyCount[1]);
//cout <<C_Ratio<<endl;
//	printf(" game dg over  ");
	return C_Ratio;
}

int GAgame::Pfpmob() //â€œâˆ†âˆ‚Ã˜Æ’Â£Â Î©Å“Â¬Â â€™â€œÃŠÂºâˆ†Ã€â€
{
	int i,j,k,ct;
//cout<<"\npfmx\n";
	for(i=0;i<Gsize;i++)
	{
		for(j=0;j<Gsize;j++)
		{
	//		cout<<i<<" "<<j<<" "<<Pfmx[i][j]<<" "<<GameCountmx[i][j]<<"\t";
            if(GameCountmx[i][j]==0&&Pfmx[i][j]>0)
				printf("\npf  error!!!!!!!\n");
            if(GameCountmx[i][j]>0)
                Pfmx[i][j]/=GameCountmx[i][j];
//			cout<<i<<" "<<j<<" "<<Pfmx[i][j]<<" "<<GameCountmx[i][j]<<"\t";
		}
	}

	for(k=0;k<Gsize;k++)
	{	
		Fitness[k]=0.0;
		ct=0;
		for(i=0;i<Gsize;i++)
		{
			Fitness[k]+=Pfmx[k][i];
			if(GameCountmx[k][i]>0)
				ct++;
		}
	}

	return (0);
}


int GAgame::Gameas(double dg)//â€œÃâ‰¤Î©Æ’Â£Â Î©Å“Â¬ÂµÆ’â‰¤Â©ï¬Æ’
{
//	printf("  Game dg ");
	double incomeMatrix[2][2],C_Ratio;
	int m,n,i,j,node1,node2,ans1,ans2;
	int strategy1,strategy2;
	int StrategyCount[2]={0,0};

    switch(GAMETYPE)
    {
    case 20:
        //for 2x2 incomeMatrix, the subscript variable have the opposite meaning of game stratege,in game 0 means betray,1 means cooperate.
        incomeMatrix[0][0]=1;                 //R
        //incomeMatrix[0][1]=dr-1;             //S -1~1
        incomeMatrix[1][0]=dg;              //T   0~2  dg gr 0-2
        incomeMatrix[1][1]=0;                //P
        break;
    case 21:   // pd game
        incomeMatrix[0][0]=1.0;                 //R             dg 0-1
        incomeMatrix[0][1]=0.0;            //S
        incomeMatrix[1][0]=dg+1.0;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 22:   // SD
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=1.0-dg;            //S
        incomeMatrix[1][0]=1.0+dg;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 23:   //SH
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=-dg;            //S
        incomeMatrix[1][0]=dg;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    default: exit(25);
    }


//	Fitinit();
//	Hstinit();
	Randnode=rand()%Gsize;
	m=Randnode;
	node1=m;
	for( n=0;n<(int)vLadj[m].size();n++)
	{
		node2=vLadj[m][n];
		Pfmx[node1][node2]=0;
		Pfmx[node2][node1]=0;

        for(j=0;j<MEM;j++)////////////////////////////////////////memlength///////////////
        {
            ans1=rand()%2;
            ans2=rand()%2;
            GameHistory[node1][node2]=(GameHistory[node1][node2]<<2);
            GameHistory[node1][node2]=GameHistory[node1][node2]+ans1*2+ans2;

            GameHistory[node2][node1]=(GameHistory[node2][node1]<<2);
            GameHistory[node2][node1]=GameHistory[node2][node1]+ans2*2+ans1;
        }
 
	}	
	for(i=0;i<GLOOP;i++)
		for( n=0;n<(int)vLadj[m].size();n++)
		{
			node2=vLadj[m][n];
	//			cout <<GameHistory[node1][node2]<< "    gamehistory"<<endl;
			strategy1=Strategy[node1][GameHistory[node1][node2]%MEMLEN];//////////////memlenghth////////////////////////
			strategy2=Strategy[node2][GameHistory[node2][node1]%MEMLEN];//////////////memlenghth////////////////////////

			Pfmx[node1][node2]=Pfmx[node1][node2]+incomeMatrix[1-strategy1][1-strategy2];
			Pfmx[node2][node1]=Pfmx[node2][node1]+incomeMatrix[1-strategy2][1-strategy1];

//			StrategyCount[strategy1]++;
//			StrategyCount[strategy2]++;

			GameHistory[node1][node2]=(GameHistory[node1][node2]<<2);
			GameHistory[node1][node2]=GameHistory[node1][node2]+strategy1*2+strategy2;
			GameHistory[node2][node1]=(GameHistory[node2][node1]<<2);
			GameHistory[node2][node1]=GameHistory[node2][node1]+strategy2*2+strategy1;
		}

	for( n=0;n<(int)vLadj[m].size();n++)
	{
		node2=vLadj[m][n];
		Pfmx[node1][node2]/=GLOOP;
		Pfmx[node2][node1]/=GLOOP;
	}	

	for(i=0;i<Gsize;i++)
	{
		Fitness[i]=0;
		
		for(j=0;j<vLadj[i].size();j++)
			Fitness[i]=Fitness[i]+Pfmx[i][vLadj[i][j]];
		
		if (vLadj[i].size()>0) 
			Fitness[i]=Fitness[i]/vLadj[i].size();////conside the degree effection
	}	

//	C_Ratio=(double)StrategyCount[1]/(StrategyCount[0]+StrategyCount[1]);
//cout <<C_Ratio<<endl;
//	printf(" game dg over  ");
	return 0;
}

double GAgame::getCratioas()//â€œÃâ‰¤Î©Æ’Â£Â Î©Å“Â¬ÂµÆ’âˆ«Å“â—ŠËœÂ±Â»Â¬Â Âºâˆ†Ã€â€
{
	int i,j;
	int StrategyCount[2]={0,0};
	double Cratio;
	
	for (i=0;i<Gsize;i++)
		for(j=0;j<vLadj[i].size();j++)
			StrategyCount[(GameHistory[i][vLadj[i][j]])%2]++;
	
	Cratio=(double)StrategyCount[1]/(StrategyCount[0]+StrategyCount[1]);
	//printf("\ncr %lf\n",Cratio);
    return Cratio;
}
