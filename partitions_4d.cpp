#include <cstdio>
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <utility>

 
// THIS IS VERSION 2.0 OF THE PROGRAM TO COUNT NUMBERS OF TOPOLOGICAL SEQUENCES OF A GIVEN INDEX
 
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<pii, int> piii;

const int MAX = 100;
 
ll c[MAX+1]; 
ll d[MAX+1];            // d[i] = no of topological sequences of index i
int cc[MAX+1][MAX+1];   // no. of columns in given plane,row
int pp, n;              // no. of planes and n
piii x[MAX+1]; int k;   // the sequence of positions and its depth
int curidx;
int count=0;
int shape[MAX+1][MAX+1][MAX+1];
vector<int> indx;
 
// a[i] = number of 1-d partitions of sum i //
/**********************************OTHER CODE**************************/
struct tp
{
    int x;
    int y;
    int z;
 
    bool operator== (tp &tp1)
    {
        return (x == tp1.x &&
                y == tp1.y &&
                z == tp1.z);
    }
};
 
struct tpp
{
    tp tr;
    int t;
 
    bool operator>(const tpp& rhs) const
    {
        if(tr.x>rhs.tr.x)
            return true;
        if(tr.x<rhs.tr.x)
            return false;
        if(tr.y>rhs.tr.y)
            return true;
        if(tr.y<rhs.tr.y)
            return false;
        if(tr.z>rhs.tr.z)
            return true;
        return false;
    }
};
 
 
ll d2[MAX+1];          
int cc2[MAX+1][MAX+1][MAX+1];  
tpp x2[MAX+1];
tp origin={1,1,1};
int k2,curidx2; 
 
bool possible(int x, int y, int z,int t) {
  if(x>1 && cc2[x-1][y][z] < t) return 0;
  if(y>1 && cc2[x][y-1][z] < t) return 0;
  if(z>1 && cc2[x][y][z-1] < t) return 0;
  return 1;
}
 
void include(int p, int y, int z,int t) {
  k2++;
  cc2[p][y][z] = t;
  x2[k2].tr.x = p;x2[k2].tr.y = y;x2[k2].tr.z = z;
  x2[k2].t = t;
  if(x2[k2-1] > x2[k2]){
      curidx2 += (k2-1);
  }
}
void exclude(int p, int y, int z,int t) {
  if(x2[k2-1] > x2[k2]){
      curidx2 -= (k2-1);
  } 
cc2[p][y][z]--;
k2--;
}
 
 

void gen2() {
  if( k2 > n) return;
  
  if(k2==n)
    if(!(x2[k2].tr==origin))
        d2[k2+curidx2]++;
  
  int p, q, r, c;
  for(p=1; p<=n; p++) {
    for(q=1; q<=n; q++) {
        for(r=1; r<=n; r++){
            c = cc2[p][q][r]+1;
            if(c>shape[p][q][r]) continue;
            if(possible(p, q, r, c)) {
                                include(p, q, r, c);
                                gen2();
                                exclude(p, q, r, c);
        }
        if(cc2[p][q][r] == 0) break;
      }
      if(cc2[p][q][1] == 0) break;
    }
    if(cc2[p][1][1] == 0) break;
  }
}
 
void generate_topological_sequences2() {
  memset(cc2, 0, sizeof(cc2));
  //memset(d2, 0, sizeof(d2));
  //d2[0] = 1;
  k2=1;
  x2[1].tr.x = 1;x2[1].tr.y = 1;x2[1].tr.z = 1;
  x2[1].t=1;
  cc2[1][1][1] = 1;
  curidx2 = 0;
  gen2();
}

/**********************************************************************/
ll a[MAX+1];
void calculate_1d(int n) {
  for(int i=0; i<=n; i++) a[i]=1;
  for(int k=2; k<=n; k++)
    for(int i=k; i<=n; i++)
      a[i] += a[i-k];
}

void printArray(int Ar3[MAX+1][MAX+1][MAX+1])
{
    int p=1;
    while(Ar3[1][1][p]!=0)
    {
    for(int i=1;i<10;i++)
    {
        for(int j=1;j<10;j++)
        {
            if(Ar3[i][j][p] == 0) break;
    
            printf("%d ",Ar3[i][j][p]);
        }
        printf("\n");
        if(Ar3[i][1][p] == 0) break;
    }
    printf("\n");
    p++;
    }
    printf("shape\n");
    generate_topological_sequences2();
}


 void shapeArray(int p1[], int n1)
{
    if(n1<=k)
    {
    for(int i=1;i<=n1;i++)
    {
        shape[x[i].first.first][x[i].first.second][x[i].second] +=  p1[i-1];
    }
    
    generate_topological_sequences2();
    //printArray(shape);
    count++;
    
    for(int i=1;i<=n1;i++)
    {
        shape[x[i].first.first][x[i].first.second][x[i].second] -=  p1[i-1];
    }
    }
    
    if(n1>k)
    {
        for(int i=1;i<=k;i++)
        {
            shape[x[i].first.first][x[i].first.second][x[i].second] +=  p1[i-1];
        }
        
        int t=1;
        while(shape[1][1][t]!=0){
            t++;
        }
        
        int j=n1-k;
        
        while(j!=0)
        {
            shape[1][1][t]=p1[n1-j];
            t++;j--;
        }
        t--;
        
        generate_topological_sequences2();
        //printArray(shape);
        count++;
        
        for(int i=1;i<=k;i++)
        {
            shape[x[i].first.first][x[i].first.second][x[i].second] -=  p1[i-1];
        }
        
        j=n1-k;
        
        while(j!=0)
        {
            shape[1][1][t]=0;
            t--;j--;
        }
        
        //printArray(shape);
        
    }
    /*cout << endl;
    for (int i = 0; i < n1; i++)
        cout << p1[i] << " ";
    cout << endl;*/
}
 
void shapeParts(int n1)
{
    if(n1<0)
        return;
    if(n1==0)
    {
        generate_topological_sequences2();
        //printArray(shape);
        count++;
        return;
    }
    int p[n1]; // An array to store a partition
    int k1 = 0;  // Index of last element in a partition
    p[k1] = n1;  // Initialize first partition as number itself
 
    // This loop first prints current partition, then generates next
    // partition. The loop stops when the current partition has all 1s
    while (true)
    {
        // print current partition
        shapeArray(p, k1+1);
 
        // Generate next partition
 
        // Find the rightmost non-one value in p[]. Also, update the
        // rem_val so that we know how much value can be accommodated
        int rem_val = 0;
        while (k1 >= 0 && p[k1] == 1)
        {
            rem_val += p[k1];
            k1--;
        }
 
        // if k < 0, all the values are 1 so there are no more partitions
        if (k1 < 0)  return;
 
        // Decrease the p[k] found above and adjust the rem_val
        p[k1]--;
        rem_val++;
 
 
        // If rem_val is more, then the sorted order is violeted.  Divide
        // rem_val in differnt values of size p[k] and copy these values at
        // different positions after p[k]
        while (rem_val > p[k1])
        {
            p[k1+1] = p[k1];
            rem_val = rem_val - p[k1];
            k1++;
        }
 
        // Copy rem_val to next position and increment position
        p[k1+1] = rem_val;
        k1++;
    }
}


/************** GENERATING TOPOLOGICAL SEQUENCES *****************/

 
bool possible(int x, int y, int z) {
  if(x>1 && cc[x-1][y] < z) return 0;
  if(y>1 && cc[x][y-1] < z) return 0;
  return 1;
}
 
void include(int p, int y, int z) {
  k++;
  cc[p][y] = z;
  x[k] = make_pair(pii(p,y), z);
  if(x[k-1] > x[k]){
      indx.push_back(k-1);
      curidx += (k-1);
  } // if x[k-1] becomes interesting on adding x[k], then increment current index (curidx) by (k-1)    }
}
void exclude(int p, int y, int z) {
  if(x[k-1] > x[k]){
    indx.pop_back();
    curidx -= (k-1);// if x[k-1] is interesting, removal of x[k] needs us to decrement current index (curidx) by (k-1)
    }
    cc[p][y]--;
    k--;
}
 

void printconfig() { 
    //for(int i=1; i<=k; i++) printf("(%d,%d,%d)  ", x[i].first.first, x[i].first.second, x[i].second); printf("%d\n", curidx+k);
    
    memset(shape, 0, sizeof(shape));
    //printf("\nLet's do it:%d\n",indx.size());
    for(int j = 0; j < indx.size(); j++)
    {
        for(int i=1; i<=indx[j]; i++) shape[x[i].first.first][x[i].first.second][x[i].second]++;
    }
    //printArray(shape);
    shapeParts(n-curidx-k);
    
 }
 
// count the current config and make ur next move
void gen() {
  if(curidx + k > n) return;
  //if(curidx + k != n)
  //shapeParts(n-k-curidx);
  if(x[k].first!=pii(1,1)){
      indx.push_back(k);
      printconfig();
      d[curidx+k]++;
      indx.pop_back();
      //shapeParts(n-k-curidx);
  }
  int p, r, c;
  for(p=1; p<=n; p++) {
    for(r=1; r<=n; r++) {
      c = cc[p][r]+1;
      if(possible(p, r, c)) {
                                include(p, r, c);
                                gen();
                                exclude(p, r, c);
      }
      if(cc[p][r] == 0) break;
    }
    if(cc[p][1] == 0) break;
  }
}
 
void generate_topological_sequences(int nn) {
  memset(cc, 0, sizeof(cc));
  memset(d, 0, sizeof(d));
  memset(d2, 0, sizeof(d2));
  d[0] = 1;
  d2[0] = 1;
  k=1; x[1] = make_pair(pii(1,1),1);
  cc[1][1] = 1;
  curidx = 0;
  n = nn;
  gen();
}

// assumes generate_topological_sequences() and calculate_1d() have been called

void calculate_3d_correct(int n) {
  memset(c, 0, sizeof(c));
  for(int i=1; i<=n; i++) {
    for(int j=0; j<=i; j++) c[i] += (a[j]*d[i-j]);
  }
}
 
int main() {
  printf("Enter N: ");
  int N; scanf("%d", &N);
  generate_topological_sequences(N);
  calculate_1d(N);
  calculate_3d_correct(N);
  indx.clear();
  k=0;
  memset(shape,0,sizeof(shape));
  shapeParts(N);
  /*
  printf("d[i] = no. of topological sequences of index i\n");
  for(int i=0; i<=N; i++) printf("d[%d] = %lld\n", i, d[i]);
  printf("c[i] = no. of 3d partitions of i\n");
  for(int i=1; i<=N; i++) printf("c[%d] = %lld\n", i, c[i]);
  //shapeParts(0);
  printf("Is it though?? = %d\n", count);*/
  
  cout<<"\n Let's see:\n";
  //generate_topological_sequences2();
  
  cout<<"hmmm..."<<c[N]<<"\n";
  printf("Number of topos of given shape:");
  printf("d[%d] = %lld\n", N, d2[N]);
 // return 0;
}