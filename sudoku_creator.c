// Header files declation
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku_creator.h"

// Global array declaration
int arr[MAX][MAX];

// Main function
int main()
{
    srand(time(NULL));
    int good = create_array(0,0);
    if(good)
        printf("Sudoku has been created\n");
    print_array();
    check_sudoku();
    return 0;
}

// Function print_array
void print_array()
{
    int i=0, j=0;
    printf("\n");
    for(i=0; i<MAX; i++)
    {
        for(j=0; j<MAX; j++)
        {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}

// Function safe to check if it's safe to put a number at given row and column
int safe(int row, int col, int temp_num)
{
    int i=0,j=0, row_t, col_t;
    row_t=(row/3)*3;
    col_t=(col/3)*3;
    //  check the number in row
    for(i=0; i<row; i++)
    {
        if(arr[i][col]==temp_num)
        return 0;
    }
    //  check the number in column
    for(i=0; i<col; i++)
    {
        if(arr[row][i]==temp_num)
        return 0;
    }
    //  check the number in 3X3 matrices
    for(i=row_t;i<row_t+3;i++)
    {
        for(j=col_t;j<col_t+3;j++)
            if(i!=row && j!=col && arr[i][j]==temp_num)
                return 0;
    }
    return 1;
}

// Function to create array i.e. sudoku matrix
int create_array(int row, int col)
{
    int i, check1, check2=1;
    //  to terminate function
    if(row>MAX-1 || col>MAX-1)
        return 1;
    //  generate random number
    int temp = rand()%MAX +1;

    for(i=0; i<MAX; i++)
    {
        //  check whether generated number is valid or not
        check1 = safe(row, col, temp);
        if(check1)
        {
            arr[row][col]=temp;
            //  as valid then fill next column or next row if column is finished
            if(MAX==(row+1))
                check2=create_array(0,col+1);
            else
                check2=create_array(row+1,col);
            //  if it does not lead to solution check for other number
            if(!check2)
            {
                temp++;
                if(temp>MAX)
                    temp=1;
                check1=0;
            }
            else
                break;
        }
        else
        {
            temp++;
            if(temp>MAX)
                temp=1;
        }
    }
    // if not possible to put a number
    if(!check1)
        return 0;
    return 1;
}

// Function to check if generated array is sudoku or not
void check_sudoku()
{
    int i=0, j=0,a[10]={0},flag=1;
    //  check row wise whether all numbers are present with out repitition
    //  array a is used to count the numbers
    for(i=0; i<MAX; i++)
    {
        for(j=0; j<MAX; j++)
        {
            a[arr[i][j]]++;
        }
        for(j=1; j<MAX+1; j++)
        {
            if(a[j]!=1)
            {
                flag=0;
                break;
            }
        }
        if(!flag)
        {
            printf("BAD");
            break;
        }
        //  reset array
        for(j=1; j<MAX+1; j++)
            a[j]=0;
    }
    //  check 3X3 matrices
    int row_t, col_t,row,col;
    for(row=0;row<MAX;row+=3)
    	for(col=0;col<MAX;col+=3)
    {
    row_t=(row/3)*3;
    col_t=(col/3)*3;
    for(i=row_t;i<row_t+3;i++)
    {
        for(j=col_t;j<col_t+3;j++)
            a[arr[i][j]]++;
    }
    for(j=1; j<MAX+1; j++)
        {
            if(a[j]!=1)
                {
                	flag=0;
                	printf("BAD");
                	break;
                }
        }
    if(!flag)
    	break;
    for(j=1; j<MAX+1; j++)
            a[j]=0;
    }
    printf("Good\n");
}
