#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
	int 	next;
};

// Fill out this structure
struct HashType
{
	struct RecordType *hello;

};

// Compute the hash function
int hash(int x, int tableSize)
{
	return (x%tableSize); 
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
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
		}

		fclose(inFile);
	}

	return dataSz;
}

void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
	int a = record->id;
    // call the hash function to get the index
    // if the RecordType at that index is NULL
        // set 'record' equal to the HashType pointer in the table at index
    // else
        // traverse to the end of the linkedlist and add 'record' to the end of it
	
	int index = hash(a,tableSize);
	struct RecordType *curr2 = hashTable[index].hello;
	if (curr2==NULL)
	{
		hashTable[index].hello = record;
	} else 
	{
		while(curr2 -> next != NULL)
		{
			curr2 = curr2->next;
		}
		curr2->next = record;
	}

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

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
	int i;

	for (i=0; i < tableSize; ++i)
	{
		printf("Index %d ->", i);
		struct RecordType *curr = hashTable[i].hello;
		if (curr != NULL)
		{
			while(curr != NULL)
			{
				printf("%d, %c, %d", curr->id,curr->name,curr->order);
				if (curr->next == NULL)
				{
					printf(" ---> NULL");
				}
				curr = curr->next;
			}
			printf("\n");
		}
			// if index is occupied with any records, print all
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	free (pRecords);
}