
#include "f2c-bridge.h"
#include "blas_enum.h"
void		BLAS_cdot_c_s(enum blas_conj_type conj, int n, const void *alpha,
	   		const		void  *x, int incx, const void *beta,
		    		const		float *y, int incy,
		    		void         *r);


extern void	FC_FUNC_(blas_cdot_c_s, BLAS_CDOT_C_S)
                (int *conj, int *n, const void *alpha, const void *x, int *incx, const void *beta, const float *y, int *incy, void *r)
{
  BLAS_cdot_c_s((enum blas_conj_type)*conj, *n, alpha,
		x, *incx, beta,
		y, *incy,
		r);
}
