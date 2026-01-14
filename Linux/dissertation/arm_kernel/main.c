#include <linux/module.h>
#include <linux/kernel.h>

void enable_ccr(void *info)
{
    //enable user-mode access
    asm volatile ("mcr p15, 0, %0, c9, c14, 0\t\n" :: "r"(1));

    //enable all counters in the PNMC control-register
    asm volatile("mcr p15, 0, %0, c9, c12, 0\t\n" :: "r"(1));

    //Enable cycle counter specifically
    asm volatile("mcr p15, 0, %0, c9, c12, 1\t\n" :: "r"(0x80000000));
}

int init_module()
{
    printk(KERN_INFO "Entering enable_ccr driver\n");
    on_each_cpu(enable_ccr, NULL, 0);
    printk(KERNINFO "Userspace access to CCR enabled\n");
    return 0;
}

void cleanup_module(void){}