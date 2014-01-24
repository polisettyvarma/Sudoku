// Header files declaration
#include <stdio.h>
#include <stdlib.h>
#include "sudoku_solver.h"

// Global array declaration
int arr[MAX][MAX], onearr[MAX][MAX];

//  array onearr is used to keep track of original numbers

int main(void)
{
    input();

    copy_one();
    //print_array2();
    print_array();

    int out = fill_array(0,0);
    if(out)
        printf("good to go:");

    printf("\n");
    print_array();
    return 0;
}

//  to read input from a file
void input()
{
    FILE *fp;
    int i=0,j=0;
    char ch;
    //  read input from input file
    fp=fopen("input.txt","r");
    while (!feof(fp) && i!=9)
    {
        ch=fgetc(fp);
        //printf("%c ",ch);
        if(ch!='0')
        arr[i][j]=(int)ch-48;
        if(i==9)
        {
            j=0;
            i++;
        }
        j++;
    }
}

//function to copy one at the given position
void copy_one()
{
    int i=0, j=0;
    for(i=0; i<MAX; i++)
    {
        for(j=0; j<MAX; j++)
        {
            if(arr[i][j]!=0)
                onearr[i][j]=1;
        }
    }
}

// Function print_array
void print_array()
{
    int i=0, j=0;printf("\n");
    for( ; i<MAX; i++)
    {
        for(j=0; j<MAX; j++)
        {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}

// function to print copied array
void print_array2()
{
    int i=0, j=0;printf("\n");
    for( ; i<MAX; i++)
    {
        for(j=0; j<MAX; j++)
        {
            printf("%d ",onearr[i][j]);
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
    for(i=0; i<MAX; i++)
    {
        if(arr[i][col]==temp_num)
        return 0;
    }
    //  check the number in column
    for(i=0; i<MAX; i++)
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
            printf("Not");
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


// Function to fill sudoku
int fill_array(int row, int col)
{
    int i, check1=0, check2=0;
    //  to check whole has filled or not
    if(row>MAX-1 || col>MAX-1)
        return 1;
            
    int temp = 1;
    //  present element can be filled
    if(onearr[row][col]==0)
    {
        for(i=0; i<MAX; i++)
        {
            //  check this number is valid or not
            check1 = safe(row, col, temp);
            if(check1)
            {
                arr[row][col]=temp;
                //  as valid then fill next column or next row if column is finished
                if(MAX==(row+1))
                    check2=fill_array(0,col+1);
                else
                    check2=fill_array(row+1,col);
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
            }
        }
    }
    else
    {
        //  as it is fixed fill next position
        if(MAX==(row+1))
            check2=fill_array(0,col+1);
        else
            check2=fill_array(row+1,col);
        if(!check2)
        {
            return 0;
        }
    }
    //  if both didn't lead to solution then backtrack
    if(!check1 && !check2)
    {
        if(onearr[row][col]==0)
        {
            arr[row][col]=0;
        }
    return 0;
    }
    
    return 1;
}
