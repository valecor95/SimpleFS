#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bitmap.h"

int BitMap_getBit(BitMap* bmap, int pos){
    if(pos >= bmap->num_bits) return -1;                                //error, start not in range of bitmap blocks
    
    BitMapEntryKey map = BitMap_blockToIndex(pos);                      //convert to easy use shift
    return bmap->entries[map.entry_num] >> map.bit_num & mask;
}

BitMapEntryKey BitMap_blockToIndex(int num){
    BitMapEntryKey map;
    int byte = num / bit_in_byte;
    map.entry_num = byte;
    char offset = num - (byte * bit_in_byte);
    map.bit_num = offset;
    return map;
}

int BitMap_indexToBlock(int entry, char bit_num){
    if (entry < 0 || bit_num < 0) return -1;                            //error, block not in range of bitmap blocks
    return (entry * bit_in_byte) + bit_num;
}

int BitMap_get(BitMap* bmap, int start, int status){
    if (start > bmap->num_bits) return -1;                              //error, start not in range of bitmap blocks
    
    while(start < bmap->num_bits){                                      //loop to search status on bitmap
        if(BitMap_getBit(bmap, start) == status) return start;
        start++;
    }
    return -1;
    
}

int BitMap_set(BitMap* bmap, int pos, int status){
    if(pos >= bmap->num_bits) return -1;                                //error, start not in range of bitmap blocks
    
    BitMapEntryKey map = BitMap_blockToIndex(pos);
    unsigned char for_change = 1 << map.bit_num;                        //create mask for the bit in the byte
    unsigned char to_change = bmap->entries[map.entry_num];             //byte where to use mask
    
    if(status == 1){
        bmap->entries[map.entry_num] = to_change | for_change;          //mask by OR to have 1
        return to_change | for_change;
    }
    else{
        bmap->entries[map.entry_num] = to_change & (~for_change);        //mask by AND to have 0 (with !mask)
        return to_change & (~for_change);
    }
}
