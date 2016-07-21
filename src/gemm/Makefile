include ../../make.inc

SRC_PATH = .
HEADER_PATH = ../include

GEMM_SRCS =\
	$(SRC_PATH)/BLAS_dgemm_d_s.c\
	$(SRC_PATH)/BLAS_dgemm_s_d.c\
	$(SRC_PATH)/BLAS_dgemm_s_s.c\
	$(SRC_PATH)/BLAS_zgemm_z_c.c\
	$(SRC_PATH)/BLAS_zgemm_c_z.c\
	$(SRC_PATH)/BLAS_zgemm_c_c.c\
	$(SRC_PATH)/BLAS_cgemm_c_s.c\
	$(SRC_PATH)/BLAS_cgemm_s_c.c\
	$(SRC_PATH)/BLAS_cgemm_s_s.c\
	$(SRC_PATH)/BLAS_zgemm_z_d.c\
	$(SRC_PATH)/BLAS_zgemm_d_z.c\
	$(SRC_PATH)/BLAS_zgemm_d_d.c\
	$(SRC_PATH)/BLAS_sgemm_x.c\
	$(SRC_PATH)/BLAS_dgemm_x.c\
	$(SRC_PATH)/BLAS_cgemm_x.c\
	$(SRC_PATH)/BLAS_zgemm_x.c\
	$(SRC_PATH)/BLAS_dgemm_d_s_x.c\
	$(SRC_PATH)/BLAS_dgemm_s_d_x.c\
	$(SRC_PATH)/BLAS_dgemm_s_s_x.c\
	$(SRC_PATH)/BLAS_zgemm_z_c_x.c\
	$(SRC_PATH)/BLAS_zgemm_c_z_x.c\
	$(SRC_PATH)/BLAS_zgemm_c_c_x.c\
	$(SRC_PATH)/BLAS_cgemm_c_s_x.c\
	$(SRC_PATH)/BLAS_cgemm_s_c_x.c\
	$(SRC_PATH)/BLAS_cgemm_s_s_x.c\
	$(SRC_PATH)/BLAS_zgemm_z_d_x.c\
	$(SRC_PATH)/BLAS_zgemm_d_z_x.c\
	$(SRC_PATH)/BLAS_zgemm_d_d_x.c \
	\
	$(SRC_PATH)/BLAS_dgemm_d_s-f2c.c\
	$(SRC_PATH)/BLAS_dgemm_s_d-f2c.c\
	$(SRC_PATH)/BLAS_dgemm_s_s-f2c.c\
	$(SRC_PATH)/BLAS_zgemm_z_c-f2c.c\
	$(SRC_PATH)/BLAS_zgemm_c_z-f2c.c\
	$(SRC_PATH)/BLAS_zgemm_c_c-f2c.c\
	$(SRC_PATH)/BLAS_cgemm_c_s-f2c.c\
	$(SRC_PATH)/BLAS_cgemm_s_c-f2c.c\
	$(SRC_PATH)/BLAS_cgemm_s_s-f2c.c\
	$(SRC_PATH)/BLAS_zgemm_z_d-f2c.c\
	$(SRC_PATH)/BLAS_zgemm_d_z-f2c.c\
	$(SRC_PATH)/BLAS_zgemm_d_d-f2c.c\
	$(SRC_PATH)/BLAS_sgemm_x-f2c.c\
	$(SRC_PATH)/BLAS_dgemm_x-f2c.c\
	$(SRC_PATH)/BLAS_cgemm_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemm_x-f2c.c\
	$(SRC_PATH)/BLAS_dgemm_d_s_x-f2c.c\
	$(SRC_PATH)/BLAS_dgemm_s_d_x-f2c.c\
	$(SRC_PATH)/BLAS_dgemm_s_s_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemm_z_c_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemm_c_z_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemm_c_c_x-f2c.c\
	$(SRC_PATH)/BLAS_cgemm_c_s_x-f2c.c\
	$(SRC_PATH)/BLAS_cgemm_s_c_x-f2c.c\
	$(SRC_PATH)/BLAS_cgemm_s_s_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemm_z_d_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemm_d_z_x-f2c.c\
	$(SRC_PATH)/BLAS_zgemm_d_d_x-f2c.c

GEMM_OBJS = $(GEMM_SRCS:.c=.o)

all: $(GEMM_OBJS)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_LIBS) -I$(HEADER_PATH) -c -o $@ $<

