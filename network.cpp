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
    vLadjmx.resize(Size); //初始化向量
    //创造一个概率选择的数组
    vector<int> randomChoose;
    int maxLen=(Size-M)*M*2+M*M-M; //该网络可能存在的最大度数和
    randomChoose.reserve(maxLen); //分配最大容量
    
    for (i=0;i<Size;i++)
        vLadjmx[i].reserve(Size);//只分配最大容量,因为每个点的size不确定
    
    ////////////初始化M个点的全连接网络//////////////
    for(i=0;i<M;i++)
        for(j=0;j<M;j++)
            if(j!=i)
                vLadjmx[i].push_back(j);//在向量尾部插入
    for(i=0;i<M;i++)
        for(j=0;j<(int)vLadjmx[i].size();j++)
            randomChoose.push_back(i);//连接的点都加入随机选择的数组中
    
    ////////////增加Size-M个点，以及边数，完成连接概率的选择//////////////
    srand( (unsigned)time( NULL ) );
    for (i=M;i<Size;i++){ //从M下标开始加入Size-M个点
        randAdjNum = rand()%M+1; //随机选择增加的边数1-M(包括M),M在头文件中定义
//        if (randAdjNum==0)
//            randomChoose.push_back(i);//若该点为孤立点则直接加入，使其有希望被其他点连上
        vector<int> temp;//用于临时存储连接对象的下标，避免下回再次连接它
        temp.reserve(randAdjNum);
        for (j=0; j<randAdjNum; j++) {
//            memset(temp, -1, sizeof(temp));
            //开始随机选一个下标从randomChoose数组中
   LOOP:
            int index = rand()%randomChoose.size();
            k=0;
            //检测该下标是否已经选择过
            while (k<temp.size()){
                if (randomChoose[index]==temp[k] || randomChoose[index]==M)//随机选的下标与连接过的边相等或者与本身相连则再次选取，再次比较
                    goto LOOP;
                else k++;//不相等则进入下一个比较
            }
            //while语句执行完毕，说明该点是可以连接
            vLadjmx[i].push_back(randomChoose[index]);//在向量尾部插入
            vLadjmx[randomChoose[index]].push_back(i);
            randomChoose.push_back(randomChoose[index]);//连接的点都加入随机选择的数组中
            randomChoose.push_back(i);
            //把改点加入到下一次不能连接的数组中
            temp.push_back(randomChoose[index]);
        }
    }
    
    //测试输出连接点的度
//    int test[Size];
//    memset(test, 0, sizeof(test));
//    for (i=0; i<Size; i++)
//      for (j=0; j<vLadjmx[i].size(); j++)
//        test[randomChoose[i]]++;//计数加1
//    for (i=0; i<Size; i++){
//        if(test[i]==1) test[i]=0;//若只有1，表示当时只是把该点加入计算概率，并非有1个度数
//        printf("%d的度为：%d  ",i,(int)vLadjmx[i].size());
//    }
    return 0;
}

NodeAdj::~NodeAdj()
{
    
}

int NodeAdj::mixbuld() //全连接网络
{                        //void resize (size_type n); void resize (size_type n, value_type val);
    Size=1000;           //
    vLadjmx.resize(Size);//初始化向量
    int i,j;             //
   // double tpa,tpb,tpc;
    for (i=0;i<Size;i++)
    {	vLadjmx[i].clear();       //void reserve (size_type n)
        vLadjmx[i].reserve(Size); //reserver函数用来给vector预分配存储区大小，即capacity的值 ，但是没有给这段内存进行初始化。
    }                             //reserve 的参数n是推荐预分配内存的大小，实际分配的可能等于或大于这个值，即n大于capacity的值，就会reallocate内存?capacity的值会大于或者等于n 。
    
    for(i=0;i<Size;i++)
        for(j=0;j<Size;j++)
            if(j!=i)
                vLadjmx[i].push_back(j);//在向量尾部插入
    //printf("mmat2adj over  ");
    return 0;
}

int NodeAdj::latbuld(int neighbors)//网格
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

int NodeAdj::beeLat(){//6边形网络
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

int NodeAdj::movbuld(double movr)//移动网络
{
    Nratio=1.3;//number of nodes in a unit area密度
    Mv=movr;   //move ratio？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？移动速度之类
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
int NodeAdj::MplBuld()//构造移动平面
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
int NodeAdj::Mpl2adj()//构造邻接矩阵
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
            
            tpa=fabs(vLaxis[i][0]-vLaxis[j][0]);//fabs(a)=|a|求绝对值
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

int NodeAdj::Mplmove() //移动
{
    int i;
    double x,y,rr;
    for(i=0;i<Size;i++)
    {
        rr=(double(rand()%360)/360)*2*3.1415926;
        x=Mv*cos(rr); y=Mv*sin(rr);           //三角函数
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

int NodeAdj::AdjPrint()//打印邻接矩阵
{
    int i,j;
    for(i=0;i<vLadjmx.size();i++){
        if (vLadjmx[i].size()==0)
            printf("%d:该点没有连接出去的边",i);
        for(j=0;j<vLadjmx[i].size();j++)
            printf("%d-%d    ",i,vLadjmx[i][j]);
        printf("\n");}
    //	for(i=0;i<Size;i++)
    //		{
    //		printf("%d %lf %lf\t",i,vLaxis[i][0],vLaxis[i][1]);	
    //	}
    
    
    return 0;
}



