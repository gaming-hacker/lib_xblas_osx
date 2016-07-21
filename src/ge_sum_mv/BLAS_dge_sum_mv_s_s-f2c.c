
#include "f2c-bridge.h"
#include "blas_enum.h"
void		BLAS_dge_sum_mv_s_s(enum blas_order_type order, int m, int n,
		      		double	alpha , const float *a, int lda,
			  		const		float *x, int incx,
		      		double	beta  , const float *b, int ldb,
			  		double       *y, int incy);


extern void	FC_FUNC_(blas_dge_sum_mv_s_s, BLAS_DGE_SUM_MV_S_S)
                (int *m, int *n, double *alpha, const float *a, int *lda, const float *x, int *incx, double *beta, const float *b, int *ldb, double *y, int *incy)
{
  BLAS_dge_sum_mv_s_s(blas_colmajor, *m, *n,
		      *alpha, a, *lda,
		      x, *incx,
		      *beta, b, *ldb,
		      y, *incy);
}
