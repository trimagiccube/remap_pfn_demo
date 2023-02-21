ifneq ($(KERNELRELEASE),)
	obj-m := remap_pfn_kmalloc.o
	obj-m += remap_pfn_vmalloc.o
	obj-m += remap_pfn_alloc_pages.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
default:
#	$(MAKE) -C $(KERNELDIR) ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- M=$(PWD) modules
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	@rm -rf *.o *.mod.c *.mod.o *.ko *.order *.symvers .*.cmd .tmp_versions
endif
