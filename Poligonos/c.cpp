#include <bits/stdc++.h>

using namespace std;
#define int long long
#define N 100005


typedef long double ld;
const ld EPS = 1e-9;

struct point { 
    ld x, y;
    point(ld x, ld y) : x(x), y(y) {}
    point() {}
    ld norm2() { 
        return *this * *this;
    }
    ld norm() {
        return sqrt(norm2());
    }
    bool operator==(const point& other) const {
        return abs(x - other.x) < EPS && abs(y - other.y) < EPS;
    }
    point operator+(const point& other) const {
        return point(x + other.x, y + other.y);
    }
    point operator-(const point& other) const {
        return point(x - other.x, y - other.y);
    }
    point operator*(ld t) const {
        return point(x * t, y * t);
    }
    point operator/(ld t) const {
        return point(x / t, y / t);
    }
    ld operator*(const point& other) const {
        return x*other.x + y*other.y;
    }
    ld operator^(const point& other) const { // cross product
        return x*other.y - y*other.x;
    }
    bool operator<(const point& other) const { // for sweep line
        return x < other.x - EPS || (abs(x - other.x) < EPS && y < other.y - EPS);
    }
    point rotate(point r) {
        return point(*this ^ r, *this * r);
    }
    point rotate(ld ang) {
        return rotate(point(sin(ang), cos(ang)));
    }
    ld angle(point& other) { // only works for angles in the range [0, PI]
        ld cos_val = min(1.0L, max(-1.0L, *this * other / (norm() * other.norm())));
        return acos(cos_val);
    }
};
point ccw90(1, 0);
point cw90(-1, 0);

ld dist2(point p, point q) { // squared distance
    return (p - q).norm2();
}

ld dist(point p, point q) {
    return sqrt(dist2(p, q));
}

ld area2(point a, point b, point c) { // two times signed area of triangle abc
	return (b - a) ^ (c - a);
}

bool left(point a, point b, point c) {
	return area2(a, b, c) > EPS; // counterclockwise
}

bool right(point a, point b, point c) {
	return area2(a, b, c) < -EPS; // clockwise
}

bool collinear(point a, point b, point c) {
	return abs(area2(a, b, c)) < EPS;
}

// Returns 0 if vectors a and b are not parallel.
// If they are parallel, returns 1 if they have the same direction 
// and returns -1 otherwise
int paral(point a, point b) { 
    if((a ^ b) != 0) return 0;
    if((a.x > EPS) == (b.x > EPS) && (a.y > EPS) == (b.y > EPS))
        return 1;
    return -1;
}

struct polygon {
    vector<point> p;
    int n;
    polygon() : n(0) {}
    polygon(vector<point> _p) {
        p = _p;
        n = p.size();
    }
    void add(point q) {
        p.push_back(q);
        n++;
    }
    // If positive, the polygon is in ccw order. It is in cw order otherwise.
    ld orientation() { // O(n)
        ld acum = 0;
        for(int i = 0; i < n; i++)
            acum += p[i] ^ p[(i + 1) % n];
        return acum;
    }
    ld area() { // O(n)
        return abs(orientation()) / 2.0;
    }
    void turnCcw() { // O(n)
        if(orientation() < -EPS)
            reverse(p.begin(), p.end());
    }
    bool has(point q) { // O(log n). The polygon must be convex and in ccw order.
        if(right(p[0], p[1], q) || left(p[0], p[n-1], q)) return 0;
        int lo = 1, hi = n;
        while(lo + 1 < hi) {
            int mid = (lo + hi) >> 1;
            if(!right(p[0], p[mid], q)) lo = mid;
            else hi = mid;
        }
        return hi != n ? !right(p[lo], p[hi], q) : dist2(p[0], q) < dist2(p[0], p[n-1]) + EPS;
    }
    ld calipers() { // O(n). The polygon must be convex and in ccw order.
        ld ans = 0;
        for(int i = 0, j = 1; i < n; i++) {
            point vec_i = p[(i+1)%n] - p[i];
            while((vec_i ^ (p[(j+1)%n] - p[j])) > EPS) 
                j = (j + 1) % n;
            ans = max(ans, dist(p[i], p[j])); // Example with polygon diameter
        }
        return ans;
    }
    int extreme(const function<bool(point, point)> &cmp) {
        auto isExtreme = [&](int i, bool& curDir) -> bool {
            curDir = cmp(p[(i + 1) % n], p[i]);
            return !cmp(p[(i + n - 1) % n], p[i]) && !curDir;
        };
        bool lastDir, curDir;
        if(isExtreme(0, lastDir)) return 0;
        int lo = 0, hi = n; 
        while(lo + 1 < hi) {
            int m = (lo + hi) >> 1;
            if(isExtreme(m, curDir)) return m;
            bool relDir = cmp(p[m], p[lo]);
            if((!lastDir && curDir) || (lastDir == curDir && relDir == curDir)) {
                lo = m;
                lastDir = curDir;
            } else hi = m;
        }
        return lo;
    }
    pair<int, int> tangent(point q) { // O(log n) for convex polygon in ccw orientation
        // Finds the indices of the two tangents to an external point q
        auto leftTangent = [&](point r, point s) -> bool {
            return right(q, r, s);
        };
        auto rightTangent = [&](point r, point s) -> bool {
            return left(q, r, s);
        };
        return {extreme(leftTangent), extreme(rightTangent)};
    }
    int maximize(point v) { // O(log n) for convex polygon in ccw orientation
        // Finds the extreme point in the direction of the vector
        return extreme([&](point p, point q) {return p * v > q * v + EPS;});
    }
    void normalize() { // p[0] becomes the lowest leftmost point 
        rotate(p.begin(), min_element(p.begin(), p.end()), p.end());
    }
    polygon operator+(polygon& other) { // Minkowsky sum
        vector<point> sum;
        normalize();
        other.normalize();
        ld dir;
        for(int i = 0, j = 0; i < n || j < other.n; i += dir > -EPS, j = dir < EPS) {
            sum.push_back(p[i % n] + other.p[j % other.n]);
            dir = (p[(i + 1) % n] - p[i % n]) 
                    ^ (other.p[(j + 1) % other.n] - other.p[j % other.n]);
        }
        return polygon(sum);
    }       
     
};

vector<point> convexHull(vector<point> p) {
    int n =p.size();
	sort(p.begin(), p.end());
	vector<point> low, up;
	for(int i = 0; i < n; i++) {
		if(i && p[i] == p[i - 1]) continue;
		while(up.size() >= 2 && !right(up[up.size()-2], up.back(), p[i]))
			up.pop_back();
		up.push_back(p[i]);
		while(low.size() >= 2 && !left(low[low.size()-2], low.back(), p[i]))
			low.pop_back();
		low.push_back(p[i]);
	}
    vector<point> ch;
	if(low.size() == 1) return low;
	for(int i = 0; i < low.size()- 1; i++)
        ch.push_back(low[i]);
	for(int i = up.size() - 1; i >= 1; i--)
        ch.push_back(up[i]);
    return ch;


}


signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int t;
    cin>>t;
    //cout<<"t: "<<t<<"\n";
    for(int loops=0;loops<t;loops++){
        int n;
        cin>>n;
        //cout<<"n: "<<n<<"\n";
        vector<point> pontos(n);
        for(int i=0;i<n;i++){
            cin>>pontos[i].x>>pontos[i].y;
        }
        sort(pontos.begin(),pontos.end());

        vector<point> tmp=convexHull(pontos);
        polygon p(tmp);
        
        int q;
        cin>>q;
        //cout<<"q: "<<q<<"\n";
        for(int i=0;i<q;i++){
            double tmpx,tmpy;
            cin>>tmpx>>tmpy;
            if(p.has(point(tmpx,tmpy))){
                cout<<"Yes\n";
            }
            else{
                cout<<"No\n";
            }
        }

        cout<<"\n";        
    }
    return 0;
}
