#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/kprobes.h>
#include <linux/mm.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/vmalloc.h>
#include <asm/set_memory.h>

#define BUF_SIZE (32*PAGE_SIZE)

static void *kbuff;

static int remap_pfn_open(struct inode *inode, struct file *file)
{
	struct mm_struct *mm = current->mm;

	printk("client: %s (%d)\n", current->comm, current->pid);
	printk("code  section: [0x%lx   0x%lx]\n", mm->start_code, mm->end_code);
	printk("data  section: [0x%lx   0x%lx]\n", mm->start_data, mm->end_data);
	printk("brk   section: s: 0x%lx, c: 0x%lx\n", mm->start_brk, mm->brk);
	printk("mmap  section: s: 0x%lx\n", mm->mmap_base);
	printk("stack section: s: 0x%lx\n", mm->start_stack);
	printk("arg   section: [0x%lx   0x%lx]\n", mm->arg_start, mm->arg_end);
	printk("env   section: [0x%lx   0x%lx]\n", mm->env_start, mm->env_end);

	return 0;
}

static int remap_pfn_mmap(struct file *file, struct vm_area_struct *vma)
{
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long virt_start = (unsigned long)kbuff + (unsigned long)(vma->vm_pgoff << PAGE_SHIFT);
	unsigned long pfn_start = (unsigned long)vmalloc_to_pfn((void *)virt_start);
	unsigned long size = vma->vm_end - vma->vm_start;
	int ret = 0;
	unsigned long vmstart = vma->vm_start;
	int i = 0;

	printk("phy: 0x%lx, offset: 0x%lx, size: 0x%lx\n", pfn_start << PAGE_SHIFT, offset, size);

	while (size > 0) {
		ret = remap_pfn_range(vma, vmstart, pfn_start, PAGE_SIZE, vma->vm_page_prot);
		if (ret) {
			printk("%s: remap_pfn_range failed at [0x%lx  0x%lx]\n",
				__func__, vmstart, vmstart + PAGE_SIZE);
			ret = -ENOMEM;
			goto err;
		} else
			printk("%s: map 0x%lx (0x%lx) to 0x%lx , size: 0x%lx, number: %d\n", __func__, virt_start,
				pfn_start << PAGE_SHIFT, vmstart, PAGE_SIZE, ++i);

		if (size <= PAGE_SIZE)
			size = 0;
		else {
			size -= PAGE_SIZE;
			vmstart += PAGE_SIZE;
			virt_start += PAGE_SIZE;
			pfn_start = vmalloc_to_pfn((void *)virt_start);
		}
	}

	return 0;
err:
	return ret;
}

static const struct file_operations remap_pfn_fops = {
	.owner = THIS_MODULE,
	.open = remap_pfn_open,
	.mmap = remap_pfn_mmap,
};

static struct miscdevice remap_pfn_misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "remap_pfn",
	.fops = &remap_pfn_fops,
};

unsigned int test_call(unsigned int arg)
{
	if(arg > 256) {
		return 2;
	} else if(arg <= 256) {
		return 1;
	} else {
		return 0;
	}
}

#if 1
static unsigned long (*my_kallsyms_lookup_name)(const char *name);
unsigned long lookup_name(const char *name)
{
	struct kprobe kp = {
		.symbol_name = "kallsyms_lookup_name"
	};
	unsigned long retval;
	int ret;

	ret = register_kprobe(&kp);
	if (ret < 0) {
		pr_err("register error, ret %d\n", ret);
		return 0;
	}
	my_kallsyms_lookup_name = (unsigned long) kp.addr;
	unregister_kprobe(&kp);

	retval = my_kallsyms_lookup_name(name);
	return retval;
}
#else
unsigned long lookup_name(const char *name)
{
	return kallsyms_lookup_name(name);
}
#endif

unsigned int test_call(unsigned int arg);
static int pulse_logger_init(void)
{
	unsigned int (*test)(unsigned int arg);
	int (*myset_memory_x)(unsigned long addr, int numpages);
	static void* buffer;
	printk(KERN_INFO "test_call returns: %d %d %d\n", test_call(0), test_call(256), test_call(512));
	myset_memory_x = lookup_name("set_memory_x");
	pr_info("myset_memory_x 0x%llx\n", myset_memory_x);
	buffer = vmalloc(4096);
	pr_info("buffer of vmalloc 0x%llx\n", buffer);
	if(buffer != NULL){
//		buffer = (void*) ALIGN((uint32_t)buffer, 4) + 4;
		printk(KERN_INFO "\t  buffer(0x%llx)\n", (unsigned long)buffer);
		printk(KERN_INFO "\t  test_call(0x%llx)\n", (unsigned long)test_call);
		/* why size is 26 objdump -S pfn_vmalloc_exec.ko see it is 26
		 * different platform should use differnet size, change it
unsigned int test_call(unsigned int arg)
{
   0:	e8 00 00 00 00       	callq  5 <test_call+0x5>
   5:	55                   	push   %rbp
	if(arg > 256) {
		return 2;
	} else if(arg <= 256) {
		return 1;
   6:	31 c0                	xor    %eax,%eax
   8:	81 ff 00 01 00 00    	cmp    $0x100,%edi
   e:	0f 97 c0             	seta   %al
{
  11:	48 89 e5             	mov    %rsp,%rbp
		return 1;
  14:	83 c0 01             	add    $0x1,%eax
	} else {
		return 0;
	}
}
  17:	5d                   	pop    %rbp
  18:	c3                   	retq   
  19:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
		 *
		 */
		memcpy(buffer, test_call, 26);
		myset_memory_x((long)buffer, 1);
		printk(KERN_INFO "\t  test_call copied to buffer\n");
		test = (unsigned int (*)(unsigned int)) buffer;
		printk(KERN_INFO "\t  test pointer assigned (%llx)\n", test);
		printk(KERN_INFO "test returns: %d %d %d\n", test(0), test(256), test(512));
		vfree(buffer);
	}
	return 0;
}

static int __init remap_pfn_init(void)
{
	int ret = 0;

	kbuff = vmalloc(BUF_SIZE);
	if (!kbuff) {
		ret = -ENOMEM;
		goto err;
	}

	ret = misc_register(&remap_pfn_misc);
	if (unlikely(ret)) {
		pr_err("failed to register misc device!\n");
		goto err;
	}

	pulse_logger_init();
	pr_info("insmod okay\n");
	return 0;

err:
	return ret;
}

static void __exit remap_pfn_exit(void)
{
	misc_deregister(&remap_pfn_misc);
	vfree(kbuff);
}

module_init(remap_pfn_init);
module_exit(remap_pfn_exit);
MODULE_LICENSE("GPL");
