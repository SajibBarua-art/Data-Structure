// You are given some ranges, you have to increase the range by 'val'.
// In a query you are able to know the sum of a range. 
// o based indexing

#include<bits/stdc++.h>
using namespace std;
const int maxN = 2e5+50;

int tree[4*maxN] = {0};  // To store segment tree
int lazy[4*maxN] = {0};  // To store pending updates
int arr[maxN]; // To store the given array which you may update

// To handle testcases
void reload(int n) {
    for(int i=0; i<=4*n; i++) {
        tree[i] = 0;
        lazy[i] = 0;
    }
}

void updateRangeUtil(int si, int ss, int se, int us,
                     int ue, int diff)
{
    if (lazy[si] != 0)
    {
        tree[si] += (se-ss+1)*lazy[si];
        if (ss != se)
        {
            lazy[si*2 + 1]   += lazy[si];
            lazy[si*2 + 2]   += lazy[si];
        }
  
        lazy[si] = 0;
    }

    if (ss>se || ss>ue || se<us)
        return ;
    if (ss>=us && se<=ue)
    {
        tree[si] += (se-ss+1)*diff;
        if (ss != se)
        {
            lazy[si*2 + 1]   += diff;
            lazy[si*2 + 2]   += diff;
        }
        return;
    }
    int mid = (ss+se)/2;
    updateRangeUtil(si*2+1, ss, mid, us, ue, diff);
    updateRangeUtil(si*2+2, mid+1, se, us, ue, diff);
  
    tree[si] = tree[si*2+1] + tree[si*2+2];
}

void updateRange(int n, int us, int ue, int diff)
{
   updateRangeUtil(0, 0, n-1, us, ue, diff);
}
int getSumUtil(int ss, int se, int qs, int qe, int si)
{
    if (lazy[si] != 0)
    {
        tree[si] += (se-ss+1)*lazy[si];
  
        if (ss != se)
        {
            lazy[si*2+1] += lazy[si];
            lazy[si*2+2] += lazy[si];
        }
        lazy[si] = 0;
    }
    if (ss>se || ss>qe || se<qs)
        return 0;
    if (ss>=qs && se<=qe)
        return tree[si];

    int mid = (ss + se)/2;
    return getSumUtil(ss, mid, qs, qe, 2*si+1) +
           getSumUtil(mid+1, se, qs, qe, 2*si+2);
}
int getSum(int n, int qs, int qe)
{
    if (qs < 0 || qe > n-1 || qs > qe)
    {
        printf("Invalid Input");
        return -1;
    }
  
    return getSumUtil(0, n-1, qs, qe, 0);
}
void constructSTUtil(int ss, int se, int si)
{
    if (ss > se)
        return ;
  
    if (ss == se)
    {
        tree[si] = arr[ss];
        return;
    }
  
    int mid = (ss + se)/2;
    constructSTUtil(ss, mid, si*2+1);
    constructSTUtil(mid+1, se, si*2+2);
  
    tree[si] = tree[si*2 + 1] + tree[si*2 + 2];
}

void constructST(int n)
{
    constructSTUtil(0, n-1, 0);
}

int main()
{
    arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
  
    // Build segment tree from given array
    constructST(n);
  
    // Print sum of values in array from index 1 to 3
    printf("Sum of values in given range = %d\n",
           getSum(n, 1, 3));
  
    // Add 10 to all nodes at indexes from 1 to 5.
    updateRange(n, 1, 5, 10);
  
    // Find sum after the value is updated
    printf("Updated sum of values in given range = %d\n",
            getSum(n, 1, 3));
  
    return 0;
}
