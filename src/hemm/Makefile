include ../../make.inc

SRC_PATH = .
HEADER_PATH = ../include

HEMM_SRCS =\
	$(SRC_PATH)/BLAS_zhemm_z_c.c\
	$(SRC_PATH)/BLAS_zhemm_c_z.c\
	$(SRC_PATH)/BLAS_zhemm_c_c.c\
	$(SRC_PATH)/BLAS_chemm_c_s.c\
	$(SRC_PATH)/BLAS_zhemm_z_d.c\
	$(SRC_PATH)/BLAS_chemm_x.c\
	$(SRC_PATH)/BLAS_zhemm_x.c\
	$(SRC_PATH)/BLAS_zhemm_z_c_x.c\
	$(SRC_PATH)/BLAS_zhemm_c_z_x.c\
	$(SRC_PATH)/BLAS_zhemm_c_c_x.c\
	$(SRC_PATH)/BLAS_chemm_c_s_x.c\
	$(SRC_PATH)/BLAS_zhemm_z_d_x.c \
	\
	$(SRC_PATH)/BLAS_zhemm_z_c-f2c.c\
	$(SRC_PATH)/BLAS_zhemm_c_z-f2c.c\
	$(SRC_PATH)/BLAS_zhemm_c_c-f2c.c\
	$(SRC_PATH)/BLAS_chemm_c_s-f2c.c\
	$(SRC_PATH)/BLAS_zhemm_z_d-f2c.c\
	$(SRC_PATH)/BLAS_chemm_x-f2c.c\
	$(SRC_PATH)/BLAS_zhemm_x-f2c.c\
	$(SRC_PATH)/BLAS_zhemm_z_c_x-f2c.c\
	$(SRC_PATH)/BLAS_zhemm_c_z_x-f2c.c\
	$(SRC_PATH)/BLAS_zhemm_c_c_x-f2c.c\
	$(SRC_PATH)/BLAS_chemm_c_s_x-f2c.c\
	$(SRC_PATH)/BLAS_zhemm_z_d_x-f2c.c

HEMM_OBJS = $(HEMM_SRCS:.c=.o)

all: $(HEMM_OBJS)

.c.o:
	$(CC) $(CFLAGS) -I$(HEADER_PATH) -c -o $@ $<
