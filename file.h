#ifndef FILE_H
#define FILE_H

#define MAX_NAME 8
#define MAX_EXT 3

#include<stdlib.h>
#include<string.h>

typedef struct Inode{
    int id;
    int byte_size;
    int start_block;
    char name[MAX_NAME+1];
    char extension[MAX_EXT+1];
} inode;

inode *new_inode(char *name, char *ext){
    inode *n = (inode *)malloc(sizeof(inode));
    n->id = 0;
    n->byte_size = 0;
    n->start_block = 0;
    //n->name = malloc(sizeof(char) * MAX_NAME);
    //n->extension = malloc(sizeof(char) * MAX_EXT);
    strcpy(n->name, name);
    strcpy(n->extension, ext);
    return n;
}

#endif