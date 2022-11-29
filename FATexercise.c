#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <stdint.h>
int totalBytes = 0;
int fatBytes = 0;
int storePointer = 0;
int fd;

typedef struct __attribute__((__packed__))
{
    uint8_t BS_jmpBoot[ 3 ]; // x86 jump instr. to boot code
    uint8_t BS_OEMName[ 8 ]; // What created the filesystem
    uint16_t BPB_BytsPerSec; // Bytes per Sector
    uint8_t BPB_SecPerClus; // Sectors per Cluster
    uint16_t BPB_RsvdSecCnt; // Reserved Sector Count
    uint8_t BPB_NumFATs; // Number of copies of FAT
    uint16_t BPB_RootEntCnt; // FAT12/FAT16: size of root DIR
    uint16_t BPB_TotSec16; // Sectors, may be 0, see below
    uint8_t BPB_Media; // Media type, e.g. fixed
    uint16_t BPB_FATSz16; // Sectors in FAT (FAT12 or FAT16)
    uint16_t BPB_SecPerTrk; // Sectors per Track
    uint16_t BPB_NumHeads; // Number of heads in disk
    uint32_t BPB_HiddSec; // Hidden Sector count
    uint32_t BPB_TotSec32; // Sectors if BPB_TotSec16 == 0
    uint8_t BS_DrvNum; // 0 = floppy, 0x80 = hard disk
    uint8_t BS_Reserved1; //
    uint8_t BS_BootSig; // Should = 0x29
    uint32_t BS_VolID; // 'Unique' ID for volume
    uint8_t BS_VolLab[ 11 ]; // Non zero terminated string
    uint8_t BS_FilSysType[ 8 ]; // e.g. 'FAT16 ' (Not 0 term.)
} BootSector;

/*pedef struct __attribute__((__packed__))
{
	uint16_t    clusterLabels[ fatBytes/16 ];		// breaking the entire FAT into 16 bit sections - these are the labels for the 
//ASK IF THIS CAN BE DONE WITHOUT A TYPE DEF --- COULDN'T FIND A SUITABLE DATA TYPE TO GO INTO void*
} FatTable;
*/

typedef struct __attribute__((__packed__))
{
	uint8_t		DIR_Name[ 11 ];		// Non zero terminated string
	uint8_t		DIR_Attr;		// File attributes
	uint8_t		DIR_NTRes;		// Used by Windows NT, ignore
	uint8_t		DIR_CrtTimeTenth;	// Tenths of sec. 0..199
	uint16_t	DIR_CrtTime;		// Creation Time in 2s intervals
	uint16_t	DIR_CrtDate;
	uint16_t	DIR_LstAccDate;		// Date of last read or write
	uint16_t	DIR_FstClusHI;		// Top bits file's 1st cluster
	uint16_t	DIR_WrtTime;		// Time of last write
	uint16_t	DIR_WrtDate;		// Date of last write
	uint16_t	DIR_FstClusLO;		// Lower bits file's 1st cluster
	uint32_t	DIR_FileSize;		// File size in bytes

} DirectoryEntry;

void Boot_Sector_Vals(BootSector *fileBoot)
{
    read(fd, fileBoot, sizeof(BootSector)); //reading in entire bootsector and assigning each section to a part of the struct 
}

int * Find_File_Clusters()
{
    /*
    static int *clusterList;
    clusterList = malloc(sizeof(uint16_t) * size);
    //go through chain again storing order of clusters

    }

    static int *clusterList;
    clusterList = malloc(sizeof(uint16_t) * size);
    //go through chain again storing order of clusters
*/
}


int main()
{
    char * store = (char *) malloc(100);

    fd = open("fat16.img", O_RDONLY);

    if(fd != -1)
    {

    //initialising values of boot sector
        BootSector fileBoot; 
        Boot_Sector_Vals(&fileBoot);
        printf("%s\n", fileBoot.BS_VolLab);

        printf("%d\n", fileBoot.BPB_BytsPerSec);





        //create var of start of fat
        fatBytes = fileBoot.BPB_FATSz16 * fileBoot.BPB_BytsPerSec;
        int fatStart = sizeof(BootSector) +  (fileBoot.BPB_BytsPerSec * fileBoot.BPB_RsvdSecCnt);
        //var for size of FAT (for validation)
        int startingCluster = 02; //this value changes depending on starting cluster of file
        int *fileClusterList = Find_File_Clusters(fatStart, startingCluster); //values called with *(fileClusterStart + x*16) where x is the element in the array
        //get value of first cluster number - not at first 16 bits of table
        //seek to next cluster number*16 




    //start of directory
        int dirStart = sizeof(BootSector) + (fileBoot.BPB_BytsPerSec * fileBoot.BPB_RsvdSecCnt) + (fileBoot.BPB_NumFATs * fatBytes); // size of the boot sector * size of the reserved sectors * size of all FATs
        //lseek(fd, dirStart, SEEK_SET);
    //create a table to output (in style of the one on the pointer arithmetic page) 

    //loop (each entry is 22 bytes)
        //lseek(fd, 22, SEEK_CUR);
        //create entry
        //add this entry to the running table in format stated in task 4 description
    }   
    close(fd);
    free(store);
    return 0;
}