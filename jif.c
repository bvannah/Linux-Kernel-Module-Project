 #include <linux/module.h>
 #include <linux/init.h>
 #include <linux/kernel.h>
 #include <linux/fs.h>		// for basic filesystem
 #include <linux/proc_fs.h>	// for the proc filesystem
 #include <linux/seq_file.h>	// for sequence files


char finalbuf[641]; //our final buffer, the database represented as a string
int entries; //the number of entries in our database

int add(char * key, char * value); //adds new key-value pairs
int delete(char *key); //deletes key-value pairs
int read(char* key, char* buffer); //reads value based on key
EXPORT_SYMBOL(add);
EXPORT_SYMBOL(delete); //export them so you can use them in other places
EXPORT_SYMBOL(read);


int add(char *key, char * value){

		int linenum=1;
		while(linenum<=10){			
			if(finalbuf[linenum*64]==' '){ //if the first character of the line is blank, the line is unused. write to it
				int i=0; //total number of characters written
				int j=0; //second pointerstrlen()
				while(i<strlen(key)){ //write the key
					finalbuf[linenum*64+i]=key[i];
					i++;
				}

				finalbuf[i]=' '; //write a space
				i++;
				
				while(j<strlen(value)){//write the value
					finalbuf[linenum*64+i] = value[j]; 
					i++;
					j++;
				}
				while(i<63){ //write a bunch of spaces until the line is 63 bytes long
					finalbuf[linenum*64+i]=' ';
					i++;
				}
				finalbuf[linenum*64+i]='\n'; //add the newline, for readability
				entries++;
				finalbuf[0]=entries+'0';
				return 0;
			}			
			linenum++;//iterate through each line
		}
	return -1;//no space for it, we cannot add :(
}


int delete(char *key){
	int iskey;
	int linenum=1;
	while(linenum<=10){ //iterate through each line
		int i=0;
		iskey=1;
		while(i<strlen(key)){ //if the key doesn't match a character of the key field in the finalbuf, iskey will be set to 0
			if(finalbuf[linenum*64+i]!=key[i]) iskey=0;
			i++;
		}
		if(iskey==1){ //if iskey==1, the key must match the key we're looking for
			int j=0;
			while(j<63){ //re-initialize our line, deleting the line
				finalbuf[linenum*64+j]=' ';
				j++;
			}		
			entries--;
			finalbuf[0]=entries+'0';
			return 0;
		}
		linenum++;
	}
	return -1;//not found, key is not in our database
}

int read(char *key, char* buffer){//puts the value in the buffer
	/*int iskey;
	int linenum=1;
	while(linenum<=10){
		int i=0;
		iskey=1;
		while(i<strlen(key)){
			if(finalbuf[linenum*64+i]!=key[i]) iskey=0;
			i++;
		}
		if(iskey==1){
			char foundval[strlen(key)];
			int j=0;
			while(finalbuf[linenum*64+strlen(key)+1+j]!=' '){ //while the next char of val isn't a space
				foundval[j]=finalbuf[linenum*64+strlen(key)+1+j];
				j++;
			}	
			strcpy(buffer, foundval);
			return 0;
		}
		linenum++;
	}
*/
return -1; //didn't find it
}







 static struct proc_dir_entry* jif_file;

 static int 
 jif_show(struct seq_file *m, void *v)//This copies the finalbuf into the file, each time the file is opened
 {
     seq_printf(m, finalbuf); //print our buffer
     return 0;
 }

 static int //I have no idea what this does. I copied it from the internet
 jif_open(struct inode *inode, struct file *file)
 {
     return single_open(file, jif_show, NULL);
 }

 static const struct file_operations jif_fops = {//I have no idea what this does. I copied it from the internet
     .owner	= THIS_MODULE,
     .open	= jif_open,
     .read	= seq_read,
     .llseek	= seq_lseek,
     .release	= single_release,
 };

 static int __init 
 jif_init(void)
 {	//the first time we load the module, we should initialize our database 
	int i;
	char buffer[20];
    jif_file = proc_create("jif", 0, NULL, &jif_fops); //create the procfile
	//initialize finalbuf
	finalbuf[640]='\0'; //last character of the string should be '\0'
	i=0;
	while(i<10){//initialize file, line by line. iterate through the lines
		int j=0;
		while(j<63){ //initialize our line
			finalbuf[i*64+j]=' '; //63 spaces and a newline char
			j++;
		}
		finalbuf[i*64+63]='\n';
		i++;
	}
	finalbuf[0]='0';
	//initialize first line to hold size	
	entries = finalbuf[0]-'0'; //only holds 9 entries
     return 0;
 }

 static void __exit
 jif_exit(void)
 {//to exit/unload the module, just delete the proc file
     remove_proc_entry("jif", NULL);
 }

 module_init(jif_init);
 module_exit(jif_exit);

 MODULE_LICENSE("GPL"); 
