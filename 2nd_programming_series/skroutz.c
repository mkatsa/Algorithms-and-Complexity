/*-----------------------------------including the necessairy libraries-------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------global variables-------------------------------------------------------------------------------*/
long long int N,k;


/*----------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------functions-------------------------------------------------------------------------------------*/

long long int max( long long int a , long long int b );
long long int fill( long long int p[] , long long int ar1[] , long long int ar2[] , long long int ar3[] , long long int ar4[] );

/*----------------------------------------------------------------------------------------------------------------------------------*/

	long long int sell_prev[1000000];
	long long int buy_prev[1000000];
	long long int sell_new[1000000];
	long long int buy_new[1000000];

/*---------------------------------------------------main---------------------------------------------------------------------------*/

int main( int argc , char *argv[])
{
	
	scanf( "%d %d" , &N , &k );
	
	long long int p[ N + 2];	
	
	long long int i,j;
	
	for( i = 0; i <= N - 1; i++ )
	{
		scanf( "%lld" , &p[ i ] );
		sell_prev[ i ] = 0;
		buy_prev[ i ] = 0;
		sell_new[ i ] = 0;
		buy_new[ i ] = 0;
	}
	
	for( i = 1; i <= k; i++ )
	{
		if( i % 2 == 1 )		//Skroutz has to buy chocolate
		{
			fill( p , buy_prev , sell_prev , sell_new , buy_new );
		}
		else					//else Skroutz has to sell chocolate
		{
			fill( p , buy_new , sell_new , sell_prev , buy_prev );
		}

	}
	
	long long int profit;
	if( k % 2 == 0 )
	{
		profit = buy_prev[ 0 ];
	}
	else
	{
		profit = buy_new[ 0 ];
	}
	
	printf( "%lld\n" , profit );

	return 0;
}

/*----------------------------------------------------------------------------------------------------------------------------------*/

long long int max(long long int a, long long int b)
{
	if( a > b )
	{
		return a;
	}
	else
	{
		return b;
	}	
}

long long int fill( long long int p[] , long long int ar0[] , long long int ar1[] , long long int ar1n[] , long long int ar0n[] )
{
	long long int i; 
	for( i = N - 1; i >= 0; i-- )
	{
		ar1n[ i ] = max( p[ i ] + ar0[i + 1] , ar1n[ i + 1] );
	}
	for( i = N - 2; i >= 0; i-- )
	{
		ar0n[ i ] = max( ar0n[ i+1 ] , ar1n[ i+1 ] - p[ i ] );
	}
}
