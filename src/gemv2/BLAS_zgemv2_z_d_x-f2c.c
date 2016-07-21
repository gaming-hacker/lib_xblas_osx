
#include "f2c-bridge.h"
#include "blas_enum.h"
void		BLAS_zgemv2_z_d_x(enum blas_order_type order, enum blas_trans_type trans,
					int		m       , int n, const void *alpha, const void *a, int lda,
					const		double *head_x, const double *tail_x, int incx,
	     		const		void  *beta, void *y, int incy,
					enum		blas_prec_type prec);


extern void	FC_FUNC_(blas_zgemv2_z_d_x, BLAS_ZGEMV2_Z_D_X)
                (int *trans, int *m, int *n, const void *alpha, const void *a, int *lda, const double *head_x, const double *tail_x, int *incx, const void *beta, void *y, int *incy, int *prec)
{
  BLAS_zgemv2_z_d_x(blas_colmajor, (enum blas_trans_type)*trans,
		    *m, *n, alpha, a, *lda,
		    head_x, tail_x, *incx,
		    beta, y, *incy,
		    (enum blas_prec_type)*prec);
}