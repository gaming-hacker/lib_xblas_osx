include ../../make.inc

SRC_PATH = .
HEADER_PATH = ../include

HEMV2_SRCS =\
	$(SRC_PATH)/BLAS_zhemv2_z_c.c\
	$(SRC_PATH)/BLAS_zhemv2_c_z.c\
	$(SRC_PATH)/BLAS_zhemv2_c_c.c\
	$(SRC_PATH)/BLAS_chemv2_c_s.c\
	$(SRC_PATH)/BLAS_zhemv2_z_d.c\
	$(SRC_PATH)/BLAS_chemv2_x.c\
	$(SRC_PATH)/BLAS_zhemv2_x.c\
	$(SRC_PATH)/BLAS_zhemv2_z_c_x.c\
	$(SRC_PATH)/BLAS_zhemv2_c_z_x.c\
	$(SRC_PATH)/BLAS_zhemv2_c_c_x.c\
	$(SRC_PATH)/BLAS_chemv2_c_s_x.c\
	$(SRC_PATH)/BLAS_zhemv2_z_d_x.c \
	$(SRC_PATH)/BLAS_zhemv2_z_c-f2c.c\
	$(SRC_PATH)/BLAS_zhemv2_c_z-f2c.c\
	$(SRC_PATH)/BLAS_zhemv2_c_c-f2c.c\
	$(SRC_PATH)/BLAS_chemv2_c_s-f2c.c\
	$(SRC_PATH)/BLAS_zhemv2_z_d-f2c.c\
	$(SRC_PATH)/BLAS_chemv2_x-f2c.c\
	$(SRC_PATH)/BLAS_zhemv2_x-f2c.c\
	$(SRC_PATH)/BLAS_zhemv2_z_c_x-f2c.c\
	$(SRC_PATH)/BLAS_zhemv2_c_z_x-f2c.c\
	$(SRC_PATH)/BLAS_zhemv2_c_c_x-f2c.c\
	$(SRC_PATH)/BLAS_chemv2_c_s_x-f2c.c\
	$(SRC_PATH)/BLAS_zhemv2_z_d_x-f2c.c

HEMV2_OBJS = $(HEMV2_SRCS:.c=.o)

all: $(HEMV2_OBJS)

.c.o:
	$(CC) $(CFLAGS) $(EXTRA_LIBS) -I$(HEADER_PATH) -c -o $@ $<
