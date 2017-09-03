/*-------------------------------------------------libraries--------------------------------------------------------------------------------------------------------------------------------*/  
  
#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>  
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/  
  
  
/*-------------------------------------------------main-------------------------------------------------------------------------------------------------------------------------------------*/  
  
int main()  
{  
    int N , k;      //N = the length of the playground , k = number of trees that we want  
    int i , j;              //i and j are counters  
       
      
    scanf( "%d" , &N );  	//Read N
    scanf( "%d" , &k );  	//Read k 
      
    int park[ N + 1][ N ];              //Table that has 1s and 0s, according to the existance of a tree in (i,j) position or not  
    int enter;  
    //read input from keyboard and count the summary of line i till the line j and save it to park[i][j]  

      
    for( i = 0; i <= N; i++ )  
    {  
        for( j = 0; j <= N - 1; j++ )  
        {             
            if( i == 0 )  
            {  
                park[ i ][ j ] = 0;  
            }  
            else  
            {     
                park[ i ][ j ] = getc(stdin);  			//read if the next square has a tree(1) or not(0)
                park[ i ][ j ] = park[ i ][ j ] - '0';
                park[ i ][ j ] = park[ i - 1][ j ] + park[ i ][ j ];   
            }  
        }  
        enter = getc(stdin);  
    }  
      
      
    int front = 0 , rear = 0;  //"pointers" to out array
      
    int df =0;  
    int dr = 0;  
    long long int num_of_subtables = 0;  //The total numbers of all subtables that have summary equal to k
    int x = 1 , y = 2;
    long long int sum = 0;  	//it will have the current summary of the trees
    int end = 0;  
  
    for( x = 1; x <= N; x++ )  //for all the lines
    {  
        for( y = x; y <= N; y++ )  //for all the columns
        {  
            front = 0;  
            rear = 0;  
            sum = park[ y ][ 0 ] - park[ x - 1][ 0 ];  
            end = 0;  
              
            while( rear < N )  //while pointer rear has not reached the end
            {  
                if( sum < k && front < N - 1 )  //check if we have less trees and pointer front hasn't reached the end
                {  
                    front++;  					//if yes we have to increase fron and add the new element to the total summary of the trees
                    sum = sum + park[ y ][ front ] - park[ x - 1 ][ front ];   
                }  
                else if( sum > k && front != rear )  //if we hace more trees, we increase rear, so we reduce the array we look at and we have to substract from the total
                {  									 //summary of the trees the part that we cut.
                    rear++;  	
                    sum = sum - park[ y ][ rear - 1] + park[ x - 1][ rear - 1 ];  
                }  
                else if( sum > k && front == rear && front < N - 1 )  //if the trees are more than k and front ,rear are at the same point, but not to the end, then 
                {  													  //we just move front and rear to the next column and we find the new summary.
                    front++;  
                    rear++;  
                    sum = park[ y ][ front ] - park[ x - 1 ][ front ];  
                }  
                else if( sum == k )  	//if the current summary of trees is equal to the number of trees we want then we need to add subatbles,until we find a subtable that has more trees
                {  
                    df = 0;   
                    dr = 0;  
                    if( front < N - 1 )  
                    {  
                        front++;  
                    }  
                    else   
                        end = 1;  
                      
                    while( park[ y ][ front] - park[ x - 1 ][ front ] == 0 && end == 0 )  
                    {  
                        if( front < N - 1)  
                            front++;  
                        else  
                            end = 1;  
                              
                        df++;  
                    }  
                      
                    while( park[ y ][ rear ] - park[ x - 1 ][ rear ] == 0 && rear < front )  
                    {  
                        dr++;  
                        rear++;  
                    }  
                    if( end == 0 )  
                    {  
                        sum = sum + park[ y ][front] - park[ x - 1 ][ front ];  
                    }  
                      
                    rear++;  
                    sum = sum - park[ y ][ rear - 1 ] + park[ x - 1][ rear - 1];  
                      
                    num_of_subtables += ( ( dr + 1 ) * ( df + 1 ) );  
                }  
                else  
                    break;  
            }  
        }  
    }  
      
    printf( "%lld\n" , num_of_subtables );  
      
    return 0;  
}
