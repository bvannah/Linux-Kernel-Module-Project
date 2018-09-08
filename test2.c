#include <linux/module.h>
 #include <linux/init.h>
 #include <linux/kernel.h>
 #include <linux/fs.h>		// for basic filesystem
 #include <linux/proc_fs.h>	// for the proc filesystem
 #include <linux/seq_file.h>

extern int add(char* key, char* value);
extern int delete(char * key);

 static int __init 
 test2_init(void)
 {
	delete("test1key");
	add("test2key", "test2val");
	
     return 0;
 }

 static void __exit
 test2_exit(void)
 {

 }

 module_init(test2_init);
 module_exit(test2_exit);

 MODULE_LICENSE("GPL"); 
