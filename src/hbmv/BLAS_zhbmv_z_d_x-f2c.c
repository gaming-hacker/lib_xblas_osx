
#include "f2c-bridge.h"
#include "blas_enum.h"
void		BLAS_zhbmv_z_d_x(enum blas_order_type order,
		 		enum		blas_uplo_type uplo, int n, int k,
	      		const		void  *alpha, const void *a, int lda,
	     		const		double *x, int incx, const void *beta,
	      		void         *y, int incy, enum blas_prec_type prec);


extern void	FC_FUNC_(blas_zhbmv_z_d_x, BLAS_ZHBMV_Z_D_X)
                (int *uplo, int *n, int *k, const void *alpha, const void *a, int *lda, const double *x, int *incx, const void *beta, void *y, int *incy, int *prec)
{
  BLAS_zhbmv_z_d_x(blas_colmajor,
		   (enum blas_uplo_type)*uplo, *n, *k,
		   alpha, a, *lda,
		   x, *incx, beta,
		   y, *incy, (enum blas_prec_type)*prec);
}