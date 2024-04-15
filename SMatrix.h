#ifndef LAB3_SMATRIX_H
#define LAB3_SMATRIX_H

typedef struct Vector
{
    double *Data;
    unsigned long int VectorSize;
} SVector;

typedef struct Matrix
{
    double **Data;
    unsigned long int Row;
    unsigned long int Col;
} SMatrix;

typedef SVector SVectorPtr;
typedef SMatrix SMatrixPtr;

#endif //LAB3_SMATRIX_H
