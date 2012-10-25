#include <hashTable.h>

//hash func if we decide to use pid as our hash key
int hash(int key){
	if(key > TABLESIZE){
    	int mod = key % TABLESIZE;
    	int divisor = key / mod;
    	mod--; //decrement mod number to fill space zero in hash table
    	return divisor + mod;
    }else{
    	return key - 1; //subtract one to fill zero space in hash table
    }	
	//we should not get here
	return -1;
}

//hash func if we decide to use the process name as key
int hash(char * key){
	return -1; //implement
}

void hashTable_new(hashTable * ht){
	int i = 0;
	for(i; i < TABLESIZE; i++){
		ht->table[i] = NULL;
	}
}