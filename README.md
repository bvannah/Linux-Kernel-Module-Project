# Linux-Kernel-Module-Project
A project for a class
I have uploaded, alongside this write-up: a Makefile, three test files, and my main module. To use
them, copy those five items to the same directory and enter into terminal:

make

sudo insmod jif.ko
sudo insmod test1.ko
sudo insmod test2.ko
sudo insmod test3.ko

This will initialize the database and store it in /proc/jif, making changes to it based on the add/delete
function calls in test1, test2, and test3 modules. If you don’t want to use all three test modules, you can
just load in the first one and make changes as you wish, and then see the results in:
cat /proc/jif

TL;DR: Does some /proc/ stuff. 10 lines of 64 bytes each, one key-val per line, first
line is the number of entries.

My LKM is a little database creation and maintenance program. With it, you can create databases, add
entries, remove entries, and read entries. It is most useful for storing simple ASCII text, because those
will be easily human-readable. The database is basically a text file. Each key-value pair is an entry, and
is on its own line in the text file. Each entry has the name (or key) of the data stored and the data. The
data can be stored in different types, but in our database they are represented as char *, so the data are
only easily-human readable from the database file if the data stored is ASCII text. This database
program is designed to be easily human-readable.

The database file (located at /proc/jif) is formatted as 10 64-character lines. The first line is just the
number of entries, and the 9 lines after that are the space for the keys and values to be stored. There is
one key-value pair on each line. Unused lines are made completely filled with spaces, the ‘ ‘ character.
This way, I can tell which lines are allocated as key-value pairs, and which are just empty. The lines
with key-value pairs have the key (in characters), a single space ‘ ‘, and then the value (in characters).
This format is obviously space-inefficient. Text files with returns and spaces are much less efficient
than plain files with just data in them, instead of adding the spaces and formatting that are in my text
file. I decided to use text files with this formatting so that the database would be easily readable by a
human, for debugging and performance monitoring. Also, with the format like this, if you want to send
the database to somewhere else, it could be easily read by someone. They don’t need any specific byte-
parsing instructions to read the data, they can probably just do it by eye. Furthermore, I am wasting
many bytes of ‘ ‘ in each line, assuming they are not completely filled.I added a size (number of entries) field to the database, so that you can quickly check to see roughly
how large the database is. You can also check to see if an opened database file is uninitialized. The first
line in the /proc/jif file should be just a single number, which is the number of entries.

My database definitely has its shortcomings. For one, it’s not efficient with space. It also only handles
one database. It wouldn’t be very challenging to change the code to handle multiple databases, but for
this assignment I think one is okay. I have limited the length of each line to 64, for simplicity purposes,
so users can’t add very long keys or very long values. This makes reading and writing much easier to
code. I have also limited the possible number of entries to 9, just to make it easier to code. I could
definitely change it to include more entries, variable line lengths, etc, I just think it would be a simple
extension as a C language exercise rather than a Linux operating system exercise.

I started writing this LKM from a LKM skeleton I found on the internet, where someone had made a
module that writes a /proc/ file to show the number of jiffies. That’s why its called jif.

What I liked about this project:
I had a lot of freedom to implement the module however I wanted. It felt like I was really learning on
my own. Over the course of the project, I learned a lot about Linux, and I found a bunch of resources
where I could learn more. I think I understand kernel-space versus user-space a lot more now.

What I didn’t like about this project:
Not much. It just took a long time, I wish I had started earlier. I went through many iterations and had
to start over twice, because I misunderstood something critical. The first time I wrote this module, I
wrote it using stdio, which I later learned is not accessible by modules because stdio is in user space
and the modules are in kernel space. Then, following an old tutorial, I wrote the module using outdated
and obsolete functions like create_proc_entry(), which I later learned had been removed from Linux
and my module would never work. But altogether those were just small roadblocks on the journey to an
LKM that does some stuff with /proc/.
