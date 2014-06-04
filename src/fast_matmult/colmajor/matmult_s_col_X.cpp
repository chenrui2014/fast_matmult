
#include "fast_matmult/colmajor/matmult_s_col_X.h"

/* ѭ��˳��: m, k - n */
void matmult_s_col_MxK_N(const int M, const int N, const int K,
                         const cblas_float alpha,
                         const cblas_float *A, const int lda,
                         const cblas_float *B, const int ldb,
                         const cblas_float beta,
                         cblas_float *C, const int ldc)
{
    cblas_float A_m_k;
    int m, n, k;

    for (m = 0; m < M; ++m) {
        for (k = 0; k < K; ++k) {
            // A_m_k = A[m, k];
            A_m_k = A[k * M + m];
            for (n = 0; n < N; ++n) {
                // C[m, n] += A_m_k * B[k, n];
                C[n * M + m] += A_m_k * B[n * K + k];
            }
        }
    }
}

/* ѭ��˳��: k, m - n */
void matmult_s_col_KxM_N(const int M, const int N, const int K,
                         const cblas_float alpha,
                         const cblas_float *A, const int lda,
                         const cblas_float *B, const int ldb,
                         const cblas_float beta,
                         cblas_float *C, const int ldc)
{
    cblas_float A_m_k;
    int m, n, k;

    for (k = 0; k < K; ++k) {
        for (m = 0; m < M; ++m) {
            // A_m_k = A[m, k];
            A_m_k = A[k * M + m];
            for (n = 0; n < N; ++n) {
                // C[m, n] += A_m_k * B[k, n];
                C[n * M + m] += A_m_k * B[n * K + k];
            }
        }
    }
}

/* ѭ��˳��: m, n - k */
void matmult_s_col_MxN_K(const int M, const int N, const int K,
                         const cblas_float alpha,
                         const cblas_float *A, const int lda,
                         const cblas_float *B, const int ldb,
                         const cblas_float beta,
                         cblas_float *C, const int ldc)
{
    cblas_float C_m_n;
    int m, n, k;

    for (m = 0; m < M; ++m) {
        for (n = 0; n < N; ++n) {
            C_m_n = (cblas_float)0.0;
            for (k = 0; k < K; ++k) {
                // C[m, n] += A[m, k] * B[k, n];
                C_m_n += A[k * M + m] * B[n * K + k];
            }
            C[n * M + m] = C_m_n;
        }
    }
}

/* ѭ��˳��: n, m - k */
void matmult_s_col_NxM_K(const int M, const int N, const int K,
                         const cblas_float alpha,
                         const cblas_float *A, const int lda,
                         const cblas_float *B, const int ldb,
                         const cblas_float beta,
                         cblas_float *C, const int ldc)
{
    cblas_float C_m_n;
    int m, n, k;

    for (n = 0; n < N; ++n) {
        for (m = 0; m < M; ++m) {
            C_m_n = (cblas_float)0.0;
            for (k = 0; k < K; ++k) {
                // C[m, n] += A[m, k] * B[k, n];
                C_m_n += A[k * M + m] * B[n * K + k];
            }
            C[n * M + m] = C_m_n;
        }
    }
}

/* ѭ��˳��: k, n - m */
void matmult_s_col_KxN_M(const int M, const int N, const int K,
                         const cblas_float alpha,
                         const cblas_float *A, const int lda,
                         const cblas_float *B, const int ldb,
                         const cblas_float beta,
                         cblas_float *C, const int ldc)
{
    cblas_float B_k_n;
    int m, n, k;

    for (k = 0; k < K; ++k) {
        for (n = 0; n < N; ++n) {
            // B_k_n = B[k, n];
            B_k_n = B[n * K + k];
            for (m = 0; m < M; ++m) {
                // C[m, n] += A[m, k] * B_k_n;
                C[n * M + m] += A[k * M + m] * B_k_n;
            }
        }
    }
}

/* ѭ��˳��: n, k - m */
void matmult_s_col_NxK_M(const int M, const int N, const int K,
                         const cblas_float alpha,
                         const cblas_float *A, const int lda,
                         const cblas_float *B, const int ldb,
                         const cblas_float beta,
                         cblas_float *C, const int ldc)
{
    cblas_float B_k_n;
    int m, n, k;

    for (n = 0; n < N; ++n) {
        for (k = 0; k < K; ++k) {
            // B_k_n = B[k, n];
            B_k_n = B[n * K + k];
            for (m = 0; m < M; ++m) {
                // C[m, n] += A[m, k] * B_k_n;
                C[n * M + m] += A[k * M + m] * B_k_n;
            }
        }
    }
}

/* ѭ��˳��: m, n - k */
void matmult_s_col_MxN_K_transA(const int M, const int N, const int K,
                                const cblas_float alpha,
                                const cblas_float *A, const int lda,
                                const cblas_float *B, const int ldb,
                                const cblas_float beta,
                                cblas_float *C, const int ldc)
{
    cblas_float C_m_n;
    int m, n, k;

    // ��ת�þ���A
    matrix_fast_transpose_NxN((cblas_float *)A, M, K);

    for (m = 0; m < M; ++m) {
        for (n = 0; n < N; ++n) {
            C_m_n = (cblas_float)0.0;
            for (k = 0; k < K; ++k) {
                // C[m, n] += A'[m, k] * B[k, n];
                C_m_n += A[m * K + k] * B[n * K + k];
            }
            C[n * M + m] = C_m_n;
        }
    }

    // �������Ժ���ת��(��ԭ)����A
    matrix_fast_transpose_NxN((cblas_float *)A, K, M);
}

/* ѭ��˳��: n, m - k */
void matmult_s_col_NxM_K_transA(const int M, const int N, const int K,
                                const cblas_float alpha,
                                const cblas_float *A, const int lda,
                                const cblas_float *B, const int ldb,
                                const cblas_float beta,
                                cblas_float *C, const int ldc)
{
    cblas_float C_m_n;
    int m, n, k;

    // ��ת�þ���A
    matrix_fast_transpose_NxN((cblas_float *)A, M, K);

    for (n = 0; n < N; ++n) {
        for (m = 0; m < M; ++m) {
            C_m_n = (cblas_float)0.0;
            for (k = 0; k < K; ++k) {
                // C[m, n] += A'[m, k] * B[k, n];
                C_m_n += A[m * K + k] * B[n * K + k];
            }
            C[n * M + m] = C_m_n;
        }
    }

    // �������Ժ���ת��(��ԭ)����A
    matrix_fast_transpose_NxN((cblas_float *)A, K, M);
}
