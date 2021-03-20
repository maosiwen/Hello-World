#include<iostream>
#include<math.h>
#include <stdlib.h>
#include<iomanip> 
using namespace std;
struct point
{
	float x,y;
}P[30];
struct dpoint   //标记最近点对的距离及是哪两点
{
	double d;
	int p1,p2;
}dp[20];
dpoint Min(point *P,int m,int n); //递归求最近点对
double dis(point *P,int m,int n);//求两点间距离
dpoint all(point *P,int m,int n,double d);//求整个区间的最近点对
float R(float a, float b) {   //随机生成1-10的浮点数 
    return ((float)rand()/RAND_MAX)*(b-a)+a;
}
int main()
{
	int i,j;
	float m;
	dpoint dp;
	cout<<"随机生成的30个点为："<<endl;
	for(i=0;i<30;i++)  //随机生成坐标值均在1-10的30个点
	{
		P[i].x=R(1,10);
        P[i].y=R(1,10);
	}
	for(i=0;i<30;i++)                //按横坐标的大小排序
		for(j=1;j<(30-i);j++)
		{
			if(P[j-1].x>P[j].x){
				m=P[j-1].x;
				P[j-1].x=P[j].x;
				P[j].x=m;
			}
		}
	for(i=0;i<30;i++)                 //输出随机生成的30个点
	{
		cout<<"( "<<fixed<<setprecision(3)<<P[i].x<<" , "<<fixed<<setprecision(3)<<P[i].y<<" )\t";
		//fixed与setprecision(n)连用表示保留n位小数 
		if((i+1)%5==0)                //每5个换一行
		cout<<endl;
	}
	dp=Min(P,0,29);                   //计算最近点对
	cout<<"最近点对为：( "<<P[dp.p1].x<<" , "<<P[dp.p1].y<<" )与( "<<P[dp.p2].x<<" , "<<P[dp.p2].y<<" )"<<endl;//输出最近点对
	cout<<"最近点对距离为："<<dp.d<<endl;//输出最近点对的距离
	return 0;
}
dpoint Min(point *P,int m,int n)
{
	double d1,d2,d3,d;     //两点间距离
	if(m==(n-1))           //区间里只有两个点时
	{
		dp[0].d=dis(P,m,n);
		dp[0].p1=m;
		dp[0].p2=n;
	}
	else if(m==(n-2))      //区间里有三个点
	{
		d1=dis(P,m,m+1);
		d2=dis(P,m,n);
		d3=dis(P,m+1,n);
		if(d1<d2&&d1<d3){
			dp[0].d=d1;
			dp[0].p1=m;
			dp[0].p2=m+1;
		}
		else if(d2<d3){
			dp[0].d=d2;
			dp[0].p1=m;
			dp[0].p2=n;
		}
		else
		{
			dp[0].d=d3;
			dp[0].p1=m+1;
			dp[0].p2=n;
		}
	}
	else{                              //区间中超过3个点
		dp[1]=Min(P,m,(m+n)/2);        //求左区间的最近点对
		dp[2]=Min(P,((m+n)/2+1),n);    //求右区间的最近点对
		dp[0]=dp[1];
		if(dp[1].d>dp[2].d)
		dp[0]=dp[2];
		d=dp[0].d;
		dp[3]=all(P,m,n,d);            //求整个区间上的最近点对
		if(dp[3].d<d)
		dp[0]=dp[3];
	}
	return dp[0];
}
double dis(point *P,int m,int n)      //求两点间距离
{
	double q;
	q=sqrt((P[n].x-P[m].x)*(P[n].x-P[m].x)+(P[n].y-P[m].y)*(P[n].y-P[m].y));
	return q;
}
dpoint all(point *P,int m,int n,double d)       //求整个区间最近点对
{
	int i,j=0,k=4,mn,ii;  //ii用来标记p1中从第几个开始距离垂直线小于d
	mn=(m+n)/2;
	double d1;
	for(i=m;i<=mn;i++)       //垂直线x=(m+n)/2为分割线
		if(P[i].x>(P[mn].x-d))   //找p1区间横坐标离垂直线小于d的点p
		{
			if(j==0)
			ii=i;
			j++;
		}
	int jj=ii;
	for(;ii<(j+jj);ii++)    //依次对于p1区间符合的点p找p2区间在矩形区间的点q
		for(i=(mn+1);i<=n;i++)
		if(P[i].y>(P[ii].y-d)&&P[i].y<(P[ii].y+d)&&P[i].x<(P[mn].x+d)) 
		{
			d1=dis(P,ii,i);
			if(d1<d)
			dp[k].d=d1;
			dp[k].p1=ii;
			dp[k].p2=i;
			k++;
		}
	j=4;     //用j来标记第j对点中距离最短
	for(i=5;i<k;i++)
		if(dp[j].d>dp[i].d)
		j=i; 
	return dp[j]; 
}
