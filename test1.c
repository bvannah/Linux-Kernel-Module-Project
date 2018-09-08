#include <linux/module.h>
 #include <linux/init.h>
 #include <linux/kernel.h>
 #include <linux/fs.h>		// for basic filesystem
 #include <linux/proc_fs.h>	// for the proc filesystem
 #include <linux/seq_file.h>

extern int add(char* key, char* value);
extern int delete(char * key);

 static int __init 
 test1_init(void)
 {
	add("test1key", "test1val");
	add("testsdkfhsd", "tadkltj");
     return 0;
 }

 static void __exit
 test1_exit(void)
 {

 }

 module_init(test1_init);
 module_exit(test1_exit);

 MODULE_LICENSE("GPL"); 
