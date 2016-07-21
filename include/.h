#ifndef BLAS_DENSE_PROTO_H
#define BLAS_DENSE_PROTO_H

  /* Chapter 2 prototypes */

  /* Reduction Operations */

void BLAS_sdot( enum blas_conj_type conj, int n, float alpha,
                const float *x, int incx, float beta, const float *y,
                int incy, float *r );
void BLAS_ddot( enum blas_conj_type conj, int n, double alpha,
                const double *x, int incx, double beta, const double *y,
                int incy, double *r );
void BLAS_cdot( enum blas_conj_type conj, int n, const void *alpha,
                const void *x, int incx, const void *beta, const void *y,
                int incy, void *r );
void BLAS_zdot( enum blas_conj_type conj, int n, const void *alpha,
                const void *x, int incx, const void *beta, const void *y,
                int incy, void *r );

void BLAS_snorm( enum blas_norm_type norm, int n, const float *x, int incx,
                 float *r );
void BLAS_dnorm( enum blas_norm_type norm, int n, const double *x, int incx,
                 double *r );
void BLAS_cnorm( enum blas_norm_type norm, int n, const void *x, int incx,
                 float *r );
void BLAS_znorm( enum blas_norm_type norm, int n, const void *x, int incx,
                 double *r );

void BLAS_ssum( int n, const float *x, int incx, float *sum );
void BLAS_dsum( int n, const double *x, int incx, double *sum );
void BLAS_csum( int n, const void *x, int incx, void *sum );
void BLAS_zsum( int n, const void *x, int incx, void *sum );

void BLAS_smin_val( int n, const float *x, int incx, int k, float *r );
void BLAS_dmin_val( int n, const double *x, int incx, int k, double *r );

void BLAS_samin_val( int n, const float *x, int incx, int k, float *r );
void BLAS_damin_val( int n, const double *x, int incx, int k, double *r );
void BLAS_camin_val( int n, const void *x, int incx, int k, float *r );
void BLAS_zamin_val( int n, const void *x, int incx, int k, double *r );

void BLAS_smax_val( int n, const float *x, int incx, int k, float *r );
void BLAS_dmax_val( int n, const double *x, int incx, int k, double *r );

void BLAS_samax_val( int n, const float *x, int incx, int k, float *r );
void BLAS_damax_val( int n, const double *x, int incx, int k, double *r );
void BLAS_camax_val( int n, const void *x, int incx, int k, float *r );
void BLAS_zamax_val( int n, const void *x, int incx, int k, double *r );

void BLAS_ssumsq( int n, const float *x, int incx, float *ssq, float *scl );
void BLAS_dsumsq( int n, const double *x, int incx, double *ssq,
                  double *scl );
void BLAS_csumsq( int n, const void *x, int incx, float *ssq, float *scl );
void BLAS_zsumsq( int n, const void *x, int incx, double *ssq, double *scl );

  /* Generate Transformations */

void BLAS_sgen_grot( float a, float b, float *c, float *s, float *r );
void BLAS_dgen_grot( double a, double b, double *c, double *s, double *r );
void BLAS_cgen_grot( const void *a, const void *b, float *c, void *s,
                     void *r );
void BLAS_zgen_grot( const void *a, const void *b, double *c, void *s,
                     void *r );

void BLAS_sgen_jrot( enum blas_jrot_type jrot, float *x, float y,
                     float *z, float *c, float *s );
void BLAS_dgen_jrot( enum blas_jrot_type jrot, double *x, double y,
                     double *z, double *c, double *s );
void BLAS_cgen_jrot( enum blas_jrot_type jrot, float *x, const void *y,
                     float *z, float *c, void *s );
void BLAS_zgen_jrot( enum blas_jrot_type jrot, double *x, const void *y,
                     double *z, double *c, void *s );

void BLAS_sgen_house( int n, float *alpha, float *x, int incx, float *tau );
void BLAS_dgen_house( int n, double *alpha, double *x, int incx,
                      double *tau );
void BLAS_cgen_house( int n, void *alpha, void *x, int incx, void *tau );
void BLAS_zgen_house( int n, void *alpha, void *x, int incx, void *tau );

  /* Vector Operations */

void BLAS_srscale( int n, float alpha, float *x, int incx );
void BLAS_drscale( int n, double alpha, double *x, int incx );
void BLAS_crscale( int n, float alpha, void *x, int incx );
void BLAS_zrscale( int n, double alpha, void *x, int incx );

void BLAS_saxpby( int n, float alpha, const float *x, int incx,
                  float beta, float *y, int incy );
void BLAS_daxpby( int n, double alpha, const double *x, int incx,
                  double beta, double *y, int incy );
void BLAS_caxpby( int n, const void *alpha, const void *x, int incx,
                  const void *beta, void *y, int incy );
void BLAS_zaxpby( int n, const void *alpha, const void *x, int incx,
                  const void *beta, void *y, int incy );

void BLAS_swaxpby( int n, float alpha, const float *x, int incx,
                   float beta, const float *y, int incy, float *w,
                   int incw );
void BLAS_dwaxpby( int n, double alpha, const double *x, int incx,
                   double beta, const double *y, int incy, double *w,
                   int incw );
void BLAS_cwaxpby( int n, const void *alpha, const void *x, int incx,
                   const void *beta, const void *y, int incy, void *w,
                   int incw );
void BLAS_zwaxpby( int n, const void *alpha, const void *x, int incx,
                   const void *beta, const void *y, int incy, void *w,
                   int incw );

void BLAS_saxpy_dot( int n, float alpha, float *w, int incw, const float *v,
                     int incv, const float *u, int incu, float *r );
void BLAS_daxpy_dot( int n, double alpha, double *w, int incw,
                     const double *v, int incv, const double *u,
                     int incu, double *r );
void BLAS_caxpy_dot( int n, const void *alpha, void *w, int incw,
                     const void *v, int incv, const void *u, int incu,
                     void *r );
void BLAS_zaxpy_dot( int n, const void *alpha, void *w, int incw,
                     const void *v, int incv, const void *u, int incu, 
                     void *r );

void BLAS_sapply_grot( int n, float c, float s, float *x, int incx,
                       float *y, int incy );
void BLAS_dapply_grot( int n, double c, double s, double *x, int incx,
                       double *y, int incy );
void BLAS_capply_grot( int n, float c, const void *s, void *x, int incx,
                       void *y, int incy );
void BLAS_zapply_grot( int n, double c, const void *s, void *x, int incx,
                       void *y, int incy );

  /* Data Movement with Vectors */

void BLAS_scopy( int n, const float *x, int incx, float *y, int incy );
void BLAS_dcopy( int n, const double *x, int incx, double *y, int incy );
void BLAS_ccopy( int n, const void *x, int incx, void *y, int incy );
void BLAS_zcopy( int n, const void *x, int incx, void *y, int incy );

void BLAS_sswap( int n, float *x, int incx, float *y, int incy );
void BLAS_dswap( int n, double *x, int incx, double *y, int incy );
void BLAS_cswap( int n, void *x, int incx, void *y, int incy );
void BLAS_zswap( int n, void *x, int incx, void *y, int incy );

void BLAS_ssort( enum blas_sort_type sort, int n, float *x, int incx );
void BLAS_dsort( enum blas_sort_type sort, int n, double *x, int incx );

void BLAS_ssortv( enum blas_sort_type sort, int n, float *x, int incx,
                  int *p, int incp );
void BLAS_dsortv( enum blas_sort_type sort, int n, double *x, int incx,
                  int *p, int incp );

void BLAS_spermute( int n, const int *p, int incp, float *x, int incx );
void BLAS_dpermute( int n, const int *p, int incp, double *x, int incx );
void BLAS_cpermute( int n, const int *p, int incp, void *x, int incx );
void BLAS_zpermute( int n, const int *p, int incp, void *x, int incx );

  /* Matrix-Vector Operations */

void BLAS_sgemv( enum blas_order_type order, enum blas_trans_type trans,
                 int m, int n, float alpha, const float *a, int lda,
                 const float *x, int incx, float beta, float *y, int incy );
void BLAS_dgemv( enum blas_order_type order, enum blas_trans_type trans,
                 int m, int n, double alpha, const double *a, int lda,
                 const double *x, int incx, double beta, double *y,
                 int incy );
void BLAS_cgemv( enum blas_order_type order, enum blas_trans_type trans,
                 int m, int n, const void *alpha, const void *a, int lda,
                 const void *x, int incx, const void *beta, void *y,
                 int incy );
void BLAS_zgemv( enum blas_order_type order, enum blas_trans_type trans,
                 int m, int n, const void *alpha, const void *a, int lda,
                 const void *x, int incx, const void *beta, void *y,
                 int incy );

void BLAS_sgbmv( enum blas_order_type order, enum blas_trans_type trans,
                 int m, int n, int kl, int ku, float alpha, const float *a,
                 int lda, const float *x, int incx, float beta,
                 float *y, int incy );
void BLAS_dgbmv( enum blas_order_type order, enum blas_trans_type trans,
                 int m, int n, int kl, int ku, double alpha, const double *a,
                 int lda, const double *x, int incx, double beta,
                 double *y, int incy );
void BLAS_cgbmv( enum blas_order_type order, enum blas_trans_type trans,
                 int m, int n, int kl, int ku, const void *alpha,
                 const void *a, int lda, const void *x, int incx,
                 const void *beta, void *y, int incy );
void BLAS_zgbmv( enum blas_order_type order, enum blas_trans_type trans,
                 int m, int n, int kl, int ku, const void *alpha,
                 const void *a, int lda, const void *x, int incx,
                 const void *beta, void *y, int incy );

void BLAS_ssymv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, float alpha, const float *a, int lda,
                 const float *x, int incx, float beta, float *y, int incy );
void BLAS_dsymv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, double alpha, const double *a, int lda,
                 const double *x, int incx, double beta, double *y,
                 int incy );
void BLAS_csymv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, const void *alpha, const void *a, int lda,
                 const void *x, int incx, const void *beta, void *y,
                 int incy );
void BLAS_zsymv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, const void *alpha, const void *a, int lda,
                 const void *x, int incx, const void *beta, void *y,
                 int incy );

void BLAS_ssbmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, int k, float alpha, const float *a, int lda,
                 const float *x, int incx, float beta, float *y, int incy );
void BLAS_dsbmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, int k, double alpha, const double *a, int lda,
                 const double *x, int incx, double beta, double *y,
                 int incy );
void BLAS_csbmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, int k, const void *alpha, const void *a, int lda,
                 const void *x, int incx, const void *beta, void *y,
                 int incy );
void BLAS_zsbmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, int k, const void *alpha, const void *a, int lda,
                 const void *x, int incx, const void *beta, void *y,
                 int incy );

void BLAS_sspmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, float alpha, const float *ap, const float *x,
                 int incx, float beta, float *y, int incy );
void BLAS_dspmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, double alpha, const double *ap, const double *x,
                 int incx, double beta, double *y, int incy );
void BLAS_cspmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, const void *alpha, const void *ap, const void *x,
                 int incx, const void *beta, void *y, int incy );
void BLAS_zspmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, const void *alpha, const void *ap, const void *x,
                 int incx, const void *beta, void *y, int incy );

void BLAS_chemv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, const void *alpha, const void *a, int lda,
                 const void *x, int incx, const void *beta, void *y,
                 int incy );
void BLAS_zhemv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, const void *alpha, const void *a, int lda,
                 const void *x, int incx, const void *beta, void *y,
                 int incy );

void BLAS_chbmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, int k, const void *alpha, const void *a, int lda,
                 const void *x, int incx, const void *beta, void *y,
                 int incy );
void BLAS_zhbmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, int k, const void *alpha, const void *a, int lda,
                 const void *x, int incx, const void *beta, void *y,
                 int incy );

void BLAS_chpmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, const void *alpha, const void *ap, const void *x,
                 int incx, const void *beta, void *y, int incy );
void BLAS_zhpmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 int n, const void *alpha, const void *ap, const void *x,
                 int incx, const void *beta, void *y, int incy );

void BLAS_strmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, float alpha, const float *t, int ldt, float *x,
                 int incx );
void BLAS_dtrmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, double alpha, const double *t, int ldt, double *x,
                 int incx );
void BLAS_ctrmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, const void *alpha, const void *t, int ldt, void *x,
                 int incx );
void BLAS_ztrmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, const void *alpha, const void *t, int ldt, void *x,
                 int incx );

void BLAS_stbmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, int k, float alpha, const float *t, int ldt,
                 float *x, int incx );
void BLAS_dtbmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, int k, double alpha, const double *t, int ldt,
                 double *x, int incx );
void BLAS_ctbmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, int k, const void *alpha, const void *t, int ldt,
                 void *x, int incx );
void BLAS_ztbmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, int k, const void *alpha, const void *t, int ldt,
                 void *x, int incx );

void BLAS_stpmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, float alpha, const float *tp, float *x, int incx );
void BLAS_dtpmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, double alpha, const double *tp, double *x,
                 int incx );
void BLAS_ctpmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, const void *alpha, const void *tp, void *x, 
                 int incx );
void BLAS_ztpmv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, const void *alpha, const void *tp, void *x,
                 int incx );

void BLAS_sge_sum_mv( enum blas_order_type order, int m, int n,
                      float alpha, const float *a, int lda, const float *x,
                      int incx, float beta, const float *B, int ldb,
                      float *y, int incy );
void BLAS_dge_sum_mv( enum blas_order_type order, int m, int n,
                      double alpha, const double *a, int lda,
                      const double *x, int incx, double beta,
                      const double *B, int ldb, double *y, int incy );
void BLAS_cge_sum_mv( enum blas_order_type order, int m, int n,
                      const void *alpha, const void *a, int lda,
                      const void *x, int incx, const void *beta,
                      const void *B, int ldb, void *y, int incy );
void BLAS_zge_sum_mv( enum blas_order_type order, int m, int n,
                      const void *alpha, const void *a, int lda,
                      const void *x, int incx, const void *beta,
                      const void *B, int ldb, void *y, int incy );

void BLAS_sgemvt( enum blas_order_type order, int m, int n, float alpha,
                  const float *a, int lda, float *x, int incx,
                  const float *y, int incy, float beta, float *w, int incw,
                  const float *z, int incz );
void BLAS_dgemvt( enum blas_order_type order, int m, int n, double alpha,
                  const double *a, int lda, double *x, int incx,
                  const double *y, int incy, double beta, double *w,
                  int incw, const double *z, int incz );
void BLAS_cgemvt( enum blas_order_type order, int m, int n,
                  const void *alpha, const void *a, int lda, void *x,
                  int incx, const void *y, int incy, const void *beta,
                  void *w, int incw, const void *z, int incz );
void BLAS_zgemvt( enum blas_order_type order, int m, int n,
                  const void *alpha, const void *a, int lda, void *x,
                  int incx, const void *y, int incy, const void *beta,
                  void *w, int incw, const void *z, int incz );

void BLAS_strmvt( enum blas_order_type order, enum blas_uplo_type uplo,
                  int n, const float *t, int ldt, float *x, int incx,
                  const float *y, int incy, float *w, int incw,
                  const float *z, int incz );
void BLAS_dtrmvt( enum blas_order_type order, enum blas_uplo_type uplo,
                  int n, const float *t, int ldt, float *x, int incx,
                  const float *y, int incy, float *w, int incw,
                  const float *z, int incz );
void BLAS_ctrmvt( enum blas_order_type order, enum blas_uplo_type uplo,
                  int n, const void *t, int ldt, void *x, int incx,
                  const void *y, int incy, void *w, int incw,
                  const void *z, int incz );
void BLAS_ztrmvt( enum blas_order_type order, enum blas_uplo_type uplo,
                  int n, const void *t, int ldt, void *x, int incx,
                  const void *y, int incy, void *w, int incw,
                  const void *z, int incz );

void BLAS_sgemver( enum blas_order_type order, int m, int n, float *a,
                   int lda, const float *u1, const float *v1,
                   const float *u2, const float *v2, float alpha, float *x,
                   int incx, const float *y, int incy, float *w, int incw,
                   float beta, const float *z, int incz );
void BLAS_dgemver( enum blas_order_type order, int m, int n, double *a,
                   int lda, const double *u1, const double *v1,
                   const double *u2, const double *v2, double alpha,
                   double *x, int incx, const double *y, int incy,
                   double *w, int incw, double beta, const double *z,
                   int incz );
void BLAS_cgemver( enum blas_order_type order, int m, int n, void *a,
                   int lda, const void *u1, const void *v1,
                   const void *u2, const void *v2, const void *alpha,
                   void *x, int incx, const void *y, int incy, void *w,
                   int incw, const void *beta, const void *z, int incz );
void BLAS_zgemver( enum blas_order_type order, int m, int n, void *a,
                   int lda, const void *u1, const void *v1,
                   const void *u2, const void *v2, const void *alpha,
                   void *x, int incx, const void *y, int incy, void *w,
                   int incw, const void *beta, const void *z, int incz );

void BLAS_strsv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, float alpha, const float *t, int ldt,
                 float *x, int incx );
void BLAS_dtrsv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, double alpha, const double *t, int ldt,
                 double *x, int incx );
void BLAS_ctrsv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, const void *alpha, const void *t, int ldt,
                 void *x, int incx );
void BLAS_ztrsv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, const void *alpha, const void *t, int ldt,
                 void *x, int incx );

void BLAS_stbsv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, int k, float alpha, const float *t, int ldt,
                 float *x, int incx );
void BLAS_dtbsv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, int k, double alpha, const double *t, int ldt,
                 double *x, int incx );
void BLAS_ctbsv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, int k, const void *alpha, const void *t, int ldt,
                 void *x, int incx );
void BLAS_ztbsv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, int k, const void *alpha, const void *t, int ldt,
                 void *x, int incx );

void BLAS_stpsv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, float alpha, const float *tp, float *x, int incx );
void BLAS_dtpsv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, double alpha, const double *tp, double *x,
                 int incx );
void BLAS_ctpsv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, const void *alpha, const void *tp, void *x,
                 int incx );
void BLAS_ztpsv( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, enum blas_diag_type diag,
                 int n, const void *alpha, const void *tp, void *x,
                 int incx );

void BLAS_sger( enum blas_order_type order, enum blas_conj_type conj,
                int m, int n, float alpha, const float *x, int incx,
                const float *y, int incy, float beta, float *a, int lda );
void BLAS_dger( enum blas_order_type order, enum blas_conj_type conj,
                int m, int n, double alpha, const double *x, int incx,
                const double *y, int incy, double beta, double *a, int lda );
void BLAS_cger( enum blas_order_type order, enum blas_conj_type conj,
                int m, int n, const void *alpha, const void *x, int incx,
                const void *y, int incy, const void *beta, void *a,
                int lda );
void BLAS_zger( enum blas_order_type order, enum blas_conj_type conj,
                int m, int n, const void *alpha, const void *x, int incx,
                const void *y, int incy, const void *beta, void *a,
                int lda );

void BLAS_ssyr( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                float alpha, const float *x, int incx, float beta,
                float *a, int lda );
void BLAS_dsyr( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                double alpha, const double *x, int incx, double beta,
                double *a, int lda );
void BLAS_csyr( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                const void *alpha, const void *x, int incx, const void *beta,
                void *a, int lda );
void BLAS_zsyr( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                const void *alpha, const void *x, int incx, const void *beta,
                void *a, int lda );

void BLAS_sspr( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                float alpha, const float *x, int incx, float beta,
                float *ap );
void BLAS_dspr( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                double alpha, const double *x, int incx, double beta,
                double *ap );
void BLAS_cspr( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                const void *alpha, const void *x, int incx, const void *beta,
                void *ap );
void BLAS_zspr( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                const void *alpha, const void *x, int incx, const void *beta,
                void *ap );

void BLAS_cher( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                float alpha, const void *x, int incx, float beta,
                void *a, int lda );
void BLAS_zher( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                double alpha, const void *x, int incx, double beta,
                void *a, int lda );

void BLAS_chpr( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                float alpha, const void *x, int incx, float beta,
                void *ap );
void BLAS_zhpr( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                double alpha, const void *x, int incx, double beta,
                void *ap );

void BLAS_ssyr2( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                 float alpha, const float *x, int incx, const float *y,
                 int incy, float beta, float *a, int lda );
void BLAS_dsyr2( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                 double alpha, const double *x, int incx, const double *y,
                 int incy, double beta, double *a, int lda );
void BLAS_csyr2( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                 const void *alpha, const void *x, int incx, const void *y,
                 int incy, const void *beta, void *a, int lda );
void BLAS_zsyr2( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                 const void *alpha, const void *x, int incx, const void *y,
                 int incy, const void *beta, void *a, int lda );

void BLAS_sspr2( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                 float alpha, const float *x, int incx, const float *y,
                 int incy, float beta, float *ap );
void BLAS_dspr2( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                 double alpha, const double *x, int incx, const double *y,
                 int incy, double beta, double *ap );
void BLAS_cspr2( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                 const void *alpha, const void *x, int incx, const void *y,
                 int incy, const void *beta, void *ap );
void BLAS_zspr2( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                 const void *alpha, const void *x, int incx, const void *y,
                 int incy, const void *beta, void *ap );

void BLAS_cher2( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                 const void *alpha, const void *x, int incx, const void *y,
                 int incy, float beta, void *a, int lda );
void BLAS_zher2( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                 const void *alpha, const void *x, int incx, const void *y,
                 int incy, double beta, void *a, int lda );

void BLAS_chpr2( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                 const void *alpha, const void *x, int incx, const void *y,
                 int incy, float beta, void *ap );
void BLAS_zhpr2( enum blas_order_type order, enum blas_uplo_type uplo, int n,
                 const void *alpha, const void *x, int incx, const void *y,
                 int incy, double beta, void *ap );

  /* Matrix Operations */

void BLAS_sge_norm( enum blas_order_type order, enum blas_norm_type norm,
                    int m, int n, const float *a, int lda, float *r );
void BLAS_dge_norm( enum blas_order_type order, enum blas_norm_type norm,
                    int m, int n, const double *a, int lda, double *r );
void BLAS_cge_norm( enum blas_order_type order, enum blas_norm_type norm,
                    int m, int n, const void *a, int lda, float *r );
void BLAS_zge_norm( enum blas_order_type order, enum blas_norm_type norm,
                    int m, int n, const void *a, int lda, double *r );

void BLAS_sgb_norm( enum blas_order_type order, enum blas_norm_type norm,
                    int m, int n, int kl, int ku, const float *a, int lda,
                    float *r );
void BLAS_dgb_norm( enum blas_order_type order, enum blas_norm_type norm, 
                    int m, int n, int kl, int ku, const double *a, int lda,
                    double *r );
void BLAS_cgb_norm( enum blas_order_type order, enum blas_norm_type norm,
                    int m, int n, int kl, int ku, const void *a, int lda,
                    float *r );
void BLAS_zgb_norm( enum blas_order_type order, enum blas_norm_type norm,
                    int m, int n, int kl, int ku, const void *a, int lda,
                    double *r );

void BLAS_ssy_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, const float *a,
                    int lda, float *r );
void BLAS_dsy_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, const double *a,
                    int lda, double *r );
void BLAS_csy_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, const void *a,
                    int lda, float *r );
void BLAS_zsy_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, const void *a, int lda,
                    double *r );

void BLAS_che_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, const void *a, int lda,
                    float *r );
void BLAS_zhe_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, const void *a, int lda,
                    double *r );

void BLAS_ssb_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, int k, const float *a,
                    int lda, float *r );
void BLAS_dsb_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, int k, const double *a,
                    int lda, double *r );
void BLAS_csb_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, int k, const void *a,
                    int lda, float *r );
void BLAS_zsb_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, int k, const void *a,
                    int lda, double *r );

void BLAS_chb_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, int k, const void *a,
                    int lda, float *r );
void BLAS_zhb_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, int k, const void *a,
                    int lda, double *r );

void BLAS_ssp_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, const float *ap,
                    float *r );
void BLAS_dsp_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, const double *ap,
                    double *r );
void BLAS_csp_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, const void *ap,
                    float *r );
void BLAS_zsp_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, const void *ap,
                    double *r );

void BLAS_chp_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, const void *ap,
                    float *r );
void BLAS_zhp_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, int n, const void *ap,
                    double *r );

void BLAS_str_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, enum blas_diag_type diag,
                    int n, const float *a, int lda, float *r );
void BLAS_dtr_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, enum blas_diag_type diag,
                    int n, const double *a, int lda, double *r );
void BLAS_ctr_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, enum blas_diag_type diag,
                    int n, const void *a, int lda, float *r );
void BLAS_ztr_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, enum blas_diag_type diag,
                    int n, const void *a, int lda, double *r );

void BLAS_stb_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, enum blas_diag_type diag,
                    int n, int k, const float *a, int lda, float *r );
void BLAS_dtb_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, enum blas_diag_type diag,
                    int n, int k, const double *a, int lda, double *r );
void BLAS_ctb_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, enum blas_diag_type diag,
                    int n, int k, const void *a, int lda, float *r );
void BLAS_ztb_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, enum blas_diag_type diag,
                    int n, int k, const void *a, int lda, double *r );

void BLAS_stp_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, enum blas_diag_type diag,
                    int n, const float *ap, float *r );
void BLAS_dtp_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, enum blas_diag_type diag,
                    int n, const double *ap, double *r );
void BLAS_ctp_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, enum blas_diag_type diag,
                    int n, const void *ap, float *r );
void BLAS_ztp_norm( enum blas_order_type order, enum blas_norm_type norm,
                    enum blas_uplo_type uplo, enum blas_diag_type diag,
                    int n, const void *ap, double *r );

void BLAS_sge_diag_scale( enum blas_order_type order,
                          enum blas_side_type side, int m, int n,
                          const float *d, int incd, float *a, int lda );
void BLAS_dge_diag_scale( enum blas_order_type order,
                          enum blas_side_type side, int m, int n,
                          const double *d, int incd, double *a, int lda );
void BLAS_cge_diag_scale( enum blas_order_type order,
                          enum blas_side_type side, int m, int n,
                          const void *d, int incd, void *a, int lda );
void BLAS_zge_diag_scale( enum blas_order_type order,
                          enum blas_side_type side, int m, int n, 
                          const void *d, int incd, void *a, int lda );

void BLAS_sgb_diag_scale( enum blas_order_type order,
                          enum blas_side_type side, int m, int n,
                          int kl, int ku, const float *d, int incd,
                          float *a, int lda );
void BLAS_dgb_diag_scale( enum blas_order_type order,
                          enum blas_side_type side, int m, int n,
                          int kl, int ku, const double *d, int incd,
                          double *a, int lda );
void BLAS_cgb_diag_scale( enum blas_order_type order,
                          enum blas_side_type side, int m, int n,
                          int kl, int ku, const void *d, int incd,
                          void *a, int lda );
void BLAS_zgb_diag_scale( enum blas_order_type order,
                          enum blas_side_type side, int m, int n,
                          int kl, int ku, const void *d, int incd,
                          void *a, int lda );

void BLAS_sge_lrscale( enum blas_order_type order, int m, int n,
                       const float *dl, int incdl, const float *dr,
                       int incdr, float *a, int lda );
void BLAS_dge_lrscale( enum blas_order_type order, int m, int n,
                       const double *dl, int incdl, const double *dr,
                       int incdr, double *a, int lda );
void BLAS_cge_lrscale( enum blas_order_type order, int m, int n,
                       const void *dl, int incdl, const void *dr,
                       int incdr, void *a, int lda );
void BLAS_zge_lrscale( enum blas_order_type order, int m, int n,
                       const void *dl, int incdl, const void *dr,
                       int incdr, void *a, int lda );

void BLAS_sgb_lrscale( enum blas_order_type order, int m, int n, int kl,
                       int ku, const float *dl, int incdl, const float *dr,
                       int incdr, float *a, int lda );
void BLAS_dgb_lrscale( enum blas_order_type order, int m, int n, int kl,
                       int ku, const double *dl, int incdl,
                       const double *dr, int incdr, double *a, int lda );
void BLAS_cgb_lrscale( enum blas_order_type order, int m, int n, int kl,
                       int ku, const void *dl, int incdl, const void *dr,
                       int incdr, void *a, int lda );
void BLAS_zgb_lrscale( enum blas_order_type order, int m, int n, int kl,
                       int ku, const void *dl, int incdl, const void *dr,
                       int incdr, void *a, int lda );

void BLAS_ssy_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, const float *d, int incd, float *a, int lda );
void BLAS_dsy_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, const double *d, int incd, double *a,
                       int lda );
void BLAS_csy_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, const void *d, int incd, void *a, int lda );
void BLAS_zsy_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, const void *d, int incd, void *a, int lda );

void BLAS_ssb_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, int k, const float *d, int incd, float *a,
                       int lda );
void BLAS_dsb_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, int k, const double *d, int incd, double *a,
                       int lda );
void BLAS_csb_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, int k, const void *d, int incd, void *a,
                       int lda );
void BLAS_zsb_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, int k, const void *d, int incd, void *a,
                       int lda );

void BLAS_ssp_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, const float *d, int incd, float *ap );
void BLAS_dsp_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, const double *d, int incd, double *ap );
void BLAS_csp_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, const void *d, int incd, void *ap );
void BLAS_zsp_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, const void *d, int incd, void *ap );

void BLAS_che_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, const void *d, int incd, void *a, int lda );
void BLAS_zhe_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, const void *d, int incd, void *a, int lda );

void BLAS_chb_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, int k, const void *d, int incd, void *a,
                       int lda );
void BLAS_zhb_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, int k, const void *d, int incd, void *a,
                       int lda );

void BLAS_chp_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, const void *d, int incd, void *ap );
void BLAS_zhp_lrscale( enum blas_order_type order, enum blas_uplo_type uplo,
                       int n, const void *d, int incd, void *ap );

void BLAS_sge_diag_scale_acc( enum blas_order_type order, int m, int n,
                              const float *b, int ldb, const float *d,
                              int incd, float *a, int lda );
void BLAS_dge_diag_scale_acc( enum blas_order_type order, int m, int n,
                              const double *b, int ldb, const double *d,
                              int incd, double *a, int lda );
void BLAS_cge_diag_scale_acc( enum blas_order_type order, int m, int n,
                              const void *b, int ldb, const void *d,
                              int incd, void *a, int lda );
void BLAS_zge_diag_scale_acc( enum blas_order_type order, int m, int n,
                              const void *b, int ldb, const void *d,
                              int incd, void *a, int lda );

void BLAS_sgb_diag_scale_acc( enum blas_order_type order, int m, int n,
                              int kl, int ku, const float *b, int ldb,
                              const float *d, int incd, float *a, int lda );
void BLAS_dgb_diag_scale_acc( enum blas_order_type order, int m, int n,
                              int kl, int ku, const double *b, int ldb,
                              const double *d, int incd, double *a,
                              int lda );
void BLAS_cgb_diag_scale_acc( enum blas_order_type order, int m, int n,
                              int kl, int ku, const void *b, int ldb,
                              const void *d, int incd, void *a, int lda );
void BLAS_zgb_diag_scale_acc( enum blas_order_type order, int m, int n,
                              int kl, int ku, const void *b, int ldb,
                              const void *d, int incd, void *a, int lda );

void BLAS_sge_acc( enum blas_order_type order, enum blas_trans_type trans,
                   int m, int n, float alpha, const float *a, int lda,
                   float beta, float *b, int ldb );
void BLAS_dge_acc( enum blas_order_type order, enum blas_trans_type trans,
                   int m, int n, double alpha, const double *a, int lda,
                   double beta, double *b, int ldb );
void BLAS_cge_acc( enum blas_order_type order, enum blas_trans_type trans,
                   int m, int n, const void *alpha, const void *a, int lda,
                   const void *beta, void *b, int ldb );
void BLAS_zge_acc( enum blas_order_type order, enum blas_trans_type trans,
                   int m, int n, const void *alpha, const void *a, int lda,
                   const void *beta, void *b, int ldb );

void BLAS_ssy_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_trans_type trans, int n, float alpha,
                   const float *a, int lda, float beta, float *b, int ldb );
void BLAS_dsy_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_trans_type trans, int n, double alpha,
                   const double *a, int lda, double beta, double *b,
                   int ldb );
void BLAS_csy_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_trans_type trans, int n, const void *alpha,
                   const void *a, int lda, const void *beta, void *b,
                   int ldb );
void BLAS_zsy_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_trans_type trans, int n, const void *alpha,
                   const void *a, int lda, const void *beta, void *b,
                   int ldb );

void BLAS_ssb_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_trans_type trans, int n, int k, float alpha,
                   const float *a, int lda, float beta, float *b, int ldb );
void BLAS_dsb_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_trans_type trans, int n, int k, double alpha,
                   const double *a, int lda, double beta, double *b,
                   int ldb );
void BLAS_csb_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_trans_type trans, int n, int k,
                   const void *alpha, const void *a, int lda,
                   const void *beta, void *b, int ldb );
void BLAS_zsb_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_trans_type trans, int n, int k,
                   const void *alpha, const void *a, int lda,
                   const void *beta, void *b, int ldb );

void BLAS_ssp_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_trans_type trans, int n, float alpha,
                   const float *ap, float beta, float *bp );
void BLAS_dsp_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_trans_type trans, int n, double alpha,
                   const double *ap, double beta, double *bp );
void BLAS_csp_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_trans_type trans, int n, const void *alpha,
                   const void *ap, const void *beta, void *bp );
void BLAS_zsp_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_trans_type trans, int n, const void *alpha,
                   const void *ap, const void *beta, void *bp );

void BLAS_sgb_acc( enum blas_order_type order, int m, int n, int kl, int ku,
                   float alpha, const float *a, int lda, float beta,
                   float *b, int ldb );
void BLAS_dgb_acc( enum blas_order_type order, int m, int n, int kl, int ku,
                   double alpha, const double *a, int lda, double beta,
                   double *b, int ldb );
void BLAS_cgb_acc( enum blas_order_type order, int m, int n, int kl, int ku,
                   const void *alpha, const void *a, int lda,
                   const void *beta, void *b, int ldb );
void BLAS_zgb_acc( enum blas_order_type order, int m, int n, int kl, int ku,
                   const void *alpha, const void *a, int lda,
                   const void *beta, void *b, int ldb );

void BLAS_str_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, float alpha,
                   const float *a, int lda, float beta, float *b, int ldb );
void BLAS_dtr_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, double alpha,
                   const double *a, int lda, double beta, double *b,
                   int ldb );
void BLAS_ctr_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, const void *alpha,
                   const void *a, int lda, const void *beta, void *b, 
                   int ldb );
void BLAS_ztr_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, const void *alpha,
                   const void *a, int lda, const void *beta, void *b,
                   int ldb );

void BLAS_stb_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, int k, float alpha,
                   const float *a, int lda, float beta, float *b, int ldb );
void BLAS_dtb_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, int k, double alpha,
                   const double *a, int lda, double beta, double *b,
                   int ldb );
void BLAS_ctb_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, int k, const void *alpha,
                   const void *a, int lda, const void *beta, void *b,
                   int ldb );
void BLAS_ztb_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, int k, const void *alpha,
                   const void *a, int lda, const void *beta, void *b,
                   int ldb );

void BLAS_stp_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, float alpha,
                   const float *ap, float beta, float *bp );
void BLAS_dtp_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, double alpha,
                   const double *ap, double beta, double *bp );
void BLAS_ctp_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, const void *alpha,
                   const void *ap, const void *beta, void *bp );
void BLAS_ztp_acc( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, const void *alpha,
                   const void *ap, const void *beta, void *bp );

void BLAS_sge_add( enum blas_order_type order, int m, int n, float alpha,
                   const float *a, int lda, float beta, const float *b,
                   int ldb, float *c, int ldc );
void BLAS_dge_add( enum blas_order_type order, int m, int n, double alpha,
                   const double *a, int lda, double beta, const double *b,
                   int ldb, double *c, int ldc );
void BLAS_cge_add( enum blas_order_type order, int m, int n,
                   const void *alpha, const void *a, int lda,
                   const void *beta, const void *b,
                   int ldb, void *c, int ldc );
void BLAS_zge_add( enum blas_order_type order, int m, int n,
                   const void *alpha, const void *a, int lda,
                   const void *beta, const void *b,
                   int ldb, void *c, int ldc );

void BLAS_sgb_add( enum blas_order_type order, int m, int n, int kl, int ku,
                   float alpha, const float *a, int lda, float beta,
                   const float *b, int ldb, float *c, int ldc );
void BLAS_dgb_add( enum blas_order_type order, int m, int n, int kl, int ku,
                   double alpha, const double *a, int lda, double beta,
                   const double *b, int ldb, double *c, int ldc );
void BLAS_cgb_add( enum blas_order_type order, int m, int n, int kl, int ku,
                   const void *alpha, const void *a, int lda,
                   const void *beta, const void *b, int ldb, void *c,
                   int ldc );
void BLAS_zgb_add( enum blas_order_type order, int m, int n, int kl, int ku,
                   const void *alpha, const void *a, int lda,
                   const void *beta, const void *b, int ldb, void *c,
                   int ldc );

void BLAS_ssy_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   int n, float alpha, const float *a, int lda, float beta,
                   const float *b, int ldb, float *c, int ldc );
void BLAS_dsy_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   int n, double alpha, const double *a, int lda,
                   double beta, const double *b, int ldb, double *c,
                   int ldc );
void BLAS_csy_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   int n, const void *alpha, const void *a, int lda,
                   const void *beta, const void *b, int ldb, void *c,
                   int ldc );
void BLAS_zsy_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   int n, const void *alpha, const void *a, int lda,
                   const void *beta, const void *b, int ldb, void *c,
                   int ldc );

void BLAS_ssb_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   int n, int k, float alpha, const float *a, int lda,
                   float beta, const float *b, int ldb, float *c, int ldc );
void BLAS_dsb_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   int n, int k, double alpha, const double *a, int lda,
                   double beta, const double *b, int ldb, double *c, 
                   int ldc );
void BLAS_csb_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   int n, int k, const void *alpha, const void *a, int lda,
                   const void *beta, const void *b, int ldb, void *c,
                   int ldc );
void BLAS_zsb_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   int n, int k, const void *alpha, const void *a, int lda,
                   const void *beta, const void *b, int ldb, void *c,
                   int ldc );

void BLAS_ssp_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   int n, float alpha, const float *ap, float beta,
                   const float *bp, float *cp );
void BLAS_dsp_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   int n, double alpha, const double *ap, double beta,
                   const double *bp, double *cp );
void BLAS_csp_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   int n, const void *alpha, const void *ap,
                   const void *beta, const void *bp, void *cp );
void BLAS_zsp_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   int n, const void *alpha, const void *ap,
                   const void *beta, const void *bp, void *cp );

void BLAS_str_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, float alpha,
                   const float *a, int lda, float beta, const float *b,
                   int ldb, float *c, int ldc );
void BLAS_dtr_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, double alpha,
                   const double *a, int lda, double beta, const double *b,
                   int ldb, double *c, int ldc );
void BLAS_ctr_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, const void *alpha,
                   const void *a, int lda, const void *beta, const void *b,
                   int ldb, void *c, int ldc );
void BLAS_ztr_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, const void *alpha,
                   const void *a, int lda, const void *beta, const void *b,
                   int ldb, void *c, int ldc );

void BLAS_stb_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, int k, float alpha,
                   const float *a, int lda, float beta, const float *b,
                   int ldb, float *c, int ldc );
void BLAS_dtb_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, int k, double alpha,
                   const double *a, int lda, double beta, const double *b,
                   int ldb, double *c, int ldc );
void BLAS_ctb_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, int k, const void *alpha,
                   const void *a, int lda, const void *beta, const void *b,
                   int ldb, void *c, int ldc );
void BLAS_ztb_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, int k, const void *alpha,
                   const void *a, int lda, const void *beta, const void *b,
                   int ldb, void *c, int ldc );

void BLAS_stp_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, float alpha,
                   const float *ap, float beta, const float *bp,
                   float *cp );
void BLAS_dtp_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, double alpha,
                   const double *ap, double beta, const double *bp,
                   double *cp );
void BLAS_ctp_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, const void *alpha,
                   const void *ap, const void *beta, const void *bp,
                   void *cp );
void BLAS_ztp_add( enum blas_order_type order, enum blas_uplo_type uplo,
                   enum blas_diag_type diag, int n, const void *alpha,
                   const void *ap, const void *beta, const void *bp,
                   void *cp );

  /* Matrix-Matrix Operations */

void BLAS_sgemm( enum blas_order_type order, enum blas_trans_type transa,
                 enum blas_trans_type transb, int m, int n, int k,
                 float alpha, const float *a, int lda, const float *b,
                 int ldb, float beta, float *c, int ldc );
void BLAS_dgemm( enum blas_order_type order, enum blas_trans_type transa,
                 enum blas_trans_type transb, int m, int n, int k,
                 double alpha, const double *a, int lda, const double *b,
                 int ldb, double beta, double *c, int ldc );
void BLAS_cgemm( enum blas_order_type order, enum blas_trans_type transa,
                 enum blas_trans_type transb, int m, int n, int k,
                 const void *alpha, const void *a, int lda, const void *b,
                 int ldb, const void *beta, void *c, int ldc );
void BLAS_zgemm( enum blas_order_type order, enum blas_trans_type transa,
                 enum blas_trans_type transb, int m, int n, int k,
                 const void *alpha, const void *a, int lda, const void *b,
                 int ldb, const void *beta, void *c, int ldc );

void BLAS_ssymm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, int m, int n, float alpha,
                 const float *a, int lda, const float *b, int ldb,
                 float beta, float *c, int ldc );
void BLAS_dsymm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, int m, int n, double alpha,
                 const double *a, int lda, const double *b, int ldb,
                 double beta, double *c, int ldc );
void BLAS_csymm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, int m, int n, const void *alpha,
                 const void *a, int lda, const void *b, int ldb,
                 const void *beta, void *c, int ldc );
void BLAS_zsymm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, int m, int n, const void *alpha,
                 const void *a, int lda, const void *b, int ldb,
                 const void *beta, void *c, int ldc );

void BLAS_chemm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, int m, int n, const void *alpha,
                 const void *a, int lda, const void *b, int ldb,
                 const void *beta, void *c, int ldc );
void BLAS_zhemm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, int m, int n, const void *alpha,
                 const void *a, int lda, const void *b, int ldb,
                 const void *beta, void *c, int ldc );

void BLAS_strmm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, enum blas_trans_type transt,
                 enum blas_diag_type diag, int m, int n, float alpha,
                 const float *t, int ldt, float *b, int ldb );
void BLAS_dtrmm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, enum blas_trans_type transt,
                 enum blas_diag_type diag, int m, int n, double alpha,
                 const double *t, int ldt, double *b, int ldb );
void BLAS_ctrmm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, enum blas_trans_type transt,
                 enum blas_diag_type diag, int m, int n, const void *alpha,
                 const void *t, int ldt, void *b, int ldb );
void BLAS_ztrmm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, enum blas_trans_type transt,
                 enum blas_diag_type diag, int m, int n, const void *alpha,
                 const void *t, int ldt, void *b, int ldb );

void BLAS_strsm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, enum blas_trans_type transt,
                 enum blas_diag_type diag, int m, int n, float alpha,
                 const float *t, int ldt, float *b, int ldb );
void BLAS_dtrsm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, enum blas_trans_type transt,
                 enum blas_diag_type diag, int m, int n, double alpha,
                 const double *t, int ldt, double *b, int ldb );
void BLAS_ctrsm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, enum blas_trans_type transt,
                 enum blas_diag_type diag, int m, int n, const void *alpha,
                 const void *t, int ldt, void *b, int ldb );
void BLAS_ztrsm( enum blas_order_type order, enum blas_side_type side,
                 enum blas_uplo_type uplo, enum blas_trans_type transt,
                 enum blas_diag_type diag, int m, int n, const void *alpha,
                 const void *t, int ldt, void *b, int ldb );

void BLAS_ssyrk( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, int n, int k, float alpha,
                 const float *a, int lda, float beta, float *c, int ldc );
void BLAS_dsyrk( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, int n, int k, double alpha,
                 const double *a, int lda, double beta, double *c, int ldc );
void BLAS_csyrk( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, int n, int k, const void *alpha,
                 const void *a, int lda, const void *beta, void *c,
                 int ldc );
void BLAS_zsyrk( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, int n, int k, const void *alpha,
                 const void *a, int lda, const void *beta, void *c,
                 int ldc );

void BLAS_cherk( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, int n, int k, float alpha,
                 const void *a, int lda, float beta, void *c, int ldc );
void BLAS_zherk( enum blas_order_type order, enum blas_uplo_type uplo,
                 enum blas_trans_type trans, int n, int k, double alpha,
                 const void *a, int lda, double beta, void *c, int ldc );

void BLAS_ssy_tridiag_rk( enum blas_order_type order,
                          enum blas_uplo_type uplo,
                          enum blas_trans_type trans, int n, int k,
                          float alpha, const float *a, int lda, 
                          const float *d, const float *e, float beta,
                          float *c, int ldc );
void BLAS_dsy_tridiag_rk( enum blas_order_type order,
                          enum blas_uplo_type uplo,
                          enum blas_trans_type trans, int n, int k,
                          double alpha, const double *a, int lda,
                          const double *d, const double *e, double beta,
                          double *c, int ldc );
void BLAS_csy_tridiag_rk( enum blas_order_type order,
                          enum blas_uplo_type uplo,
                          enum blas_trans_type trans, int n, int k,
                          const void *alpha, const void *a, int lda,
                          const void *d, const void *e, const void *beta,
                          void *c, int ldc );
void BLAS_zsy_tridiag_rk( enum blas_order_type order,
                          enum blas_uplo_type uplo,
                          enum blas_trans_type trans, int n, int k,
                          const void *alpha, const void *a, int lda,
                          const void *d, const void *e, const void *beta,
                          void *c, int ldc );

void BLAS_che_tridiag_rk( enum blas_order_type order,
                          enum blas_uplo_type uplo,
                          enum blas_trans_type trans, int n, int k,
                          float alpha, const void *a, int lda,
                          const void *d, const void *e, float beta,
                          void *c, int ldc );
void BLAS_zhe_tridiag_rk( enum blas_order_type order,
                          enum blas_uplo_type uplo,
                          enum blas_trans_type trans, int n, int k,
                          double alpha, const void *a, int lda,
                          const void *d, const void *e, double beta,
                          void *c, int ldc );

void BLAS_ssyr2k( enum blas_order_type order, enum blas_uplo_type uplo,
                  enum blas_trans_type trans, int n, int k, float alpha,
                  const float *a, int lda, const float *b, int ldb,
                  float beta, float *c, int ldc );
void BLAS_dsyr2k( enum blas_order_type order, enum blas_uplo_type uplo,
                  enum blas_trans_type trans, int n, int k, double alpha,
                  const double *a, int lda, const double *b, int ldb,
                  double beta, double *c, int ldc );
void BLAS_csyr2k( enum blas_order_type order, enum blas_uplo_type uplo,
                  enum blas_trans_type trans, int n, int k,
                  const void *alpha, const void *a, int lda, const void *b,
                  int ldb, const void *beta, void *c, int ldc );
void BLAS_zsyr2k( enum blas_order_type order, enum blas_uplo_type uplo,
                  enum blas_trans_type trans, int n, int k, 
                  const void *alpha, const void *a, int lda, const void *b,
                  int ldb, const void *beta, void *c, int ldc );

void BLAS_cher2k( enum blas_order_type order, enum blas_uplo_type uplo,
                  enum blas_trans_type trans, int n, int k,
                  const void *alpha, const void *A, int lda, const void *b,
                  int ldb, float beta, void *c, int ldc );
void BLAS_zher2k( enum blas_order_type order, enum blas_uplo_type uplo,
                  enum blas_trans_type trans, int n, int k,
                  const void *alpha, const void *A, int lda, const void *b,
                  int ldb, double beta, void *c, int ldc );

void BLAS_ssy_tridiag_r2k( enum blas_order_type order,
                           enum blas_uplo_type uplo,
                           enum blas_trans_type trans, int n, int k,
                           float alpha, const float *a, int lda,
                           const float *d, const float *e, const float *b,
                           int ldb, float beta, float *c, int ldc );
void BLAS_dsy_tridiag_r2k( enum blas_order_type order,
                           enum blas_uplo_type uplo,
                           enum blas_trans_type trans, int n, int k,
                           double alpha, const double *a, int lda,
                           const double *d, const double *e, const double *b,
                           int ldb, double beta, double *c, int ldc );
void BLAS_csy_tridiag_r2k( enum blas_order_type order,
                           enum blas_uplo_type uplo,
                           enum blas_trans_type trans, int n, int k,
                           const void *alpha, const void *a, int lda,
                           const void *d, const void *e, const void *b,
                           int ldb, const void *beta, void *c, int ldc );
void BLAS_zsy_tridiag_r2k( enum blas_order_type order,
                           enum blas_uplo_type uplo,
                           enum blas_trans_type trans, int n, int k,
                           const void *alpha, const void *a, int lda,
                           const void *d, const void *e, const void *b,
                           int ldb, const void *beta, void *c, int ldc );

void BLAS_che_tridiag_r2k( enum blas_order_type order,
                           enum blas_uplo_type uplo,
                           enum blas_trans_type trans, int n, int k,
                           const void *alpha, const void *a, int lda,
                           const void *d, const void *e, const void *b,
                           int ldb, float beta, void *c, int ldc );
void BLAS_zhe_tridiag_r2k( enum blas_order_type order,
                           enum blas_uplo_type uplo,
                           enum blas_trans_type trans, int n, int k,
                           const void *alpha, const void *a, int lda,
                           const void *d, const void *e, const void *b,
                           int ldb, double beta, void *c, int ldc );

  /* Data Movement with Matrices */

void BLAS_sge_copy( enum blas_order_type order, enum blas_trans_type trans,
                    int m, int n, const float *a, int lda, float *b,
                    int ldb );
void BLAS_dge_copy( enum blas_order_type order, enum blas_trans_type trans,
                    int m, int n, const double *a, int lda, double *b,
                    int ldb );
void BLAS_cge_copy( enum blas_order_type order, enum blas_trans_type trans,
                    int m, int n, const void *a, int lda, void *b, int ldb );
void BLAS_zge_copy( enum blas_order_type order, enum blas_trans_type trans,
                    int m, int n, const void *a, int lda, void *b, int ldb );

void BLAS_sgb_copy( enum blas_order_type order, enum blas_trans_type trans,
                    int m, int n, int kl, int ku, const float *a, int lda,
                    float *b, int ldb );
void BLAS_dgb_copy( enum blas_order_type order, enum blas_trans_type trans,
                    int m, int n, int kl, int ku, const double *a, int lda,
                    double *b, int ldb );
void BLAS_cgb_copy( enum blas_order_type order, enum blas_trans_type trans,
                    int m, int n, int kl, int ku, const void *a, int lda,
                    void *b, int ldb );
void BLAS_zgb_copy( enum blas_order_type order, enum blas_trans_type trans,
                    int m, int n, int kl, int ku, const void *a, int lda,
                    void *b, int ldb );

void BLAS_ssy_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, const float *a, int lda, float *b, int ldb );
void BLAS_dsy_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, const double *a, int lda, double *b, int ldb );
void BLAS_csy_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, const void *a, int lda, void *b, int ldb );
void BLAS_zsy_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, const void *a, int lda, void *b, int ldb );

void BLAS_ssb_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, int k, const float *a, int lda, float *b,
                    int ldb );
void BLAS_dsb_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, int k, const double *a, int lda, double *b,
                    int ldb );
void BLAS_csb_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, int k, const void *a, int lda, void *b, int ldb );
void BLAS_zsb_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, int k, const void *a, int lda, void *b, int ldb );

void BLAS_ssp_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, const float *ap, float *bp );
void BLAS_dsp_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, const double *ap, double *bp );
void BLAS_csp_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, const void *ap, void *bp );
void BLAS_zsp_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, const void *ap, void *bp );

void BLAS_str_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    enum blas_trans_type trans, enum blas_diag_type diag,
                    int n, const float *a, int lda, float *b, int ldb );
void BLAS_dtr_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    enum blas_trans_type trans, enum blas_diag_type diag,
                    int n, const double *a, int lda, double *b, int ldb );
void BLAS_ctr_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    enum blas_trans_type trans, enum blas_diag_type diag,
                    int n, const void *a, int lda, void *b, int ldb );
void BLAS_ztr_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    enum blas_trans_type trans, enum blas_diag_type diag,
                    int n, const void *a, int lda, void *b, int ldb );

void BLAS_stb_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    enum blas_trans_type trans, enum blas_diag_type diag,
                    int n, int k, const float *a, int lda, float *b, 
                    int ldb );
void BLAS_dtb_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    enum blas_trans_type trans, enum blas_diag_type diag,
                    int n, int k, const double *a, int lda, double *b,
                    int ldb );
void BLAS_ctb_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    enum blas_trans_type trans, enum blas_diag_type diag,
                    int n, int k, const void *a, int lda, void *b, int ldb );
void BLAS_ztb_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    enum blas_trans_type trans, enum blas_diag_type diag,
                    int n, int k, const void *a, int lda, void *b, int ldb );

void BLAS_stp_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    enum blas_trans_type trans, enum blas_diag_type diag,
                    int n, const float *ap, float *bp );
void BLAS_dtp_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    enum blas_trans_type trans, enum blas_diag_type diag,
                    int n, const double *ap, double *bp );
void BLAS_ctp_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    enum blas_trans_type trans, enum blas_diag_type diag,
                    int n, const void *ap, void *bp );
void BLAS_ztp_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    enum blas_trans_type trans, enum blas_diag_type diag,
                    int n, const void *ap, void *bp );

void BLAS_che_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, const void *a, int lda, void *b, int ldb );
void BLAS_zhe_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, const void *a, int lda, void *b, int ldb );

void BLAS_chb_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, int k, const void *a, int lda, void *b, int ldb );
void BLAS_zhb_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, int k, const void *a, int lda, void *b, int ldb );

void BLAS_chp_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, const void *ap, void *bp );
void BLAS_zhp_copy( enum blas_order_type order, enum blas_uplo_type uplo,
                    int n, const void *ap, void *bp );

void BLAS_sge_trans( enum blas_order_type order, enum blas_conj_type conj,
                     int n, float *a, int lda );
void BLAS_dge_trans( enum blas_order_type order, enum blas_conj_type conj,
                     int n, double *a, int lda );
void BLAS_cge_trans( enum blas_order_type order, enum blas_conj_type conj,
                     int n, void *a, int lda );
void BLAS_zge_trans( enum blas_order_type order, enum blas_conj_type conj,
                     int n, void *a, int lda );

void BLAS_sge_permute( enum blas_order_type order, enum blas_side_type side,
                       int m, int n, const int *p, int incp, float *a,
                       int lda );
void BLAS_dge_permute( enum blas_order_type order, enum blas_side_type side,
                       int m, int n, const int *p, int incp, double *a,
                       int lda );
void BLAS_cge_permute( enum blas_order_type order, enum blas_side_type side,
                       int m, int n, const int *p, int incp, void *a,
                       int lda );
void BLAS_zge_permute( enum blas_order_type order, enum blas_side_type side,
                       int m, int n, const int *p, int incp, void *a,
                       int lda );

  /* Environmental Enquiry */

float c_sfpinfo( enum blas_cmach_type cmach );
double c_dfpinfo( enum blas_cmach_type cmach );

#endif
   /* BLAS_DENSE_PROTO_H */
#ifndef BLAS_ENUM_H
#define BLAS_ENUM_H

/* Enumerated types */

enum blas_order_type {
            blas_rowmajor = 101,
            blas_colmajor = 102 };

enum blas_trans_type {
            blas_no_trans   = 111,
            blas_trans      = 112,
            blas_conj_trans = 113 };

enum blas_uplo_type  {
            blas_upper = 121,
            blas_lower = 122 };

enum blas_diag_type {
            blas_non_unit_diag = 131,
            blas_unit_diag     = 132 };

enum blas_side_type {
            blas_left_side  = 141,
            blas_right_side = 142 };

enum blas_cmach_type {
            blas_base      = 151,
            blas_t         = 152,
            blas_rnd       = 153,
            blas_ieee      = 154,
            blas_emin      = 155,
            blas_emax      = 156,
            blas_eps       = 157,
            blas_prec      = 158,
            blas_underflow = 159,
            blas_overflow  = 160,
            blas_sfmin     = 161};

enum blas_norm_type {
            blas_one_norm       = 171,
            blas_real_one_norm  = 172,
            blas_two_norm       = 173,
            blas_frobenius_norm = 174,
            blas_inf_norm       = 175,
            blas_real_inf_norm  = 176,
            blas_max_norm       = 177,
            blas_real_max_norm  = 178 };

enum blas_sort_type {
            blas_increasing_order = 181,
            blas_decreasing_order = 182 };

enum blas_conj_type {
            blas_conj    = 191,
            blas_no_conj = 192 };

enum blas_jrot_type {
            blas_jrot_inner  = 201,
            blas_jrot_outer  = 202,
            blas_jrot_sorted = 203 };

enum blas_prec_type {
            blas_prec_single     = 211,
            blas_prec_double     = 212,
            blas_prec_indigenous = 213,
            blas_prec_extra      = 214 };

enum blas_base_type {
            blas_zero_base = 221,
            blas_one_base  = 222 };

enum blas_symmetry_type {
            blas_general          = 231,
            blas_symmetric        = 232,
            blas_hermitian        = 233,
            blas_triangular       = 234,
            blas_lower_triangular = 235,
            blas_upper_triangular = 236 };

enum blas_field_type {
            blas_complex          = 241,
            blas_real             = 242,
            blas_double_precision = 243,
            blas_single_precision = 244  };

enum blas_size_type {
            blas_num_rows      = 251,
            blas_num_cols      = 252,
            blas_num_nonzeros  = 253  };

enum blas_handle_type{
            blas_invalid_handle = 261,
			blas_new_handle     = 262,
			blas_open_handle    = 263,
			blas_closed_handle  = 264};

enum blas_sparsity_optimization_type {
            blas_regular       = 271,
            blas_irregular     = 272,
            blas_block         = 273,
            blas_unassembled   = 274 };

#endif
   /* BLAS_ENUM_H */
#ifndef BLAS_EXTENDED_H
#define BLAS_EXTENDED_H

#include "blas_enum.h"
#include "blas_malloc.h"

#include "blas_extended_proto.h"
#include "blas_dense_proto.h"

#endif /* BLAS_EXTENDED_H */
#ifndef BLAS_EXTENDED_PRIVATE_H
#define BLAS_EXTENDED_PRIVATE_H

/* constants */
#define BITS_S  24
#define BITS_D  53
#define BITS_E  106

/* Split a double into 2 parts with at most 26 bits each. (2^27 + 1) */
#define split 	(134217729.0)

/* macros */
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

#include "blas_fpu.h"

#endif /* BLAS_EXTENDED_PRIVATE_H */
#ifndef BLAS_EXTENDED_PROTO_H
#define BLAS_EXTENDED_PROTO_H


void BLAS_ddot_d_s(enum blas_conj_type conj, int n, double alpha,
		   const double *x, int incx, double beta,
		   const float *y, int incy, double *r);
void BLAS_ddot_s_d(enum blas_conj_type conj, int n, double alpha,
		   const float *x, int incx, double beta,
		   const double *y, int incy, double *r);
void BLAS_ddot_s_s(enum blas_conj_type conj, int n, double alpha,
		   const float *x, int incx, double beta,
		   const float *y, int incy, double *r);
void BLAS_zdot_z_c(enum blas_conj_type conj, int n, const void *alpha,
		   const void *x, int incx, const void *beta,
		   const void *y, int incy, void *r);
void BLAS_zdot_c_z(enum blas_conj_type conj, int n, const void *alpha,
		   const void *x, int incx, const void *beta,
		   const void *y, int incy, void *r);
void BLAS_zdot_c_c(enum blas_conj_type conj, int n, const void *alpha,
		   const void *x, int incx, const void *beta,
		   const void *y, int incy, void *r);
void BLAS_cdot_c_s(enum blas_conj_type conj, int n, const void *alpha,
		   const void *x, int incx, const void *beta,
		   const float *y, int incy, void *r);
void BLAS_cdot_s_c(enum blas_conj_type conj, int n, const void *alpha,
		   const float *x, int incx, const void *beta,
		   const void *y, int incy, void *r);
void BLAS_cdot_s_s(enum blas_conj_type conj, int n, const void *alpha,
		   const float *x, int incx, const void *beta,
		   const float *y, int incy, void *r);
void BLAS_zdot_z_d(enum blas_conj_type conj, int n, const void *alpha,
		   const void *x, int incx, const void *beta,
		   const double *y, int incy, void *r);
void BLAS_zdot_d_z(enum blas_conj_type conj, int n, const void *alpha,
		   const double *x, int incx, const void *beta,
		   const void *y, int incy, void *r);
void BLAS_zdot_d_d(enum blas_conj_type conj, int n, const void *alpha,
		   const double *x, int incx, const void *beta,
		   const double *y, int incy, void *r);
void BLAS_sdot_x(enum blas_conj_type conj, int n, float alpha,
		 const float *x, int incx, float beta,
		 const float *y, int incy,
		 float *r, enum blas_prec_type prec);
void BLAS_ddot_x(enum blas_conj_type conj, int n, double alpha,
		 const double *x, int incx, double beta,
		 const double *y, int incy,
		 double *r, enum blas_prec_type prec);
void BLAS_cdot_x(enum blas_conj_type conj, int n, const void *alpha,
		 const void *x, int incx, const void *beta,
		 const void *y, int incy, void *r, enum blas_prec_type prec);
void BLAS_zdot_x(enum blas_conj_type conj, int n, const void *alpha,
		 const void *x, int incx, const void *beta,
		 const void *y, int incy, void *r, enum blas_prec_type prec);
void BLAS_ddot_d_s_x(enum blas_conj_type conj, int n, double alpha,
		     const double *x, int incx, double beta,
		     const float *y, int incy,
		     double *r, enum blas_prec_type prec);
void BLAS_ddot_s_d_x(enum blas_conj_type conj, int n, double alpha,
		     const float *x, int incx, double beta,
		     const double *y, int incy,
		     double *r, enum blas_prec_type prec);
void BLAS_ddot_s_s_x(enum blas_conj_type conj, int n, double alpha,
		     const float *x, int incx, double beta,
		     const float *y, int incy,
		     double *r, enum blas_prec_type prec);
void BLAS_zdot_z_c_x(enum blas_conj_type conj, int n, const void *alpha,
		     const void *x, int incx, const void *beta,
		     const void *y, int incy,
		     void *r, enum blas_prec_type prec);
void BLAS_zdot_c_z_x(enum blas_conj_type conj, int n, const void *alpha,
		     const void *x, int incx, const void *beta,
		     const void *y, int incy,
		     void *r, enum blas_prec_type prec);
void BLAS_zdot_c_c_x(enum blas_conj_type conj, int n, const void *alpha,
		     const void *x, int incx, const void *beta,
		     const void *y, int incy,
		     void *r, enum blas_prec_type prec);
void BLAS_cdot_c_s_x(enum blas_conj_type conj, int n, const void *alpha,
		     const void *x, int incx, const void *beta,
		     const float *y, int incy,
		     void *r, enum blas_prec_type prec);
void BLAS_cdot_s_c_x(enum blas_conj_type conj, int n, const void *alpha,
		     const float *x, int incx, const void *beta,
		     const void *y, int incy,
		     void *r, enum blas_prec_type prec);
void BLAS_cdot_s_s_x(enum blas_conj_type conj, int n, const void *alpha,
		     const float *x, int incx, const void *beta,
		     const float *y, int incy,
		     void *r, enum blas_prec_type prec);
void BLAS_zdot_z_d_x(enum blas_conj_type conj, int n, const void *alpha,
		     const void *x, int incx, const void *beta,
		     const double *y, int incy,
		     void *r, enum blas_prec_type prec);
void BLAS_zdot_d_z_x(enum blas_conj_type conj, int n, const void *alpha,
		     const double *x, int incx, const void *beta,
		     const void *y, int incy,
		     void *r, enum blas_prec_type prec);
void BLAS_zdot_d_d_x(enum blas_conj_type conj, int n, const void *alpha,
		     const double *x, int incx, const void *beta,
		     const double *y, int incy,
		     void *r, enum blas_prec_type prec);


void BLAS_ssum_x(int n, const float *x, int incx,
		 float *sum, enum blas_prec_type prec);
void BLAS_dsum_x(int n, const double *x, int incx,
		 double *sum, enum blas_prec_type prec);
void BLAS_csum_x(int n, const void *x, int incx,
		 void *sum, enum blas_prec_type prec);
void BLAS_zsum_x(int n, const void *x, int incx,
		 void *sum, enum blas_prec_type prec);


void BLAS_daxpby_s(int n, double alpha, const float *x, int incx,
		   double beta, double *y, int incy);
void BLAS_caxpby_s(int n, const void *alpha, const float *x, int incx,
		   const void *beta, void *y, int incy);
void BLAS_zaxpby_c(int n, const void *alpha, const void *x, int incx,
		   const void *beta, void *y, int incy);
void BLAS_zaxpby_d(int n, const void *alpha, const double *x, int incx,
		   const void *beta, void *y, int incy);
void BLAS_saxpby_x(int n, float alpha, const float *x, int incx,
		   float beta, float *y, int incy, enum blas_prec_type prec);
void BLAS_daxpby_x(int n, double alpha, const double *x, int incx,
		   double beta, double *y,
		   int incy, enum blas_prec_type prec);
void BLAS_caxpby_x(int n, const void *alpha, const void *x, int incx,
		   const void *beta, void *y,
		   int incy, enum blas_prec_type prec);
void BLAS_zaxpby_x(int n, const void *alpha, const void *x, int incx,
		   const void *beta, void *y,
		   int incy, enum blas_prec_type prec);
void BLAS_daxpby_s_x(int n, double alpha, const float *x, int incx,
		     double beta, double *y,
		     int incy, enum blas_prec_type prec);
void BLAS_zaxpby_c_x(int n, const void *alpha, const void *x, int incx,
		     const void *beta, void *y,
		     int incy, enum blas_prec_type prec);
void BLAS_caxpby_s_x(int n, const void *alpha, const float *x, int incx,
		     const void *beta, void *y,
		     int incy, enum blas_prec_type prec);
void BLAS_zaxpby_d_x(int n, const void *alpha, const double *x, int incx,
		     const void *beta, void *y,
		     int incy, enum blas_prec_type prec);


void BLAS_dwaxpby_d_s(int n, double alpha, const double *x, int incx,
		      double beta, const float *y, int incy, double *w,
		      int incw);
void BLAS_dwaxpby_s_d(int n, double alpha, const float *x, int incx,
		      double beta, const double *y, int incy, double *w,
		      int incw);
void BLAS_dwaxpby_s_s(int n, double alpha, const float *x, int incx,
		      double beta, const float *y, int incy, double *w,
		      int incw);
void BLAS_zwaxpby_z_c(int n, const void *alpha, const void *x, int incx,
		      const void *beta, const void *y, int incy, void *w,
		      int incw);
void BLAS_zwaxpby_c_z(int n, const void *alpha, const void *x, int incx,
		      const void *beta, const void *y, int incy, void *w,
		      int incw);
void BLAS_zwaxpby_c_c(int n, const void *alpha, const void *x, int incx,
		      const void *beta, const void *y, int incy, void *w,
		      int incw);
void BLAS_cwaxpby_c_s(int n, const void *alpha, const void *x, int incx,
		      const void *beta, const float *y, int incy, void *w,
		      int incw);
void BLAS_cwaxpby_s_c(int n, const void *alpha, const float *x, int incx,
		      const void *beta, const void *y, int incy, void *w,
		      int incw);
void BLAS_cwaxpby_s_s(int n, const void *alpha, const float *x, int incx,
		      const void *beta, const float *y, int incy, void *w,
		      int incw);
void BLAS_zwaxpby_z_d(int n, const void *alpha, const void *x, int incx,
		      const void *beta, const double *y, int incy, void *w,
		      int incw);
void BLAS_zwaxpby_d_z(int n, const void *alpha, const double *x, int incx,
		      const void *beta, const void *y, int incy, void *w,
		      int incw);
void BLAS_zwaxpby_d_d(int n, const void *alpha, const double *x, int incx,
		      const void *beta, const double *y, int incy, void *w,
		      int incw);
void BLAS_swaxpby_x(int n, float alpha, const float *x, int incx,
		    float beta, const float *y, int incy, float *w,
		    int incw, enum blas_prec_type prec);
void BLAS_dwaxpby_x(int n, double alpha, const double *x, int incx,
		    double beta, const double *y, int incy, double *w,
		    int incw, enum blas_prec_type prec);
void BLAS_cwaxpby_x(int n, const void *alpha, const void *x, int incx,
		    const void *beta, const void *y, int incy, void *w,
		    int incw, enum blas_prec_type prec);
void BLAS_zwaxpby_x(int n, const void *alpha, const void *x, int incx,
		    const void *beta, const void *y, int incy, void *w,
		    int incw, enum blas_prec_type prec);
void BLAS_dwaxpby_d_s_x(int n, double alpha, const double *x, int incx,
			double beta, const float *y, int incy, double *w,
			int incw, enum blas_prec_type prec);
void BLAS_dwaxpby_s_d_x(int n, double alpha, const float *x, int incx,
			double beta, const double *y, int incy, double *w,
			int incw, enum blas_prec_type prec);
void BLAS_dwaxpby_s_s_x(int n, double alpha, const float *x, int incx,
			double beta, const float *y, int incy, double *w,
			int incw, enum blas_prec_type prec);
void BLAS_zwaxpby_z_c_x(int n, const void *alpha, const void *x, int incx,
			const void *beta, const void *y, int incy, void *w,
			int incw, enum blas_prec_type prec);
void BLAS_zwaxpby_c_z_x(int n, const void *alpha, const void *x, int incx,
			const void *beta, const void *y, int incy, void *w,
			int incw, enum blas_prec_type prec);
void BLAS_zwaxpby_c_c_x(int n, const void *alpha, const void *x, int incx,
			const void *beta, const void *y, int incy, void *w,
			int incw, enum blas_prec_type prec);
void BLAS_cwaxpby_c_s_x(int n, const void *alpha, const void *x, int incx,
			const void *beta, const float *y, int incy, void *w,
			int incw, enum blas_prec_type prec);
void BLAS_cwaxpby_s_c_x(int n, const void *alpha, const float *x, int incx,
			const void *beta, const void *y, int incy, void *w,
			int incw, enum blas_prec_type prec);
void BLAS_cwaxpby_s_s_x(int n, const void *alpha, const float *x, int incx,
			const void *beta, const float *y, int incy, void *w,
			int incw, enum blas_prec_type prec);
void BLAS_zwaxpby_z_d_x(int n, const void *alpha, const void *x, int incx,
			const void *beta, const double *y, int incy, void *w,
			int incw, enum blas_prec_type prec);
void BLAS_zwaxpby_d_z_x(int n, const void *alpha, const double *x, int incx,
			const void *beta, const void *y, int incy, void *w,
			int incw, enum blas_prec_type prec);
void BLAS_zwaxpby_d_d_x(int n, const void *alpha, const double *x, int incx,
			const void *beta, const double *y, int incy, void *w,
			int incw, enum blas_prec_type prec);


void BLAS_dgemv_d_s(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, double alpha, const double *a, int lda,
		    const float *x, int incx, double beta, double *y,
		    int incy);
void BLAS_dgemv_s_d(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, double alpha, const float *a, int lda,
		    const double *x, int incx, double beta, double *y,
		    int incy);
void BLAS_dgemv_s_s(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, double alpha, const float *a, int lda,
		    const float *x, int incx, double beta, double *y,
		    int incy);
void BLAS_zgemv_z_c(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_zgemv_c_z(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_zgemv_c_c(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_cgemv_c_s(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, const void *alpha, const void *a, int lda,
		    const float *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_cgemv_s_c(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, const void *alpha, const float *a, int lda,
		    const void *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_cgemv_s_s(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, const void *alpha, const float *a, int lda,
		    const float *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_zgemv_z_d(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, const void *alpha, const void *a, int lda,
		    const double *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_zgemv_d_z(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, const void *alpha, const double *a, int lda,
		    const void *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_zgemv_d_d(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, const void *alpha, const double *a, int lda,
		    const double *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_sgemv_x(enum blas_order_type order, enum blas_trans_type trans,
		  int m, int n, float alpha, const float *a, int lda,
		  const float *x, int incx, float beta, float *y,
		  int incy, enum blas_prec_type prec);
void BLAS_dgemv_x(enum blas_order_type order, enum blas_trans_type trans,
		  int m, int n, double alpha, const double *a, int lda,
		  const double *x, int incx, double beta, double *y,
		  int incy, enum blas_prec_type prec);
void BLAS_cgemv_x(enum blas_order_type order, enum blas_trans_type trans,
		  int m, int n, const void *alpha, const void *a, int lda,
		  const void *x, int incx, const void *beta, void *y,
		  int incy, enum blas_prec_type prec);
void BLAS_zgemv_x(enum blas_order_type order, enum blas_trans_type trans,
		  int m, int n, const void *alpha, const void *a, int lda,
		  const void *x, int incx, const void *beta, void *y,
		  int incy, enum blas_prec_type prec);
void BLAS_dgemv_d_s_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, double alpha, const double *a, int lda,
		      const float *x, int incx, double beta, double *y,
		      int incy, enum blas_prec_type prec);
void BLAS_dgemv_s_d_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, double alpha, const float *a, int lda,
		      const double *x, int incx, double beta, double *y,
		      int incy, enum blas_prec_type prec);
void BLAS_dgemv_s_s_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, double alpha, const float *a, int lda,
		      const float *x, int incx, double beta, double *y,
		      int incy, enum blas_prec_type prec);
void BLAS_zgemv_z_c_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta, void *y,
		      int incy, enum blas_prec_type prec);
void BLAS_zgemv_c_z_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta, void *y,
		      int incy, enum blas_prec_type prec);
void BLAS_zgemv_c_c_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta, void *y,
		      int incy, enum blas_prec_type prec);
void BLAS_cgemv_c_s_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, const void *alpha, const void *a, int lda,
		      const float *x, int incx, const void *beta, void *y,
		      int incy, enum blas_prec_type prec);
void BLAS_cgemv_s_c_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, const void *alpha, const float *a,
		      int lda, const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_cgemv_s_s_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, const void *alpha, const float *a,
		      int lda, const float *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zgemv_z_d_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, const void *alpha, const void *a, int lda,
		      const double *x, int incx, const void *beta, void *y,
		      int incy, enum blas_prec_type prec);
void BLAS_zgemv_d_z_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, const void *alpha, const double *a,
		      int lda, const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zgemv_d_d_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, const void *alpha, const double *a,
		      int lda, const double *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);


void BLAS_dge_sum_mv_d_s(enum blas_order_type order, int m, int n,
			 double alpha, const double *a, int lda,
			 const float *x, int incx,
			 double beta, const double *b, int ldb,
			 double *y, int incy);
void BLAS_dge_sum_mv_s_d(enum blas_order_type order, int m, int n,
			 double alpha, const float *a, int lda,
			 const double *x, int incx,
			 double beta, const float *b, int ldb,
			 double *y, int incy);
void BLAS_dge_sum_mv_s_s(enum blas_order_type order, int m, int n,
			 double alpha, const float *a, int lda,
			 const float *x, int incx,
			 double beta, const float *b, int ldb,
			 double *y, int incy);
void BLAS_zge_sum_mv_z_c(enum blas_order_type order, int m, int n,
			 const void *alpha, const void *a, int lda,
			 const void *x, int incx,
			 const void *beta, const void *b, int ldb,
			 void *y, int incy);
void BLAS_zge_sum_mv_c_z(enum blas_order_type order, int m, int n,
			 const void *alpha, const void *a, int lda,
			 const void *x, int incx,
			 const void *beta, const void *b, int ldb,
			 void *y, int incy);
void BLAS_zge_sum_mv_c_c(enum blas_order_type order, int m, int n,
			 const void *alpha, const void *a, int lda,
			 const void *x, int incx,
			 const void *beta, const void *b, int ldb,
			 void *y, int incy);
void BLAS_cge_sum_mv_c_s(enum blas_order_type order, int m, int n,
			 const void *alpha, const void *a, int lda,
			 const float *x, int incx,
			 const void *beta, const void *b, int ldb,
			 void *y, int incy);
void BLAS_cge_sum_mv_s_c(enum blas_order_type order, int m, int n,
			 const void *alpha, const float *a, int lda,
			 const void *x, int incx,
			 const void *beta, const float *b, int ldb,
			 void *y, int incy);
void BLAS_cge_sum_mv_s_s(enum blas_order_type order, int m, int n,
			 const void *alpha, const float *a, int lda,
			 const float *x, int incx,
			 const void *beta, const float *b, int ldb,
			 void *y, int incy);
void BLAS_zge_sum_mv_z_d(enum blas_order_type order, int m, int n,
			 const void *alpha, const void *a, int lda,
			 const double *x, int incx,
			 const void *beta, const void *b, int ldb,
			 void *y, int incy);
void BLAS_zge_sum_mv_d_z(enum blas_order_type order, int m, int n,
			 const void *alpha, const double *a, int lda,
			 const void *x, int incx,
			 const void *beta, const double *b, int ldb,
			 void *y, int incy);
void BLAS_zge_sum_mv_d_d(enum blas_order_type order, int m, int n,
			 const void *alpha, const double *a, int lda,
			 const double *x, int incx,
			 const void *beta, const double *b, int ldb,
			 void *y, int incy);
void BLAS_sge_sum_mv_x(enum blas_order_type order, int m, int n,
		       float alpha, const float *a, int lda,
		       const float *x, int incx,
		       float beta, const float *b, int ldb,
		       float *y, int incy, enum blas_prec_type prec);
void BLAS_dge_sum_mv_x(enum blas_order_type order, int m, int n,
		       double alpha, const double *a, int lda,
		       const double *x, int incx,
		       double beta, const double *b, int ldb,
		       double *y, int incy, enum blas_prec_type prec);
void BLAS_cge_sum_mv_x(enum blas_order_type order, int m, int n,
		       const void *alpha, const void *a, int lda,
		       const void *x, int incx,
		       const void *beta, const void *b, int ldb,
		       void *y, int incy, enum blas_prec_type prec);
void BLAS_zge_sum_mv_x(enum blas_order_type order, int m, int n,
		       const void *alpha, const void *a, int lda,
		       const void *x, int incx,
		       const void *beta, const void *b, int ldb,
		       void *y, int incy, enum blas_prec_type prec);
void BLAS_dge_sum_mv_d_s_x(enum blas_order_type order, int m, int n,
			   double alpha, const double *a, int lda,
			   const float *x, int incx,
			   double beta, const double *b, int ldb,
			   double *y, int incy, enum blas_prec_type prec);
void BLAS_dge_sum_mv_s_d_x(enum blas_order_type order, int m, int n,
			   double alpha, const float *a, int lda,
			   const double *x, int incx,
			   double beta, const float *b, int ldb,
			   double *y, int incy, enum blas_prec_type prec);
void BLAS_dge_sum_mv_s_s_x(enum blas_order_type order, int m, int n,
			   double alpha, const float *a, int lda,
			   const float *x, int incx,
			   double beta, const float *b, int ldb,
			   double *y, int incy, enum blas_prec_type prec);
void BLAS_zge_sum_mv_z_c_x(enum blas_order_type order, int m, int n,
			   const void *alpha, const void *a, int lda,
			   const void *x, int incx,
			   const void *beta, const void *b, int ldb,
			   void *y, int incy, enum blas_prec_type prec);
void BLAS_zge_sum_mv_c_z_x(enum blas_order_type order, int m, int n,
			   const void *alpha, const void *a, int lda,
			   const void *x, int incx,
			   const void *beta, const void *b, int ldb,
			   void *y, int incy, enum blas_prec_type prec);
void BLAS_zge_sum_mv_c_c_x(enum blas_order_type order, int m, int n,
			   const void *alpha, const void *a, int lda,
			   const void *x, int incx,
			   const void *beta, const void *b, int ldb,
			   void *y, int incy, enum blas_prec_type prec);
void BLAS_cge_sum_mv_c_s_x(enum blas_order_type order, int m, int n,
			   const void *alpha, const void *a, int lda,
			   const float *x, int incx,
			   const void *beta, const void *b, int ldb,
			   void *y, int incy, enum blas_prec_type prec);
void BLAS_cge_sum_mv_s_c_x(enum blas_order_type order, int m, int n,
			   const void *alpha, const float *a, int lda,
			   const void *x, int incx,
			   const void *beta, const float *b, int ldb,
			   void *y, int incy, enum blas_prec_type prec);
void BLAS_cge_sum_mv_s_s_x(enum blas_order_type order, int m, int n,
			   const void *alpha, const float *a, int lda,
			   const float *x, int incx,
			   const void *beta, const float *b, int ldb,
			   void *y, int incy, enum blas_prec_type prec);
void BLAS_zge_sum_mv_z_d_x(enum blas_order_type order, int m, int n,
			   const void *alpha, const void *a, int lda,
			   const double *x, int incx,
			   const void *beta, const void *b, int ldb,
			   void *y, int incy, enum blas_prec_type prec);
void BLAS_zge_sum_mv_d_z_x(enum blas_order_type order, int m, int n,
			   const void *alpha, const double *a, int lda,
			   const void *x, int incx,
			   const void *beta, const double *b, int ldb,
			   void *y, int incy, enum blas_prec_type prec);
void BLAS_zge_sum_mv_d_d_x(enum blas_order_type order, int m, int n,
			   const void *alpha, const double *a, int lda,
			   const double *x, int incx,
			   const void *beta, const double *b, int ldb,
			   void *y, int incy, enum blas_prec_type prec);


void BLAS_dgbmv_d_s(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, int kl, int ku, double alpha,
		    const double *a, int lda, const float *x, int incx,
		    double beta, double *y, int incy);
void BLAS_dgbmv_s_d(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, int kl, int ku, double alpha,
		    const float *a, int lda, const double *x, int incx,
		    double beta, double *y, int incy);
void BLAS_dgbmv_s_s(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, int kl, int ku, double alpha,
		    const float *a, int lda, const float *x, int incx,
		    double beta, double *y, int incy);
void BLAS_zgbmv_z_c(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, int kl, int ku, const void *alpha,
		    const void *a, int lda, const void *x, int incx,
		    const void *beta, void *y, int incy);
void BLAS_zgbmv_c_z(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, int kl, int ku, const void *alpha,
		    const void *a, int lda, const void *x, int incx,
		    const void *beta, void *y, int incy);
void BLAS_zgbmv_c_c(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, int kl, int ku, const void *alpha,
		    const void *a, int lda, const void *x, int incx,
		    const void *beta, void *y, int incy);
void BLAS_cgbmv_c_s(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, int kl, int ku, const void *alpha,
		    const void *a, int lda, const float *x, int incx,
		    const void *beta, void *y, int incy);
void BLAS_cgbmv_s_c(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, int kl, int ku, const void *alpha,
		    const float *a, int lda, const void *x, int incx,
		    const void *beta, void *y, int incy);
void BLAS_cgbmv_s_s(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, int kl, int ku, const void *alpha,
		    const float *a, int lda, const float *x, int incx,
		    const void *beta, void *y, int incy);
void BLAS_zgbmv_z_d(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, int kl, int ku, const void *alpha,
		    const void *a, int lda, const double *x, int incx,
		    const void *beta, void *y, int incy);
void BLAS_zgbmv_d_z(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, int kl, int ku, const void *alpha,
		    const double *a, int lda, const void *x, int incx,
		    const void *beta, void *y, int incy);
void BLAS_zgbmv_d_d(enum blas_order_type order, enum blas_trans_type trans,
		    int m, int n, int kl, int ku, const void *alpha,
		    const double *a, int lda, const double *x, int incx,
		    const void *beta, void *y, int incy);
void BLAS_sgbmv_x(enum blas_order_type order, enum blas_trans_type trans,
		  int m, int n, int kl, int ku, float alpha,
		  const float *a, int lda, const float *x, int incx,
		  float beta, float *y, int incy, enum blas_prec_type prec);
void BLAS_dgbmv_x(enum blas_order_type order, enum blas_trans_type trans,
		  int m, int n, int kl, int ku, double alpha,
		  const double *a, int lda, const double *x, int incx,
		  double beta, double *y, int incy, enum blas_prec_type prec);
void BLAS_cgbmv_x(enum blas_order_type order, enum blas_trans_type trans,
		  int m, int n, int kl, int ku, const void *alpha,
		  const void *a, int lda, const void *x, int incx,
		  const void *beta, void *y, int incy,
		  enum blas_prec_type prec);
void BLAS_zgbmv_x(enum blas_order_type order, enum blas_trans_type trans,
		  int m, int n, int kl, int ku, const void *alpha,
		  const void *a, int lda, const void *x, int incx,
		  const void *beta, void *y, int incy,
		  enum blas_prec_type prec);
void BLAS_dgbmv_d_s_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, int kl, int ku, double alpha,
		      const double *a, int lda, const float *x, int incx,
		      double beta, double *y, int incy,
		      enum blas_prec_type prec);
void BLAS_dgbmv_s_d_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, int kl, int ku, double alpha,
		      const float *a, int lda, const double *x, int incx,
		      double beta, double *y, int incy,
		      enum blas_prec_type prec);
void BLAS_dgbmv_s_s_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, int kl, int ku, double alpha,
		      const float *a, int lda, const float *x, int incx,
		      double beta, double *y, int incy,
		      enum blas_prec_type prec);
void BLAS_zgbmv_z_c_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, int kl, int ku, const void *alpha,
		      const void *a, int lda, const void *x, int incx,
		      const void *beta, void *y, int incy,
		      enum blas_prec_type prec);
void BLAS_zgbmv_c_z_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, int kl, int ku, const void *alpha,
		      const void *a, int lda, const void *x, int incx,
		      const void *beta, void *y, int incy,
		      enum blas_prec_type prec);
void BLAS_zgbmv_c_c_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, int kl, int ku, const void *alpha,
		      const void *a, int lda, const void *x, int incx,
		      const void *beta, void *y, int incy,
		      enum blas_prec_type prec);
void BLAS_cgbmv_c_s_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, int kl, int ku, const void *alpha,
		      const void *a, int lda, const float *x, int incx,
		      const void *beta, void *y, int incy,
		      enum blas_prec_type prec);
void BLAS_cgbmv_s_c_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, int kl, int ku, const void *alpha,
		      const float *a, int lda, const void *x, int incx,
		      const void *beta, void *y, int incy,
		      enum blas_prec_type prec);
void BLAS_cgbmv_s_s_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, int kl, int ku, const void *alpha,
		      const float *a, int lda, const float *x, int incx,
		      const void *beta, void *y, int incy,
		      enum blas_prec_type prec);
void BLAS_zgbmv_z_d_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, int kl, int ku, const void *alpha,
		      const void *a, int lda, const double *x, int incx,
		      const void *beta, void *y, int incy,
		      enum blas_prec_type prec);
void BLAS_zgbmv_d_z_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, int kl, int ku, const void *alpha,
		      const double *a, int lda, const void *x, int incx,
		      const void *beta, void *y, int incy,
		      enum blas_prec_type prec);
void BLAS_zgbmv_d_d_x(enum blas_order_type order, enum blas_trans_type trans,
		      int m, int n, int kl, int ku, const void *alpha,
		      const double *a, int lda, const double *x, int incx,
		      const void *beta, void *y, int incy,
		      enum blas_prec_type prec);


void BLAS_dsymv_d_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, double alpha, const double *a, int lda,
		    const float *x, int incx, double beta,
		    double *y, int incy);
void BLAS_dsymv_s_d(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, double alpha, const float *a, int lda,
		    const double *x, int incx, double beta,
		    double *y, int incy);
void BLAS_dsymv_s_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, double alpha, const float *a, int lda,
		    const float *x, int incx, double beta,
		    double *y, int incy);
void BLAS_zsymv_z_c(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zsymv_c_z(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zsymv_c_c(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_csymv_c_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *a, int lda,
		    const float *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_csymv_s_c(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const float *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_csymv_s_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const float *a, int lda,
		    const float *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zsymv_z_d(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *a, int lda,
		    const double *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zsymv_d_z(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const double *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zsymv_d_d(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const double *a, int lda,
		    const double *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_ssymv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, float alpha, const float *a, int lda,
		  const float *x, int incx, float beta,
		  float *y, int incy, enum blas_prec_type prec);
void BLAS_dsymv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, double alpha, const double *a, int lda,
		  const double *x, int incx, double beta,
		  double *y, int incy, enum blas_prec_type prec);
void BLAS_csymv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, const void *alpha, const void *a, int lda,
		  const void *x, int incx, const void *beta,
		  void *y, int incy, enum blas_prec_type prec);
void BLAS_zsymv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, const void *alpha, const void *a, int lda,
		  const void *x, int incx, const void *beta,
		  void *y, int incy, enum blas_prec_type prec);
void BLAS_dsymv_d_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, double alpha, const double *a, int lda,
		      const float *x, int incx, double beta,
		      double *y, int incy, enum blas_prec_type prec);
void BLAS_dsymv_s_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, double alpha, const float *a, int lda,
		      const double *x, int incx, double beta,
		      double *y, int incy, enum blas_prec_type prec);
void BLAS_dsymv_s_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, double alpha, const float *a, int lda,
		      const float *x, int incx, double beta,
		      double *y, int incy, enum blas_prec_type prec);
void BLAS_zsymv_z_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zsymv_c_z_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zsymv_c_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_csymv_c_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *a, int lda,
		      const float *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_csymv_s_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const float *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_csymv_s_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const float *a, int lda,
		      const float *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zsymv_z_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *a, int lda,
		      const double *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zsymv_d_z_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const double *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zsymv_d_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const double *a, int lda,
		      const double *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);


void BLAS_dspmv_d_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, double alpha, const double *ap,
		    const float *x, int incx, double beta,
		    double *y, int incy);
void BLAS_dspmv_s_d(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, double alpha, const float *ap,
		    const double *x, int incx, double beta,
		    double *y, int incy);
void BLAS_dspmv_s_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, double alpha, const float *ap,
		    const float *x, int incx, double beta,
		    double *y, int incy);
void BLAS_zspmv_z_c(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *ap,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zspmv_c_z(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *ap,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zspmv_c_c(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *ap,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_cspmv_c_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *ap,
		    const float *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_cspmv_s_c(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const float *ap,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_cspmv_s_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const float *ap,
		    const float *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zspmv_z_d(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *ap,
		    const double *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zspmv_d_z(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const double *ap,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zspmv_d_d(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const double *ap,
		    const double *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_sspmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, float alpha, const float *ap,
		  const float *x, int incx, float beta,
		  float *y, int incy, enum blas_prec_type prec);
void BLAS_dspmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, double alpha, const double *ap,
		  const double *x, int incx, double beta,
		  double *y, int incy, enum blas_prec_type prec);
void BLAS_cspmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, const void *alpha, const void *ap,
		  const void *x, int incx, const void *beta,
		  void *y, int incy, enum blas_prec_type prec);
void BLAS_zspmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, const void *alpha, const void *ap,
		  const void *x, int incx, const void *beta,
		  void *y, int incy, enum blas_prec_type prec);
void BLAS_dspmv_d_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, double alpha, const double *ap,
		      const float *x, int incx, double beta,
		      double *y, int incy, enum blas_prec_type prec);
void BLAS_dspmv_s_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, double alpha, const float *ap,
		      const double *x, int incx, double beta,
		      double *y, int incy, enum blas_prec_type prec);
void BLAS_dspmv_s_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, double alpha, const float *ap,
		      const float *x, int incx, double beta,
		      double *y, int incy, enum blas_prec_type prec);
void BLAS_zspmv_z_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *ap,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zspmv_c_z_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *ap,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zspmv_c_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *ap,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_cspmv_c_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *ap,
		      const float *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_cspmv_s_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const float *ap,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_cspmv_s_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const float *ap,
		      const float *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zspmv_z_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *ap,
		      const double *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zspmv_d_z_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const double *ap,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zspmv_d_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const double *ap,
		      const double *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);


void BLAS_dsbmv_d_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, int k, double alpha, const double *a, int lda,
		    const float *x, int incx, double beta,
		    double *y, int incy);
void BLAS_dsbmv_s_d(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, int k, double alpha, const float *a, int lda,
		    const double *x, int incx, double beta,
		    double *y, int incy);
void BLAS_dsbmv_s_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, int k, double alpha, const float *a, int lda,
		    const float *x, int incx, double beta,
		    double *y, int incy);
void BLAS_zsbmv_z_c(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, int k, const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zsbmv_c_z(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, int k, const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zsbmv_c_c(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, int k, const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_csbmv_c_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, int k, const void *alpha, const void *a, int lda,
		    const float *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_csbmv_s_c(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, int k, const void *alpha, const float *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_csbmv_s_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, int k, const void *alpha, const float *a, int lda,
		    const float *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zsbmv_z_d(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, int k, const void *alpha, const void *a, int lda,
		    const double *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zsbmv_d_z(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, int k, const void *alpha, const double *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zsbmv_d_d(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, int k, const void *alpha, const double *a, int lda,
		    const double *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_ssbmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, int k, float alpha, const float *a, int lda,
		  const float *x, int incx, float beta,
		  float *y, int incy, enum blas_prec_type prec);
void BLAS_dsbmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, int k, double alpha, const double *a, int lda,
		  const double *x, int incx, double beta,
		  double *y, int incy, enum blas_prec_type prec);
void BLAS_csbmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, int k, const void *alpha, const void *a, int lda,
		  const void *x, int incx, const void *beta,
		  void *y, int incy, enum blas_prec_type prec);
void BLAS_zsbmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, int k, const void *alpha, const void *a, int lda,
		  const void *x, int incx, const void *beta,
		  void *y, int incy, enum blas_prec_type prec);
void BLAS_dsbmv_d_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, int k, double alpha, const double *a, int lda,
		      const float *x, int incx, double beta,
		      double *y, int incy, enum blas_prec_type prec);
void BLAS_dsbmv_s_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, int k, double alpha, const float *a, int lda,
		      const double *x, int incx, double beta,
		      double *y, int incy, enum blas_prec_type prec);
void BLAS_dsbmv_s_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, int k, double alpha, const float *a, int lda,
		      const float *x, int incx, double beta,
		      double *y, int incy, enum blas_prec_type prec);
void BLAS_zsbmv_z_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, int k, const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zsbmv_c_z_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, int k, const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zsbmv_c_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, int k, const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_csbmv_c_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, int k, const void *alpha, const void *a, int lda,
		      const float *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_csbmv_s_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, int k, const void *alpha, const float *a,
		      int lda, const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_csbmv_s_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, int k, const void *alpha, const float *a,
		      int lda, const float *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zsbmv_z_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, int k, const void *alpha, const void *a, int lda,
		      const double *x, int incx, const void *beta, void *y,
		      int incy, enum blas_prec_type prec);
void BLAS_zsbmv_d_z_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, int k, const void *alpha, const double *a,
		      int lda, const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zsbmv_d_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, int k, const void *alpha, const double *a,
		      int lda, const double *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);


void BLAS_zhemv_z_c(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zhemv_c_z(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zhemv_c_c(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_chemv_c_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *a, int lda,
		    const float *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zhemv_z_d(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *a, int lda,
		    const double *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_chemv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, const void *alpha, const void *a, int lda,
		  const void *x, int incx, const void *beta,
		  void *y, int incy, enum blas_prec_type prec);
void BLAS_zhemv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, const void *alpha, const void *a, int lda,
		  const void *x, int incx, const void *beta,
		  void *y, int incy, enum blas_prec_type prec);
void BLAS_zhemv_z_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zhemv_c_z_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zhemv_c_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_chemv_c_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *a, int lda,
		      const float *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zhemv_z_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *a, int lda,
		      const double *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);


void BLAS_zhpmv_z_c(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *ap,
		    const void *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_zhpmv_c_z(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *ap,
		    const void *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_zhpmv_c_c(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *ap,
		    const void *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_chpmv_c_s(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *ap,
		    const float *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_zhpmv_z_d(enum blas_order_type order, enum blas_uplo_type uplo,
		    int n, const void *alpha, const void *ap,
		    const double *x, int incx, const void *beta, void *y,
		    int incy);
void BLAS_chpmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, const void *alpha, const void *ap,
		  const void *x, int incx, const void *beta, void *y,
		  int incy, enum blas_prec_type prec);
void BLAS_zhpmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  int n, const void *alpha, const void *ap,
		  const void *x, int incx, const void *beta, void *y,
		  int incy, enum blas_prec_type prec);
void BLAS_zhpmv_z_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *ap,
		      const void *x, int incx, const void *beta, void *y,
		      int incy, enum blas_prec_type prec);
void BLAS_zhpmv_c_z_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *ap,
		      const void *x, int incx, const void *beta, void *y,
		      int incy, enum blas_prec_type prec);
void BLAS_zhpmv_c_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *ap,
		      const void *x, int incx, const void *beta, void *y,
		      int incy, enum blas_prec_type prec);
void BLAS_chpmv_c_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *ap,
		      const float *x, int incx, const void *beta, void *y,
		      int incy, enum blas_prec_type prec);
void BLAS_zhpmv_z_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		      int n, const void *alpha, const void *ap,
		      const double *x, int incx, const void *beta, void *y,
		      int incy, enum blas_prec_type prec);


void BLAS_zhbmv_z_c(enum blas_order_type order,
		    enum blas_uplo_type uplo, int n, int k,
		    const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zhbmv_c_z(enum blas_order_type order,
		    enum blas_uplo_type uplo, int n, int k,
		    const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zhbmv_c_c(enum blas_order_type order,
		    enum blas_uplo_type uplo, int n, int k,
		    const void *alpha, const void *a, int lda,
		    const void *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_chbmv_c_s(enum blas_order_type order,
		    enum blas_uplo_type uplo, int n, int k,
		    const void *alpha, const void *a, int lda,
		    const float *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_zhbmv_z_d(enum blas_order_type order,
		    enum blas_uplo_type uplo, int n, int k,
		    const void *alpha, const void *a, int lda,
		    const double *x, int incx, const void *beta,
		    void *y, int incy);
void BLAS_chbmv_x(enum blas_order_type order,
		  enum blas_uplo_type uplo, int n, int k,
		  const void *alpha, const void *a, int lda,
		  const void *x, int incx, const void *beta,
		  void *y, int incy, enum blas_prec_type prec);
void BLAS_zhbmv_x(enum blas_order_type order,
		  enum blas_uplo_type uplo, int n, int k,
		  const void *alpha, const void *a, int lda,
		  const void *x, int incx, const void *beta,
		  void *y, int incy, enum blas_prec_type prec);
void BLAS_zhbmv_z_c_x(enum blas_order_type order,
		      enum blas_uplo_type uplo, int n, int k,
		      const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zhbmv_c_z_x(enum blas_order_type order,
		      enum blas_uplo_type uplo, int n, int k,
		      const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zhbmv_c_c_x(enum blas_order_type order,
		      enum blas_uplo_type uplo, int n, int k,
		      const void *alpha, const void *a, int lda,
		      const void *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_chbmv_c_s_x(enum blas_order_type order,
		      enum blas_uplo_type uplo, int n, int k,
		      const void *alpha, const void *a, int lda,
		      const float *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);
void BLAS_zhbmv_z_d_x(enum blas_order_type order,
		      enum blas_uplo_type uplo, int n, int k,
		      const void *alpha, const void *a, int lda,
		      const double *x, int incx, const void *beta,
		      void *y, int incy, enum blas_prec_type prec);


void BLAS_dtrmv_s(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag, int n,
		  double alpha, const float *T, int ldt, double *x, int incx);
void BLAS_ztrmv_c(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag, int n,
		  const void *alpha, const void *T, int ldt,
		  void *x, int incx);
void BLAS_ctrmv_s(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag, int n,
		  const void *alpha, const float *T, int ldt,
		  void *x, int incx);
void BLAS_ztrmv_d(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag, int n,
		  const void *alpha, const double *T, int ldt,
		  void *x, int incx);
void BLAS_strmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag, int n,
		  float alpha, const float *T, int ldt,
		  float *x, int incx, enum blas_prec_type prec);
void BLAS_dtrmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag, int n,
		  double alpha, const double *T, int ldt,
		  double *x, int incx, enum blas_prec_type prec);
void BLAS_ctrmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag, int n,
		  const void *alpha, const void *T, int ldt,
		  void *x, int incx, enum blas_prec_type prec);
void BLAS_ztrmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag, int n,
		  const void *alpha, const void *T, int ldt,
		  void *x, int incx, enum blas_prec_type prec);
void BLAS_dtrmv_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, double alpha, const float *T, int ldt, double *x,
		    int incx, enum blas_prec_type prec);
void BLAS_ztrmv_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, const void *alpha, const void *T, int ldt, void *x,
		    int incx, enum blas_prec_type prec);
void BLAS_ctrmv_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, const void *alpha, const float *T, int ldt,
		    void *x, int incx, enum blas_prec_type prec);
void BLAS_ztrmv_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, const void *alpha, const double *T, int ldt,
		    void *x, int incx, enum blas_prec_type prec);


void BLAS_dtpmv_s(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, double alpha, const float *tp, double *x, int incx);
void BLAS_ztpmv_c(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, const void *alpha, const void *tp,
		  void *x, int incx);
void BLAS_ctpmv_s(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, const void *alpha, const float *tp,
		  void *x, int incx);
void BLAS_ztpmv_d(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, const void *alpha, const double *tp,
		  void *x, int incx);
void BLAS_stpmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, float alpha, const float *tp,
		  float *x, int incx, enum blas_prec_type prec);
void BLAS_dtpmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, double alpha, const double *tp,
		  double *x, int incx, enum blas_prec_type prec);
void BLAS_ctpmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, const void *alpha, const void *tp,
		  void *x, int incx, enum blas_prec_type prec);
void BLAS_ztpmv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, const void *alpha, const void *tp,
		  void *x, int incx, enum blas_prec_type prec);
void BLAS_dtpmv_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, double alpha, const float *tp,
		    double *x, int incx, enum blas_prec_type prec);
void BLAS_ztpmv_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, const void *alpha, const void *tp,
		    void *x, int incx, enum blas_prec_type prec);
void BLAS_ctpmv_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, const void *alpha, const float *tp,
		    void *x, int incx, enum blas_prec_type prec);
void BLAS_ztpmv_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, const void *alpha, const double *tp,
		    void *x, int incx, enum blas_prec_type prec);


void BLAS_dtrsv_s(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, double alpha, const float *T, int ldt,
		  double *x, int incx);
void BLAS_ztrsv_c(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, const void *alpha, const void *T, int ldt,
		  void *x, int incx);
void BLAS_ctrsv_s(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, const void *alpha, const float *T, int ldt,
		  void *x, int incx);
void BLAS_ztrsv_d(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, const void *alpha, const double *T, int ldt,
		  void *x, int incx);
void BLAS_strsv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, float alpha, const float *T, int ldt,
		  float *x, int incx, enum blas_prec_type prec);
void BLAS_dtrsv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, double alpha, const double *T, int ldt,
		  double *x, int incx, enum blas_prec_type prec);
void BLAS_dtrsv_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, double alpha, const float *T, int ldt,
		    double *x, int incx, enum blas_prec_type prec);
void BLAS_ctrsv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, const void *alpha, const void *T, int ldt,
		  void *x, int incx, enum blas_prec_type prec);
void BLAS_ztrsv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, const void *alpha, const void *T, int ldt,
		  void *x, int incx, enum blas_prec_type prec);
void BLAS_ztrsv_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, const void *alpha, const void *T, int ldt,
		    void *x, int incx, enum blas_prec_type prec);
void BLAS_ctrsv_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, const void *alpha, const float *T, int ldt,
		    void *x, int incx, enum blas_prec_type prec);
void BLAS_ztrsv_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, const void *alpha, const double *T, int ldt,
		    void *x, int incx, enum blas_prec_type prec);


void BLAS_dtbsv_s(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, int k, double alpha, const float *t, int ldt,
		  double *x, int incx);
void BLAS_ztbsv_c(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, int k, const void *alpha, const void *t, int ldt,
		  void *x, int incx);
void BLAS_ctbsv_s(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, int k, const void *alpha, const float *t, int ldt,
		  void *x, int incx);
void BLAS_ztbsv_d(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, int k, const void *alpha, const double *t, int ldt,
		  void *x, int incx);
void BLAS_stbsv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, int k, float alpha, const float *t, int ldt,
		  float *x, int incx, enum blas_prec_type prec);
void BLAS_dtbsv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, int k, double alpha, const double *t, int ldt,
		  double *x, int incx, enum blas_prec_type prec);
void BLAS_dtbsv_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, int k, double alpha, const float *t, int ldt,
		    double *x, int incx, enum blas_prec_type prec);
void BLAS_ctbsv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, int k, const void *alpha, const void *t, int ldt,
		  void *x, int incx, enum blas_prec_type prec);
void BLAS_ztbsv_x(enum blas_order_type order, enum blas_uplo_type uplo,
		  enum blas_trans_type trans, enum blas_diag_type diag,
		  int n, int k, const void *alpha, const void *t, int ldt,
		  void *x, int incx, enum blas_prec_type prec);
void BLAS_ztbsv_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, int k, const void *alpha, const void *t, int ldt,
		    void *x, int incx, enum blas_prec_type prec);
void BLAS_ctbsv_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, int k, const void *alpha, const float *t, int ldt,
		    void *x, int incx, enum blas_prec_type prec);
void BLAS_ztbsv_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		    enum blas_trans_type trans, enum blas_diag_type diag,
		    int n, int k, const void *alpha, const double *t, int ldt,
		    void *x, int incx, enum blas_prec_type prec);


void BLAS_dgemm_d_s(enum blas_order_type order, enum blas_trans_type transa,
		    enum blas_trans_type transb, int m, int n, int k,
		    double alpha, const double *a, int lda, const float *b,
		    int ldb, double beta, double *c, int ldc);
void BLAS_dgemm_s_d(enum blas_order_type order, enum blas_trans_type transa,
		    enum blas_trans_type transb, int m, int n, int k,
		    double alpha, const float *a, int lda, const double *b,
		    int ldb, double beta, double *c, int ldc);
void BLAS_dgemm_s_s(enum blas_order_type order, enum blas_trans_type transa,
		    enum blas_trans_type transb, int m, int n, int k,
		    double alpha, const float *a, int lda, const float *b,
		    int ldb, double beta, double *c, int ldc);
void BLAS_zgemm_z_c(enum blas_order_type order, enum blas_trans_type transa,
		    enum blas_trans_type transb, int m, int n, int k,
		    const void *alpha, const void *a, int lda, const void *b,
		    int ldb, const void *beta, void *c, int ldc);
void BLAS_zgemm_c_z(enum blas_order_type order, enum blas_trans_type transa,
		    enum blas_trans_type transb, int m, int n, int k,
		    const void *alpha, const void *a, int lda, const void *b,
		    int ldb, const void *beta, void *c, int ldc);
void BLAS_zgemm_c_c(enum blas_order_type order, enum blas_trans_type transa,
		    enum blas_trans_type transb, int m, int n, int k,
		    const void *alpha, const void *a, int lda, const void *b,
		    int ldb, const void *beta, void *c, int ldc);
void BLAS_cgemm_c_s(enum blas_order_type order, enum blas_trans_type transa,
		    enum blas_trans_type transb, int m, int n, int k,
		    const void *alpha, const void *a, int lda, const float *b,
		    int ldb, const void *beta, void *c, int ldc);
void BLAS_cgemm_s_c(enum blas_order_type order, enum blas_trans_type transa,
		    enum blas_trans_type transb, int m, int n, int k,
		    const void *alpha, const float *a, int lda, const void *b,
		    int ldb, const void *beta, void *c, int ldc);
void BLAS_cgemm_s_s(enum blas_order_type order, enum blas_trans_type transa,
		    enum blas_trans_type transb, int m, int n, int k,
		    const void *alpha, const float *a, int lda,
		    const float *b, int ldb, const void *beta, void *c,
		    int ldc);
void BLAS_zgemm_z_d(enum blas_order_type order, enum blas_trans_type transa,
		    enum blas_trans_type transb, int m, int n, int k,
		    const void *alpha, const void *a, int lda,
		    const double *b, int ldb, const void *beta, void *c,
		    int ldc);
void BLAS_zgemm_d_z(enum blas_order_type order, enum blas_trans_type transa,
		    enum blas_trans_type transb, int m, int n, int k,
		    const void *alpha, const double *a, int lda,
		    const void *b, int ldb, const void *beta, void *c,
		    int ldc);
void BLAS_zgemm_d_d(enum blas_order_type order, enum blas_trans_type transa,
		    enum blas_trans_type transb, int m, int n, int k,
		    const void *alpha, const double *a, int lda,
		    const double *b, int ldb, const void *beta, void *c,
		    int ldc);
void BLAS_sgemm_x(enum blas_order_type order, enum blas_trans_type transa,
		  enum blas_trans_type transb, int m, int n, int k,
		  float alpha, const float *a, int lda, const float *b,
		  int ldb, float beta, float *c, int ldc,
		  enum blas_prec_type prec);
void BLAS_dgemm_x(enum blas_order_type order, enum blas_trans_type transa,
		  enum blas_trans_type transb, int m, int n, int k,
		  double alpha, const double *a, int lda, const double *b,
		  int ldb, double beta, double *c, int ldc,
		  enum blas_prec_type prec);
void BLAS_cgemm_x(enum blas_order_type order, enum blas_trans_type transa,
		  enum blas_trans_type transb, int m, int n, int k,
		  const void *alpha, const void *a, int lda, const void *b,
		  int ldb, const void *beta, void *c, int ldc,
		  enum blas_prec_type prec);
void BLAS_zgemm_x(enum blas_order_type order, enum blas_trans_type transa,
		  enum blas_trans_type transb, int m, int n, int k,
		  const void *alpha, const void *a, int lda, const void *b,
		  int ldb, const void *beta, void *c, int ldc,
		  enum blas_prec_type prec);
void BLAS_dgemm_d_s_x(enum blas_order_type order, enum blas_trans_type transa,
		      enum blas_trans_type transb, int m, int n, int k,
		      double alpha, const double *a, int lda, const float *b,
		      int ldb, double beta, double *c, int ldc,
		      enum blas_prec_type prec);
void BLAS_dgemm_s_d_x(enum blas_order_type order, enum blas_trans_type transa,
		      enum blas_trans_type transb, int m, int n, int k,
		      double alpha, const float *a, int lda, const double *b,
		      int ldb, double beta, double *c, int ldc,
		      enum blas_prec_type prec);
void BLAS_dgemm_s_s_x(enum blas_order_type order, enum blas_trans_type transa,
		      enum blas_trans_type transb, int m, int n, int k,
		      double alpha, const float *a, int lda, const float *b,
		      int ldb, double beta, double *c, int ldc,
		      enum blas_prec_type prec);
void BLAS_zgemm_z_c_x(enum blas_order_type order, enum blas_trans_type transa,
		      enum blas_trans_type transb, int m, int n, int k,
		      const void *alpha, const void *a, int lda,
		      const void *b, int ldb, const void *beta, void *c,
		      int ldc, enum blas_prec_type prec);
void BLAS_zgemm_c_z_x(enum blas_order_type order, enum blas_trans_type transa,
		      enum blas_trans_type transb, int m, int n, int k,
		      const void *alpha, const void *a, int lda,
		      const void *b, int ldb, const void *beta, void *c,
		      int ldc, enum blas_prec_type prec);
void BLAS_zgemm_c_c_x(enum blas_order_type order, enum blas_trans_type transa,
		      enum blas_trans_type transb, int m, int n, int k,
		      const void *alpha, const void *a, int lda,
		      const void *b, int ldb, const void *beta, void *c,
		      int ldc, enum blas_prec_type prec);
void BLAS_cgemm_c_s_x(enum blas_order_type order, enum blas_trans_type transa,
		      enum blas_trans_type transb, int m, int n, int k,
		      const void *alpha, const void *a, int lda,
		      const float *b, int ldb, const void *beta, void *c,
		      int ldc, enum blas_prec_type prec);
void BLAS_cgemm_s_c_x(enum blas_order_type order, enum blas_trans_type transa,
		      enum blas_trans_type transb, int m, int n, int k,
		      const void *alpha, const float *a, int lda,
		      const void *b, int ldb, const void *beta, void *c,
		      int ldc, enum blas_prec_type prec);
void BLAS_cgemm_s_s_x(enum blas_order_type order, enum blas_trans_type transa,
		      enum blas_trans_type transb, int m, int n, int k,
		      const void *alpha, const float *a, int lda,
		      const float *b, int ldb, const void *beta, void *c,
		      int ldc, enum blas_prec_type prec);
void BLAS_zgemm_z_d_x(enum blas_order_type order, enum blas_trans_type transa,
		      enum blas_trans_type transb, int m, int n, int k,
		      const void *alpha, const void *a, int lda,
		      const double *b, int ldb, const void *beta, void *c,
		      int ldc, enum blas_prec_type prec);
void BLAS_zgemm_d_z_x(enum blas_order_type order, enum blas_trans_type transa,
		      enum blas_trans_type transb, int m, int n, int k,
		      const void *alpha, const double *a, int lda,
		      const void *b, int ldb, const void *beta, void *c,
		      int ldc, enum blas_prec_type prec);
void BLAS_zgemm_d_d_x(enum blas_order_type order, enum blas_trans_type transa,
		      enum blas_trans_type transb, int m, int n, int k,
		      const void *alpha, const double *a, int lda,
		      const double *b, int ldb, const void *beta, void *c,
		      int ldc, enum blas_prec_type prec);


void BLAS_dsymm_d_s(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    double alpha, const double *a, int lda,
		    const float *b, int ldb, double beta, double *c, int ldc);
void BLAS_dsymm_s_d(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    double alpha, const float *a, int lda,
		    const double *b, int ldb, double beta,
		    double *c, int ldc);
void BLAS_dsymm_s_s(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    double alpha, const float *a, int lda,
		    const float *b, int ldb, double beta, double *c, int ldc);
void BLAS_zsymm_z_c(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const void *a, int lda,
		    const void *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_zsymm_c_z(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const void *a, int lda,
		    const void *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_zsymm_c_c(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const void *a, int lda,
		    const void *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_csymm_c_s(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const void *a, int lda,
		    const float *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_csymm_s_c(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const float *a, int lda,
		    const void *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_csymm_s_s(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const float *a, int lda,
		    const float *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_zsymm_z_d(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const void *a, int lda,
		    const double *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_zsymm_d_z(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const double *a, int lda,
		    const void *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_zsymm_d_d(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const double *a, int lda,
		    const double *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_ssymm_x(enum blas_order_type order, enum blas_side_type side,
		  enum blas_uplo_type uplo, int m, int n,
		  float alpha, const float *a, int lda,
		  const float *b, int ldb, float beta,
		  float *c, int ldc, enum blas_prec_type prec);
void BLAS_dsymm_x(enum blas_order_type order, enum blas_side_type side,
		  enum blas_uplo_type uplo, int m, int n,
		  double alpha, const double *a, int lda,
		  const double *b, int ldb, double beta,
		  double *c, int ldc, enum blas_prec_type prec);
void BLAS_csymm_x(enum blas_order_type order, enum blas_side_type side,
		  enum blas_uplo_type uplo, int m, int n,
		  const void *alpha, const void *a, int lda,
		  const void *b, int ldb, const void *beta,
		  void *c, int ldc, enum blas_prec_type prec);
void BLAS_zsymm_x(enum blas_order_type order, enum blas_side_type side,
		  enum blas_uplo_type uplo, int m, int n,
		  const void *alpha, const void *a, int lda,
		  const void *b, int ldb, const void *beta,
		  void *c, int ldc, enum blas_prec_type prec);
void BLAS_dsymm_d_s_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      double alpha, const double *a, int lda,
		      const float *b, int ldb, double beta,
		      double *c, int ldc, enum blas_prec_type prec);
void BLAS_dsymm_s_d_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      double alpha, const float *a, int lda,
		      const double *b, int ldb, double beta,
		      double *c, int ldc, enum blas_prec_type prec);
void BLAS_dsymm_s_s_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      double alpha, const float *a, int lda,
		      const float *b, int ldb, double beta,
		      double *c, int ldc, enum blas_prec_type prec);
void BLAS_zsymm_z_c_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const void *a, int lda,
		      const void *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);
void BLAS_zsymm_c_z_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const void *a, int lda,
		      const void *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);
void BLAS_zsymm_c_c_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const void *a, int lda,
		      const void *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);
void BLAS_csymm_c_s_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const void *a, int lda,
		      const float *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);
void BLAS_csymm_s_c_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const float *a, int lda,
		      const void *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);
void BLAS_csymm_s_s_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const float *a, int lda,
		      const float *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);
void BLAS_zsymm_z_d_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const void *a, int lda,
		      const double *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);
void BLAS_zsymm_d_z_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const double *a, int lda,
		      const void *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);
void BLAS_zsymm_d_d_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const double *a, int lda,
		      const double *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);


void BLAS_zhemm_z_c(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const void *a, int lda,
		    const void *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_zhemm_c_z(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const void *a, int lda,
		    const void *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_zhemm_c_c(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const void *a, int lda,
		    const void *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_chemm_c_s(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const void *a, int lda,
		    const float *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_zhemm_z_d(enum blas_order_type order, enum blas_side_type side,
		    enum blas_uplo_type uplo, int m, int n,
		    const void *alpha, const void *a, int lda,
		    const double *b, int ldb, const void *beta,
		    void *c, int ldc);
void BLAS_chemm_x(enum blas_order_type order, enum blas_side_type side,
		  enum blas_uplo_type uplo, int m, int n,
		  const void *alpha, const void *a, int lda,
		  const void *b, int ldb, const void *beta,
		  void *c, int ldc, enum blas_prec_type prec);
void BLAS_zhemm_x(enum blas_order_type order, enum blas_side_type side,
		  enum blas_uplo_type uplo, int m, int n,
		  const void *alpha, const void *a, int lda,
		  const void *b, int ldb, const void *beta,
		  void *c, int ldc, enum blas_prec_type prec);
void BLAS_zhemm_z_c_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const void *a, int lda,
		      const void *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);
void BLAS_zhemm_c_z_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const void *a, int lda,
		      const void *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);
void BLAS_zhemm_c_c_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const void *a, int lda,
		      const void *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);
void BLAS_chemm_c_s_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const void *a, int lda,
		      const float *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);
void BLAS_zhemm_z_d_x(enum blas_order_type order, enum blas_side_type side,
		      enum blas_uplo_type uplo, int m, int n,
		      const void *alpha, const void *a, int lda,
		      const double *b, int ldb, const void *beta,
		      void *c, int ldc, enum blas_prec_type prec);


void BLAS_dgemv2_d_s(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, double alpha, const double *a, int lda,
		     const float *head_x, const float *tail_x, int incx,
		     double beta, double *y, int incy);
void BLAS_dgemv2_s_d(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, double alpha, const float *a, int lda,
		     const double *head_x, const double *tail_x, int incx,
		     double beta, double *y, int incy);
void BLAS_dgemv2_s_s(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, double alpha, const float *a, int lda,
		     const float *head_x, const float *tail_x, int incx,
		     double beta, double *y, int incy);
void BLAS_zgemv2_z_c(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, const void *alpha, const void *a, int lda,
		     const void *head_x, const void *tail_x, int incx,
		     const void *beta, void *y, int incy);
void BLAS_zgemv2_c_z(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, const void *alpha, const void *a, int lda,
		     const void *head_x, const void *tail_x, int incx,
		     const void *beta, void *y, int incy);
void BLAS_zgemv2_c_c(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, const void *alpha, const void *a, int lda,
		     const void *head_x, const void *tail_x, int incx,
		     const void *beta, void *y, int incy);
void BLAS_cgemv2_c_s(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, const void *alpha, const void *a, int lda,
		     const float *head_x, const float *tail_x, int incx,
		     const void *beta, void *y, int incy);
void BLAS_cgemv2_s_c(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, const void *alpha, const float *a, int lda,
		     const void *head_x, const void *tail_x, int incx,
		     const void *beta, void *y, int incy);
void BLAS_cgemv2_s_s(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, const void *alpha, const float *a, int lda,
		     const float *head_x, const float *tail_x, int incx,
		     const void *beta, void *y, int incy);
void BLAS_zgemv2_z_d(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, const void *alpha, const void *a, int lda,
		     const double *head_x, const double *tail_x, int incx,
		     const void *beta, void *y, int incy);
void BLAS_zgemv2_d_z(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, const void *alpha, const double *a,
		     int lda, const void *head_x, const void *tail_x,
		     int incx, const void *beta, void *y, int incy);
void BLAS_zgemv2_d_d(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, const void *alpha, const double *a,
		     int lda, const double *head_x, const double *tail_x,
		     int incx, const void *beta, void *y, int incy);
void BLAS_sgemv2_x(enum blas_order_type order, enum blas_trans_type trans,
		   int m, int n, float alpha, const float *a, int lda,
		   const float *head_x, const float *tail_x, int incx,
		   float beta, float *y, int incy, enum blas_prec_type prec);
void BLAS_dgemv2_x(enum blas_order_type order, enum blas_trans_type trans,
		   int m, int n, double alpha, const double *a, int lda,
		   const double *head_x, const double *tail_x, int incx,
		   double beta, double *y, int incy,
		   enum blas_prec_type prec);
void BLAS_cgemv2_x(enum blas_order_type order, enum blas_trans_type trans,
		   int m, int n, const void *alpha, const void *a, int lda,
		   const void *head_x, const void *tail_x, int incx,
		   const void *beta, void *y, int incy,
		   enum blas_prec_type prec);
void BLAS_zgemv2_x(enum blas_order_type order, enum blas_trans_type trans,
		   int m, int n, const void *alpha, const void *a, int lda,
		   const void *head_x, const void *tail_x, int incx,
		   const void *beta, void *y, int incy,
		   enum blas_prec_type prec);
void BLAS_dgemv2_d_s_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, double alpha, const double *a, int lda,
		       const float *head_x, const float *tail_x, int incx,
		       double beta, double *y, int incy,
		       enum blas_prec_type prec);
void BLAS_dgemv2_s_d_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, double alpha, const float *a, int lda,
		       const double *head_x, const double *tail_x, int incx,
		       double beta, double *y, int incy,
		       enum blas_prec_type prec);
void BLAS_dgemv2_s_s_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, double alpha, const float *a, int lda,
		       const float *head_x, const float *tail_x, int incx,
		       double beta, double *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zgemv2_z_c_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, const void *alpha, const void *a,
		       int lda, const void *head_x, const void *tail_x,
		       int incx, const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zgemv2_c_z_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, const void *alpha, const void *a,
		       int lda, const void *head_x, const void *tail_x,
		       int incx, const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zgemv2_c_c_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, const void *alpha, const void *a,
		       int lda, const void *head_x, const void *tail_x,
		       int incx, const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_cgemv2_c_s_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, const void *alpha, const void *a,
		       int lda, const float *head_x, const float *tail_x,
		       int incx, const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_cgemv2_s_c_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, const void *alpha, const float *a,
		       int lda, const void *head_x, const void *tail_x,
		       int incx, const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_cgemv2_s_s_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, const void *alpha, const float *a,
		       int lda, const float *head_x, const float *tail_x,
		       int incx, const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zgemv2_z_d_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, const void *alpha, const void *a,
		       int lda, const double *head_x, const double *tail_x,
		       int incx, const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zgemv2_d_z_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, const void *alpha, const double *a,
		       int lda, const void *head_x, const void *tail_x,
		       int incx, const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zgemv2_d_d_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, const void *alpha, const double *a,
		       int lda, const double *head_x, const double *tail_x,
		       int incx, const void *beta, void *y, int incy,
		       enum blas_prec_type prec);


void BLAS_dsymv2_d_s(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, double alpha, const double *a, int lda,
		     const float *x_head, const float *x_tail, int incx,
		     double beta, double *y, int incy);
void BLAS_dsymv2_s_d(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, double alpha, const float *a, int lda,
		     const double *x_head, const double *x_tail, int incx,
		     double beta, double *y, int incy);
void BLAS_dsymv2_s_s(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, double alpha, const float *a, int lda,
		     const float *x_head, const float *x_tail, int incx,
		     double beta, double *y, int incy);
void BLAS_zsymv2_z_c(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const void *a, int lda,
		     const void *x_head, const void *x_tail, int incx,
		     const void *beta, void *y, int incy);
void BLAS_zsymv2_c_z(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const void *a, int lda,
		     const void *x_head, const void *x_tail, int incx,
		     const void *beta, void *y, int incy);
void BLAS_zsymv2_c_c(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const void *a, int lda,
		     const void *x_head, const void *x_tail, int incx,
		     const void *beta, void *y, int incy);
void BLAS_csymv2_c_s(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const void *a, int lda,
		     const float *x_head, const float *x_tail, int incx,
		     const void *beta, void *y, int incy);
void BLAS_csymv2_s_c(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const float *a, int lda,
		     const void *x_head, const void *x_tail, int incx,
		     const void *beta, void *y, int incy);
void BLAS_csymv2_s_s(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const float *a, int lda,
		     const float *x_head, const float *x_tail, int incx,
		     const void *beta, void *y, int incy);
void BLAS_zsymv2_z_d(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const void *a, int lda,
		     const double *x_head, const double *x_tail, int incx,
		     const void *beta, void *y, int incy);
void BLAS_zsymv2_d_z(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const double *a, int lda,
		     const void *x_head, const void *x_tail, int incx,
		     const void *beta, void *y, int incy);
void BLAS_zsymv2_d_d(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const double *a, int lda,
		     const double *x_head, const double *x_tail, int incx,
		     const void *beta, void *y, int incy);
void BLAS_ssymv2_x(enum blas_order_type order, enum blas_uplo_type uplo,
		   int n, float alpha, const float *a, int lda,
		   const float *x_head, const float *x_tail, int incx,
		   float beta, float *y, int incy, enum blas_prec_type prec);
void BLAS_dsymv2_x(enum blas_order_type order, enum blas_uplo_type uplo,
		   int n, double alpha, const double *a, int lda,
		   const double *x_head, const double *x_tail, int incx,
		   double beta, double *y, int incy,
		   enum blas_prec_type prec);
void BLAS_csymv2_x(enum blas_order_type order, enum blas_uplo_type uplo,
		   int n, const void *alpha, const void *a, int lda,
		   const void *x_head, const void *x_tail, int incx,
		   const void *beta, void *y, int incy,
		   enum blas_prec_type prec);
void BLAS_zsymv2_x(enum blas_order_type order, enum blas_uplo_type uplo,
		   int n, const void *alpha, const void *a, int lda,
		   const void *x_head, const void *x_tail, int incx,
		   const void *beta, void *y, int incy,
		   enum blas_prec_type prec);
void BLAS_dsymv2_d_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, double alpha, const double *a, int lda,
		       const float *x_head, const float *x_tail, int incx,
		       double beta, double *y, int incy,
		       enum blas_prec_type prec);
void BLAS_dsymv2_s_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, double alpha, const float *a, int lda,
		       const double *x_head, const double *x_tail, int incx,
		       double beta, double *y, int incy,
		       enum blas_prec_type prec);
void BLAS_dsymv2_s_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, double alpha, const float *a, int lda,
		       const float *x_head, const float *x_tail, int incx,
		       double beta, double *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zsymv2_z_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const void *a, int lda,
		       const void *x_head, const void *x_tail, int incx,
		       const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zsymv2_c_z_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const void *a, int lda,
		       const void *x_head, const void *x_tail, int incx,
		       const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zsymv2_c_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const void *a, int lda,
		       const void *x_head, const void *x_tail, int incx,
		       const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_csymv2_c_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const void *a, int lda,
		       const float *x_head, const float *x_tail, int incx,
		       const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_csymv2_s_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const float *a, int lda,
		       const void *x_head, const void *x_tail, int incx,
		       const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_csymv2_s_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const float *a, int lda,
		       const float *x_head, const float *x_tail, int incx,
		       const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zsymv2_z_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const void *a, int lda,
		       const double *x_head, const double *x_tail, int incx,
		       const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zsymv2_d_z_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const double *a, int lda,
		       const void *x_head, const void *x_tail, int incx,
		       const void *beta, void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zsymv2_d_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const double *a, int lda,
		       const double *x_head, const double *x_tail, int incx,
		       const void *beta, void *y, int incy,
		       enum blas_prec_type prec);


void BLAS_zhemv2_z_c(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const void *a, int lda,
		     const void *x_head, const void *x_tail, int incx,
		     const void *beta, const void *y, int incy);
void BLAS_zhemv2_c_z(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const void *a, int lda,
		     const void *x_head, const void *x_tail, int incx,
		     const void *beta, const void *y, int incy);
void BLAS_zhemv2_c_c(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const void *a, int lda,
		     const void *x_head, const void *x_tail, int incx,
		     const void *beta, const void *y, int incy);
void BLAS_chemv2_c_s(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const void *a, int lda,
		     const float *x_head, const float *x_tail, int incx,
		     const void *beta, const float *y, int incy);
void BLAS_zhemv2_z_d(enum blas_order_type order, enum blas_uplo_type uplo,
		     int n, const void *alpha, const void *a, int lda,
		     const double *x_head, const double *x_tail, int incx,
		     const void *beta, const double *y, int incy);
void BLAS_chemv2_x(enum blas_order_type order, enum blas_uplo_type uplo,
		   int n, const void *alpha, const void *a, int lda,
		   const void *x_head, const void *x_tail, int incx,
		   const void *beta, const void *y, int incy,
		   enum blas_prec_type prec);
void BLAS_zhemv2_x(enum blas_order_type order, enum blas_uplo_type uplo,
		   int n, const void *alpha, const void *a, int lda,
		   const void *x_head, const void *x_tail, int incx,
		   const void *beta, const void *y, int incy,
		   enum blas_prec_type prec);
void BLAS_zhemv2_z_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const void *a, int lda,
		       const void *x_head, const void *x_tail, int incx,
		       const void *beta, const void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zhemv2_c_z_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const void *a, int lda,
		       const void *x_head, const void *x_tail, int incx,
		       const void *beta, const void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zhemv2_c_c_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const void *a, int lda,
		       const void *x_head, const void *x_tail, int incx,
		       const void *beta, const void *y, int incy,
		       enum blas_prec_type prec);
void BLAS_chemv2_c_s_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const void *a, int lda,
		       const float *x_head, const float *x_tail, int incx,
		       const void *beta, const float *y, int incy,
		       enum blas_prec_type prec);
void BLAS_zhemv2_z_d_x(enum blas_order_type order, enum blas_uplo_type uplo,
		       int n, const void *alpha, const void *a, int lda,
		       const double *x_head, const double *x_tail, int incx,
		       const void *beta, const double *y, int incy,
		       enum blas_prec_type prec);


void BLAS_dgbmv2_d_s(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, int kl, int ku, double alpha,
		     const double *a, int lda, const float *head_x,
		     const float *tail_x, int incx, double beta,
		     double *y, int incy);
void BLAS_dgbmv2_s_d(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, int kl, int ku, double alpha,
		     const float *a, int lda, const double *head_x,
		     const double *tail_x, int incx, double beta,
		     double *y, int incy);
void BLAS_dgbmv2_s_s(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, int kl, int ku, double alpha,
		     const float *a, int lda, const float *head_x,
		     const float *tail_x, int incx, double beta,
		     double *y, int incy);
void BLAS_zgbmv2_z_c(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, int kl, int ku, const void *alpha,
		     const void *a, int lda, const void *head_x,
		     const void *tail_x, int incx, const void *beta,
		     void *y, int incy);
void BLAS_zgbmv2_c_z(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, int kl, int ku, const void *alpha,
		     const void *a, int lda, const void *head_x,
		     const void *tail_x, int incx, const void *beta,
		     void *y, int incy);
void BLAS_zgbmv2_c_c(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, int kl, int ku, const void *alpha,
		     const void *a, int lda, const void *head_x,
		     const void *tail_x, int incx, const void *beta,
		     void *y, int incy);
void BLAS_cgbmv2_c_s(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, int kl, int ku, const void *alpha,
		     const void *a, int lda, const float *head_x,
		     const float *tail_x, int incx, const void *beta,
		     void *y, int incy);
void BLAS_cgbmv2_s_c(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, int kl, int ku, const void *alpha,
		     const float *a, int lda, const void *head_x,
		     const void *tail_x, int incx, const void *beta,
		     void *y, int incy);
void BLAS_cgbmv2_s_s(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, int kl, int ku, const void *alpha,
		     const float *a, int lda, const float *head_x,
		     const float *tail_x, int incx, const void *beta,
		     void *y, int incy);
void BLAS_zgbmv2_z_d(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, int kl, int ku, const void *alpha,
		     const void *a, int lda, const double *head_x,
		     const double *tail_x, int incx, const void *beta,
		     void *y, int incy);
void BLAS_zgbmv2_d_z(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, int kl, int ku, const void *alpha,
		     const double *a, int lda, const void *head_x,
		     const void *tail_x, int incx, const void *beta,
		     void *y, int incy);
void BLAS_zgbmv2_d_d(enum blas_order_type order, enum blas_trans_type trans,
		     int m, int n, int kl, int ku, const void *alpha,
		     const double *a, int lda, const double *head_x,
		     const double *tail_x, int incx, const void *beta,
		     void *y, int incy);
void BLAS_sgbmv2_x(enum blas_order_type order, enum blas_trans_type trans,
		   int m, int n, int kl, int ku, float alpha,
		   const float *a, int lda, const float *head_x,
		   const float *tail_x, int incx, float beta,
		   float *y, int incy, enum blas_prec_type prec);
void BLAS_dgbmv2_x(enum blas_order_type order, enum blas_trans_type trans,
		   int m, int n, int kl, int ku, double alpha,
		   const double *a, int lda, const double *head_x,
		   const double *tail_x, int incx, double beta,
		   double *y, int incy, enum blas_prec_type prec);
void BLAS_cgbmv2_x(enum blas_order_type order, enum blas_trans_type trans,
		   int m, int n, int kl, int ku, const void *alpha,
		   const void *a, int lda, const void *head_x,
		   const void *tail_x, int incx, const void *beta,
		   void *y, int incy, enum blas_prec_type prec);
void BLAS_zgbmv2_x(enum blas_order_type order, enum blas_trans_type trans,
		   int m, int n, int kl, int ku, const void *alpha,
		   const void *a, int lda, const void *head_x,
		   const void *tail_x, int incx, const void *beta,
		   void *y, int incy, enum blas_prec_type prec);
void BLAS_dgbmv2_d_s_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, int kl, int ku, double alpha,
		       const double *a, int lda, const float *head_x,
		       const float *tail_x, int incx, double beta,
		       double *y, int incy, enum blas_prec_type prec);
void BLAS_dgbmv2_s_d_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, int kl, int ku, double alpha,
		       const float *a, int lda, const double *head_x,
		       const double *tail_x, int incx, double beta,
		       double *y, int incy, enum blas_prec_type prec);
void BLAS_dgbmv2_s_s_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, int kl, int ku, double alpha,
		       const float *a, int lda, const float *head_x,
		       const float *tail_x, int incx, double beta,
		       double *y, int incy, enum blas_prec_type prec);
void BLAS_zgbmv2_z_c_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, int kl, int ku, const void *alpha,
		       const void *a, int lda, const void *head_x,
		       const void *tail_x, int incx, const void *beta,
		       void *y, int incy, enum blas_prec_type prec);
void BLAS_zgbmv2_c_z_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, int kl, int ku, const void *alpha,
		       const void *a, int lda, const void *head_x,
		       const void *tail_x, int incx, const void *beta,
		       void *y, int incy, enum blas_prec_type prec);
void BLAS_zgbmv2_c_c_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, int kl, int ku, const void *alpha,
		       const void *a, int lda, const void *head_x,
		       const void *tail_x, int incx, const void *beta,
		       void *y, int incy, enum blas_prec_type prec);
void BLAS_cgbmv2_c_s_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, int kl, int ku, const void *alpha,
		       const void *a, int lda, const float *head_x,
		       const float *tail_x, int incx, const void *beta,
		       void *y, int incy, enum blas_prec_type prec);
void BLAS_cgbmv2_s_c_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, int kl, int ku, const void *alpha,
		       const float *a, int lda, const void *head_x,
		       const void *tail_x, int incx, const void *beta,
		       void *y, int incy, enum blas_prec_type prec);
void BLAS_cgbmv2_s_s_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, int kl, int ku, const void *alpha,
		       const float *a, int lda, const float *head_x,
		       const float *tail_x, int incx, const void *beta,
		       void *y, int incy, enum blas_prec_type prec);
void BLAS_zgbmv2_z_d_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, int kl, int ku, const void *alpha,
		       const void *a, int lda, const double *head_x,
		       const double *tail_x, int incx, const void *beta,
		       void *y, int incy, enum blas_prec_type prec);
void BLAS_zgbmv2_d_z_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, int kl, int ku, const void *alpha,
		       const double *a, int lda, const void *head_x,
		       const void *tail_x, int incx, const void *beta,
		       void *y, int incy, enum blas_prec_type prec);
void BLAS_zgbmv2_d_d_x(enum blas_order_type order, enum blas_trans_type trans,
		       int m, int n, int kl, int ku, const void *alpha,
		       const double *a, int lda, const double *head_x,
		       const double *tail_x, int incx, const void *beta,
		       void *y, int incy, enum blas_prec_type prec);



int BLAS_fpinfo_x(enum blas_cmach_type cmach, enum blas_prec_type prec);
void BLAS_error(const char *rname, int iflag, int ival, char *form, ...);

#endif /* BLAS_EXTENDED_PROTO_H */
#ifndef BLAS_FPU_H
#define BLAS_FPU_H

/* Contains code to set up the FPU control registers on x86
   systems.  The current double-double code requires that 
   all arithmetic is done in double precision (as opposed to
   double-extended).                                         */

#ifdef x86
#ifdef _WIN32

#include <float.h>
#define FPU_FIX_DECL unsigned int __old_cw, __new_cw;
#define FPU_FIX_START \
  __old_cw = _control87(0, 0);  \
  __new_cw = _control87(0x00010000, 0x00030000);
#define FPU_FIX_STOP \
  _control87(*_old_cw, 0xFFFFFFFF);
#else  /* _WIN32 */

#if HAVE_FPU_CONTROL_H
#include <fpu_control.h>
#endif

#ifndef _FPU_GETCW
#define _FPU_GETCW(x) asm volatile ("fnstcw %0":"=m" (x));
#endif

#ifndef _FPU_SETCW
#define _FPU_SETCW(x) asm volatile ("fldcw %0": :"m" (x));
#endif

#ifndef _FPU_EXTENDED
#define _FPU_EXTENDED 0x0300
#endif

#ifndef _FPU_DOUBLE
#define _FPU_DOUBLE 0x0200
#endif

#define FPU_FIX_DECL unsigned short __old_cw, __new_cw;
#define FPU_FIX_START \
  _FPU_GETCW(__old_cw); \
  __new_cw = (__old_cw & ~_FPU_EXTENDED) | _FPU_DOUBLE; \
  _FPU_SETCW(__new_cw); 
#define FPU_FIX_STOP \
  _FPU_SETCW(__old_cw);
#endif  /* else _WIN32 */

#else   /* x86 */
#define FPU_FIX_DECL
#define FPU_FIX_START
#define FPU_FIX_STOP
#endif  /* else x86 */

#endif /* BLAS_FPU_H */

#ifndef BLAS_MALLOC_H
#define BLAS_MALLOC_H 1

#ifdef NO_BLASMALLOC

#include <malloc.h>
#define blas_malloc(s) malloc(s)
#define blas_realloc(p, s) realloc(p,s)
#define blas_free(p) free(p)

#else

/* stddef is needed for size_t */
#include <stddef.h>
void  *blas_malloc(size_t size);
void *blas_realloc(void *p, size_t size);
void blas_free(void *p);


#endif

#endif
#if !defined(XBLAS_F2C_BRIDGE_H_)
#define XBLAS_F2C_BRIDGE_H_

/*
  Adapting to a specific Fortran name mangling requires adding
  some of the following CPP flags in make.inc:

    CONFIG_FC_UNDERSCORE       : Add one underscore to each name.

    CONFIG_FC_DBL_UNDERSCORE   : If the name has an underscore in it already,
                                 add two; otherwise add one.

    CONFIG_FC_UCASE            : The name is converted to upper-case; default
                                 is lower-case.

    CONFIG_FC_RETURNS_DBL_REAL : REAL values are returned in C doubles as in
                                 f2c.  (currently unused)

  The first two flags are mutually exclusive.
*/

#if defined(CONFIG_FC_UNDERSCORE)
#define FC_UNDER(x) x##_
#define FC_UNDER2(x) x##_
#elif defined(CONFIG_FC_DBL_UNDERSCORE)
#define FC_UNDER(x) x##_
#define FC_UNDER2(x) x##__
#else
#define FC_UNDER(x) x
#define FC_UNDER2(x) x
#endif

#if defined(CONFIG_FC_UCASE)
#define FC_FUNC(x,X) FC_UNDER(X)
#define FC_FUNC_(x,X) FC_UNDER2(X)
#else
#define FC_FUNC(x,X) FC_UNDER(x)
#define FC_FUNC_(x,X) FC_UNDER2(x)
#endif

#if defined(CONFIG_FC_RETURNS_DBL_REAL)
typedef double fc_real_result_t;
#else
typedef float fc_real_result_t;
#endif

/*
  Possible future config options:

  CONFIG_FC_STUPID_TYPES
    When the Fortran compiler defines 64-bit REALs and INTEGERs
    as the default KIND.
*/

#endif /* XBLAS_F2C_BRIDGE_H_ */
