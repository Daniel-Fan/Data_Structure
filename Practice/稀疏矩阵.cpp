#include<stdio.h>
#define MAXSIZE 12500

typedef struct{
	int i,j;
	int e;
}Triple;

typedef struct{
	Triple data[MAXSIZE+1];
	int rpos[MAXSIZE+1];
	int mu,nu,tu;
}RLSMatrix;

int MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix &Q) 
{  
  int arow,brow,p,q,t,ctemp[30],l,ccol,tp;
  if (M.nu != N.mu) return 0;
  Q.mu = M.mu; Q.nu = N.nu; Q.tu = 0;      
  if (M.tu*N.tu != 0) {  
    for (arow=1; arow<=M.mu; ++arow) 
	{ 
      for (l=1; l<=M.nu; ++l) 
	  ctemp[l] = 0;
      Q.rpos[arow] = Q.tu+1; 
      tp=M.rpos[arow+1];
      for (p=M.rpos[arow]; p<tp;++p) {   
        brow=M.data[p].j;      
        t = N.rpos[brow+1];
        for (q=N.rpos[brow];  q< t;  ++q) {
          ccol = N.data[q].j;
          ctemp[ccol] += M.data[p].e * N.data[q].e;
        }
    } 
      for (ccol=1; ccol<=Q.nu; ++ccol) 
        if (ctemp[ccol]) { 
          if (++Q.tu > MAXSIZE) return 0;
          Q.data[Q.tu].i=arow;
          Q.data[Q.tu].j=ccol;
          Q.data[Q.tu].e=ctemp[ccol];
        }
    }
  }
  return 1;
}

int main()
{
	RLSMatrix M={{{1,1,3},{1,4,5},{2,2,-1},{3,1,2}},{1,3,4,5},3,4,4};
	RLSMatrix N={{{1,2,2},{2,1,1},{3,1,-2},{3,2,4}},{1,2,3,5,5},4,2,4};
	RLSMatrix Q;
	printf("%d\n",MultSMatrix(M,N,Q));
}