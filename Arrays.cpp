#include <iostream>







struct Array {

	int A[10];
	int size;
	int length;
};


void display(struct Array arr) {
	int i;
	std::cout << "Elements are: " << '\n';
	for (i = 0; i < arr.length; i++) {
		std::cout << arr.A[i] << '\n';
	}
};

//Inserts a new element at the end of the array
//we will use a pointer as the parameter since we want to change the value by address

void append(struct Array *arr, int x) {

	if (arr->length < arr->size) {
		arr->A[arr->length++] = x;
		
	}
};
//Take the array by ADDRESS since it will modify the array
void insert(struct Array *arr, int index, int value) {

	//First we have to check if the index is valid, which is 0 to the length of the array
	//if you do index < arr-> then you cannot append because it will not insert at the length of the array
	//but if you do <= then it will insert at the next available slot


	if (index >= 0 && index <= arr->length) {
		for (int i = arr->length; i > index; i--) {

			//A[i] represents the next available location
			//we want to take the last element inside of the array with i-1, and equal it to A[i]
			//this will shift all of the elements up to index, 
			arr->A[i] = arr->A[i - 1];
		};
		//then we insert our values since everything has been shifted
		arr->A[index] = value;

		//the length of our index has grown by 1 since we inserted a value, so we have to 
		//increase the legnth
		arr->length++;
	};

};


int main(){

	
	struct Array arr = { {2,3,4,6,8}, 10,5 };

	int i;
	int v;
	std::cin >> i;
	std::cin >> v;

	insert(&arr, i, v);
	insert(&arr, 6, 525);
	append(&arr, 99);
	display(arr);


	return 0;
};









/*

-------------------------------------------------------------------------------------------------------------------------- -


#include <iostream>

//Increase size of array when created inside the heap



int* array1(int s, int v1, int v2, int v3 ) {


	//Created dynamic memory from the heap, store it in pointer
	int* pointerArray1 = new int[s];

	pointerArray1[0] = v1;
	pointerArray1[1] = v2;
	pointerArray1[2] = v3;


	std::cout << '\n' << "Value of Array 1: " << '\n';
	//values in the Array
	for (int i = 0; i < 3; i++) {
		std::cout << pointerArray1[i] << '\n';
	}


	//return the new arry created in the heap
	//* dereferences it, which is the actual value
	//pointerArray1 by itself is the actaul memory location
	return pointerArray1;


};


int* array2() {

	int* arrayPointer1 = new int[10];

	//initialize values with 0;



	std::cout << '\n' << "Value of Array 2: " << '\n';
	//values in the Array
	for (int i = 0; i < 10; i++) {
		std::cout << arrayPointer1[i] << '\n';
	}

	return arrayPointer1;
};








int main(){

//Swap arrays, or memory swap, the objective is to take an array of size 5, which was dynamically created on the heap
//Insert values, then shift those values to a new array using pointers



	int* pointer = array1(3, 2, 4, 5);

	int* pointer2 = array2();


	//Transfer the values from the first array to the second array
	for (int i = 0; i < 4; i++) {

		pointer2[i] = pointer[i];
	};

	//Delete the allocated memory from array1
	delete []pointer;

	//Point the first pointer to the new array
	pointer = pointer2;

	//Make the second pointer NULL
	pointer2 = NULL;


	std::cout << '\n' << "Array 2 Values: " << '\n';
	for (int i = 0; i < 10; i++) {

		std::cout << pointer[i] << '\n';

	}


	//Had to debug, swapped pointer[i] w pointer1[i], the second array is = to the first

	return 0;
};





-------------------------------------------------------------------------------------------------------------------------- -






#include <iostream>












int main(){

	 //2 dimensional array
	//Nested for loop helps you traverse through a two-dimensional array, row by row

	//Method 1, create a 2d array on the stack normally
	// 4x3, row then column
	//initialize it
	//Fully in the stack
	int Array1[4][3] = { {55,62,45},{786,56,645},{62,347,13},{72,73,43} };

	//Retrieve value of down 3 right 2 (0,0 starting point)
	std::cout << Array1[2][1] << '\n';

	//Method 2, Create a 2D array through a pointer and the heap
	//Create pointer with N amount of rows, and in each row create a new array inside of the heap which will determine the column
	//The array pointer is created in side of the stack, the arrays are created in the heap
	//Half in stack, and half in heap
	int* Array2[3];

	Array2[0] = new int[4];
	Array2[1] = new int[4];
	Array2[2] = new int[4];

	Array2[1][2] = 255;

	//Retrieve value of down 2, right 3
	std::cout << Array2[1][2] << '\n';



	//Method 3, using a double pointer
	//Create a double pointer which will point at a pointer created in the heap, and have the pointer created in the heap
	//point at arrays also created in the heap
	//Everything is inside of the heap, except for the double pointer

	//Double pointer which will be pointed at a pointer that is created in the heap
	int **Array3;

	//Double pointer array 3 has the memory address of a pointer of arrays that have been created inside of the heap
	//the double pointer can use [] in order to find the memory addresses of all 3 pointers and create arrays within the heap
	Array3 = new int* [3];

	//Create first row out of 3 of the array, this is not a pointer,its just an array
	Array3[0] = new int[4];
	Array3[1] = new int[4];
	Array3[2] = new int[4];


	//Input a value

	Array3[1][3] = 55;

	std::cout << Array3[1][3] << '\n';

	//Row
	for (int i = 0; i < 3; i++) {
		//Column
		for (int j = 0; j < 4; j++) {
			Array3[i][j] = 0;
		};
	};

	//Row
	for (int i = 0; i < 3; i++) {
		//Column
		for (int j = 0; j < 4; j++) {
			std::cout << Array3[i][j] << " (" << i << ' ' << j << ')' << '\n';
		};
	};



	return 0;
};


















-------------------------------------------------------------------------------------------------------------------------- -

#include <iostream>







struct Array {

	int* A;
	int size;
	int length;
};


//Displays all of the elements within the array
void DisplayElements(struct Array arr) {
	int i;

	std::cout << "Elements are: " << '\n' << '\n';

	for (int i = 0; i < arr.size; i++) {
		std::cout << "Element: " << arr.A[i] << " Index: " << i << '\n';
	}
};


//Inserts an element within the array
void insertElement(struct Array arr, int index, int element) {
	//index and element are needed to insert the new value
	//int c can be our current location
	int c;

	for (int i = arr.length; i > index; i--) {
		arr.A[i] = arr.A[i - 1];

	}
	arr.A[index] = element;
	arr.length++;



};

void addElement(struct Array arr, int element) {

	int length = arr.length;

	arr.A[length] = element;


};




int main(){

	//Create an array in the heap w/ a structure
	struct Array arr;

	int elements;

	std::cout << "Enter size of an array: ";
	std::cin >> arr.size;

	//Create a new array inside of the heap of user input size
	arr.A = new int[arr.size];

	//User input to enter how many elements that will be inside of the array
	std::cout << "Enter number of elements: ";
	std::cin >> elements;

	//For loop to traverse through the array to enter elements
	std::cout << "Enter all emenents:";

	for (int i = 0; i < elements; i++) {
		std::cin >> arr.A[i];
	}

	//Number of elements inside of the array
	arr.length = elements;

	DisplayElements(arr);

	insertElement(arr, 9, 99);
	arr.length++;
	insertElement(arr, 9, 98);
	arr.length++;
	DisplayElements(arr);
	addElement(arr, 2222);
	arr.length++;
	DisplayElements(arr);
	insertElement(arr, 4, 9999);
	arr.length++;
	DisplayElements(arr);





	return 0;
};





-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -

























-------------------------------------------------------------------------------------------------------------------------- -




-------------------------------------------------------------------------------------------------------------------------- -



*/











