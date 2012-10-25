#ifndef HASHTABLE_H_
#define HASHTABLE_H_

//pick a prime number to help even distribution of hashTable
#define TABLESIZE 151

typedef struct{
    int table[TABLESIZE];
}hashTable;

typedef struct{
	unsigned int key; //aka pid #
	unsigned int hashed_key;
	char process_name[250];
	unsigned int mem_usage;
	unsigned int cpu_usage;
	unsigned int running;
  unsigned int num_threads;
	/* TODO: Finish implementing entry struct for data we decide to store */
}hashEntry;


int hash(int key);
void hashTable_new(hashTable * ht);

#endif /* HASHTABLE_H_ */
