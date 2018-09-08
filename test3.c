#include <linux/module.h>
 #include <linux/init.h>
 #include <linux/kernel.h>
 #include <linux/fs.h>		// for basic filesystem
 #include <linux/proc_fs.h>	// for the proc filesystem
 #include <linux/seq_file.h>

extern int add(char* key, char* value);
extern int delete(char * key);

 static int __init 
 test3_init(void)
 {
	add("test3key", "test3val");
	delete("test2key");
     return 0;
 }

 static void __exit
 test3_exit(void)
 {

 }

 module_init(test3_init);
 module_exit(test3_exit);

 MODULE_LICENSE("GPL"); 
