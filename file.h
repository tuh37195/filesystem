#ifndef FILE_H
#define FILE_H

#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX_NAME 20
#define MAX_EXT 5

typedef struct Inode{
    //the name of the inode
    char name[MAX_NAME+1];
    //the inode's extension
    char extension[MAX_EXT+1];
    //unique id for the inode
    unsigned long id;
    //the side of the inode's data in bytes
    unsigned long byte_size;
    //the size of the inode's data in blocks
    unsigned long block_count;


} inode;

typedef struct Directory{
    char name[MAX_NAME]; // file name
    int used;                   // whether the file is being used
    int byte_size;              // file size
    int block_count;            // number of blocks
    int start_block;            // first data block
    int fd_count;               // number of file descriptors using this file
    int bloacks[];
} directory;


inode *create_file(int id, char *name, char *ext){
    //allocate memory for new inode
    inode *n = (inode*)malloc(sizeof(inode));
    
    //set id
    n->id = id;
    //add name and extension to inode, with null terminating chars at the end
    memcpy(n->name, name, MAX_NAME);
    n->name[MAX_NAME] = '\0';
    memcpy(n->extension, ext, MAX_EXT);
    n->extension[MAX_EXT] = '\0';

    //byte size and block size default to 0 (empty files)
    n->byte_size = 0;
    n->block_count = 0;

    return n;
}

directory *create_directory(){
    
    //allocate memory for the directory struct
    directory *d = (directory*)malloc(sizeof(directory));
    //set all values to 0 or null
    d->byte_size = 0;
    d->block_count = 0;
    d->fd_count = 0;
    d->used = 0;
}

#endif