#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
	long long int N,k;
	scanf( "%lld" , &N );		//read N from stdin
	scanf( "%lld" , &k );		//read k from stdin
	if( N == k )
	{
		printf( "%d\n" , 0 );
		return 0;
	}
	
	long long int i,j,l;
	long long int A[ N ][ N ];	//store the input
	long long int E[ k ][ N ];	//for dynamic programming
	
	//E is the matrix we're going to fill using dynamic programming
	for( i = 0; i <= N - 1; i++ )		//initialize A[][] and E[][] with 0 elements
	{
		for( j = 0; j <= N - 1; j++ )
		{
			if( i <= k - 1 )
			{
				E[ i ][ j ] = 0;
			}
			A[ i ][ j ] = 0;
		}
	}

	//read input from keyboard and store it to A
	for( i = 0; i <= N - 2; i++ )		//N-1 lines
	{
		for( j = i + 1; j <= N - 1; j++ )
		{
			scanf( "%lld" , &A[ i ][ j ] );	//read from standard input
			A[ j ][ i ] = A[ i ][ j ];
		}
	}

	
	for( j = N - 2; j >= 0; j-- )
	{
		for( i = j + 1; i <= N - 1; i++ )
		{
			E[ k - 1 ][ j ] = E[ k - 1 ][ j ] + A[ j ][ i ];
		}
		
		E[ k - 1 ][ j ] = E[ k - 1 ][ j ] + E[ k - 1 ][ j + 1 ];
	}

    long long int w , q;
    long long int sum1 = 0;
    
    for ( i = k - 2; i >= 0; i-- )
    {

        for ( j = N - k - 1 + i; j >= 0; j-- )
        {
            sum1 = 0;
            long long int min = 2147483647;
            long long int sum = 0;
            for ( w = j; w <= N - k + i; w++)
            {
                for ( q = j; q < w; q++)
                {
                    sum1 = sum1 + A[ w ][ q ];

                }

                sum = sum1 + E[ i + 1 ][ w + 1 ];

                if ( sum < min ) { min = sum; E[ i ][ j ] = sum;}
                sum = 0;
            }
        }
    }
	
	printf( "%lld\n" , E[ 0 ][ 0 ] );
	
	
	return 0;
}
