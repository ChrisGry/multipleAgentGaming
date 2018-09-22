#include "network.h"
#include "math.h"

vector<vector<int> >  vLadjmx;

NodeAdj::NodeAdj(int nettype,int neighbors)
{
    
    switch(nettype)
    {
        case 10:mixbuld();break;
        case 11:latbuld(neighbors);break;
        case 12:BAnetbuld();break;
        case 13:beeLat();break;
    //    case MOV:movbuld(movr);break;     //MOV 12
        default: exit(110);
    }
    //printf("net ok\n");//cout<<"network init\n"<<endl;
}

int NodeAdj::BAnetbuld()
{
    Size=1000;
    int i,j,k,randAdjNum;
    vLadjmx.resize(Size); //��ʼ������
    //����һ������ѡ�������
    vector<int> randomChoose;
    int maxLen=(Size-M)*M*2+M*M-M; //��������ܴ��ڵ���������
    randomChoose.reserve(maxLen); //�����������
    
    for (i=0;i<Size;i++)
        vLadjmx[i].reserve(Size);//ֻ�����������,��Ϊÿ�����size��ȷ��
    
    ////////////��ʼ��M�����ȫ��������//////////////
    for(i=0;i<M;i++)
        for(j=0;j<M;j++)
            if(j!=i)
                vLadjmx[i].push_back(j);//������β������
    for(i=0;i<M;i++)
        for(j=0;j<(int)vLadjmx[i].size();j++)
            randomChoose.push_back(i);//���ӵĵ㶼�������ѡ���������
    
    ////////////����Size-M���㣬�Լ�������������Ӹ��ʵ�ѡ��//////////////
    srand( (unsigned)time( NULL ) );
    for (i=M;i<Size;i++){ //��M�±꿪ʼ����Size-M����
        randAdjNum = rand()%M+1; //���ѡ�����ӵı���1-M(����M),M��ͷ�ļ��ж���
//        if (randAdjNum==0)
//            randomChoose.push_back(i);//���õ�Ϊ��������ֱ�Ӽ��룬ʹ����ϣ��������������
        vector<int> temp;//������ʱ�洢���Ӷ�����±꣬�����»��ٴ�������
        temp.reserve(randAdjNum);
        for (j=0; j<randAdjNum; j++) {
//            memset(temp, -1, sizeof(temp));
            //��ʼ���ѡһ���±��randomChoose������
   LOOP:
            int index = rand()%randomChoose.size();
            k=0;
            //�����±��Ƿ��Ѿ�ѡ���
            while (k<temp.size()){
                if (randomChoose[index]==temp[k] || randomChoose[index]==M)//���ѡ���±������ӹ��ı���Ȼ����뱾���������ٴ�ѡȡ���ٴαȽ�
                    goto LOOP;
                else k++;//������������һ���Ƚ�
            }
            //while���ִ����ϣ�˵���õ��ǿ�������
            vLadjmx[i].push_back(randomChoose[index]);//������β������
            vLadjmx[randomChoose[index]].push_back(i);
            randomChoose.push_back(randomChoose[index]);//���ӵĵ㶼�������ѡ���������
            randomChoose.push_back(i);
            //�Ѹĵ���뵽��һ�β������ӵ�������
            temp.push_back(randomChoose[index]);
        }
    }
    
    //����������ӵ�Ķ�
//    int test[Size];
//    memset(test, 0, sizeof(test));
//    for (i=0; i<Size; i++)
//      for (j=0; j<vLadjmx[i].size(); j++)
//        test[randomChoose[i]]++;//������1
//    for (i=0; i<Size; i++){
//        if(test[i]==1) test[i]=0;//��ֻ��1����ʾ��ʱֻ�ǰѸõ���������ʣ�������1������
//        printf("%d�Ķ�Ϊ��%d  ",i,(int)vLadjmx[i].size());
//    }
    return 0;
}

NodeAdj::~NodeAdj()
{
    
}

int NodeAdj::mixbuld() //ȫ��������
{                        //void resize (size_type n); void resize (size_type n, value_type val);
    Size=1000;           //
    vLadjmx.resize(Size);//��ʼ������
    int i,j;             //
   // double tpa,tpb,tpc;
    for (i=0;i<Size;i++)
    {	vLadjmx[i].clear();       //void reserve (size_type n)
        vLadjmx[i].reserve(Size); //reserver����������vectorԤ����洢����С����capacity��ֵ ������û�и�����ڴ���г�ʼ����
    }                             //reserve �Ĳ���n���Ƽ�Ԥ�����ڴ�Ĵ�С��ʵ�ʷ���Ŀ��ܵ��ڻ�������ֵ����n����capacity��ֵ���ͻ�reallocate�ڴ�?capacity��ֵ����ڻ��ߵ���n ��
    
    for(i=0;i<Size;i++)
        for(j=0;j<Size;j++)
            if(j!=i)
                vLadjmx[i].push_back(j);//������β������
    //printf("mmat2adj over  ");
    return 0;
}

int NodeAdj::latbuld(int neighbors)//����
{
    int i;
    int side=30;
    Size=side*side;
    vLadjmx.resize(Size);
    for(i=0;i<Size;i++)
    {
        vLadjmx[i].clear();
        vLadjmx[i].reserve(neighbors);
        int left,right,up,down;
        left = (side+i-1)%side+(i/side)*side;
        right = (i+1)%side+(i/side)*side;
        up = i%side+((side+i/side-1)%side)*side;
        down = i%side+((i/side+1)%side)*side;
        //extern
        int upLeft = (side+up-1)%side+(up/side)*side;
        int upRight = (up+1)%side+(up/side)*side;
        int downLeft = (side+down-1)%side+(down/side)*side;
        int downRight = (down+1)%side+(down/side)*side;
        //add all of neighbors into a temp array,then push_back the numbers you want by for loop
        int tmpArray[8] = {left,right,up,down,upLeft,upRight,downLeft,downRight};
        for (int j=0; j<neighbors; j++) vLadjmx[i].push_back(tmpArray[j]);
    }
    
    return 0;
}

int NodeAdj::beeLat(){//6��������
	int i;
    int side=30;
    Size=side*side;
    vLadjmx.resize(Size);
    for(i=0;i<Size;i++)
    {
        vLadjmx[i].clear();
        vLadjmx[i].reserve(6);
        int left,right,up,down;
        left = (side+i-1)%side+(i/side)*side;
        right = (i+1)%side+(i/side)*side;
        up = i%side+((side+i/side-1)%side)*side;
        down = i%side+((i/side+1)%side)*side;
        //extern
        int upLeft = (side+up-1)%side+(up/side)*side;
        int upRight = (up+1)%side+(up/side)*side;
        int downLeft = (side+down-1)%side+(down/side)*side;
        int downRight = (down+1)%side+(down/side)*side;
        //add all of neighbors into a temp array,then push_back the numbers you want by for loop
        int tmpArray[4] = {left,right,up,down};
        for (int j=0; j<4; j++) vLadjmx[i].push_back(tmpArray[j]);
        if(i<Size/2){
        	vLadjmx[i].push_back(upLeft);
        	vLadjmx[i].push_back(downRight);
        }else{
        	vLadjmx[i].push_back(upRight);
        	vLadjmx[i].push_back(downLeft);
        }
    }

    return 0;
}

int NodeAdj::movbuld(double movr)//�ƶ�����
{
    Nratio=1.3;//number of nodes in a unit area�ܶ�
    Mv=movr;   //move ratio���������������������������������������������������������������������ƶ��ٶ�֮��
    Size=300;  //number of nodes
    vLadjmx.resize(Size);
    
    dSide=sqrt(Size/Nratio);// one side of square where the nodes put;
    //	iSide=(int)dSide*10000;//
    // getchar();
    
    MplBuld();
    //       AdjPrint();
    //	getchar();
    return 0;
}
int NodeAdj::MplBuld()//�����ƶ�ƽ��
{
    printf("Mpl buld ok");
    double row,column;
    int i;
    //	vLmatrix.resize(SIDE,vector<int>(SIDE,-1));
    vLaxis.resize(Size, vector<double>(2,0));
    
    for(i=0;i<Size;i++)
    {
        {	row=dSide*(double(rand()%1000)/1000);
            column=dSide*(double(rand()%1000)/1000);
        }//while (vLmatrix[row][column]!=-1);
        //	vLmatrix[row][column]=i;
        vLaxis[i][0]=row;
        vLaxis[i][1]=column;
    }
    Mpl2adj();
    return 0;
}
int NodeAdj::Mpl2adj()//�����ڽӾ���
{
    int i,j;
    double tpa,tpb,tpc;
    for (i=0;i<Size;i++)
    {	vLadjmx[i].clear();
        vLadjmx[i].reserve(4);
    }
    
    for(i=0;i<Size;i++)
        for(j=i+1;j<Size;j++)
        {
            
            tpa=fabs(vLaxis[i][0]-vLaxis[j][0]);//fabs(a)=|a|�����ֵ
            tpb=fabs(vLaxis[i][1]-vLaxis[j][1]);
            if((tpa<=1||dSide-tpa<=1)&&(tpb<=1||dSide-tpb<=1))
            {
                if (dSide-tpa<=1)
                    tpa=dSide-tpa;
                if (dSide-tpb<=1)
                    tpb=dSide-tpb;
                tpc=sqrt(tpa*tpa+tpb*tpb);
                if(tpc<=1)
                {
                    vLadjmx[i].push_back(j);
                    vLadjmx[j].push_back(i);
                }
            }
        }
    //printf("mmat2adj over  ");
    return 0;
}

int NodeAdj::Mplmove() //�ƶ�
{
    int i;
    double x,y,rr;
    for(i=0;i<Size;i++)
    {
        rr=(double(rand()%360)/360)*2*3.1415926;
        x=Mv*cos(rr); y=Mv*sin(rr);           //���Ǻ���
        vLaxis[i][0]=vLaxis[i][0]+x;
        vLaxis[i][1]=vLaxis[i][1]+y;
        
        if(vLaxis[i][0]<0)
            vLaxis[i][0]=vLaxis[i][0]+dSide;
        else if(vLaxis[i][0]>dSide)
            vLaxis[i][0]=vLaxis[i][0]-dSide;
        if(vLaxis[i][1]<0)
            vLaxis[i][1]=vLaxis[i][1]+dSide;
        else if(vLaxis[i][1]>dSide)
            vLaxis[i][1]=vLaxis[i][1]-dSide;
    }
    Mpl2adj();
    //	AdjPrint();
    return 0;
}

int NodeAdj::AdjPrint()//��ӡ�ڽӾ���
{
    int i,j;
    for(i=0;i<vLadjmx.size();i++){
        if (vLadjmx[i].size()==0)
            printf("%d:�õ�û�����ӳ�ȥ�ı�",i);
        for(j=0;j<vLadjmx[i].size();j++)
            printf("%d-%d    ",i,vLadjmx[i][j]);
        printf("\n");}
    //	for(i=0;i<Size;i++)
    //		{
    //		printf("%d %lf %lf\t",i,vLaxis[i][0],vLaxis[i][1]);	
    //	}
    
    
    return 0;
}



