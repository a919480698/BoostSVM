/*
 * @author: shijiashuai
 */

#ifndef MASCOT_SVM_CSRMATRIX_H
#define MASCOT_SVM_CSRMATRIX_H

#include <vector>
#include <cusparse.h>
#include"../svm-shared/gpu_global_utility.h"

using std::vector;

class CSRMatrix {
public:
    const vector<vector<svm_node> > &samples;
    vector<float_point> csrVal;
    vector<float_point> csrValSelfDot;
    vector<int> csrRowPtr;
    vector<int> csrColInd;
    int numOfFeatures;

    int getNumOfFeatures() const;

    CSRMatrix(const vector<vector<svm_node> >&samples, int numOfFeatures);
    int getNnz() const;

    const float_point *getCSRVal() const;

    const float_point *getCSRValSelfDot() const;

    const int *getCSRRowPtr() const;

    const int *getCSRColInd() const;

    int getNumOfSamples() const;
    static void CSRmm2Dense(cusparseHandle_t handle, cusparseOperation_t transA, cusparseOperation_t transB,
                            int m, int n, int k,
                            const cusparseMatDescr_t descrA,
                            const int nnzA, const float *valA, const int *rowPtrA, const int *colIndA,
                            const cusparseMatDescr_t descrB,
                            const int nnzB, const float *valB, const int *rowPtrB, const int *colIndB,
                            float *C);
    void copy2Dev(float_point *&devVal, int *&devRowPtr, int *&devColInd);
    void freeDev(float_point *&devVal, int *&devRowPtr, int *&devColInd);
};

#endif //MASCOT_SVM_CSRMATRIX_H
