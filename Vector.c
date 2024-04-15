#include <stdlib.h>
#include <stdio.h>
#include "Vector.h"

SVector VectorCreate(unsigned long int NumElement)
{
    SVector v;
    v.VectorSize = NumElement;
    v.Data = calloc(NumElement, sizeof(double));
    return v;
}

void VectorDisplay(SVector v1)
{
    int i;
    printf("\nvector[%llu]=", v1.VectorSize);
    for(i = 0; i < v1.VectorSize; i++)
        printf(" %g", v1.Data[i]);
}

SVector VectorAdd(SVector v1, SVector v2)
{
    SVector result = VectorCreate(v1.VectorSize);
    int i;
    for(i = 0; i < v1.VectorSize; i++)
    {
        result.Data[i] = v1.Data[i] + v2.Data[i];
    }
    return result;
}

SVector VectorDiff(SVector v1, SVector v2)
{
    SVector result = VectorCreate(v1.VectorSize);
    int i;
    for(i = 0; i < v1.VectorSize; i++)
    {
        result.Data[i] = v1.Data[i] - v2.Data[i];
    }
    return result;
}

double VectorScalar(SVector v1, SVector v2)
{
    double result = 0.0;
    int i;
    for(i = 0; i < v1.VectorSize; i++)
    {
        result += v1.Data[i] * v2.Data[i];
    }
    return result;
}

SVector VectorMultConst(SVector v1, double c)
{
    SVector result = VectorCreate(v1.VectorSize);
    int i;
    for(i = 0; i < v1.VectorSize; i++)
    {
        result.Data[i] = v1.Data[i] * c;
    }
    return result;
}

SVector VectorCopy(SVector v1)
{
    SVector copy = VectorCreate(v1.VectorSize);
    int i;
    for(i = 0; i < v1.VectorSize; i++)
    {
        copy.Data[i] = v1.Data[i];
    }
    return copy;
}

void VectorDelete(SVector *v1)
{
    free(v1->Data);
    v1->Data = NULL;
    v1->VectorSize = 0;
}

SMatrix MatrixCreate(unsigned long int row, unsigned long int col)
{
    SMatrix matrix;
    matrix.Row = row;
    matrix.Col = col;

    // Виділення пам'яті для матриці
    matrix.Data = (double **)malloc(row * sizeof(double *));
    if (matrix.Data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned long int i = 0; i < row; ++i) {
        matrix.Data[i] = (double *)malloc(col * sizeof(double));
        if (matrix.Data[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    return matrix;
}

void MatrixDisplay(SMatrix m1)
{
    printf("\nMatrix[%lu][%lu]:\n", m1.Row, m1.Col);
    for (unsigned long int i = 0; i < m1.Row; ++i) {
        for (unsigned long int j = 0; j < m1.Col; ++j) {
            printf("%g ", m1.Data[i][j]);
        }
        printf("\n");
    }
}

void MatrixMakeE(SMatrix *m1)
{
    if (m1->Row != m1->Col) {
        fprintf(stderr, "Cannot make identity matrix: not square\n");
        return;
    }

    for (unsigned long int i = 0; i < m1->Row; ++i) {
        for (unsigned long int j = 0; j < m1->Col; ++j) {
            m1->Data[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

SMatrix MatrixMMMult(SMatrix m1, SMatrix m2)
{
    if (m1.Col != m2.Row) {
        fprintf(stderr, "Matrix multiplication not possible: incompatible dimensions\n");
        exit(EXIT_FAILURE);
    }

    SMatrix result = MatrixCreate(m1.Row, m2.Col);

    for (unsigned long int i = 0; i < m1.Row; ++i) {
        for (unsigned long int j = 0; j < m2.Col; ++j) {
            result.Data[i][j] = 0.0;
            for (unsigned long int k = 0; k < m1.Col; ++k) {
                result.Data[i][j] += m1.Data[i][k] * m2.Data[k][j];
            }
        }
    }

    return result;
}

SMatrix MatrixMMAdd(SMatrix m1, SMatrix m2)
{
    if (m1.Row != m2.Row || m1.Col != m2.Col) {
        fprintf(stderr, "Matrix addition not possible: incompatible dimensions\n");
        exit(EXIT_FAILURE);
    }

    SMatrix result = MatrixCreate(m1.Row, m1.Col);

    for (unsigned long int i = 0; i < m1.Row; ++i) {
        for (unsigned long int j = 0; j < m1.Col; ++j) {
            result.Data[i][j] = m1.Data[i][j] + m2.Data[i][j];
        }
    }

    return result;
}

SMatrix MatrixMVMult(SMatrix m1, SVector v1)
{
    if (m1.Col != v1.VectorSize) {
        fprintf(stderr, "Matrix-vector multiplication not possible: incompatible dimensions\n");
        exit(EXIT_FAILURE);
    }

    SMatrix result = MatrixCreate(m1.Row, 1);

    for (unsigned long int i = 0; i < m1.Row; ++i) {
        result.Data[i][0] = 0.0;
        for (unsigned long int j = 0; j < m1.Col; ++j) {
            result.Data[i][0] += m1.Data[i][j] * v1.Data[j];
        }
    }

    return result;
}

SMatrix MatrixCopy(SMatrix m1)
{
    SMatrix copy = MatrixCreate(m1.Row, m1.Col);

    for (unsigned long int i = 0; i < m1.Row; ++i) {
        for (unsigned long int j = 0; j < m1.Col; ++j) {
            copy.Data[i][j] = m1.Data[i][j];
        }
    }

    return copy;
}

void MatrixDelete(SMatrix *m1)
{
    for (unsigned long int i = 0; i < m1->Row; ++i) {
        free(m1->Data[i]);
    }
    free(m1->Data);
    m1->Data = NULL;
    m1->Row = 0;
    m1->Col = 0;
}

// Функція для виведення координат вектору у файл (на екран)
void VectorOutputToFile(FILE *file, SVector vector)
{
    fprintf(file, "Vector [%lu]: ", vector.VectorSize);
    for (unsigned long int i = 0; i < vector.VectorSize; i++)
    {
        fprintf(file, "%.2f ", vector.Data[i]);
    }
    fprintf(file, "\n");
}

// Функція для виведення елементів матриці у файл (на екран)
void MatrixOutputToFile(FILE *file, SMatrix matrix)
{
    fprintf(file, "Matrix [%lu x %lu]:\n", matrix.Row, matrix.Col);
    for (unsigned long int i = 0; i < matrix.Row; i++)
    {
        for (unsigned long int j = 0; j < matrix.Col; j++)
        {
            fprintf(file, "%.2f ", matrix.Data[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
}
