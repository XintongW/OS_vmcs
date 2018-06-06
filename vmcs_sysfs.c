#include<linux/device.h>
#include<linux/init.h>
#include<linux/string.h>
#include<linux/sysfs.h>
#include<linux/kernel.h>
#include<linux/stat.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
  extern void vwrite(unsigned long address, unsigned long value);
  extern unsigned long vread(unsigned long address);
  extern unsigned long getaddr(const char*address);
  struct kobject kbj;

struct attribute flag={
  .name="flags",
  .mode=S_IRWXUGO,
};
struct attribute intinfo={
  .name="interupt_info",
  .mode=S_IRWXUGO,
};

struct attribute cr_3={
  .name="cr3_3",
  .mode=S_IRWXUGO,
};
struct attribute r_1={
  .name="r1_1",
  .mode=S_IRWXUGO,
};
struct attribute r_2={
  .name="r2_2",
  .mode=S_IRWXUGO,
};

static struct attribute *db[]={
   &intinfo,
   &flag,
   &r_1,
   &r_2,
   &cr_3,
   NULL,
};

static ssize_t kb_show(struct kobject *koj, struct attribute *arr, char*buf)
{
  ssize_t count;
  unsigned long value;
  unsigned long address;
  address=getaddr(arr->name);
    printk("vmcs starts to read%ld\n",address);
  value=vread(address);
    count=sprintf(buf, "%ld\n", value);
      return count};
}

static void vrelease(struct kobject *koj)
{
printk("vmcs starts to release\n");
}

static int init vmodule_init(void)
{
  int rst;
    printk("vmcs starts to init\n");
    rst= kobject_init_and_add(&kbj,NULL,"vmcs");
     return rst;
}
static void exit vmodule_exit(void)
{
    printk("vmcs starts to exit\n");
    kobject_del(&kbj);
}
static ssize_t kb_save(struct kbject *koj, struct attribute*arr, const char)
{
  unsigned long value;
  unsigned long address;
    address=getaddr(arr->name);
    value=simple_strtoul(buf,NULL,2);
     printk("vmcs starts to write%ld\n", address);
     vwrite(address, value);
      return count;
}
module_init(vmodule_init);
module_exit(vmodule_exit);
