ifneq ($(KERNELRELEASE),)
include $(src)/alloc.Kbuild
# when you type in make , it will enter linux kernel (MAKE -C);
# and new version of kernel Kbuild system will read Kbuild file in $(src) ;
# but if build system of kernel is old ,it will read this Makefile, and you include
# alloc.Kbuild file and not do anything else
# $(src) :The directory containing this alloc.Kbuild file. you can replace with next line
#  include $(src)/alloc.Kbuild
#  include $(src)/alloc_pages/alloc.Kbuild
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build

modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURDIR)

clean:
	@rm -rf *.o *.mod.c *.mod.o *.ko *.order *.symvers .*.cmd .tmp_versions *.mod

endif

