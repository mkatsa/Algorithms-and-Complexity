#include <stdio.h>
#include <stdlib.h>

long long int n,m,i,j,x,y,temp;
long long int con[3000][3000];
long long int MST[3000][3000];
long long int c[3000][3000];

int reach[3000];

long long int max(long long int a ,long long int b)
{
	if( a > b )
		return a;
	return b; 
}

void dfs( long long int i , long long int w , long long int g ){  
    reach[i]=1;  
    long long int j,x;  
    for (j=1; j<=n; j++)  
        if (!reach[j] && MST[i][j]!=0){  
            x=max(MST[i][j],w);  
            c[g][j]=x;  
            c[j][g]=x;  
            dfs(j,x,g);  
        }  
}


void prim() {
   long long int i, j, startVertex, endVertex;
   long long int k, nr[n], temp, minimumCost = 0, tree[n][3];
 
   /* For first smallest edge */
   temp = con[0][0];
   for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
         if (temp > con[i][j]) {
            temp = con[i][j];
            startVertex = i;
            endVertex = j;
         }
      }
   }
   /* Now we have fist smallest edge in graph */
   tree[0][0] = startVertex;
   tree[0][1] = endVertex;
   tree[0][2] = temp;
   minimumCost = temp;
 
   /* Now we have to find min dis of each vertex from either
    startVertex or endVertex by initialising nr[] array
    */
 
   for (i = 0; i < n; i++) {
      if (con[i][startVertex] < con[i][endVertex])
         nr[i] = startVertex;
      else
         nr[i] = endVertex;
   }
 
   /* To indicate visited vertex initialise nr[] for them to 100 */
   nr[startVertex] = 100000001;
   nr[endVertex] = 100000001;
 
   /* Now find out remaining n-2 edges */
   temp = 100000001;
   for (i = 1; i < n - 1; i++) {
      for (j = 0; j < n; j++) {
         if (nr[j] != 100000001 && con[j][nr[j]] < temp) {
            temp = con[j][nr[j]];
            k = j;
         }
      }
      /* Now i have got next vertex */
      tree[i][0] = k;
      tree[i][1] = nr[k];
      tree[i][2] = con[k][nr[k]];
      minimumCost = minimumCost + con[k][nr[k]];
      nr[k] = 100000001;
 
      /* Now find if k is nearest to any vertex
       than its previous near value */
 
      for (j = 0; j < n; j++) {
         if (nr[j] != 100000001 && con[j][nr[j]] > con[j][k])
            nr[j] = k;
      }
      temp = 100000001;
   }
   /* Now i have the answer, just going to print it */
   //printf("\nThe min spanning tree is:- \n");
   for (i = 0; i < n - 1; i++) {
      /*for (j = 0; j < 3; j++)
      {
         printf("%d ", tree[i][j]);
      }*/
      MST[ tree[ i ][ 0 ] ][ tree[ i ][ 1 ] ] = tree[ i ][ 2 ];
      MST[ tree[ i ][ 1 ] ][ tree[ i ][ 0 ] ] = tree[ i ][ 2 ];
      //printf("\n");
   }
 
   //printf("\nMin cost : %d\n", minimumCost);
}

int main()
{
	scanf( "%lld %lld" , &n , &m );
	
	for( i = 0; i <= n - 1; i++ )
	{
		for( j = 0; j <= n - 1; j++ )
		{	
			con[ i ][ j ] = 100000001;		// a very big number in order to implement Kruskal's algorithm for MST
			MST[ i ][ j ] = 0;
		}
	}
	for( i = 0; i <= m - 1; i++ )
	{
		scanf( "%lld %lld %lld" , &x , &y , &temp );
		con[ x - 1 ][ y - 1 ] = temp;
		con[ y - 1 ][ x - 1 ] = temp;		//epeidi oloi oi dromoi einai diplis
	}
	
	
	/*printf( "GRAPH\n" );
	for( i = 0; i <= n - 1; i++ )
	{
		for( j = 0; j <= n - 1; j++ )
		{
			printf( "%d " , con[ i ][ j ] );
		}
		printf( "\n" );
	}*/

	prim();
	
	//printf( "\n" );
	
	/*for( i = 0; i <= n - 1; i++ )
	{
		for( j = 0; j <= n - 1; j++ )
		{
			printf( "%d " , MST[ i ][ j ] );
		}
		printf( "\n" );
	}*/
	
	for (i = 0; i <= n - 1; i++){  
        for (j = 0; j <= n-1; j++)  
            reach[j]=0;  
        dfs(i,0,i);  
    }
    
    
    
    long long int q;
	scanf( "%lld" , &q );
	int pos[ q ][ 2 ];
	
	//int start,fin;
	
	for( i = 0; i <= q - 1; i++ )
	{
		scanf( "%lld %lld" , &pos[ i ][ 0 ] , &pos[ i ][ 1 ] );
	}
	
	for( i = 0; i <= q - 1; i++ )
	{
		printf("%lld\n" , c[pos[ i ][ 0 ] - 1][pos[ i ][ 1 ] - 1] );
	}
		
	return 0;
}
