#include<iostream>
#include<math.h>
#include <stdlib.h>
#include<iomanip> 
using namespace std;
struct point
{
	float x,y;
}P[30];
struct dpoint   //��������Եľ��뼰��������
{
	double d;
	int p1,p2;
}dp[20];
dpoint Min(point *P,int m,int n); //�ݹ���������
double dis(point *P,int m,int n);//����������
dpoint all(point *P,int m,int n,double d);//�����������������
float R(float a, float b) {   //�������1-10�ĸ����� 
    return ((float)rand()/RAND_MAX)*(b-a)+a;
}
int main()
{
	int i,j;
	float m;
	dpoint dp;
	cout<<"������ɵ�30����Ϊ��"<<endl;
	for(i=0;i<30;i++)  //�����������ֵ����1-10��30����
	{
		P[i].x=R(1,10);
        P[i].y=R(1,10);
	}
	for(i=0;i<30;i++)                //��������Ĵ�С����
		for(j=1;j<(30-i);j++)
		{
			if(P[j-1].x>P[j].x){
				m=P[j-1].x;
				P[j-1].x=P[j].x;
				P[j].x=m;
			}
		}
	for(i=0;i<30;i++)                 //���������ɵ�30����
	{
		cout<<"( "<<fixed<<setprecision(3)<<P[i].x<<" , "<<fixed<<setprecision(3)<<P[i].y<<" )\t";
		//fixed��setprecision(n)���ñ�ʾ����nλС�� 
		if((i+1)%5==0)                //ÿ5����һ��
		cout<<endl;
	}
	dp=Min(P,0,29);                   //����������
	cout<<"������Ϊ��( "<<P[dp.p1].x<<" , "<<P[dp.p1].y<<" )��( "<<P[dp.p2].x<<" , "<<P[dp.p2].y<<" )"<<endl;//���������
	cout<<"�����Ծ���Ϊ��"<<dp.d<<endl;//��������Եľ���
	return 0;
}
dpoint Min(point *P,int m,int n)
{
	double d1,d2,d3,d;     //��������
	if(m==(n-1))           //������ֻ��������ʱ
	{
		dp[0].d=dis(P,m,n);
		dp[0].p1=m;
		dp[0].p2=n;
	}
	else if(m==(n-2))      //��������������
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
	else{                              //�����г���3����
		dp[1]=Min(P,m,(m+n)/2);        //���������������
		dp[2]=Min(P,((m+n)/2+1),n);    //���������������
		dp[0]=dp[1];
		if(dp[1].d>dp[2].d)
		dp[0]=dp[2];
		d=dp[0].d;
		dp[3]=all(P,m,n,d);            //�����������ϵ�������
		if(dp[3].d<d)
		dp[0]=dp[3];
	}
	return dp[0];
}
double dis(point *P,int m,int n)      //����������
{
	double q;
	q=sqrt((P[n].x-P[m].x)*(P[n].x-P[m].x)+(P[n].y-P[m].y)*(P[n].y-P[m].y));
	return q;
}
dpoint all(point *P,int m,int n,double d)       //����������������
{
	int i,j=0,k=4,mn,ii;  //ii�������p1�дӵڼ�����ʼ���봹ֱ��С��d
	mn=(m+n)/2;
	double d1;
	for(i=m;i<=mn;i++)       //��ֱ��x=(m+n)/2Ϊ�ָ���
		if(P[i].x>(P[mn].x-d))   //��p1����������봹ֱ��С��d�ĵ�p
		{
			if(j==0)
			ii=i;
			j++;
		}
	int jj=ii;
	for(;ii<(j+jj);ii++)    //���ζ���p1������ϵĵ�p��p2�����ھ�������ĵ�q
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
	j=4;     //��j����ǵ�j�Ե��о������
	for(i=5;i<k;i++)
		if(dp[j].d>dp[i].d)
		j=i; 
	return dp[j]; 
}
