
#include "fast_matmult/rowmajor/matmult_s_row_X.h"

/* ѭ��˳��: m, k - n */
void matmult_s_row_MxK_N(const int M, const int N, const int K,
                         const float_t alpha,
                         const float_t *A, const int lda,
                         const float_t *B, const int ldb,
                         const float_t beta,
                         float_t *C, const int ldc)
{
    float_t A_m_k;
    int m, n, k;

    for (m = 0; m < M; ++m) {
        for (k = 0; k < K; ++k) {
            // A_m_k = A[m, k];
            A_m_k = A[m * K + k];
            for (n = 0; n < N; ++n) {
                // C[m, n] += A_m_k * B[k, n];
                C[m * N + n] += A_m_k * B[k * N + n];
            }
        }
    }
}

/* ѭ��˳��: k, m - n */
void matmult_s_row_KxM_N(const int M, const int N, const int K,
                         const float_t alpha,
                         const float_t *A, const int lda,
                         const float_t *B, const int ldb,
                         const float_t beta,
                         float_t *C, const int ldc)
{
    float_t A_m_k;
    int m, n, k;

    for (k = 0; k < K; ++k) {
        for (m = 0; m < M; ++m) {
            // A_m_k = A[m, k];
            A_m_k = A[m * K + k];
            for (n = 0; n < N; ++n) {
                // C[m, n] += A_m_k * B[k, n];
                C[m * N + n] += A_m_k * B[k * N + n];
            }
        }
    }
}

/* ѭ��˳��: m, n - k */
void matmult_s_row_MxN_K(const int M, const int N, const int K,
                         const float_t alpha,
                         const float_t *A, const int lda,
                         const float_t *B, const int ldb,
                         const float_t beta,
                         float_t *C, const int ldc)
{
    float_t C_m_n;
    int m, n, k;

    for (m = 0; m < M; ++m) {
        for (n = 0; n < N; ++n) {
            C_m_n = (float_t)0.0;
            for (k = 0; k < K; ++k) {
                // C[m, n] += A[m, k] * B[k, n];
                C_m_n += A[m * K + k] * B[k * N + n];
            }
            C[m * N + n] = C_m_n;
        }
    }
}

/* ѭ��˳��: n, m - k */
void matmult_s_row_NxM_K(const int M, const int N, const int K,
                         const float_t alpha,
                         const float_t *A, const int lda,
                         const float_t *B, const int ldb,
                         const float_t beta,
                         float_t *C, const int ldc)
{
    float_t C_m_n;
    int m, n, k;

    for (n = 0; n < N; ++n) {
        for (m = 0; m < M; ++m) {
            C_m_n = (float_t)0.0;
            for (k = 0; k < K; ++k) {
                // C[m, n] += A[m, k] * B[k, n];
                C_m_n += A[m * K + k] * B[k * N + n];
            }
            C[m * N + n] = C_m_n;
        }
    }
}

/* ѭ��˳��: k, n - m */
void matmult_s_row_KxN_M(const int M, const int N, const int K,
                         const float_t alpha,
                         const float_t *A, const int lda,
                         const float_t *B, const int ldb,
                         const float_t beta,
                         float_t *C, const int ldc)
{
    float_t B_k_n;
    int m, n, k;

    for (k = 0; k < K; ++k) {
        for (n = 0; n < N; ++n) {
            // B_k_n = B[k, n];
            B_k_n = B[k * N + n];
            for (m = 0; m < M; ++m) {
                // C[m, n] += A[m, k] * B_k_n;
                C[m * N + n] += A[m * K + k] * B_k_n;
            }
        }
    }
}

/* ѭ��˳��: n, k - m */
void matmult_s_row_NxK_M(const int M, const int N, const int K,
                         const float_t alpha,
                         const float_t *A, const int lda,
                         const float_t *B, const int ldb,
                         const float_t beta,
                         float_t *C, const int ldc)
{
    float_t B_k_n;
    int m, n, k;

    for (n = 0; n < N; ++n) {
        for (k = 0; k < K; ++k) {
            // B_k_n = B[k, n];
            B_k_n = B[k * N + n];
            for (m = 0; m < M; ++m) {
                // C[m, n] += A[m, k] * B_k_n;
                C[m * N + n] += A[m * K + k] * B_k_n;
            }
        }
    }
}

/* ѭ��˳��: m, n - k */
void matmult_s_row_MxN_K_transB(const int M, const int N, const int K,
                                const float_t alpha,
                                const float_t *A, const int lda,
                                const float_t *B, const int ldb,
                                const float_t beta,
                                float_t *C, const int ldc)
{
    float_t C_m_n;
    int m, n, k;

    // ��ת�þ���B
    matrix_fast_transpose_NxN((float_t *)B, K, N);

    // ѭ��˳��: m, n - k
    for (m = 0; m < M; ++m) {
        for (n = 0; n < N; ++n) {
            C_m_n = (float_t)0.0;
            for (k = 0; k < K; ++k) {
                // C[m, n] += A[m, k] * B'[k, n];
                C_m_n += A[m * K + k] * B[n * K + k];
            }
            C[m * N + n] = C_m_n;
        }
    }

    // �������Ժ���ת��(��ԭ)����B
    matrix_fast_transpose_NxN((float_t *)B, N, K);
}

/* ѭ��˳��: n, m - k */
void matmult_s_row_NxM_K_transB(const int M, const int N, const int K,
                                const float_t alpha,
                                const float_t *A, const int lda,
                                const float_t *B, const int ldb,
                                const float_t beta,
                                float_t *C, const int ldc)
{
    float_t C_m_n;
    int m, n, k;

    // ��ת�þ���B
    matrix_fast_transpose_NxN((float_t *)B, K, N);

    // ѭ��˳��: n, m - k
    for (n = 0; n < N; ++n) {
        for (m = 0; m < M; ++m) {
            C_m_n = (float_t)0.0;
            for (k = 0; k < K; ++k) {
                // C[m, n] += A[m, k] * B'[k, n];
                C_m_n += A[m * K + k] * B[n * K + k];
            }
            C[m * N + n] = C_m_n;
        }
    }

    // �������Ժ���ת��(��ԭ)����B
    matrix_fast_transpose_NxN((float_t *)B, N, K);
}
