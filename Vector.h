#ifndef MATRIXVECTOR_H
#define MATRIXVECTOR_H

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

SVector VectorCreate(unsigned long int);
void VectorDisplay(SVector);
SVector VectorAdd(SVector, SVector);
SVector VectorDiff(SVector, SVector);
double VectorScalar(SVector, SVector);
SVector VectorMultConst(SVector, double);
SVector VectorCopy(SVector);
void VectorDelete(SVector *);
void VectorOutputToFile(FILE *, SVector);

SMatrix MatrixCreate(unsigned long int, unsigned long int);
void MatrixDisplay(SMatrix);
void MatrixMakeE(SMatrix *);
SMatrix MatrixMMMult(SMatrix, SMatrix);
SMatrix MatrixMMAdd(SMatrix, SMatrix);
SMatrix MatrixMVMult(SMatrix, SVector);
SMatrix MatrixCopy(SMatrix);
void MatrixDelete(SMatrix *);
void MatrixOutputToFile(FILE *, SMatrix);

#endif
