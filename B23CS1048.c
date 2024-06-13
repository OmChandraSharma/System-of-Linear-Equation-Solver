//System of linear equation solver
#include <stdio.h>
#include <stdlib.h>

int n = 20; //maximum number of variables

void take_input(int n, float matrix[n][n], float constants[]); //function to take input of coefficents

float determinant(int n, float matrix[n][n]); //function to calculate determinant of a matrix

void generate_cofactor_matrix(int n , float cofactor_matrix[n][n],float matrix[n][n]);//function to genrate co-factor matrix

void generate_inverse_matrix(int n , float cofactor_matrix[n][n], float inverse_matrix[n][n], float matrix[n][n]);//function to generate inverse of the matrix

void get_solution_set(int n, float solutions[], float inverse_matrix[n][n], float constants[]);

int check_sub_dets(int n, float matrix[n][n], float constants[]);

int check_for_same(int n, float matrix[n][n], float constants[]);

int main() {
    printf("                               WELCOME TO SYSTEM OF LINEAR EQUATIONS SOLVER\n\n");
    int code =0;
    while(1)
    {
    printf("MENU\n\n");
    printf("1. TO KNOW ABOUT THEORY OF SOLVING SYSTEM OF LINEAR EQUATIONS\n");
    printf("2. SOLUTION SET CALCULATOR\n");
    printf("3. TO EXIT THE PROGRAM\n\n");

    int count =0;
    do
    {
        if(count >0)
            printf("\nInvalid choice, Try Again\n");
        printf("Choose an option from the menu: ");
        scanf("%d", &code);
        ++count;
    }while(code <0 || code >3);
    
    if(code == 1)
    {
        printf("A system of linear Equation can be solved using CRAMER'S Rule\n");
        printf("The sytem of equations is written as below:\n\n");
        printf("                                     A1x1 + A2x2 + A3x3 +..............+Anxn = k1\n");
        printf("                                     B1x1 + B2x2 + B3x3 +..............+Bnxn = k2\n");
        printf("                                     C1x1 + C2x2 + C3x3 +..............+Cnxn = k2\n");
        printf("                                     D1x1 + D2x2 + D3x3 +..............+Dnxn = k2\n");
        printf("                                     .\n");
        printf("                                     .\n");
        printf("                                     .\n");
        printf("                                     .\n");
        printf("                                     .\n");
        printf("                                     .\n");
        printf("                                     .\n");
        printf("                                     .\n");
        printf("                                     .upto n equations\n\n");
        printf("Here Ai, Bi, Ci etc are the respective coefficients of variable xi.\n\n");
        printf("This set of equations can represented with the help of matrix as: \n\n");
        printf("                                     |A1 A2 A3...............An| |x1|     |C1|\n");
        printf("                                     |B1 B2 B3...............Bn| |x2|     |C2|\n");
        printf("                                     |C1 C2 C3...............Cn| |x3|     |C3|\n");
        printf("                                     |D1 D2 D3...............Dn| |x4|  =  |C4|\n");
        printf("                                     |.                        | |. |     |. |\n");
        printf("                                     |.                        | |. |     |. |\n");
        printf("                                     |.                        | |. |     |. |\n");
        printf("                                     |.                        | |. |     |. |\n");
        printf("                                     |.                        | |. |     |. |\n");
        printf("                                     |.........................| |xn|     |. |\n");
        printf("                                                    ^              ^        ^\n");
        printf("                                                    |              |        |\n");
        printf("                                                Matrix A   solution set    set of constants\n");
        printf("\nMatrix A is the matrix of set of coefficients of the variables.\nThe solution set can be calculated by multiplying both sides with inverse of matrix A\n");
        printf("Let solution set be represented as X and constant set with K\n\n");
        printf("                                     AX = K\n");
        printf("Multiplying both sides by A-1\n");
        printf("                                    A-1*A*X = A-1*K\n");
        printf("Since, A-1*A = 1\n");
        printf("                          Therefore, X = A-1*K\n\n");
        printf("The inverse matrix can be calculated by forming the co-factor matrix.\n");
        printf("Co-factor of an element of a matrix is the derminant ofremaining\n");
        printf("elements of matrix after taking out the row and column elements of\n");
        printf("the element we are calculating co-factor of.\n");
        printf("The inverse matrix is the matrix obtained by dividing every term of co-factor matrix by determinant of the matrix\n\n");

    }
    else if(code ==2)
    {
    printf("A linear equation is of the form:\n                    C1x1 + C2x2 + C3x3 + ............+ Cnxn = k\n\n");
    do
    {
    printf("Enter the number of variables: ");
    scanf("%d", &n);
    printf("\n");
    }while( n <0);

    float matrix[n][n];
    float constants[n];

    take_input(n, matrix, constants);//call to take input
    if(check_for_same(n, matrix, constants) == 0)
    {
            printf("The equations have infinitely many solutions\n\n");
            continue;
    }

    if(determinant(n, matrix) == 0)
    {
        if(check_sub_dets(n, matrix, constants) == 1)
        {
            printf("The equations have infinitely many solutions\n\n");
            continue;
        }
        else
        {
            printf("The Equations have no solution\n\n");
            continue;
        }
        continue;
    }

    float cofactor_matrix[n][n];

    generate_cofactor_matrix(n, cofactor_matrix, matrix);

    float inverse_matrix[n][n];

    generate_inverse_matrix(n, cofactor_matrix, inverse_matrix, matrix);

    float solutions[n];

    get_solution_set(n, solutions, inverse_matrix, constants);

    printf("\nThe Solution set is:\n");
    for(int i =0; i<n; ++i)
        printf("X%d = %f     ",i+1, solutions[i]);
    printf ("\n\n");

    }
    else
        break;
    }
    return 0;
}

void take_input(int n, float matrix[n][n], float constants[])
{
    for(int i= 1;i <n+1; ++i)
    {
        printf("Enter coefficients of variables of equation no.%d\n\n", i);
        for(int j =1; j <n+1; ++j)
        {
            printf("X%d: ", j);
            scanf("%f", &matrix[i-1][j-1]);
        }
        printf("K: ");
        scanf("%f", &constants[i-1]);
        printf("\n");
    }
}

float determinant(int n, float matrix[n][n])
{
    float temp_matrix[n-1][n-1];
    float det =0;

    if(n == 1)
        return matrix[0][0];
    else
    {
        for(int i =0; i <n; ++i) // loop to expand for determinant along row1
        {
            int temp_row =0;
            for(int j= 1; j <n; ++j )//2 loops to assign values to temp_matrix
            {
                int temp_column =0;
                for(int k =0; k <n; ++k)
                {
                    if(k == i)//removing the column of element along which determinant is expanded i.e. matrix[0][i]
                        continue;
                    temp_matrix[temp_row][temp_column] = matrix[j][k];
                    ++temp_column;
                }
                ++temp_row;
            }
            if(i % 2 == 0)
                det += (matrix[0][i])*determinant(n-1, temp_matrix);
            else    
                det += (-1)*(matrix[0][i])*determinant(n-1, temp_matrix);
        }
    }
    return det;
}

void generate_cofactor_matrix(int n , float cofactor_matrix[n][n],float matrix[n][n])
{
    float temp_matrix[n-1][n-1];

    for(int i =0; i <n; ++i)// Iterating through matrix elements to calculate their cofactors
        for(int j =0; j <n; ++j)
        {
            int temp_row =0;
            for(int a =0; a <n; ++a)/* Filling temp_matrix*/
            {
                int temp_column =0;
                for(int b=0; b <n; ++b)
                {
                    if(a == i || b ==j)//skipping through row and column elements matrix[j][i] is in
                        continue;
                    temp_matrix[temp_row][temp_column]= matrix[a][b];
                    ++temp_column;
                }
                if(a ==i)
                    continue;
                ++temp_row;
            }
            cofactor_matrix[i][j]= determinant(n-1, temp_matrix)*((i+j)%2 ==0 ? 1 : -1);

        }
}
    
void generate_inverse_matrix(int n , float cofactor_matrix[n][n], float inverse_matrix[n][n], float matrix[n][n])
{
    for(int i =0; i <n; ++i)
        for(int j =0; j <n; ++j)
        {
            inverse_matrix[i][j]= (cofactor_matrix[i][j])/determinant(n,matrix);
        }
    float copy[n][n];

    for(int i =0; i <n; ++i)
        for(int j =0; j <n; ++j)
        {
            copy[i][j]= inverse_matrix[i][j];
        }
    for(int i =0; i <n; ++i)
        for(int j =0; j <n; ++j)
        {
            inverse_matrix[i][j]= copy[j][i];
        }
}

void get_solution_set(int n, float solutions[], float inverse_matrix[n][n], float constants[])
{
    float sum=0;
    for(int i =0; i <n; ++i)
    {   
        sum =0;
        for(int j=0; j <n; ++j)
        {
            sum += (inverse_matrix[i][j])*constants[j];
        }
        solutions[i]= sum;
    }
}

int check_sub_dets(int n, float matrix[n][n], float constants[])
{
    float check[n];
    float copy[n][n];

    for(int i =0; i <n; ++i)
        for(int j =0; j <n; ++j)
        {
            copy[i][j]= matrix[i][j];
        }

    for(int i =0; i <n; ++i)
    {
        for(int j=0; j <n; ++j)
        {
            copy[i][j]= constants[j];
        }
        check[i]= determinant(n, copy);

        for(int j=0; j <n; ++j)
        {
            copy[i][j]= matrix[i][j];
        }
    }

    for(int i=0; i<n; ++i)
        if(check[i] !=0)
            return 0;
    
    return 1;
}

int check_for_same(int n, float matrix[n][n], float constants[])
{
    int count =0;
    for(int i =0; i <n; ++i)
    {
        for(int j =i+1; j <n; ++j)
        {
            count =0;
            for(int k =0; k <n-1; ++k)
            {
                if(matrix[i][k]/matrix[j][k] == matrix[i][k+1]/matrix[j][k+1] && matrix[i][k]/matrix[j][k] == constants[i]/constants[j])
                ++count;
            }
            if(count == n-1)
                return 0;
        }
    }
    return 1;
}


