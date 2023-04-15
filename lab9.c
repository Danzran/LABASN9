#include <stdio.h>
#include <stdlib.h>


// RecordType
typedef struct RecordType
{
    int id;
    char name;
    int order;
    // create a next pointer (for linkedlist structure)
    struct RecordType *next;
}RecordType;

// Fill out this structure
struct HashType
{
    // create a pointer to a RecordType
  struct RecordType *head;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    // hash function is x % tableSize
    return x % tableSize;
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    // call the hash function to get the index
    int index = hash(record->id, tableSize);
    // if the RecordType at that index is NULL
    if(hashTable[index].head == NULL)
      hashTable[index].head = record;
        // set 'record' equal to the HashType pointer in the table at index
    // else
    else{
      RecordType *tmp = hashTable[index].head;
      while(tmp->next != NULL){
        tmp = tmp->next;
      }
      tmp->next = record;
    }
        // traverse to the end of the linkedlist and add 'record' to the end of it
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    int i;
    RecordType *currentRecord;

    for (i = 0; i < tableSize; i++)
    {
        currentRecord = hashTable[i].head;

        printf("Index %d -> ", i);

        while (currentRecord != NULL)
        {
            printf("%d, %c, %d -> ", currentRecord->id, currentRecord->name, currentRecord->order);
            currentRecord = currentRecord->next;
        }

        printf("NULL\n");
    }
}


int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize the hash table
    int hashTableSize = 11;
    struct HashType *HashTable = calloc(hashTableSize, sizeof(struct HashType));
    for(int i = 0; i < recordSz; i++){
      insertRecord(HashTable, &pRecords[i], hashTableSize);
    }
    displayRecordsInHash(HashTable, hashTableSize);
    // create a variable hashTableSize and assign it a value
    // initialize a hashTable, use calloc (so everything is assigned to NULL)
    // for each record in pRecords, insert it into the hash table using the insertRecord function
    // call the display records function
    // free all the allocated memory
    free(pRecords);
    free(HashTable);

    return 0;
}