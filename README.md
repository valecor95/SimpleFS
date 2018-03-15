# SimpleFS
File System
   implement a file system interface using binary files
   - The file system reserves the first part of the file
     to store:
     - a linked list of free blocks
     - linked lists of file blocks
     - a single global directory
     
   - Blocks are of two types
     - data blocks
     - directory blocks

   A data block are "random" information
   A directory block contains a sequence of
   structs of type "directory_entry",
   containing the blocks where the files in that folder start
   and if they are directory themselves
    
This is a project developed for the Operating Systems course at Sapienza University of Rome

For more info go to the Wiki section
