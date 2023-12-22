#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

static LIST_HEAD(birthday_list);

struct birthday {
   int day;
   int month;
   int year;
   struct list_head list;
};

void birthday(int day_new, int month_new, int year_new, struct birthday *person)
{
   person->day=day_new;
   person->month=month_new;
   person->year=year_new;
   INIT_LIST_HEAD(&person->list);
   list_add_tail(&person->list, &birthday_list);
}

/* This function is called when the module is loaded. */
int simple_init(void)
{
struct birthday *person;
   struct birthday *ptr;

  printk(KERN_INFO "Loading Module\n");

person = kmalloc(sizeof(*person)*5, GFP_KERNEL);

   birthday(8,2,1995,person);
   person=person+1;

   birthday(30,1,2000,person);
   person=person+1;

   birthday(18,2,2000,person);
   person=person+1;

   birthday(11,3,2001,person);
   person=person+1;

   birthday(6,10,2020,person);

list_for_each_entry(ptr, &birthday_list, list) {
      printk(KERN_INFO "The birthday is %d %d %d.\n",ptr->year,ptr->month,ptr->day);
}
  return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
struct birthday *ptr, *next;
   list_for_each_entry_safe(ptr, next, &birthday_list, list){
      list_del(&ptr->list);
      kfree(ptr);
   }
printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


