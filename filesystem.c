
#include<stdlib.h>
#include<stdio.h>
#define USED 1
#define NOT_USED 0
#define BLOCK_SIZE 512
#define INODE_MAX 30
#define INODE_SIZE 60
#define SUPERBLOCK_SIZE 2048
#define DISK_NAME "./Drive10MB"

void error(char *message, char *location);

#include"./file.h"
#include"./disk.h"

int find_open_inode();
int find_open_block();
void fs_create(char *name, char *ext, char *disk_name, superblock *sb);


int main(){
    
    //initialize the disk
    superblock *sb = init_disk(DISK_NAME, sb);
    printf("%d\n", sb->inode_count);
    puts("!");
    //create the root directory
    fs_create("root", "dir", DISK_NAME, sb);
    //open the root file
    FILE *disk = fopen(DISK_NAME, "r+");
    inode *n = (inode *)malloc(sizeof(inode));
    fseek(disk, sb->inode_locaton, SEEK_SET);
    fread(&n, sizeof(n), 1, disk);
    fclose(disk);
    printf("ID: %d\nStart Block: %d\nName: %s\nExt: %s\n", n->id, n->start_block, n->name, n->extension);
    
}

//a light shell for the user to interact with the file system
void shell(){


}

//finds and returns the number of an open block
int find_open_block(superblock *sb){
    //loop through the block map
    for(int i = 1; i < sb->block_count; i++){
        //if open block found
        if (sb->block_map[i] == NOT_USED){
            //set block to used
            sb->block_map[i] = USED;
            //return the block number
            return i; 
        }
    }
    //else no open blocks
    error("No open block found", "find_open_block");
    return 0;
}

//finds and returns the number of the open inode spot
int find_open_inode(superblock *sb){
    //loop through the inode map
    for(int i = 1; i < sb->inode_max; i++){
        //if open inode found
        if (sb->inode_map[i] == NOT_USED){
            //set inode to used
            sb->inode_map[i] = USED;
            //return the inode number
            return i; 
        }
    }
    //else no open inodea
    error("No open inode found", "find_open_inode");
    return 0;
}

void fs_create(char *name, char *ext, char *disk_name, superblock *sb){
    inode *n = new_inode(name, ext);
    if (n == NULL){
        error("Could not create inode", "fs_create");
        return;
    }

    if (sb == NULL){
        error("Could not read superblock", "fs_create");
        free(n);
        return;
    }
    
    //get file location and starting block address
    int inode_num = find_open_inode(sb);
    int block_num = find_open_block(sb);
    //calculate the block address
    int inode_address = (inode_num * INODE_SIZE) + sb->inode_locaton;
    int block_address = (block_num * BLOCK_SIZE) + sb->data_location;

    //if no open inodes or blocks
    if (inode_num == 0 || block_num == 0){
        error("Could not create file", "fs_create");
        free(n);
        return;
    }
    //set the inode info
    n->id = inode_num;
    n->start_block = block_num;

    //open the disk
    FILE *disk = fopen(disk_name, "r+");
    //if disk couldn't be opened
    if (disk == NULL){
        error("File could not be opened", "fs_create");
        free(n);
        exit(1);
    }
    
    fseek(disk, sb->inode_locaton, SEEK_SET);
    //else write the inode to disk
    fwrite(&n, sizeof(n), 1, disk);
    
    //close disk
    fclose(disk);
    
}

void error(char *message, char *location){
    printf("ERROR: %s\nLOCATION: %s\n", message, location);
    return;
}