#include<stdio.h>
#include<stdlib.h>

#include"./file.h"
//size of blocks in virtual disk
#define BLOCK_SIZE 512
//max number of blocks, 5mb total (10240 blocks *512 bytes / 1048578 b/mb)
#define MAX_BLOCKS 10240
//Preset size for superblock is 4kb
#define SUPERBLOCK_SIZE 4096
//assumes INODE takes up 60 bytes
#define INODE_SIZE 60
#define MAX_FILE_COUNT 128 //max 128 files

#define DISK1 "./temp.test"

int main(){
    //open the disk
    inode *n = create_file(1, "abcdefghilkmopqrssssst", "12wwwwww34");
    printf("TOTAL: %lu\nID: %lu\nNAME: %lu\nEXT: %lu\nBLOCK_SIZE: %lu\nBYTE_SIZE: %lu\n", sizeof(n), sizeof(n->id), sizeof(n->name), sizeof(n->extension), sizeof(n->block_count), sizeof(n->byte_size));

    inode *n2 = create_file(2, "new file", ".dat");
    FILE *disk = fopen(DISK1, "w+");
       if (disk == NULL){
        
    }
}

//Reads an inode from the disk
//Returns NULL if failed
inode *fs_open(int offset){
    
    //open the disk file
    FILE *disk = fopen(DISK1, "r+");
    
    //if disk open failed
    if (disk == NULL){
        return NULL;
    }
    
    //move to correct spot for file
    fseek(disk, offset, SEEK_SET);
    //create inode
    inode *node = malloc(sizeof(inode));
    //get data
    node = fread(node, sizeof(inode), 1, disk);
    
    //if failed read: free memory, return null
    if (node == NULL){
        free(node);
        return NULL;
    }

    return node;
}

int fs_close(int offset){
    

}

int fs_write(){

}
