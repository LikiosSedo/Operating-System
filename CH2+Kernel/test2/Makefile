obj-m += simple.o
KERNELBUILD += /usr/src/linux-headers-5.4.0-87-generic
all:
	make -C ${KERNELBUILD} M=${shell pwd} modules
clean:
	rm -f *.ko *.o *.mod.o *mod.c *.symvers
