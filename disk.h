#ifndef DISK_H
#define DISK_H
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct Superblock{
int inode_locaton; 
int inode_count;
int inode_max;
int data_location;
int block_count; 
//long int sectors[];
} superblock;

int get_disk_size(char *disk_name){
    //open disk
    FILE *disk = fopen(disk_name, "r+");
    //move to end of disk
    fseek(disk, 0, SEEK_END);
    //get the position
    int pos = ftell(disk);
    //close file
    fclose(disk);
    return pos;
}

//create the superblock
superblock* init_super(int superblock_size, int inode_max, int inode_size, int block_size, char *disk_name){
    //allocate memory
    superblock *sb = (superblock*)malloc(sizeof(superblock));
    //set inode location
    sb->inode_locaton = superblock_size + 1;
    sb->inode_count = 0;
    sb->inode_max = inode_max;
    //get disk size
    int disk_size = get_disk_size(disk_name);
    //subtract size of superblock and inode locations
    disk_size -= superblock_size + (inode_size * inode_max);
    //get the maximum number of blocks
    int block_count = disk_size/block_size;
    sb->block_count = block_count;
    //break up the block into 32bit chunks
    //long int chunks = block_count/sizeof(long int) + (block_count % sizeof(long int));
    //sb->blocks = (long*)malloc(sizeof(long int) * chunks);
    return sb;
    
}






#endif