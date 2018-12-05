#ifndef DISK_H
#define DISK_H

#include<math.h>

typedef struct Superblock{
int inode_locaton; 
int inode_max;
int inode_count;
int data_location;
int block_count; 
int *block_map;
int *inode_map;
} superblock;

superblock *new_superblock(int superblock_max, int inode_max, int inode_size, int disk_size, int block_size){
    //malloc memory
    superblock *super = (superblock *)malloc(sizeof(superblock));
    //set inode location after superblock section
    super->inode_locaton = superblock_max + 1;
    //set inode max
    super->inode_max = inode_max;
    //inode count starts at 0
    super->inode_count = 0;
    //set data location after the superblock and inode table
    super->data_location = superblock_max + (inode_max * inode_size) + 1;
    //get available blocks
    super->block_count = floor((disk_size - superblock_max - (inode_max * inode_size))/ block_size);
    //create a map for each block and inode
    super->block_map = calloc(super->block_count, sizeof(int));
    super->inode_map = calloc(INODE_MAX, sizeof(int));
    //return the superblock
    return super;
}

//get the size of the disk using fseek
int get_disk_size(char *disk_name){
    //open disk
    FILE *disk = fopen(disk_name, "r");
    //move to the end of the disk
    fseek(disk, 0, SEEK_END);
    //get the position as the size
    int size = ftell(disk);
    //close the disk
    fclose(disk);
    //return the size
    return size;
}

//initialize the disk with a new superblock
superblock *init_disk(char *disk_name, superblock *sb){
    
    //get the size of the disk
    int disk_size = get_disk_size(disk_name);
    //create the superblock
    superblock *super = new_superblock(SUPERBLOCK_SIZE, INODE_MAX, INODE_SIZE, disk_size, BLOCK_SIZE);
    //open the disk
    FILE *disk = fopen(disk_name, "r+");
    //if disk couldn't be opened
    if (disk == NULL){
        error("File could not be opened", "init_disk");
        exit(1);
    }
    
    //else write the superblock to disk
    fwrite(sb, sizeof(superblock), 1, disk);
    
    //close disk
    fclose(disk);
    return super;
}
//update the superblock on the disk
void update_super(char *disk_name, superblock *sb){
    //open the disk
    FILE *disk = fopen(disk_name, "r+");
    //if disk couldn't be opened
    if (disk == NULL){
        error("File could not be opened", "update_super");
        exit(1);
    }
    //else write the superblock to disk
    fwrite(sb, sizeof(superblock), 1, disk);
    
    //close disk
    fclose(disk);
}

#endif