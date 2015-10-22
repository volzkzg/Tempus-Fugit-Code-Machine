#include<cstdio>
#include<complex>
#include<vector>
#include<cmath>
#include<iostream>
#include<string>
#include<algorithm>
 
using namespace std;
 
typedef double Real;
 
typedef complex<Real> Point;
typedef complex<Real> Vector;
typedef pair<Point,Point> Segment;
typedef pair<Point,Point> Line;
typedef vector<Point> Polygon;
 
const Real eps=1e-9;
const Real PI=acos(-1.0);
 
template<class T> bool eq(T a,T b){
	return abs(a-b)<eps;
}
template<class T> int sgn(T a){
	if(eq(a,0.0)) return 0;
	if(a>0) return 1;
	return -1;
}
 
Real arg(Point p){
	return atan2(p.imag(),p.real());
}
 
Real crP(Vector a,Vector b){
	return (conj(a)*b).imag();
}
 
Point iLL(Line l1,Line l2){ // find intersect of two lines 
	Point a=l1.first,b=l1.second;
	Point c=l2.first,d=l2.second;
	Real num=crP(c-a,d-a);
	Real den=crP(b-a,d-c);
	return a+(b-a)*num/den;
}
 
bool onSeg(Point a,Point b,Point c){
	return eq(abs(a-b),abs(a-c)+abs(b-c));
}
 
bool onLine(Point a,Point b,Point c){
	return onSeg(a,b,c)||onSeg(b,c,a)||onSeg(c,a,b);
}
 
Real xs[1010],ys[1010],zs[1010];
Real theta0,phi0;
int N;
 
void rotate(){
	for(int i=0;i<N;i++){
		Point p=Point(xs[i],ys[i]);
		Point coe = polar(1.0, -theta0);
		p*=coe;
		xs[i]=p.real();
		ys[i]=p.imag();
         
		p=Point(xs[i],zs[i]);
		coe = polar(1.0, phi0);
		p*=coe;
		xs[i]=p.real(),zs[i]=p.imag();
		//      printf("(%f,%f,%f)\n",xs[i],ys[i],zs[i]);
	}
}
 
Point pts[1010];
Real rs[1010];
Point cs[1010];
bool isLine[1010];
 
void sphereMap(){
	for(int i=0;i<N;i++){
		Real coe=2.0/(1.0-zs[i]);
		pts[i]=Point(xs[i]*coe,ys[i]*coe);
		//      printf("(%f,%f)\n",pts[i].real(),pts[i].imag());
	}
	for(int i=0;i<N;i++){
		Point p=pts[i],q=pts[(i+1)%N];
		Real x=-xs[i],y=-ys[i],z=-zs[i];
		if(eq(1.0,z)){
			isLine[i]=true;
			continue;
		}
		Real coe=2.0/(1.0-z);
		Point r=Point(x*coe,y*coe); 
		if(onLine(p,q,r)){
			//          printf("Line\n");
			isLine[i]=true;
			continue;
		}
		Vector perp=Vector(0,1);
		Segment s1=Segment((p+q)/2.0,(p+q)/2.0+(q-p)*perp);
		Segment s2=Segment((q+r)/2.0,(q+r)/2.0+(q-r)*perp);
		cs[i]=iLL(s1,s2); // 重心
		Real val=abs(cs[i]-p);
		if(eq(val,abs(cs[i]-q))==false){
			printf("error in finding center\n");
			exit(0);
		}
		if(eq(val,abs(cs[i]-r))==false){
			printf("error in finding center\n");
			exit(0);
		}
		rs[i]=val; // 重心到点的距离
		//      printf("circle (%f,%f) %f\n",cs[i].real(),cs[i].imag(),rs[i]);
	}
}
 
Real normalize(Real ang){
	while(ang<0) ang+=PI*2;
	while(ang>PI*2) ang-=PI*2;
	return ang;
}
 
Real calc(Real r,Real theta){
	return r*r*(theta-sin(theta))/2.0;
}
 
Real getArea(int id){
	Point p=pts[id],q=pts[(id+1)%N];
	if(isLine[id]){
		return crP(p,q)/2;
	}
	Real area1=crP(p,q)/2;
	int s=sgn(area1);
	if(s==0){
		//      printf("s=0\n");
		return 0;
	}
	area1=abs(area1);
	//  Real angp=arg(p),angq=arg(q);
	//  Real theta=normalize(angp-angq);
	Vector vp=p-cs[id],vq=q-cs[id];
	Real angp=arg(vp),angq=arg(vq);
	Real theta=normalize(angp-angq);
	if(theta>PI) theta=PI*2-theta;
	if(sgn(crP(-p,q-p))*sgn(crP(cs[id]-p,q-p))==-1){
		theta=PI*2-theta;
	}
	Real area2=calc(rs[id],theta);
	Real res=(area1+area2)*s;
	//  printf("r=%f,theta=%f,area1=%f,area2=%f,res=%f\n",rs[id],theta,area1,area2,res);
	return res;
}
 
bool solve(){
	Real area=0;
	for(int i=0;i<N;i++){
		Real cur=getArea(i);
		area+=cur;
	}
	//  printf("%f\n",area);
	if(sgn(area)>0) return true;
	else return false;
}
 
void input(){
	scanf("%d",&N);
	int p,t;
	scanf("%d%d",&p,&t);
	theta0=(Real)t*PI/180;
	p=(p-90)*-1;
	phi0=(Real)p*PI/180;
	for(int i=0;i<N;i++){
		int p,t;
		scanf("%d%d",&p,&t);
		Real theta=(Real)t*PI/180;
		p=(p-90)*-1;
		Real phi=(Real)p*PI/180;
		xs[i]=cos(theta)*sin(phi);
		ys[i]=sin(theta)*sin(phi);
		zs[i]=cos(phi);
	}
}
 
int main(){
	input();
	rotate();
	sphereMap();
	bool flg=solve();
	if(flg) printf("Yes\n");
	else printf("No\n");
	return 0;
}
