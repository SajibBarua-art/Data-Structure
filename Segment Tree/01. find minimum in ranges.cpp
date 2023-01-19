#include<bits/stdc++.h>
using namespace std;

const int maxN = 1e5;
const int INF = INT_MAX;
int segmentTree[maxN*4+50], arr[maxN+5];

void buildTree(int sIndex, int sStart, int sEnd) {
    if(sStart == sEnd) {
        segmentTree[sIndex] = arr[sStart];
        return;
    }

    int mid = (sStart+sEnd)/2;
    buildTree(sIndex*2, sStart, mid);
    buildTree(sIndex*2+1, mid+1, sEnd);

    segmentTree[sIndex] = min(segmentTree[sIndex*2], segmentTree[sIndex*2+1]);
}

int query(int sIndex, int sStart, int sEnd, int qStart, int qEnd) {
    if(qStart>sEnd || qEnd<sStart) // completely outside
        return INF;
    if(sStart>=qStart && sEnd<=qEnd) // completely inside
        return segmentTree[sIndex];

    int mid = (sStart + sEnd)/2;
    int l = query(sIndex*2, sStart, mid, qStart, qEnd);
    int r = query(sIndex*2+1, mid+1, sEnd, qStart, qEnd);
    return min(l, r);
}

int main() {
    int n; cin >> n;
    for(int i=1; i<=n; i++) cin >> arr[i];

    buildTree(1, 1, n);
    cout << query(1, 1, n, 2, 4) << endl;
}