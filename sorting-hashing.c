/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE	        13	/* prime number */
#define MAX_HASH_TABLE_SIZE     MAX_ARRAY_SIZE

int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function�쇰줈 援ы쁽 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a�먮� �� hash table�� 留뚮뱺��. */
int hashing(int *a, int **ht);

/* hash table�먯꽌 key瑜� 李얠븘 hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

    printf("[--------- [    Choi Yoolim    ] [    2020022001    ] ---------]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array媛� NULL�� 寃쎌슦 硫붾え由� �좊떦 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �좊떦�� 硫붾え由ъ쓽 二쇱냼瑜� 蹂듭궗 --> main�먯꽌 諛곗뿴�� control �좎닔 �덈룄濡� ��*/
	} else
		temp = *a;

	/* �쒕뜡媛믪쓣 諛곗뿴�� 媛믪쑝濡� ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table�� NULL�� 寃쎌슦 硫붾え由� �좊떦 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �좊떦�� 硫붾え由ъ쓽 二쇱냼瑜� 蹂듭궗 --> main�먯꽌 諛곗뿴�� control �좎닔 �덈룄濡� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �꾨땶寃쎌슦, table �ы솢��, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);

		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}


