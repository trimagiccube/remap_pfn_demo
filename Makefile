all: modules

#alloc_pages		= alloc_pages/remap_pfn_alloc_pages.ko
#pfn_kmalloc		= pfn_kmalloc/remap_pfn_kmalloc.ko
#pfn_vmalloc		= pfn_vmalloc/remap_pfn_vmalloc.ko
#pfn_vmalloc_exec		= pfn_vmalloc_exec/remap_pfn_vmalloc_exec.ko

# add all module use wildcard, which will use dir name for module name
TEST_KERNEL_MODULES ?= $(wildcard alloc_pages pfn_kmalloc pfn_vmalloc pfn_vmalloc_exec)
$(info "all module list :$(TEST_KERNEL_MODULES)")

ifndef ARCH
	ARCH := $(shell uname -m | sed -e 's/i.86/i386/' \
		-e 's/armv[0-7]\w\+/arm/' \
		-e 's/aarch64/arm64/' \
		-e 's/ppc64le/powerpc/' \
		)
endif
$(info test ARCH is :$(ARCH))

.PHONY: modules alloc_pages pfn_kmalloc pfn_vmalloc pfn_vmalloc_exec

alloc_pages:
# use @echo for just show start build alloc_pages
# when remove @, shell will show echo "start build alloc_pages"
	@echo "start build alloc_pages"
	$(MAKE) -C alloc_pages modules

pfn_kmalloc:
	@echo "start build pfn_kmalloc"
	$(MAKE) -C pfn_kmalloc/

pfn_vmalloc:
	@echo "start build pfn_vmalloc"
	$(MAKE) -C pfn_vmalloc modules

pfn_vmalloc_exec:
	echo "start build pfn_vmalloc_exec"
	$(MAKE) -C pfn_vmalloc_exec/
#########################################################
# clean
#########################################################
.PHONY: clean alloc_pages.clean pfn_kmalloc.clean pfn_vmalloc.clean

clean: alloc_pages.clean pfn_kmalloc.clean pfn_vmalloc.clean pfn_vmalloc_exec.clean
	@rm -rf *.o *.mod.c *.mod.o *.ko *.order *.symvers .*.cmd .tmp_versions *.mod

alloc_pages.clean:
	$(MAKE) -C alloc_pages/ clean;

pfn_kmalloc.clean:
	$(MAKE) -C pfn_kmalloc/ clean;

pfn_vmalloc.clean:
	$(MAKE) -C pfn_vmalloc/ clean;

pfn_vmalloc_exec.clean:
	$(MAKE) -C pfn_vmalloc_exec/ clean;
