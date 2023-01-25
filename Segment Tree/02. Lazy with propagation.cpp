// You are given some ranges, you have to increase the range by 'val'.
// In a query you are able to know the sum of a range. 

#include<bits/stdc++.h>
using namespace std;
const int maxN = 2e5+5;
int arr[maxN];
int segmentTree[4*maxN], lazy[4*maxN];

void buildTree(int sIndex, int sStart, int sEnd) {
    if(sStart == sEnd) {
        segmentTree[sIndex] = arr[sStart];
        return;
    }

    int mid = (sStart+sEnd)/2;
    buildTree(sIndex*2, sStart, mid);
    buildTree(sIndex*2+1, mid+1, sEnd);

    segmentTree[sIndex] = segmentTree[sIndex*2] + segmentTree[sIndex*2+1];
}

int query(int sIndex, int sStart, int sEnd, int qStart, int qEnd) {
    // for pending update
    if(lazy[sIndex] != 0) {
        int dx = lazy[sIndex];
        lazy[sIndex] = 0;
        segmentTree[sIndex] += (dx*(sEnd-sStart));

        if(sStart != sEnd) {
            lazy[sIndex*2] += dx;
            lazy[sIndex*2 + 1] += dx;
        }
    }

    if(qStart>sEnd || qEnd<sStart) // completely outside
        return 0; // change here
    if(sStart>=qStart && sEnd<=qEnd) // completely inside
        return segmentTree[sIndex];

    int mid = (sStart + sEnd)/2;
    int l = query(sIndex*2, sStart, mid, qStart, qEnd);
    int r = query(sIndex*2+1, mid+1, sEnd, qStart, qEnd);
    return (l+r); // change here
}

void update(int sIndex, int sStart, int sEnd, int qStart, int qEnd, int val) {
    // for pending update
    if(lazy[sIndex] != 0) {
        int dx = lazy[sIndex];
        lazy[sIndex] = 0;
        segmentTree[sIndex] += (dx*(sEnd-sStart));

        if(sStart != sEnd) {
            lazy[sIndex*2] += dx;
            lazy[sIndex*2 + 1] += dx;
        }
    }

    if(sStart>qEnd || sEnd<qStart) return;
    if(sStart>=qStart && sEnd<=qEnd) {
        int dx = (sEnd-sStart+1)*val;
        segmentTree[sIndex] += dx;

        if(sStart != sEnd) {
            lazy[2*sIndex] += val;
            lazy[2*sIndex+1] += val;
        }
        return;
    }

    int mid = (sStart + sEnd)/2;
    update(sIndex*2, sStart, mid, qStart, qEnd, val);
    update(sIndex*2+1, mid+1, sEnd, qStart, qEnd, val);

    segmentTree[sIndex] = segmentTree[sIndex*2] + segmentTree[sIndex*2+1]; // change here
}

int main() {
    int n, q, code, l, r, value; cin >> n >> q;
    buildTree(1, 1, n);
    while(q--) {
        cin >> code;
        if(code == 1) {
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << endl;
        }
        else {
            cin >> l >> r >> value;
            update(1, 1, n, l, r, value);
        }
    }
}