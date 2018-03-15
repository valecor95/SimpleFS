CCOPTS = -g -std=gnu99 -Wstrict-prototypes
LIBS = 
CC = gcc
AR = ar

HEADERS = bitmap.h\
		disk_driver.h\
		simplefs.h\
		shell.h
 
shell: shell.c bitmap.c disk_driver.c simplefs.c $(HEADERS)
	$(CC) $(CCOPTS) shell.c bitmap.c disk_driver.c simplefs.c -o shell
	
simplefs_test: bitmap.c disk_driver.c simplefs.c simplefs_test.c $(HEADERS)
	$(CC) $(CCOPTS) bitmap.c disk_driver.c simplefs.c simplefs_test.c -o simplefs_test
	
<<<<<<< HEAD
disk_driver_test: bitmap.c disk_driver.c disk_driver_test.c $(HEADERS)
=======
disk_driver_test: bitmap.c disk_driver.c test_disk_driver.c $(HEADERS)
>>>>>>> 77478fe1c82cd164a7d7f0b5f5c8c99e15d23a12
	$(CC) $(CCOPTS) bitmap.c disk_driver.c disk_driver_test.c -o disk_driver_test

bitmap_test: bitmap.c bitmap_test.c $(HEADERS)
	$(CC) $(CCOPTS) bitmap.c bitmap_test.c -o bitmap_test
	
.phony: clean

clean:
	rm -f *.o shell bitmap_test disk_driver_test simplefs_test disk_file.txt disco.disk
