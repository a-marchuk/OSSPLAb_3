#include <stdio.h>
#include "Vector.h"

int main()
{
    printf("\nStart!\n");

    unsigned long int size;
    printf("Enter the size of the vector: ");
    if (scanf("%lu", &size) != 1)
    {
        printf("Invalid input for vector size!\n");
        return 1;
    }

    SVector inputVector = VectorCreate(size);
    if (inputVector.Data == NULL)
    {
        printf("Error creating vector.\n");
        return 1;
    }

    printf("Enter the coordinates of the vector:\n");
    for (unsigned long int i = 0; i < size; i++)
    {
        printf("Coordinate %lu: ", i + 1);
        if (scanf("%lf", &inputVector.Data[i]) != 1)
        {
            printf("Invalid input for coordinate %lu!\n", i + 1);
            return 1;
        }
    }

    printf("\nVector:\n");
    VectorDisplay(inputVector);

    FILE *outputFile = fopen("vector_output.txt", "w");
    if (outputFile == NULL)
    {
        printf("Error opening vector output file!\n");
        return 1;
    }
    printf("Writing vector to output file...\n");
    VectorOutputToFile(outputFile, inputVector);
    printf("Vector successfully written to output file!\n");
    fclose(outputFile);

    VectorDelete(&inputVector);

    unsigned long int row, col;
    printf("\nEnter the number of rows of the matrix: ");
    if (scanf("%lu", &row) != 1)
    {
        printf("Invalid input for matrix rows!\n");
        return 1;
    }
    printf("Enter the number of columns of the matrix: ");
    if (scanf("%lu", &col) != 1)
    {
        printf("Invalid input for matrix columns!\n");
        return 1;
    }

    SMatrix inputMatrix = MatrixCreate(row, col);
    if (inputMatrix.Data == NULL)
    {
        printf("Error creating matrix.\n");
        return 1;
    }

    printf("Enter the elements of the matrix:\n");
    for (unsigned long int i = 0; i < row; i++)
    {
        for (unsigned long int j = 0; j < col; j++)
        {
            printf("Element (%lu, %lu): ", i + 1, j + 1);
            if (scanf("%lf", &inputMatrix.Data[i][j]) != 1)
            {
                printf("Invalid input for element (%lu, %lu)!\n", i + 1, j + 1);
                return 1;
            }
        }
    }

    printf("\nMatrix:\n");
    MatrixDisplay(inputMatrix);

    FILE *matrixOutputFile = fopen("matrix_output.txt", "w");
    if (matrixOutputFile == NULL)
    {
        printf("Error opening matrix output file!\n");
        return 1;
    }
    printf("Writing matrix to output file...\n");
    MatrixOutputToFile(matrixOutputFile, inputMatrix);
    printf("Matrix successfully written to output file!\n");
    fclose(matrixOutputFile);

    MatrixDelete(&inputMatrix);

    printf("\nStopped!\n");
    return 0;
}
