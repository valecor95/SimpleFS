#include "simplefs.h"
#include "disk_driver.h"
#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>

//ATTENTION to better use this test needs to remove comments on printf in simplefs
// if there is /// on comment it's on a loop, not necessary to use

int findBit(unsigned char c, int n) {
    static unsigned char mask2[] = {128, 64, 32, 16, 8, 4, 2, 1};
    return ((c & mask2[n]) != 0);
}

int main(int agc, char** argv) {
  printf("\nBlock size %ld\n", sizeof(FirstFileBlock));
  printf("FDB_space = %ld, DB_space = %ld, FFB_space = %ld, FB_space = %ld\n", FDB_space, DB_space, FFB_space, FB_space);

  int ret = 0, i = 0, check = 0, bit = 0;
  SimpleFS fs;
  DiskDriver disk;

  DiskDriver_init(&disk, "disco.disk", 512);
  printf("disk created\n");


  //// test on init
  printf("\n\nSTART test on init and format\n");
  DirectoryHandle* root_directory = SimpleFS_init(&fs, &disk);
  if (root_directory == NULL){
    //// test on format
    printf("format disk\n");
    SimpleFS_format(&fs);
    root_directory = SimpleFS_init(&fs, &disk);
    if (root_directory == NULL)
      exit(EXIT_FAILURE);
  }

  /*
  ////look inside root
  char v[BLOCK_SIZE];
  memcpy(v, root_directory->dcb, BLOCK_SIZE); 
  printf("\n\ninside root\n");
  for (i = 0; i < BLOCK_SIZE; i++){
    for (check = 0; check < 8; check ++){
      bit = findBit(v[i], check);
      printf("%d ", bit);
    }
    printf("\n");
  }
  */

  ////read empty directory
  printf("\n\nread empty directory\n");
    char** file = malloc(sizeof(char*));
    ret = SimpleFS_readDir(file, root_directory);
    printf("%s ", file[0]);

  ////test on create file
  printf("\n\nSTART test on create a file\n");
  FileHandle* fh = SimpleFS_createFile(root_directory, "file_test");
  if (fh == NULL){
    printf("create file failed, retry\n");
    fh = SimpleFS_createFile(root_directory, "file_test");
  }

  ////test on create directory
  printf("\n\nSTART test on create a file\n");
  ret = SimpleFS_mkDir(root_directory, "dir1");
  if (ret == -1){
    printf("create dir1 failed, retry\n");
    SimpleFS_mkDir(root_directory, "dir1");
  }
 
  char** file2 = malloc(sizeof(char*)*2);
  ret = SimpleFS_readDir(file2, root_directory);
  printf("%s ", file2[0]);
  printf("%s ", file2[1]);
  
  printf("\ntest error on already exist file\n");
  FileHandle* fh_double = SimpleFS_createFile(root_directory, "file_test");


  //test to create many files
  printf("\ntest to create more blocks in directory\n");
  char file_name[10];
  for (i=0; i<100; i++){
    sprintf(file_name, "%d", i);                                                                //function to convert number in string
    SimpleFS_createFile(root_directory, file_name);
  }
  printf("completed to create files\n");
  ///for test on error on free blocks it just needs decrease bloks of the disk


  //test on read directory
  printf("\n\nSTART test on read directory\n");
  char** files = (char**) malloc(sizeof(char*) * root_directory->dcb->num_entries);
  ret = SimpleFS_readDir(files, root_directory);
  for (i=0; i<root_directory->dcb->num_entries; i++){
    printf("%s ", files[i]);
  }
  printf("check completed\n");


  //test open file
  printf("\n\nSTART test on openfile\n");
  FileHandle* fh1 = SimpleFS_openFile(root_directory, "file_fake");
  if (fh1 == NULL){
    printf("open fake_file failed, retry with file_test\n");
    fh1 = SimpleFS_openFile(root_directory, "file_test");
  }


  //test change directrory
  printf("\n\nSTART test on change directrory\n");
  ret = SimpleFS_changeDir(root_directory, "dir2");
  if (ret == -1){
    printf("change to dir2 failed, retry with dir1\n");
    SimpleFS_changeDir(root_directory, "dir1");
    printf("current directoy = %s\n", root_directory->dcb->fcb.name);
    printf("go back to root\n");
    ret = SimpleFS_changeDir(root_directory, "..");
    if (ret == -1){
      printf("error to go back\n");
    }
    printf("current directoy = %s\n", root_directory->dcb->fcb.name);
  }



  //test remove file/dir
  printf("\n\nSTART test on remove file\n");
  ret = SimpleFS_remove(root_directory, "5");
  char** files2 = (char**) malloc(sizeof(char*) * root_directory->dcb->num_entries);
  ret = SimpleFS_readDir(files2, root_directory);
  for (i=0; i<root_directory->dcb->num_entries; i++){
    printf("%s ", files2[i]);
  }
  printf("check completed\n");
  
  //test close file
  printf("\n\nSTART test on close file\n");
  SimpleFS_close(fh);
  SimpleFS_close(fh_double);
  SimpleFS_close(fh1);
}
