ifneq ($(KERNELRELEASE),)
 include $(PWD)/alloc.Kbuild

else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	@rm -rf *.o *.mod.c *.mod.o *.ko *.order *.symvers .*.cmd .tmp_versions

endif

