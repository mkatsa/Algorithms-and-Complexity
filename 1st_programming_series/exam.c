/*This algorithm does a binary search to find between 0 and k*d1 and finds the time that the k-th student will get in the room to get examined.This
has a complexity O(nlogn).After that I find how many students will get examined at the same time before him.If they are x, the student that
we want to find will get examined by the x+1 available examiner and the total time will be the time he enters plus the time that he will be examined.
This is O(n)
So,totally, our algorithm will have a complexity O(nlogn).
*/


/*----------------------------------------libraries--------------------------------------------------------*/
#include <stdio.h>    
#include <stdlib.h>    
#include <math.h>    

/*-----------------------------------------main function---------------------------------------------------*/
    
int main()    
{    
    long long int N,k;              //Number of examiners and my position on the queue    
    long long int *Table;           //time of examination for all the examiners    
    long long int first,last,mid;   //These will be used for the binary search 
    long long int current = 0;		
	long long int sum;
	long long int min;    
    
    //read inputs from keyboard
	scanf( "%lld" , &N);    
    scanf( "%lld" , &k);    
        
    Table = malloc( N * sizeof( *Table ) );     //create an integer table of N positions     
    if( Table == NULL )                         //check if there was enough memory left and if the table was created    
    {    
        printf( "NO MEMORY AVAILABLE\n" );    //if not exit
        exit(-2);    
    }    
    
    int i;    //i will be used as a counter for the table
    scanf("%lld" , &Table[0] );    
    min = Table[ 0 ];
    for( i = 1; i <= N - 1; i++ )    
    {    
        //read from keybord for the N examiners the time that each one of them examines    
        scanf("%lld" , &Table[i] );    
        if( Table[ i ] < min )
        {
        	min = Table[ i ];
		}
    }    
        
        
    if( k <= N )  	//if k is lower or equal to the number of examiners then he will be examined by the kth examiner  
    {    
        printf( "%lld %lld\n" , k , Table[ k - 1 ] );    
        return 0;    
    }    
           
    long long int in = 0;   
	first = 0;    
    last =  k * min;    
    mid = ( first + last ) / 2;    
    
    int flag = 0;

    mid = (first + last)/2;
/*---------------------------------------------------binary-search-------------------------------------------------------*/
	while( abs( first - last != 1 ) || flag==0 ){
			
		sum = 0;
		current = 0;
		if( abs( first - last ) == 1 ){
			flag = 1;
		}
		for( i=0; i <= N-1; i++ ){
			sum = sum + mid / Table[ i ];
			if(mid % Table[ i ] != 0){
				sum = sum + 1;
			}
			else{
				current = current + 1;
			}
		}
		if( flag == 1 ){
			break;
		}
		if( sum >= k ){
			last = mid;
		}
		else
		{
			first = mid;
		}
		mid = ( first + last ) / 2;
	}
	//now mid has the result of the binary search,which is the time that the k-th student will enter the room to get examined
	
    long long int out = 0;    
    //I have to find, in time mid how many candidates will have left the examination    
    long long int examiner,rem,total_time;    


/*------------------------------------find examiner and time-------------------------------------------------------*/        
    for( i = 0; i <= N - 1; i++ )    
    {    
        if( (mid%Table[ i ] == 0))    
            out += mid / Table[ i ];    
        else    
            out += mid / Table[ i ] + 1;    
    }    
        
        
    rem = k - out;    
	for( i = 0; i <= N - 1; i++ )    
    {    
       	if( mid%Table[ i ] == 0 && rem == 1)    
       	{    
	      	examiner = i + 1;    
	    	total_time = mid + Table[ i ];
    		break;    
	    }    
	    else if( mid%Table[ i ] == 0 && rem > 1)    
	    {    
	        rem--;    
	    }    
	}
/*------------------------------------------display results------------------------------------------------------------*/
	printf( "%lld %lld\n" , examiner , total_time );    
    return 0;    
} 
