#include "blas_extended.h"
#include "blas_extended_private.h"

/*
 * Purpose
 * =======
 *
 * Computes y = alpha * ap * x + beta * y, where ap is a hermitian
 * packed matrix.
 *
 * Arguments
 * =========
 *
 * order        (input) blas_order_type
 *              Order of ap; row or column major
 *
 * uplo         (input) blas_uplo_type
 *              Whether ap is upper or lower
 *
 * n            (input) int
 *              Dimension of ap and the length of vector x
 *
 * alpha        (input) const void*
 *
 * ap           (input) void*
 *
 * x            (input) float*
 *
 * incx         (input) int
 *              The stride for vector x.
 *
 * beta         (input) const void*
 *
 * y            (input/output) void*
 *
 * incy         (input) int
 *              The stride for vector y.
 *
 * prec   (input) enum blas_prec_type
 *        Specifies the internal precision to be used.
 *        = blas_prec_single: single precision.
 *        = blas_prec_double: double precision.
 *        = blas_prec_extra : anything at least 1.5 times as accurate
 *                            than double, and wider than 80-bits.
 *                            We use double-double in our implementation.
 *
 */
void		BLAS_chpmv_c_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
       		int		n       , const void *alpha, const void *ap,
		       		const		float *x, int incx, const void *beta, void *y,
				int		incy    , enum blas_prec_type prec)
{
  static const char routine_name[] = "BLAS_chpmv_c_s_x";

  switch (prec) {
  case blas_prec_single:{
      {
	enum blas_order_type order_i;

	float          *alpha_i = (float *)alpha;
	float          *beta_i = (float *)beta;
	int		matrix_row, step, ap_index, ap_start, x_index, x_start;
	int		y_start   , y_index, incap;

	const float    *ap_i = (float *)ap;
	const float    *x_i = x;
	float          *y_i = (float *)y;
	float		rowsum   [2];
	float		rowtmp   [2];
	float		matval   [2];
	float		vecval;
	float		resval   [2];
	float		tmp1     [2];
	float		tmp2     [2];


	if (n < 1)
	  return;
	if (alpha_i[0] == 0.0 && alpha_i[1] == 0.0 && (beta_i[0] == 1.0 && beta_i[1] == 0.0))
	  return;

	/* Check for error conditions. */
	if (order != blas_colmajor && order != blas_rowmajor)
	  BLAS_error(routine_name, -1, order, NULL);
	if (uplo != blas_upper && uplo != blas_lower)
	  BLAS_error(routine_name, -2, uplo, NULL);
	if (incx == 0)
	  BLAS_error(routine_name, -7, incx, NULL);
	if (incy == 0) {
	  BLAS_error(routine_name, -10, incy, NULL);
	}
	incap = 1;
	incap *= 2;

	incy *= 2;

	if (incx < 0)
	  x_start = (-n + 1) * incx;
	else
	  x_start = 0;
	if (incy < 0)
	  y_start = (-n + 1) * incy;
	else
	  y_start = 0;

	if (uplo == blas_lower)
	  order_i = (order == blas_rowmajor) ? blas_colmajor : blas_rowmajor;
	else
	  order_i = order;

	if (alpha_i[0] == 0.0 && alpha_i[1] == 0.0) {
	  {
	    y_index = y_start;
	    for (matrix_row = 0; matrix_row < n; matrix_row++) {
	      resval[0] = y_i[y_index];
	      resval[1] = y_i[y_index + 1];

	      {
		tmp2[0] = beta_i[0] * resval[0] - beta_i[1] * resval[1];
		tmp2[1] = beta_i[0] * resval[1] + beta_i[1] * resval[0];
	      }


	      y_i[y_index] = tmp2[0];
	      y_i[y_index + 1] = tmp2[1];
	      y_index += incy;
	    }
	  }
	} else {
	  if (order_i == blas_rowmajor) {
	    if ((alpha_i[0] == 1.0 && alpha_i[1] == 0.0)) {
	      if (beta_i[0] == 0.0 && beta_i[1] == 0.0) {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      } else {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      {
			tmp2[0] = beta_i[0] * resval[0] - beta_i[1] * resval[1];
			tmp2[1] = beta_i[0] * resval[1] + beta_i[1] * resval[0];
		      }

		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      {
			tmp2[0] = beta_i[0] * resval[0] - beta_i[1] * resval[1];
			tmp2[1] = beta_i[0] * resval[1] + beta_i[1] * resval[0];
		      }

		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      }
	    } else {
	      if (beta_i[0] == 0.0 && beta_i[1] == 0.0) {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      {
			tmp1[0] = rowsum[0] * alpha_i[0] - rowsum[1] * alpha_i[1];
			tmp1[1] = rowsum[0] * alpha_i[1] + rowsum[1] * alpha_i[0];
		      }

		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      {
			tmp1[0] = rowsum[0] * alpha_i[0] - rowsum[1] * alpha_i[1];
			tmp1[1] = rowsum[0] * alpha_i[1] + rowsum[1] * alpha_i[0];
		      }

		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      } else {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      {
			tmp1[0] = rowsum[0] * alpha_i[0] - rowsum[1] * alpha_i[1];
			tmp1[1] = rowsum[0] * alpha_i[1] + rowsum[1] * alpha_i[0];
		      }

		      {
			tmp2[0] = beta_i[0] * resval[0] - beta_i[1] * resval[1];
			tmp2[1] = beta_i[0] * resval[1] + beta_i[1] * resval[0];
		      }

		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      {
			tmp1[0] = rowsum[0] * alpha_i[0] - rowsum[1] * alpha_i[1];
			tmp1[1] = rowsum[0] * alpha_i[1] + rowsum[1] * alpha_i[0];
		      }

		      {
			tmp2[0] = beta_i[0] * resval[0] - beta_i[1] * resval[1];
			tmp2[1] = beta_i[0] * resval[1] + beta_i[1] * resval[0];
		      }

		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      }
	    }
	  } else {
	    if ((alpha_i[0] == 1.0 && alpha_i[1] == 0.0)) {
	      if (beta_i[0] == 0.0 && beta_i[1] == 0.0) {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      } else {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      {
			tmp2[0] = beta_i[0] * resval[0] - beta_i[1] * resval[1];
			tmp2[1] = beta_i[0] * resval[1] + beta_i[1] * resval[0];
		      }

		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      {
			tmp2[0] = beta_i[0] * resval[0] - beta_i[1] * resval[1];
			tmp2[1] = beta_i[0] * resval[1] + beta_i[1] * resval[0];
		      }

		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      }
	    } else {
	      if (beta_i[0] == 0.0 && beta_i[1] == 0.0) {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      {
			tmp1[0] = rowsum[0] * alpha_i[0] - rowsum[1] * alpha_i[1];
			tmp1[1] = rowsum[0] * alpha_i[1] + rowsum[1] * alpha_i[0];
		      }

		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      {
			tmp1[0] = rowsum[0] * alpha_i[0] - rowsum[1] * alpha_i[1];
			tmp1[1] = rowsum[0] * alpha_i[1] + rowsum[1] * alpha_i[0];
		      }

		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      } else {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      {
			tmp1[0] = rowsum[0] * alpha_i[0] - rowsum[1] * alpha_i[1];
			tmp1[1] = rowsum[0] * alpha_i[1] + rowsum[1] * alpha_i[0];
		      }

		      {
			tmp2[0] = beta_i[0] * resval[0] - beta_i[1] * resval[1];
			tmp2[1] = beta_i[0] * resval[1] + beta_i[1] * resval[0];
		      }

		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = vecval * matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = matval[0] * vecval;
			  rowtmp[1] = matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      {
			tmp1[0] = rowsum[0] * alpha_i[0] - rowsum[1] * alpha_i[1];
			tmp1[1] = rowsum[0] * alpha_i[1] + rowsum[1] * alpha_i[0];
		      }

		      {
			tmp2[0] = beta_i[0] * resval[0] - beta_i[1] * resval[1];
			tmp2[1] = beta_i[0] * resval[1] + beta_i[1] * resval[0];
		      }

		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      }
	    }
	  }
	}			/* end alpha != 0 */

      }
      break;
    }
  case blas_prec_indigenous:
  case blas_prec_double:{
      {
	enum blas_order_type order_i;

	float          *alpha_i = (float *)alpha;
	float          *beta_i = (float *)beta;
	int		matrix_row, step, ap_index, ap_start, x_index, x_start;
	int		y_start   , y_index, incap;

	const float    *ap_i = (float *)ap;
	const float    *x_i = x;
	float          *y_i = (float *)y;
	double		rowsum  [2];
	double		rowtmp  [2];
	float		matval   [2];
	float		vecval;
	float		resval   [2];
	double		tmp1    [2];
	double		tmp2    [2];


	if (n < 1)
	  return;
	if (alpha_i[0] == 0.0 && alpha_i[1] == 0.0 && (beta_i[0] == 1.0 && beta_i[1] == 0.0))
	  return;

	/* Check for error conditions. */
	if (order != blas_colmajor && order != blas_rowmajor)
	  BLAS_error(routine_name, -1, order, NULL);
	if (uplo != blas_upper && uplo != blas_lower)
	  BLAS_error(routine_name, -2, uplo, NULL);
	if (incx == 0)
	  BLAS_error(routine_name, -7, incx, NULL);
	if (incy == 0) {
	  BLAS_error(routine_name, -10, incy, NULL);
	}
	incap = 1;
	incap *= 2;

	incy *= 2;

	if (incx < 0)
	  x_start = (-n + 1) * incx;
	else
	  x_start = 0;
	if (incy < 0)
	  y_start = (-n + 1) * incy;
	else
	  y_start = 0;

	if (uplo == blas_lower)
	  order_i = (order == blas_rowmajor) ? blas_colmajor : blas_rowmajor;
	else
	  order_i = order;

	if (alpha_i[0] == 0.0 && alpha_i[1] == 0.0) {
	  {
	    y_index = y_start;
	    for (matrix_row = 0; matrix_row < n; matrix_row++) {
	      resval[0] = y_i[y_index];
	      resval[1] = y_i[y_index + 1];

	      {
		tmp2[0] = (double)beta_i[0] * resval[0] - (double)beta_i[1] * resval[1];
		tmp2[1] = (double)beta_i[0] * resval[1] + (double)beta_i[1] * resval[0];
	      }

	      y_i[y_index] = tmp2[0];
	      y_i[y_index + 1] = tmp2[1];
	      y_index += incy;
	    }
	  }
	} else {
	  if (order_i == blas_rowmajor) {
	    if ((alpha_i[0] == 1.0 && alpha_i[1] == 0.0)) {
	      if (beta_i[0] == 0.0 && beta_i[1] == 0.0) {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      } else {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      {
			tmp2[0] = (double)beta_i[0] * resval[0] - (double)beta_i[1] * resval[1];
			tmp2[1] = (double)beta_i[0] * resval[1] + (double)beta_i[1] * resval[0];
		      }
		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      {
			tmp2[0] = (double)beta_i[0] * resval[0] - (double)beta_i[1] * resval[1];
			tmp2[1] = (double)beta_i[0] * resval[1] + (double)beta_i[1] * resval[0];
		      }
		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      }
	    } else {
	      if (beta_i[0] == 0.0 && beta_i[1] == 0.0) {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      {
			tmp1[0] = (double)rowsum[0] * alpha_i[0] - (double)rowsum[1] * alpha_i[1];
			tmp1[1] = (double)rowsum[0] * alpha_i[1] + (double)rowsum[1] * alpha_i[0];
		      }
		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      {
			tmp1[0] = (double)rowsum[0] * alpha_i[0] - (double)rowsum[1] * alpha_i[1];
			tmp1[1] = (double)rowsum[0] * alpha_i[1] + (double)rowsum[1] * alpha_i[0];
		      }
		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      } else {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      {
			tmp1[0] = (double)rowsum[0] * alpha_i[0] - (double)rowsum[1] * alpha_i[1];
			tmp1[1] = (double)rowsum[0] * alpha_i[1] + (double)rowsum[1] * alpha_i[0];
		      }
		      {
			tmp2[0] = (double)beta_i[0] * resval[0] - (double)beta_i[1] * resval[1];
			tmp2[1] = (double)beta_i[0] * resval[1] + (double)beta_i[1] * resval[0];
		      }
		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      {
			tmp1[0] = (double)rowsum[0] * alpha_i[0] - (double)rowsum[1] * alpha_i[1];
			tmp1[1] = (double)rowsum[0] * alpha_i[1] + (double)rowsum[1] * alpha_i[0];
		      }
		      {
			tmp2[0] = (double)beta_i[0] * resval[0] - (double)beta_i[1] * resval[1];
			tmp2[1] = (double)beta_i[0] * resval[1] + (double)beta_i[1] * resval[0];
		      }
		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      }
	    }
	  } else {
	    if ((alpha_i[0] == 1.0 && alpha_i[1] == 0.0)) {
	      if (beta_i[0] == 0.0 && beta_i[1] == 0.0) {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      } else {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      {
			tmp2[0] = (double)beta_i[0] * resval[0] - (double)beta_i[1] * resval[1];
			tmp2[1] = (double)beta_i[0] * resval[1] + (double)beta_i[1] * resval[0];
		      }
		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      tmp1[0] = rowsum[0];
		      tmp1[1] = rowsum[1];
		      {
			tmp2[0] = (double)beta_i[0] * resval[0] - (double)beta_i[1] * resval[1];
			tmp2[1] = (double)beta_i[0] * resval[1] + (double)beta_i[1] * resval[0];
		      }
		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      }
	    } else {
	      if (beta_i[0] == 0.0 && beta_i[1] == 0.0) {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      {
			tmp1[0] = (double)rowsum[0] * alpha_i[0] - (double)rowsum[1] * alpha_i[1];
			tmp1[1] = (double)rowsum[0] * alpha_i[1] + (double)rowsum[1] * alpha_i[0];
		      }
		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      {
			tmp1[0] = (double)rowsum[0] * alpha_i[0] - (double)rowsum[1] * alpha_i[1];
			tmp1[1] = (double)rowsum[0] * alpha_i[1] + (double)rowsum[1] * alpha_i[0];
		      }
		      y_i[y_index] = tmp1[0];
		      y_i[y_index + 1] = tmp1[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      } else {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      {
			tmp1[0] = (double)rowsum[0] * alpha_i[0] - (double)rowsum[1] * alpha_i[1];
			tmp1[1] = (double)rowsum[0] * alpha_i[1] + (double)rowsum[1] * alpha_i[0];
		      }
		      {
			tmp2[0] = (double)beta_i[0] * resval[0] - (double)beta_i[1] * resval[1];
			tmp2[1] = (double)beta_i[0] * resval[1] + (double)beta_i[1] * resval[0];
		      }
		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      rowsum[0] = rowsum[1] = 0.0;
		      rowtmp[0] = rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      rowtmp[0] = (double)vecval *matval[0];
		      rowtmp[1] = 0.0;
		      rowsum[0] = rowsum[0] + rowtmp[0];
		      rowsum[1] = rowsum[1] + rowtmp[1];
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  rowtmp[0] = (double)matval[0] * vecval;
			  rowtmp[1] = (double)matval[1] * vecval;
			}
			rowsum[0] = rowsum[0] + rowtmp[0];
			rowsum[1] = rowsum[1] + rowtmp[1];
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      {
			tmp1[0] = (double)rowsum[0] * alpha_i[0] - (double)rowsum[1] * alpha_i[1];
			tmp1[1] = (double)rowsum[0] * alpha_i[1] + (double)rowsum[1] * alpha_i[0];
		      }
		      {
			tmp2[0] = (double)beta_i[0] * resval[0] - (double)beta_i[1] * resval[1];
			tmp2[1] = (double)beta_i[0] * resval[1] + (double)beta_i[1] * resval[0];
		      }
		      tmp2[0] = tmp1[0] + tmp2[0];
		      tmp2[1] = tmp1[1] + tmp2[1];
		      y_i[y_index] = tmp2[0];
		      y_i[y_index + 1] = tmp2[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      }
	    }
	  }
	}			/* end alpha != 0 */

      }
      break;
    }

  case blas_prec_extra:{
      {
	enum blas_order_type order_i;

	float          *alpha_i = (float *)alpha;
	float          *beta_i = (float *)beta;
	int		matrix_row, step, ap_index, ap_start, x_index, x_start;
	int		y_start   , y_index, incap;

	const float    *ap_i = (float *)ap;
	const float    *x_i = x;
	float          *y_i = (float *)y;
	double		head_rowsum[2], tail_rowsum[2];
	double		head_rowtmp[2], tail_rowtmp[2];
	float		matval   [2];
	float		vecval;
	float		resval   [2];
	double		head_tmp1[2], tail_tmp1[2];
	double		head_tmp2[2], tail_tmp2[2];
	FPU_FIX_DECL;

	if (n < 1)
	  return;
	if (alpha_i[0] == 0.0 && alpha_i[1] == 0.0 && (beta_i[0] == 1.0 && beta_i[1] == 0.0))
	  return;

	/* Check for error conditions. */
	if (order != blas_colmajor && order != blas_rowmajor)
	  BLAS_error(routine_name, -1, order, NULL);
	if (uplo != blas_upper && uplo != blas_lower)
	  BLAS_error(routine_name, -2, uplo, NULL);
	if (incx == 0)
	  BLAS_error(routine_name, -7, incx, NULL);
	if (incy == 0) {
	  BLAS_error(routine_name, -10, incy, NULL);
	}
	FPU_FIX_START;

	incap = 1;
	incap *= 2;

	incy *= 2;

	if (incx < 0)
	  x_start = (-n + 1) * incx;
	else
	  x_start = 0;
	if (incy < 0)
	  y_start = (-n + 1) * incy;
	else
	  y_start = 0;

	if (uplo == blas_lower)
	  order_i = (order == blas_rowmajor) ? blas_colmajor : blas_rowmajor;
	else
	  order_i = order;

	if (alpha_i[0] == 0.0 && alpha_i[1] == 0.0) {
	  {
	    y_index = y_start;
	    for (matrix_row = 0; matrix_row < n; matrix_row++) {
	      resval[0] = y_i[y_index];
	      resval[1] = y_i[y_index + 1];

	      {
		double		head_e1, tail_e1;
		double		d1;
		double		d2;
		/* Real part */
		d1 = (double)beta_i[0] * resval[0];
		d2 = (double)-beta_i[1] * resval[1];
		{
		  /* Compute double-double = double + double. */
		  double	  e     , t1, t2;

		  /* Knuth trick. */
		  t1 = d1 + d2;
		  e = t1 - d1;
		  t2 = ((d2 - e) + (d1 - (t1 - e)));

		  /* The result is t1 + t2, after normalization. */
		  head_e1 = t1 + t2;
		  tail_e1 = t2 - (head_e1 - t1);
		}
		head_tmp2[0] = head_e1;
		tail_tmp2[0] = tail_e1;
		/* imaginary part */
		d1 = (double)beta_i[0] * resval[1];
		d2 = (double)beta_i[1] * resval[0];
		{
		  /* Compute double-double = double + double. */
		  double	  e     , t1, t2;

		  /* Knuth trick. */
		  t1 = d1 + d2;
		  e = t1 - d1;
		  t2 = ((d2 - e) + (d1 - (t1 - e)));

		  /* The result is t1 + t2, after normalization. */
		  head_e1 = t1 + t2;
		  tail_e1 = t2 - (head_e1 - t1);
		}
		head_tmp2[1] = head_e1;
		tail_tmp2[1] = tail_e1;
	      }

	      y_i[y_index] = head_tmp2[0];
	      y_i[y_index + 1] = head_tmp2[1];
	      y_index += incy;
	    }
	  }
	} else {
	  if (order_i == blas_rowmajor) {
	    if ((alpha_i[0] == 1.0 && alpha_i[1] == 0.0)) {
	      if (beta_i[0] == 0.0 && beta_i[1] == 0.0) {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      head_tmp1[0] = head_rowsum[0];
		      tail_tmp1[0] = tail_rowsum[0];
		      head_tmp1[1] = head_rowsum[1];
		      tail_tmp1[1] = tail_rowsum[1];
		      y_i[y_index] = head_tmp1[0];
		      y_i[y_index + 1] = head_tmp1[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      head_tmp1[0] = head_rowsum[0];
		      tail_tmp1[0] = tail_rowsum[0];
		      head_tmp1[1] = head_rowsum[1];
		      tail_tmp1[1] = tail_rowsum[1];
		      y_i[y_index] = head_tmp1[0];
		      y_i[y_index + 1] = head_tmp1[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      } else {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      head_tmp1[0] = head_rowsum[0];
		      tail_tmp1[0] = tail_rowsum[0];
		      head_tmp1[1] = head_rowsum[1];
		      tail_tmp1[1] = tail_rowsum[1];
		      {
			double		head_e1, tail_e1;
			double		d1;
			double		d2;
			/* Real part */
			d1 = (double)beta_i[0] * resval[0];
			d2 = (double)-beta_i[1] * resval[1];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[0] = head_e1;
			tail_tmp2[0] = tail_e1;
			/* imaginary part */
			d1 = (double)beta_i[0] * resval[1];
			d2 = (double)beta_i[1] * resval[0];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[1] = head_e1;
			tail_tmp2[1] = tail_e1;
		      }
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_tmp1[0];
			tail_a = tail_tmp1[0];
			head_b = head_tmp2[0];
			tail_b = tail_tmp2[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[0] = head_t;
			tail_tmp2[0] = tail_t;
			/* Imaginary part */
			head_a = head_tmp1[1];
			tail_a = tail_tmp1[1];
			head_b = head_tmp2[1];
			tail_b = tail_tmp2[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[1] = head_t;
			tail_tmp2[1] = tail_t;
		      }
		      y_i[y_index] = head_tmp2[0];
		      y_i[y_index + 1] = head_tmp2[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      head_tmp1[0] = head_rowsum[0];
		      tail_tmp1[0] = tail_rowsum[0];
		      head_tmp1[1] = head_rowsum[1];
		      tail_tmp1[1] = tail_rowsum[1];
		      {
			double		head_e1, tail_e1;
			double		d1;
			double		d2;
			/* Real part */
			d1 = (double)beta_i[0] * resval[0];
			d2 = (double)-beta_i[1] * resval[1];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[0] = head_e1;
			tail_tmp2[0] = tail_e1;
			/* imaginary part */
			d1 = (double)beta_i[0] * resval[1];
			d2 = (double)beta_i[1] * resval[0];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[1] = head_e1;
			tail_tmp2[1] = tail_e1;
		      }
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_tmp1[0];
			tail_a = tail_tmp1[0];
			head_b = head_tmp2[0];
			tail_b = tail_tmp2[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[0] = head_t;
			tail_tmp2[0] = tail_t;
			/* Imaginary part */
			head_a = head_tmp1[1];
			tail_a = tail_tmp1[1];
			head_b = head_tmp2[1];
			tail_b = tail_tmp2[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[1] = head_t;
			tail_tmp2[1] = tail_t;
		      }
		      y_i[y_index] = head_tmp2[0];
		      y_i[y_index + 1] = head_tmp2[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      }
	    } else {
	      if (beta_i[0] == 0.0 && beta_i[1] == 0.0) {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      {
			double		cd      [2];
			cd[0] = (double)alpha_i[0];
			cd[1] = (double)alpha_i[1];
			{
			  /*
			   * Compute complex-extra = complex-extra *
			   * complex-double.
			   */
			  double	  head_a0, tail_a0;
			  double	  head_a1, tail_a1;
			  double	  head_t1, tail_t1;
			  double	  head_t2, tail_t2;
			  head_a0 = head_rowsum[0];
			  tail_a0 = tail_rowsum[0];
			  head_a1 = head_rowsum[1];
			  tail_a1 = tail_rowsum[1];
			  /* real part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a0 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a1 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  head_t2 = -head_t2;
			  tail_t2 = -tail_t2;
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[0] = head_t1;
			  tail_tmp1[0] = tail_t1;
			  /* imaginary part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a1 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a0 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[1] = head_t1;
			  tail_tmp1[1] = tail_t1;
			}

		      }
		      y_i[y_index] = head_tmp1[0];
		      y_i[y_index + 1] = head_tmp1[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      {
			double		cd      [2];
			cd[0] = (double)alpha_i[0];
			cd[1] = (double)alpha_i[1];
			{
			  /*
			   * Compute complex-extra = complex-extra *
			   * complex-double.
			   */
			  double	  head_a0, tail_a0;
			  double	  head_a1, tail_a1;
			  double	  head_t1, tail_t1;
			  double	  head_t2, tail_t2;
			  head_a0 = head_rowsum[0];
			  tail_a0 = tail_rowsum[0];
			  head_a1 = head_rowsum[1];
			  tail_a1 = tail_rowsum[1];
			  /* real part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a0 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a1 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  head_t2 = -head_t2;
			  tail_t2 = -tail_t2;
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[0] = head_t1;
			  tail_tmp1[0] = tail_t1;
			  /* imaginary part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a1 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a0 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[1] = head_t1;
			  tail_tmp1[1] = tail_t1;
			}

		      }
		      y_i[y_index] = head_tmp1[0];
		      y_i[y_index + 1] = head_tmp1[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      } else {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      {
			double		cd      [2];
			cd[0] = (double)alpha_i[0];
			cd[1] = (double)alpha_i[1];
			{
			  /*
			   * Compute complex-extra = complex-extra *
			   * complex-double.
			   */
			  double	  head_a0, tail_a0;
			  double	  head_a1, tail_a1;
			  double	  head_t1, tail_t1;
			  double	  head_t2, tail_t2;
			  head_a0 = head_rowsum[0];
			  tail_a0 = tail_rowsum[0];
			  head_a1 = head_rowsum[1];
			  tail_a1 = tail_rowsum[1];
			  /* real part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a0 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a1 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  head_t2 = -head_t2;
			  tail_t2 = -tail_t2;
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[0] = head_t1;
			  tail_tmp1[0] = tail_t1;
			  /* imaginary part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a1 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a0 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[1] = head_t1;
			  tail_tmp1[1] = tail_t1;
			}

		      }
		      {
			double		head_e1, tail_e1;
			double		d1;
			double		d2;
			/* Real part */
			d1 = (double)beta_i[0] * resval[0];
			d2 = (double)-beta_i[1] * resval[1];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[0] = head_e1;
			tail_tmp2[0] = tail_e1;
			/* imaginary part */
			d1 = (double)beta_i[0] * resval[1];
			d2 = (double)beta_i[1] * resval[0];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[1] = head_e1;
			tail_tmp2[1] = tail_e1;
		      }
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_tmp1[0];
			tail_a = tail_tmp1[0];
			head_b = head_tmp2[0];
			tail_b = tail_tmp2[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[0] = head_t;
			tail_tmp2[0] = tail_t;
			/* Imaginary part */
			head_a = head_tmp1[1];
			tail_a = tail_tmp1[1];
			head_b = head_tmp2[1];
			tail_b = tail_tmp2[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[1] = head_t;
			tail_tmp2[1] = tail_t;
		      }
		      y_i[y_index] = head_tmp2[0];
		      y_i[y_index + 1] = head_tmp2[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (n - step - 1) * incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      {
			double		cd      [2];
			cd[0] = (double)alpha_i[0];
			cd[1] = (double)alpha_i[1];
			{
			  /*
			   * Compute complex-extra = complex-extra *
			   * complex-double.
			   */
			  double	  head_a0, tail_a0;
			  double	  head_a1, tail_a1;
			  double	  head_t1, tail_t1;
			  double	  head_t2, tail_t2;
			  head_a0 = head_rowsum[0];
			  tail_a0 = tail_rowsum[0];
			  head_a1 = head_rowsum[1];
			  tail_a1 = tail_rowsum[1];
			  /* real part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a0 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a1 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  head_t2 = -head_t2;
			  tail_t2 = -tail_t2;
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[0] = head_t1;
			  tail_tmp1[0] = tail_t1;
			  /* imaginary part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a1 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a0 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[1] = head_t1;
			  tail_tmp1[1] = tail_t1;
			}

		      }
		      {
			double		head_e1, tail_e1;
			double		d1;
			double		d2;
			/* Real part */
			d1 = (double)beta_i[0] * resval[0];
			d2 = (double)-beta_i[1] * resval[1];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[0] = head_e1;
			tail_tmp2[0] = tail_e1;
			/* imaginary part */
			d1 = (double)beta_i[0] * resval[1];
			d2 = (double)beta_i[1] * resval[0];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[1] = head_e1;
			tail_tmp2[1] = tail_e1;
		      }
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_tmp1[0];
			tail_a = tail_tmp1[0];
			head_b = head_tmp2[0];
			tail_b = tail_tmp2[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[0] = head_t;
			tail_tmp2[0] = tail_t;
			/* Imaginary part */
			head_a = head_tmp1[1];
			tail_a = tail_tmp1[1];
			head_b = head_tmp2[1];
			tail_b = tail_tmp2[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[1] = head_t;
			tail_tmp2[1] = tail_t;
		      }
		      y_i[y_index] = head_tmp2[0];
		      y_i[y_index + 1] = head_tmp2[1];
		      y_index += incy;
		      ap_start += incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      }
	    }
	  } else {
	    if ((alpha_i[0] == 1.0 && alpha_i[1] == 0.0)) {
	      if (beta_i[0] == 0.0 && beta_i[1] == 0.0) {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      head_tmp1[0] = head_rowsum[0];
		      tail_tmp1[0] = tail_rowsum[0];
		      head_tmp1[1] = head_rowsum[1];
		      tail_tmp1[1] = tail_rowsum[1];
		      y_i[y_index] = head_tmp1[0];
		      y_i[y_index + 1] = head_tmp1[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      head_tmp1[0] = head_rowsum[0];
		      tail_tmp1[0] = tail_rowsum[0];
		      head_tmp1[1] = head_rowsum[1];
		      tail_tmp1[1] = tail_rowsum[1];
		      y_i[y_index] = head_tmp1[0];
		      y_i[y_index + 1] = head_tmp1[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      } else {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      head_tmp1[0] = head_rowsum[0];
		      tail_tmp1[0] = tail_rowsum[0];
		      head_tmp1[1] = head_rowsum[1];
		      tail_tmp1[1] = tail_rowsum[1];
		      {
			double		head_e1, tail_e1;
			double		d1;
			double		d2;
			/* Real part */
			d1 = (double)beta_i[0] * resval[0];
			d2 = (double)-beta_i[1] * resval[1];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[0] = head_e1;
			tail_tmp2[0] = tail_e1;
			/* imaginary part */
			d1 = (double)beta_i[0] * resval[1];
			d2 = (double)beta_i[1] * resval[0];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[1] = head_e1;
			tail_tmp2[1] = tail_e1;
		      }
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_tmp1[0];
			tail_a = tail_tmp1[0];
			head_b = head_tmp2[0];
			tail_b = tail_tmp2[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[0] = head_t;
			tail_tmp2[0] = tail_t;
			/* Imaginary part */
			head_a = head_tmp1[1];
			tail_a = tail_tmp1[1];
			head_b = head_tmp2[1];
			tail_b = tail_tmp2[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[1] = head_t;
			tail_tmp2[1] = tail_t;
		      }
		      y_i[y_index] = head_tmp2[0];
		      y_i[y_index + 1] = head_tmp2[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      head_tmp1[0] = head_rowsum[0];
		      tail_tmp1[0] = tail_rowsum[0];
		      head_tmp1[1] = head_rowsum[1];
		      tail_tmp1[1] = tail_rowsum[1];
		      {
			double		head_e1, tail_e1;
			double		d1;
			double		d2;
			/* Real part */
			d1 = (double)beta_i[0] * resval[0];
			d2 = (double)-beta_i[1] * resval[1];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[0] = head_e1;
			tail_tmp2[0] = tail_e1;
			/* imaginary part */
			d1 = (double)beta_i[0] * resval[1];
			d2 = (double)beta_i[1] * resval[0];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[1] = head_e1;
			tail_tmp2[1] = tail_e1;
		      }
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_tmp1[0];
			tail_a = tail_tmp1[0];
			head_b = head_tmp2[0];
			tail_b = tail_tmp2[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[0] = head_t;
			tail_tmp2[0] = tail_t;
			/* Imaginary part */
			head_a = head_tmp1[1];
			tail_a = tail_tmp1[1];
			head_b = head_tmp2[1];
			tail_b = tail_tmp2[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[1] = head_t;
			tail_tmp2[1] = tail_t;
		      }
		      y_i[y_index] = head_tmp2[0];
		      y_i[y_index + 1] = head_tmp2[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      }
	    } else {
	      if (beta_i[0] == 0.0 && beta_i[1] == 0.0) {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      {
			double		cd      [2];
			cd[0] = (double)alpha_i[0];
			cd[1] = (double)alpha_i[1];
			{
			  /*
			   * Compute complex-extra = complex-extra *
			   * complex-double.
			   */
			  double	  head_a0, tail_a0;
			  double	  head_a1, tail_a1;
			  double	  head_t1, tail_t1;
			  double	  head_t2, tail_t2;
			  head_a0 = head_rowsum[0];
			  tail_a0 = tail_rowsum[0];
			  head_a1 = head_rowsum[1];
			  tail_a1 = tail_rowsum[1];
			  /* real part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a0 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a1 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  head_t2 = -head_t2;
			  tail_t2 = -tail_t2;
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[0] = head_t1;
			  tail_tmp1[0] = tail_t1;
			  /* imaginary part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a1 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a0 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[1] = head_t1;
			  tail_tmp1[1] = tail_t1;
			}

		      }
		      y_i[y_index] = head_tmp1[0];
		      y_i[y_index + 1] = head_tmp1[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      {
			double		cd      [2];
			cd[0] = (double)alpha_i[0];
			cd[1] = (double)alpha_i[1];
			{
			  /*
			   * Compute complex-extra = complex-extra *
			   * complex-double.
			   */
			  double	  head_a0, tail_a0;
			  double	  head_a1, tail_a1;
			  double	  head_t1, tail_t1;
			  double	  head_t2, tail_t2;
			  head_a0 = head_rowsum[0];
			  tail_a0 = tail_rowsum[0];
			  head_a1 = head_rowsum[1];
			  tail_a1 = tail_rowsum[1];
			  /* real part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a0 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a1 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  head_t2 = -head_t2;
			  tail_t2 = -tail_t2;
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[0] = head_t1;
			  tail_tmp1[0] = tail_t1;
			  /* imaginary part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a1 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a0 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[1] = head_t1;
			  tail_tmp1[1] = tail_t1;
			}

		      }
		      y_i[y_index] = head_tmp1[0];
		      y_i[y_index + 1] = head_tmp1[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      } else {
		{
		  y_index = y_start;
		  ap_start = 0;
		  if (uplo == blas_upper) {
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      {
			double		cd      [2];
			cd[0] = (double)alpha_i[0];
			cd[1] = (double)alpha_i[1];
			{
			  /*
			   * Compute complex-extra = complex-extra *
			   * complex-double.
			   */
			  double	  head_a0, tail_a0;
			  double	  head_a1, tail_a1;
			  double	  head_t1, tail_t1;
			  double	  head_t2, tail_t2;
			  head_a0 = head_rowsum[0];
			  tail_a0 = tail_rowsum[0];
			  head_a1 = head_rowsum[1];
			  tail_a1 = tail_rowsum[1];
			  /* real part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a0 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a1 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  head_t2 = -head_t2;
			  tail_t2 = -tail_t2;
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[0] = head_t1;
			  tail_tmp1[0] = tail_t1;
			  /* imaginary part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a1 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a0 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[1] = head_t1;
			  tail_tmp1[1] = tail_t1;
			}

		      }
		      {
			double		head_e1, tail_e1;
			double		d1;
			double		d2;
			/* Real part */
			d1 = (double)beta_i[0] * resval[0];
			d2 = (double)-beta_i[1] * resval[1];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[0] = head_e1;
			tail_tmp2[0] = tail_e1;
			/* imaginary part */
			d1 = (double)beta_i[0] * resval[1];
			d2 = (double)beta_i[1] * resval[0];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[1] = head_e1;
			tail_tmp2[1] = tail_e1;
		      }
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_tmp1[0];
			tail_a = tail_tmp1[0];
			head_b = head_tmp2[0];
			tail_b = tail_tmp2[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[0] = head_t;
			tail_tmp2[0] = tail_t;
			/* Imaginary part */
			head_a = head_tmp1[1];
			tail_a = tail_tmp1[1];
			head_b = head_tmp2[1];
			tail_b = tail_tmp2[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[1] = head_t;
			tail_tmp2[1] = tail_t;
		      }
		      y_i[y_index] = head_tmp2[0];
		      y_i[y_index + 1] = head_tmp2[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  } else {	/* if uplo == ... */
		    for (matrix_row = 0; matrix_row < n; matrix_row++) {
		      x_index = x_start;
		      ap_index = ap_start;
		      head_rowsum[0] = head_rowsum[1] = tail_rowsum[0] = tail_rowsum[1] = 0.0;
		      head_rowtmp[0] = head_rowtmp[1] = tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      for (step = 0; step < matrix_row; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];

			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += incap;
			x_index += incx;
		      }
		      /*
		       * need to do diagonal element without referencing the
		       * imaginary part
		       */
		      matval[0] = ap_i[ap_index];
		      vecval = x_i[x_index];
		      head_rowtmp[0] = (double)vecval *matval[0];
		      head_rowtmp[1] = 0.0;
		      tail_rowtmp[0] = tail_rowtmp[1] = 0.0;
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_rowsum[0];
			tail_a = tail_rowsum[0];
			head_b = head_rowtmp[0];
			tail_b = tail_rowtmp[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[0] = head_t;
			tail_rowsum[0] = tail_t;
			/* Imaginary part */
			head_a = head_rowsum[1];
			tail_a = tail_rowsum[1];
			head_b = head_rowtmp[1];
			tail_b = tail_rowtmp[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_rowsum[1] = head_t;
			tail_rowsum[1] = tail_t;
		      }
		      ap_index += (step + 1) * incap;
		      x_index += incx;
		      for (step = matrix_row + 1; step < n; step++) {
			matval[0] = ap_i[ap_index];
			matval[1] = ap_i[ap_index + 1];
			vecval = x_i[x_index];
			matval[1] = -matval[1];
			{
			  head_rowtmp[0] = (double)matval[0] * vecval;
			  tail_rowtmp[0] = 0.0;
			  head_rowtmp[1] = (double)matval[1] * vecval;
			  tail_rowtmp[1] = 0.0;
			}
			{
			  double	  head_t, tail_t;
			  double	  head_a, tail_a;
			  double	  head_b, tail_b;
			  /* Real part */
			  head_a = head_rowsum[0];
			  tail_a = tail_rowsum[0];
			  head_b = head_rowtmp[0];
			  tail_b = tail_rowtmp[0];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[0] = head_t;
			  tail_rowsum[0] = tail_t;
			  /* Imaginary part */
			  head_a = head_rowsum[1];
			  tail_a = tail_rowsum[1];
			  head_b = head_rowtmp[1];
			  tail_b = tail_rowtmp[1];
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_a + head_b;
			    bv = s1 - head_a;
			    s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_a + tail_b;
			    bv = t1 - tail_a;
			    t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t = t1 + t2;
			    tail_t = t2 - (head_t - t1);
			  }
			  head_rowsum[1] = head_t;
			  tail_rowsum[1] = tail_t;
			}
			ap_index += (step + 1) * incap;
			x_index += incx;
		      }
		      resval[0] = y_i[y_index];
		      resval[1] = y_i[y_index + 1];
		      {
			double		cd      [2];
			cd[0] = (double)alpha_i[0];
			cd[1] = (double)alpha_i[1];
			{
			  /*
			   * Compute complex-extra = complex-extra *
			   * complex-double.
			   */
			  double	  head_a0, tail_a0;
			  double	  head_a1, tail_a1;
			  double	  head_t1, tail_t1;
			  double	  head_t2, tail_t2;
			  head_a0 = head_rowsum[0];
			  tail_a0 = tail_rowsum[0];
			  head_a1 = head_rowsum[1];
			  tail_a1 = tail_rowsum[1];
			  /* real part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a0 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a1 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  head_t2 = -head_t2;
			  tail_t2 = -tail_t2;
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[0] = head_t1;
			  tail_tmp1[0] = tail_t1;
			  /* imaginary part */
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a1 * split;
			    a11 = con - head_a1;
			    a11 = con - a11;
			    a21 = head_a1 - a11;
			    con = cd[0] * split;
			    b1 = con - cd[0];
			    b1 = con - b1;
			    b2 = cd[0] - b1;

			    c11 = head_a1 * cd[0];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a1 * cd[0];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double *
			     * double.
			     */
			    double	    a11 , a21, b1, b2, c11, c21, c2,
			    		    con      , t1, t2;

			    con = head_a0 * split;
			    a11 = con - head_a0;
			    a11 = con - a11;
			    a21 = head_a0 - a11;
			    con = cd[1] * split;
			    b1 = con - cd[1];
			    b1 = con - b1;
			    b2 = cd[1] - b1;

			    c11 = head_a0 * cd[1];
			    c21 = (((a11 * b1 - c11) + a11 * b2) + a21 * b1) + a21 * b2;

			    c2 = tail_a0 * cd[1];
			    t1 = c11 + c2;
			    t2 = (c2 - (t1 - c11)) + c21;

			    head_t2 = t1 + t2;
			    tail_t2 = t2 - (head_t2 - t1);
			  }
			  {
			    /*
			     * Compute double-double = double-double +
			     * double-double.
			     */
			    double	    bv;
			    double	    s1  , s2, t1, t2;

			    /* Add two hi words. */
			    s1 = head_t1 + head_t2;
			    bv = s1 - head_t1;
			    s2 = ((head_t2 - bv) + (head_t1 - (s1 - bv)));

			    /* Add two lo words. */
			    t1 = tail_t1 + tail_t2;
			    bv = t1 - tail_t1;
			    t2 = ((tail_t2 - bv) + (tail_t1 - (t1 - bv)));

			    s2 += t1;

			    /* Renormalize (s1, s2)  to  (t1, s2) */
			    t1 = s1 + s2;
			    s2 = s2 - (t1 - s1);

			    t2 += s2;

			    /* Renormalize (t1, t2)  */
			    head_t1 = t1 + t2;
			    tail_t1 = t2 - (head_t1 - t1);
			  }
			  head_tmp1[1] = head_t1;
			  tail_tmp1[1] = tail_t1;
			}

		      }
		      {
			double		head_e1, tail_e1;
			double		d1;
			double		d2;
			/* Real part */
			d1 = (double)beta_i[0] * resval[0];
			d2 = (double)-beta_i[1] * resval[1];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[0] = head_e1;
			tail_tmp2[0] = tail_e1;
			/* imaginary part */
			d1 = (double)beta_i[0] * resval[1];
			d2 = (double)beta_i[1] * resval[0];
			{
			  /* Compute double-double = double + double. */
			  double	  e     , t1, t2;

			  /* Knuth trick. */
			  t1 = d1 + d2;
			  e = t1 - d1;
			  t2 = ((d2 - e) + (d1 - (t1 - e)));

			  /* The result is t1 + t2, after normalization. */
			  head_e1 = t1 + t2;
			  tail_e1 = t2 - (head_e1 - t1);
			}
			head_tmp2[1] = head_e1;
			tail_tmp2[1] = tail_e1;
		      }
		      {
			double		head_t , tail_t;
			double		head_a , tail_a;
			double		head_b , tail_b;
			/* Real part */
			head_a = head_tmp1[0];
			tail_a = tail_tmp1[0];
			head_b = head_tmp2[0];
			tail_b = tail_tmp2[0];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[0] = head_t;
			tail_tmp2[0] = tail_t;
			/* Imaginary part */
			head_a = head_tmp1[1];
			tail_a = tail_tmp1[1];
			head_b = head_tmp2[1];
			tail_b = tail_tmp2[1];
			{
			  /*
			   * Compute double-double = double-double +
			   * double-double.
			   */
			  double	  bv;
			  double	  s1    , s2, t1, t2;

			  /* Add two hi words. */
			  s1 = head_a + head_b;
			  bv = s1 - head_a;
			  s2 = ((head_b - bv) + (head_a - (s1 - bv)));

			  /* Add two lo words. */
			  t1 = tail_a + tail_b;
			  bv = t1 - tail_a;
			  t2 = ((tail_b - bv) + (tail_a - (t1 - bv)));

			  s2 += t1;

			  /* Renormalize (s1, s2)  to  (t1, s2) */
			  t1 = s1 + s2;
			  s2 = s2 - (t1 - s1);

			  t2 += s2;

			  /* Renormalize (t1, t2)  */
			  head_t = t1 + t2;
			  tail_t = t2 - (head_t - t1);
			}
			head_tmp2[1] = head_t;
			tail_tmp2[1] = tail_t;
		      }
		      y_i[y_index] = head_tmp2[0];
		      y_i[y_index + 1] = head_tmp2[1];
		      y_index += incy;
		      ap_start += (matrix_row + 1) * incap;
		    }
		  }		/* end if uplo == blas_upper ... */
		}
	      }
	    }
	  }
	}			/* end alpha != 0 */
	FPU_FIX_STOP;
      }
      break;
    }
  }
}