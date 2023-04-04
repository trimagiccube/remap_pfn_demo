all: modules

alloc_pages		= alloc_pages/remap_pfn_alloc_pages.ko
pfn_kmalloc		= pfn_kmalloc/remap_pfn_kmalloc.ko
pfn_vmalloc		= pfn_vmalloc/remap_pfn_vmalloc.ko

.PHONY: modules alloc_pages pfn_kmalloc pfn_vmalloc

alloc_pages:
	$(MAKE) -C alloc_pages/
