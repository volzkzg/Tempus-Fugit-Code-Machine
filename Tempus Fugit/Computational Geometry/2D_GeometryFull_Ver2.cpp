//Not checked, dangerous!!!!

#include <cstdio>
#include <cmath>
#include <algorithm> 

using namespace std;


const double eps = 1e-8;
const double pi=acos(-1.0);

inline int sign(double x)
{
	return (x < -eps ? -1 : x > eps);
}
inline double Acos(double x)
{
	if (sign(x+1)==0)
		return(acos(-1.0));
	if (sign(x-1)==0)
		return(acos(1.0));
	return(acos(x));
}
inline double Sqrt(double x)
{
	if (sign(x)==0)
		return(0);
	return(sqrt(x));
}

inline double Asin(double x)
{
	if (sign(x+1)==0)
		return(asin(-1.0));
	if (sign(x-1)==0)
		return(asin(1.0));
	return(asin(x));
}

inline double sqr(double x)
{
	return x * x;
}

class point
{
public:
	double x, y;
	point(){}
	point(double x, double y):x(x), y(y){}
	double len() const
	{
		return (sqrt(x * x + y * y));
	}
	point unit() const
	{
		double t = len();
		return point(x / t, y / t);
	}
	point rotate() const
	{
		return point(-y, x);
	}
	point rotate(double t) const
	{
		return point(x * cos(t) - y * sin(t), x * sin(t) + y * cos(t));
	}
	
};
inline point operator +(const point &a,const point &b)
{
	return(point(a.x+b.x,a.y+b.y));
}
inline point operator -(const point &a,const point &b)
{
	return(point(a.x-b.x,a.y-b.y));
}
inline point operator *(const point &a,double b)
{
	return(point(a.x*b,a.y*b));
}
inline point operator /(const point &a,double b)
{
	return(point(a.x/b,a.y/b));
}
inline bool operator <(const point &a,const point &b)
{
	return(sign(a.x-b.x)<0 || sign(a.x-b.x)==0 && sign(a.y-b.y)<0);
}
inline double dot(const point &a,const point &b)
{
	return(a.x*b.x+a.y*b.y);
}
inline double det(const point &a,const point &b)
{
	return(a.x*b.y-a.y*b.x);
}
inline double dist(const point &a,const point &b)
{
	return((a-b).len());
}
inline int side(const point &p,const point &a,const point &b)
{
	return(sign(det(b-a,p-a)));
}

inline bool online(const point &p,const point &a,const point &b)
{
	return(sign(dot(p-a,p-b))<=0 && sign(det(p-a,p-b))==0);
}

inline point project(const point &p,const point &a,const point &b)
{
	double t=dot(p-a,b-a)/dot(b-a,b-a);
	return(a+(b-a)*t);
}
inline double ptoline(const point &p,const point &a,const point &b)
{
	return(fabs(det(p-a,p-b))/dist(a,b));
}

inline double ptoseg(const point &p,const point &a,const point &b)
{
	point q=project(p,a,b);
	if (online(q,a,b))
		return(dist(p,q));
	return(min(dist(p,a),dist(p,b)));
}

inline point reflect(const point &p,const point &a,const point &b)
{
	return(project(p,a,b)*2-p);
}

inline bool parallel(const point &a,const point &b,const point &c,const point &d)
{
	return(sign(det(b-a,d-c))==0);
}

inline bool orthogonal(const point &a,const point &b,const point &c,const point &d)
{
	return(sign(dot(b-a,d-c))==0);
}

inline bool cross(const point &a,const point &b,const point &c,const point &d)
{
	return(side(a,c,d)*side(b,c,d)==-1 && side(c,a,b)*side(d,a,b)==-1);
}

inline point intersect(const point &a,const point &b,const point &c,const point &d)
{
	double s1=det(b-a,c-a),s2=det(b-a,d-a);
	return((c*s2-d*s1)/(s2-s1));
}

inline pair <point,point> intersect(const point &a,const point &b,const point &o,double r)
{
	point tmp=project(o,a,b);
	double d=dist(tmp,o);
	double l=Sqrt(sqr(r)-sqr(d));
	point dir=(b-a).unit()*l;
	return(make_pair(tmp+dir,tmp-dir));
}

inline pair <point,point> intersect(const point &o1,double r1,const point &o2,double r2)
{
	double d=dist(o1,o2);
	double x=(sqr(r1)-sqr(r2))/(2*d)+d/2;
	double l=Sqrt(sqr(r1)-sqr(x));
	point dir=(o2-o1).unit();
	return(make_pair(o1+dir*x+dir.rotate()*l,o1+dir*x-dir.rotate()*l));
}

inline point tangent(const point &p,const point &o,double r)
{
	return(intersect((p+o)/2,dist(p,o)/2,o,r).first);
}

inline pair <point,point> intangent(const point &o1,double r1,const point &o2,double r2)
{
	double t=r1/(r1+r2);
	point tmp=o1+(o2-o1)*t;
	point P=tangent(tmp,o1,r1),Q=tangent(tmp,o2,r2);
	return(make_pair(P,Q));
}

inline pair <point,point> extangent(const point &a,double r1,const point &b,double r2)
{
	if (sign(r1-r2)==0)
	{
		point dir=(b-a).rotate().unit();
		return(make_pair(a+dir*r1,b+dir*r2));
	}
	if (sign(r1-r2)>0)
	{
		pair <point,point> tmp=extangent(b,r2,a,r1);
		return(make_pair(tmp.second,tmp.first));
	}
	point p=tangent(a,b,r2-r1);
	point dir=(p-b).unit();
	return(make_pair(a+dir*r1,b+dir*r2));
}

inline void convex(int &n,point a[])
{
	static point b[100010];
	int m=0;
	sort(a+1,a+n+1);
	for (int i=1;i<=n;i++)
	{
		while (m>=2 && sign(det(b[m]-b[m-1],a[i]-b[m]))<=0)
			m--;
		b[++m]=a[i];
	}
	int rev=m;
	for (int i=n-1;i;i--)
	{
		while (m>rev && sign(det(b[m]-b[m-1],a[i]-b[m]))<=0)
			m--;
		b[++m]=a[i];
	}
	n=m-1;
	for (int i=1;i<=n;i++)
		a[i]=b[i];
}

bool parallel(const point &a, const point &b)
{
	return parallel(point(0, 0), a, point(0, 0), b);
}

inline void cut(int &n,point p[],const point &a,const point &b)
{
	static point ret[1010];
	p[0]=p[n];
	int m=0;
	for (int i=1;i<=n;i++)
	{
		point P=p[i-1],Q=p[i];
		if (side(P,a,b)>=0)
			ret[++m]=P;
		if (!parallel(Q-P,b-a))
		{
			point tmp=intersect(P,Q,a,b);
			if (sign(dot(tmp-P,tmp-Q))<0)
				ret[++m]=tmp;
		}
	}

	if (m<3)
		m=0;
	n=m;
	for (int i=1;i<=n;i++)
		p[i]=ret[i];
}

inline bool inPolygon(const point &p,int n,point a[])
{
	int res=0;
	a[0]=a[n];
	for (int i=1;i<=n;i++)
	{
		point A=a[i-1],B=a[i];
		if (online(p,A,B))
			return(true);
		if (sign(A.y-B.y)<=0)
			swap(A,B);
		if (sign(p.y-A.y)>0 || sign(p.y-B.y)<=0)
			continue;
		 res+=sign(det(B-p,A-p))>0;
	}
	return(res&1);
}

inline point center(const point &a,const point &b,const point &c)
{
	return((a+b+c)/3);
}

inline point center(int n,point a[])
{
	point ret(0,0);
	double area=0;
	a[0] = a[n];
	for (int i=1;i<=n;i++)
	{
		ret=ret+center(point(0,0),a[i-1],a[i])*det(a[i-1],a[i]);
		area+=det(a[i-1],a[i]);
	}
	return(ret/area);
}

int main()
{
	return 0;
}
