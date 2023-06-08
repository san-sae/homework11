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

int initialize(int **a); // 배열의 각 원소 초기화하는 함수
int freeArray(int *a); // 메모리 해제하는 함수
void printArray(int *a); // 배열 상태 출력하는 함수

int selectionSort(int *a); // 선택정렬 함수
int insertionSort(int *a); // 삽입정렬 함수
int bubbleSort(int *a); // 버블정렬 함수
int shellSort(int *a); // 셸정렬 함수
/* recursive functiond */
int quickSort(int *a, int n); // 퀵정렬 함수


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key); 

/* array a에 대한 hash table 만듦 */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command; // 명령어
	int *array = NULL; //정수 배열에 대한 포인터 변수
	int *hashtable = NULL; // 해시 테이블에 대한 포인터 변수
	int key = -1; // 검색에 사용되는 키값
	int index = -1; // 검색에 사용되는 인덱스

	srand(time(NULL)); // 난수 생성기의 시드 값 설정

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
		scanf(" %c", &command); // 명령어 입력

		switch(command) {
		case 'z': case 'Z':
			initialize(&array); // 배열 초기화
			break;
		case 'q': case 'Q':
			freeArray(array); // 메모리 해제
			break;
		case 's': case 'S':
			selectionSort(array); // 선택정렬
			break;
		case 'i': case 'I':
			insertionSort(array); // 삽입정렬
			break;
		case 'b': case 'B':
			bubbleSort(array); // 버블정렬
			break;
		case 'l': case 'L':
			shellSort(array); // 셸정렬
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); // 정렬 전 배열 출력
			quickSort(array, MAX_ARRAY_SIZE); // 퀵정렬
			printf("----------------------------------------------------------------\n");
			printArray(array); // 정렬 후 배열 출력

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); // 해시 전 배열 출력
			hashing(array, &hashtable); // 해싱
			printArray(hashtable); // 해싱 후 해시 테이블 출력
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key); // 키값 입력
			printArray(hashtable); // 해싱 전 해시테이블 출력
			index = search(hashtable, key); // 해시테이블에서 입력한 키에 맞는 해시코드 위치를 index에 저장
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]); // 해시코드 위치 출력
			break;

		case 'p': case 'P':
			printArray(array); // 배열 출력
			break;
		default: // 그 이외의 명령어는 무효
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

// 배열의 각 원소 초기화하는 함수
int initialize(int** a){
	int *temp = NULL; // 메모리

	/* array가 NULL인 경우(배열이 할당되지 않은 경우) */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // 메모리 동적 할당
		*a = temp;  /* main() 함수에서도 배열을 control 가능 */
	}
	/* 배열이 할당된 경우 */
	else
		temp = *a;

	/* 배열의 각 요소를 난수로 초기화 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; // 0 ~ (MAX_ARRAY_SIZE -1) 사이의 난수값 저장

	return 0;
}

// 메모리 해제 함수
int freeArray(int *a){
	if(a != NULL) // 배열 a에 대한 할당이 된 경우
		free(a); // 메모리 해제

	return 0;
}

// 배열의 각 원소 출력 함수
void printArray(int *a){

	if (a == NULL) {  // 배열 a에 대한 할당이 된 경우
		printf("nothing to print.\n");
		return;
	}

	// 배열의 인덱스 출력 반복
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");

	// 배열의 인덱스에 따른 값 출력 반복
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

// 선택정렬 알고리즘을 통해 배열 정렬하는 함수
int selectionSort(int *a){
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++){
		// i번째 배열 원소가 최소라고 가정
		minindex = i;
		min = a[i];

		for(j = i+1; j < MAX_ARRAY_SIZE; j++){
			if (min > a[j]){ // 전에 설정한 최소값이 더 이상 최소값이 아닐 경우
				min = a[j]; // 현재의 배열 원소를 최소값으로 설정
				minindex = j; // 현재의 배열 원소의 인덱스도 최소 인덱스로 설정
			}
		}

		// 최소값을 정렬 범위의 첫번째 요소로 이동하기 위해 a[minindex]와 a[i]값 교환
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 배열 출력
	return 0;
}

// 삽입정렬 알고리즘을 통해 배열 정렬하는 함수
int insertionSort(int *a){
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++){
		t = a[i]; // 현재 비교할 요소
		j = i; // 현재 비교할 요소의 인덱스

		// 정렬된 부분에서 t보다 큰 값들을 오른쪽으로 한 칸씩 이동
		while (a[j-1] > t && j > 0){
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 배열 출력

	return 0;
}

// 버블정렬 알고리즘을 통해 배열 정렬하는 함수
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++){
		for (j = 0; j < MAX_ARRAY_SIZE; j++){
			// 두 원소를 비교하여 더 작은 값을 앞으로 이동
			if (a[j-1] > a[j]){
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 배열 출력

	return 0;
}

// 셸정렬 알고리즘을 통해 배열 정렬하는 함수
int shellSort(int *a){
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2){ // 반복문을 돌면서 배열사이즈/2로 바꾸어 서브배열에 대해 삽입 정렬 수행
		for (i = 0; i < h; i++){ 
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h){
				v = a[j]; // 현재 원소 저장
				k = j;
				while (k > h-1 && a[k-h] > v){ // k가 h-1보다 크면서 이전요소(a[k-h])가 현재 원소보다 큰 경우 
					// 서브 배열 내에서 삽입정렬 수행
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v; // v의 위치를 올바르게 조정하는 마지막 단계
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 후 배열 출력

	return 0;
}

// 퀵정렬 알고리즘을 통해 배열 정렬하는 함수
int quickSort(int *a, int n){
	int v, t;
	int i, j;

	if (n > 1){ // n이 1보다 클 경우
		v = a[n-1]; // 마지막 원소를 피벗에 저장
		i = -1; // 피벗보다 큰 값을 찾기 위한 인덱스(오른쪽으로 이동할 예정)
		j = n - 1; // 피벗보다 작은 값을 찾기 위한 인덱스(왼쪽으로 이동할 예정)

		while(1){ // 무한루프
			while(a[++i] < v); // 왼쪽부터 시작하여 피벗보다 큰 값을 찾을 때까지 오른쪽으로 이동
			while(a[--j] > v); // 오른쪽부터 시작하여 피벗보다 작은 값을 찾을 때까지 왼쪽으로 이동

			if (i >= j) break; // i와 j의 위치가 반대로 될 때 반복 종료
			// a[i]와 a[j]의 값을 교환
			t = a[i]; 
			a[i] = a[j];
			a[j] = t;
		}
		// a[i]와 a[n-1]의 값을 교환
		// 피벗을 기준으로 분할
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		// 피벗을 기준으로 왼쪽 서브 배열을 재귀적 정렬
		quickSort(a, i);
		// 피벗을 기준으로 오른쪽 서브 배열을 재귀적 정렬
		quickSort(a+i+1, n-i-1);
	}

	return 0;
}

// 입력받은 키를 해시 테이블의 인덱스로 변환하는 함수
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

// 해싱 함수
int hashing(int *a, int **ht){
	int *hashtable = NULL; // 동적할당을 위한 포인터변수

	/* hash table NULL */
	if(*ht == NULL) { // 해시 테이블이 null인 경우
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // 해시 테이블에 동적 할당
		*ht = hashtable;  /* 동적할당한 해시 테이블의 주소를 복사 --> main에서 control */
	}
	else { // 해시 테이블이 null이 아닌 경우
		hashtable = *ht;	/* hash table NULL, table , reset to -1 */
	}

	// 해시테이블의 모든 요소를 -1로 초기화
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	int key = -1;
	int hashcode = -1;
	int index = -1;

	for (int i = 0; i < MAX_ARRAY_SIZE; i++){
		key = a[i]; // 현재 요소를 키로 설정
		hashcode = hashCode(key); // 키를 해시 코드로 변환

		if (hashtable[hashcode] == -1){ // 해당 해시 코드 위치가 비어 있을 경우
			hashtable[hashcode] = key; // 해당 해시 코드 위치에 현재 키로 설정
		}
		else{ // 해당 해시 코드 위치가 다른 요소로 된 경우

			index = hashcode; // 현재 해시 코드 위치를 인덱스로 설정

			while(hashtable[index] != -1){ // 비어있는 해시코드 위치인 경우 반복
				index = (++index) % MAX_HASH_TABLE_SIZE; // 모듈러 연산을 통해 index를 다음 위치로 이동
			}

			hashtable[index] = key; // 빈 위치를 찾은 경우 해당 위치를 현재 요소의 키로 설정
		}
	}

	return 0;
}

// 해시 테이블에서 입력받은 키를 검색하여 주소 반환하는 함수
int search(int *ht, int key){
	int index = hashCode(key); // 입력받은 키를 해시 코드로 변환하여 인덱스로 설정

	if(ht[index] == key) // 해당 인덱스에 대한 해시 테이블 요소가 입력받은 키와 일치하는 경우
		return index; // 해당 인덱스 반환
 
	while(ht[++index] != key) // 해당 인덱스에 대한 해시 테이블 요소와 입력받은 키가 일치할 때까지 반복
		index = index % MAX_HASH_TABLE_SIZE; // 인덱스가 해시 테이블의 크기를 초과하는 경우, 인덱스 조정

	return index; // 일치하는 테이블 요소의 인덱스 반환
}


