#include<stdio.h>
#include<stdlib.h>

#include"./file.h"
#include"./disk.h"
//size of blocks in virtual disk
#define BLOCK_SIZE 512
//max number of blocks, 5mb total 
#define MAX_BLOCKS 10240
//max number of files
#define INODE_MAX 1280
//Preset size for superblock is 4kb
#define SUPERBLOCK_SIZE 4096
//assumes INODE takes up 60 bytes
#define INODE_SIZE 60
//size of the inode table = MAX_INODES * INODE_SIZE
#define INODE_TABLE_SIZE 76800 
#define MAX_FILE_COUNT 128 //max 128 files

#define DISK1 "./disk1.dat"

int create_disk();

int main(){
    create_disk();
    exit(0);
    inode *n = create_file(1, "abcdefghilkmopqrssssst", "12wwwwww34");
    printf("TOTAL: %lu\nID: %lu\nNAME: %lu\nEXT: %lu\nBLOCK_SIZE: %lu\nBYTE_SIZE: %lu\n", sizeof(n), sizeof(n->id), sizeof(n->name), sizeof(n->extension), sizeof(n->block_count), sizeof(n->byte_size));

    inode *n2 = create_file(2, "new file", ".dat");
    FILE *disk = fopen(DISK1, "w+");
       if (disk == NULL){
        
    }
}

int create_disk(){
    superblock *sb = init_super(SUPERBLOCK_SIZE, INODE_MAX, INODE_SIZE, BLOCK_SIZE, DISK1);
    printf("MAX: %d\n", sb->inode_max);
    FILE *disk = fopen(DISK1, "r+");
    fwrite(sb, sizeof(superblock), 1, disk);
    fclose(disk);

    disk = fopen(DISK1, "r+");
    superblock *sb2 = malloc(sizeof(superblock));
    fread(sb2, sizeof(superblock), 1, disk);
    fclose(disk);
    
    printf("ILOC: %lu\nIMAX: %d\n" , sizeof(superblock), sb2->inode_max);
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
    fread(node, sizeof(inode), 1, disk);
    
    //if failed read: free memory, return null
    if (node == NULL){
        free(node);
        return NULL;
    }

    return node;
}

int fs_close(){
    

}

int fs_write(){


}

