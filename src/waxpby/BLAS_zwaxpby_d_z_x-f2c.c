
#include "f2c-bridge.h"
#include "blas_enum.h"
void		BLAS_zwaxpby_d_z_x(int n, const void *alpha, const double *x, int incx,
			 		const		void  *beta, const void *y, int incy, void *w,
	 		int		incw    , enum blas_prec_type prec);


extern void	FC_FUNC_(blas_zwaxpby_d_z_x, BLAS_ZWAXPBY_D_Z_X)
                (int *n, const void *alpha, const double *x, int *incx, const void *beta, const void *y, int *incy, void *w, int *incw, int *prec)
{
  BLAS_zwaxpby_d_z_x(*n, alpha, x, *incx,
		     beta, y, *incy, w,
		     *incw, (enum blas_prec_type)*prec);
}
