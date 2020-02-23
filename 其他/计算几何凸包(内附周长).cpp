#include <stdio.h>
#include <math.h>
#include <algorithm>

using namespace std;

const int maxn = 1005;

struct point
{
	double x, y;
}plist[maxn];
int pstack[maxn], top;

double cross(const point &p0, const point &p1, const point&p2)
{
	return (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
}

double dis(const point &p1, const point &p2)
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

bool cmp(const point &p1, const point &p2)
{
	double tmp = cross(plist[0], p1, p2);
	if (tmp > 0.0)return true;
	else if (tmp == 0.0 && dis(plist[0], p1) < dis(plist[0], p2))return true;
	else return false;
}


void Graham(int n)
{

	top = 1;
	pstack[0] = 0;
	pstack[1] = 1;
	for (int i = 2; i < n; i++) {
		while (top > 0 && cross(plist[pstack[top - 1]], plist[pstack[top]], plist[i]) <= 0)top--;
		pstack[++top] = i;
	}

}

int main()
{
	//freopen("in.txt", "r", stdin);
	int n;
	double res;
	while (scanf("%d", &n) != EOF && n) {
		res = 0;
		int k = 0;
		scanf("%lf %lf", &plist[0].x, &plist[0].y);
		point p0 = plist[0];
		for (int i = 1; i < n; i++) {
			scanf("%lf %lf", &plist[i].x, &plist[i].y);
			if (p0.y > plist[i].y || (p0.y == plist[i].y&&p0.x > plist[i].x)) {
				p0.x = plist[i].x;
				p0.y = plist[i].y;
				k = i;
			}
		}

		plist[k] = plist[0];
		plist[0] = p0;

		if (n == 1)
		{
			printf("0.00\n");
			continue;
		}
		else if (n == 2)
		{
			printf("%.2lf\n", dis(plist[0], plist[1]));
			continue;
		}

		sort(plist + 1, plist + n, cmp);
		Graham(n);
		for (int i = 1; i <= top; i++) {
			res += dis(plist[pstack[i - 1]], plist[pstack[i]]);
		}
		res += dis(plist[pstack[top]], plist[0]);
		printf("%.2lf\n", res);
	}
	return 0;
}
