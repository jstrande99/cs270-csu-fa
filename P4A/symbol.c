#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "Debug.h"
#include "symbol.h"

/** @file symbol.c
 *  @brief You will modify this file and implement the symbol.h interface
 *  @details Your implementation of the functions defined in symbol.h.
 *  You may add other functions if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file. The reference implementation added approximately
 *  110 lines of code to this file. This count includes lines containing
 *  only a single closing bracket (}).
 * <p>
 * @author <b>Your name</b> goes here
 */

/** size of LC3 memory */
#define LC3_MEMORY_SIZE  (1 << 16)

/** Provide prototype for strdup() */
char *strdup(const char *s);

/** defines data structure used to store nodes in hash table */
typedef struct node {
  struct node* next;     /**< linked list of symbols at same index */
  int          hash;     /**< hash value - makes searching faster  */
  symbol_t     symbol;   /**< the data the user is interested in   */
} node_t;

/** defines the data structure for the hash table */
struct sym_table {
  int      capacity;    /**< length of hast_table array                  */
  int      size;        /**< number of symbols (may exceed capacity)     */
  node_t** hash_table;  /**< array of head of linked list for this index */
  char**   addr_table;  /**< look up symbols by addr                     */
};

/** djb hash - found at http://www.cse.yorku.ca/~oz/hash.html
 * tolower() call to make case insensitive.
 */

static int symbol_hash (const char* name) {
  unsigned char* str  = (unsigned char*) name;
  unsigned long  hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

  c = hash & 0x7FFFFFFF; /* keep 31 bits - avoid negative values */

  return c;
}

/** @todo implement this function */
sym_table_t* symbol_init (int capacity) {

	sym_table_t *newTable = (sym_table_t*) calloc(1, sizeof(sym_table_t));

	newTable -> hash_table = (node_t**) calloc(capacity, sizeof(node_t*));

	newTable -> addr_table = (char**) calloc(LC3_MEMORY_SIZE, sizeof(char*));

	newTable -> size = 0;

	newTable -> capacity = capacity; 

  return newTable;
}

/** @todo implement this function */
void symbol_term (sym_table_t* symTab) {
	symbol_reset(symTab); 
	free(symTab -> hash_table); //try to break this during testing 
	free(symTab); 
}

/** @todo implement this function */
void symbol_reset(sym_table_t* symTab) {
	for(int i = 0; i < (symTab -> capacity); i++){  //iterate through
		node_t* current = symTab -> hash_table[i];  //new node initalized to hash table at index i
		node_t* temp;  //temp node place holder 
		while(current != NULL){ 
			temp = current; //save head 
			current = current -> next; // move head
			free(temp -> symbol.name); 
			free(temp); 
			symTab -> size--; //Check to make sure this works. 
		}
		symTab -> hash_table[i] = NULL; 
	}
}

/** @todo implement this function */
int symbol_add (sym_table_t* symTab, const char* name, int addr) {
	int hash; 
	int index; 

	if(!symbol_search(symTab, name, &hash, &index)){ 
		node_t* newNode = (node_t*) calloc(1, sizeof(node_t));
		symTab -> size++;
		newNode -> next = symTab -> hash_table[index];  
		newNode -> symbol.name = strdup(name); 
		strcpy(newNode -> symbol.name, name); 
		newNode -> symbol.addr = addr; 
		newNode -> hash = hash; 
		symTab -> hash_table[index] = newNode;
		symTab -> addr_table[addr] = newNode -> symbol.name; 		
		return 1; 
	} 
	return 0; 
}

/** @todo implement this function */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index) {
	*hash = symbol_hash(name);
	*index = (*hash % symTab -> capacity);
	node_t* node; 
	node = symTab -> hash_table[*index]; 
	while(node != NULL){ 
		if(*hash == node -> hash){ 
			if(strcasecmp(name, node -> symbol.name) == 0){ 
				return node; 
			}  
	 	}
		node = node -> next;
	}
	return NULL; 
}

/** @todo implement this function */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
	int hash;
	int index; 
	for(int i = 0; i < symTab -> capacity; i++){ 
		node_t* temp = (symTab -> hash_table[i]); 
		while(temp != NULL){
			if(symbol_search(symTab, name, &hash, &index)){
				return &(temp -> symbol);
			}
		}
	}
	return NULL; 
}

/** @todo implement this function */
char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
	if(symTab -> addr_table[addr] != NULL){ 
		return symTab -> addr_table[addr]; 
	}
	return NULL; 
}

/** @todo implement this function */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data) {
	
	for(int i = 0; i < symTab -> capacity; i++){ 
		node_t* temp = symTab -> hash_table[i]; 
		while(temp != NULL){ 
			
			(*fnc)(&(temp -> symbol), data);
			
			temp = temp -> next; 

		}
	
	}
}

/** @todo implement this function */
int symbol_size (sym_table_t* symTab) {
	//for(int i = 0; i < (symTab -> size); i++){ 
	//	symTab -> size++; 
	//}
	return symTab -> size; 
}

/** @todo implement this function */
int compare_names (const void* vp1, const void* vp2) {
	symbol_t* name1 = *((symbol_t**) vp1); // study qsort to understand this
	symbol_t* name2 = *((symbol_t**) vp2); 

	return strcmp((name1 -> name), (name2 -> name)); 
}

/** @todo implement this function */
int compare_addresses (const void* vp1, const void* vp2) {
	symbol_t* addr1 = *((symbol_t**) vp1); 
	symbol_t* addr2 = *((symbol_t**) vp2); 
	//if addr's are same then compare names
	if((addr1 -> addr) == (addr2 -> addr)){ 
		return compare_names(vp1, vp2); 
	} 

	return ((addr1 -> addr) - (addr2 -> addr)); 
}

/** @todo implement this function */
symbol_t** symbol_order (sym_table_t* symTab, int order) {
  
	symbol_t** newSym = (symbol_t**) malloc(symTab -> capacity * sizeof(symbol_t*)); //Double pointer
	int index = 0; 
	//Same as iterate
	for(int i = 0; i < (symTab -> capacity); i++){ //Capacity or size? 
		node_t* temp = symTab -> hash_table[i]; //temp node initalized to hash table at i
		while(temp != NULL){ 
			newSym[index] = &(temp -> symbol); //Must be and int out side of while loop to iterate through
			temp = temp -> next; 
			index += 1; 
		}
	}

	if(order == NAME){ 
		qsort(newSym, symTab -> size, sizeof(symbol_t*), compare_names); //qsort(arr, int, sizeof(), vars)
		return newSym; 
	}
	if(order == ADDR){ 
		qsort(newSym, symTab -> size, sizeof(symbol_t*), compare_addresses); 
		return newSym;
	} 
	if(order == HASH){ //function is completed within the for/while loop ^
		return newSym; 
	}
  return NULL;
}

