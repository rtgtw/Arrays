#include <iostream>


struct Array {

	int A[10];
	int size;
	int length;
};


//Displays the elements within an array
//Displays only from 0 to length, not 0 to the full size 
void display(struct Array arr) {
	int i;

	std::cout << '\n' << '\n';
	std::cout << "Elements are: " << '\n';
	for (i = 0; i < arr.length; i++) {
		std::cout << arr.A[i] << '\n';
	}
};






//Inserts a new element at the end of the array
//we will use a pointer as the parameter since we want to change the value by address
void append(struct Array *arr, int x) {


	// This verifies that there is room inside of the array
	//if length = size then there is no room inside of the array
	//Meaning we cannot perform the append logic
	if (arr->length < arr->size) {
		arr->A[arr->length++] = x;
		
	}
};









//Take the array by ADDRESS since it will modify the array
//This is pointing to the OBJECT arr, not a particular arr, just the WHOLE object
//Meaning we can modify its member variables 
void insertElement(struct Array *arr, int index, int value) {

	//First we have to check if the index is valid, which is 0 to the length of the array
	//if you do index < arr-> then you cannot append because it will not insert at the length of the array
	//but if you do <= then it will insert at the next available slot


	if (index >= 0 && index <= arr->length) {

		//Creates a for loop that iterates from the length of the array
		//down to the value of index(where the user wants the value to go)
		for (int i = arr->length; i > index; i--) {

			//A[i] represents the next available location
			//we want to take the last element inside of the array with i-1, and equal it to A[i]
			//this will shift all of the elements up until we hit  index(location of newly inserted value), 
			arr->A[i] = arr->A[i - 1];
		};
		//then we insert our values since everything has been shifted
		arr->A[index] = value;

		//the length of our index has grown by 1 since we inserted a value, so we have to 
		//increase the legnth
		arr->length++;
	};

};









//Delete an element within an array
//We use int here in order to return a success or failure
//Success will return the element deleted, failure will return 1
//This function requires a pointer for this ADT Array, and the index to be deleted
int deleteElement(struct Array *arr, int index) {
	
	//Deletion value, initialized
	int deletedValue = 0;


	//Check to see if the index from the input is valid, if it is between
	//0 and the length - 1, since length vacant
	if (index >= 0 && index <= arr->length - 1) {

		//this represents the actual value that we will delete after the for loop
		//this value will get printed back to the user
		deletedValue = arr->A[index];


	//This for loop starts off at the position of index, which is where the user wants to
	//make a deletion, the reason why its up to length - 1 is because:
	//there is no value at length, the last value inside of our array is length - 1
	//So if we go from userIndex < length, then our logic will copy the content
	// of length  and place it into length -1, which is incorrect, we are only worried about
	// the elements within our array, and length is not apart of our array
		for (int i = index; i < arr->length - 1; i++) {

			//transfers the content of index + 1, into index, which shifts everything to the left
			arr->A[i] = arr->A[i + 1];
		}

		//Decrease the length by 1 since we removed a value
		arr->length--;

		//return the deleted value back to user
		return deletedValue;
	};

	//if the user enters an invalid index, return 1 instead to signify an error
	return 1;
};





  //int data type since we want to return a value, which is the index at which the key is present
//we are just passing in the object inside of the parameter, not the object pointer since 
//we dont want to change any values we just want to search the object
//we pass the key in our parameters to look for the desired value
int linearArraySearch(struct Array arr, int key) {

	//we can create a for loop that iterates through the array from 0 to length in a linear fashion
	//this will take a maximum of O(n) and a minimum of O(1)
	for (int i = 0; i < arr.length; i++) {

		//throughout each iteration, if the key is present within any of the elements
		//within the array, then return the index where it is present
		if (key == arr.A[i]) {
			return i;
		}

	};
	
	//if the key was not found within the array, then return -1 to signify unsuccessful
	return -1;


};









//Create a swap function to swap the values of two elements by address
//This swap function is necessary to perform transposition or Move to Head logic on an array
//to swap two elements after a search query in order to speed up performance
void swapElements(int* x, int* y) {

	int temp;

	temp = *x;
	
	//very subtle blunder, i originally had *y = *x but it should be *x = *y
	//since we want to store x in temp, and give x the value of y
	*x = *y;

	*y = temp;

};








//an improved linear search actually modifies the values of the array through a swap
//so we must use a pointer instead of a call by value
int improvedLinearArraySearchTransposition(struct Array* arr, int key) {


	//This for loop logic took me some time because I had to account for the 
	//edge case of when i = 0; when i = 0 then swapping to i-1 will generate an error
	//To solve this, first create a for loop to iterate through the array
	// within the for loop, first create an if statement that checks if the key is within 
	//A[0], if so then just return the index, and not do i-1
	//else, use the transposition logic w/ swap, if the key is at A[0] then the for loop
	//Breaks, but if it isnt , then it checks the rest of of the array, 1 to length -1
	for (int i = 0; i < arr->length; i++) {

		//if the key matches the value within index 0 then return index 0
		if (key == arr->A[0]) {
			return i;
		}
		//if the key matches an index then, swap the values of elements in the current index and index - 1
		//using a swap function, and return index - 1 since that is the key that was found
		else if (key == arr->A[i]) {

			swapElements(&arr->A[i], &arr->A[i - 1]);

			return i - 1;

		};
	}

	return -1;
};











	//Move to head linear search, this is the same as a transposition linear search
	// the only difference is, instead of swapping out the one to the left, it gets
	//swap to the first position in the array

int improvedLinearArraySearchMoveToHead(struct Array* arr, int key) {

	for (int i = 0; i < arr->length; i++) {

		//if the key is already at A[0] then just return the key, nothing else needs to be done
		if (key == arr->A[0]) {
			return i;
		}
		else if (key == arr->A[i]) {

			//Instead of swapping with the neighbor element
			//Swap directly to the front of the array
			swapElements(&arr->A[i], &arr->A[0]);

			//the index is going to be 0 because it swapped
				return 0;

		};

	};

	//return -1 if the search was unsuccessful
	return -1;
};










//Does a binary search in log2 time complexity, a key in the parameter
//which is the value that you are looking for
//Binary search only works with an array that is sorted, it will not work with an unsorted array
int binaryArraySearchUsingLoop(struct Array arr, int key) {
	
	//define the low of the array, which is the first value
	int left = 0;

	//define the end of the array as the upper bound
	int right = arr.length - 1;
	
	//create a while loop which iterates through unless the condition turns false
	while (left <= right) {
		
		//create the mid point of the lower and upper bound
		int mid = (left + right) / 2;

		//if the key is at the index, return the index
		if (key == arr.A[mid]) {

			return mid;
		}

		//if they key's value is less than the element within the array at A[mid]
		//we want to make our upper bound to mid - 1, we do -1 here because we have already
		//verified that the element at mid is not the key
		else if (key < arr.A[mid]) {
			right = mid - 1;
		}
		//else if the value of our key was higher than the mid element's value we want to
		//make our lower bound mid + 1
		else 
			left = mid + 1;
		


	};
	//return -1 if it was unsuccessful
	return -1;

};









//pass in 4 parameters, an array, the key, left bound and right bound
int binarySearchArrayUsingRecursion(int A[], int key, int left, int right) {

	while (left <= right) {

		int mid = (left + right) / 2;

		if (key == A[mid]) {
			return mid;
		}
		//if the key is less than the mid point, recursively call the function again
		//with the only difference of the new high point being mid - 1
		else if (key < A[mid]) {
			return binarySearchArrayUsingRecursion(A, key, left, mid - 1);
		}
		//if the key is less than the mid point, recursively call the function again
		//with the only difference of the new low point being mid + 1
		else {
			return binarySearchArrayUsingRecursion(A, key, mid + 1, right);
		}

	};
	//return -1 if it was unsuccessful
	return -1;
};



//Get an element within an array
//its int because we are returning a value (key)
int getElement(struct Array arr, int index) {

	//All we have to do is check if the index is valid, by making sure
	//it is not lower than 0 or higher than the length of the array
	if (index >= 0 && index < arr.length) {
		
		//return the element at the specific index given
		return arr.A[index];
	}
	return -1;
};


//Set a value within an array
//Since we are changing the values within the array, we have to use a pointer
//We will use the int data type to return 0 for success and 1 for failure
int setElement(struct Array *arr,int index, int set) {
	
	//Checks if the index the user input is valid and within the bounds of the array
	if (index >= 0 && index < arr->length) {

		//stores the value of the user set at the specified index within the array
		arr->A[index] = set;

		//returns 0 to signify success
		return 0;
	}
	
	//returns -1 to signify failure
	return -1;
};






//Get the max element within an array
//int data type since we are returning the max value
//only parameter is the array
int maxElement(struct Array arr) {

	//create a max variable that will start at the beginning of the array
	int max = arr.A[0];

	//since our max is already set to the value at the beginning of the array
	//all is left is for us to check that value with every other element in the array
	//which will take O(n), this is the only way with an unsorted array,
	//If the array was sorted then we would take the value of length - 1
	for (int i = 1; i < arr.length; i++) {

		//if we find a value that is greater than max, then we change max to the new value
		//at that specific index
		if (arr.A[i] > max) {

			max = arr.A[i];
		};
	}

	return max;
};








//Close to the same logic as max but instead we have a min variable
//We use int data type since we are returning min
int minElement(struct Array arr) {
	
	//create a min variable that holds the first element within the array
	int min = arr.A[0];

	//create a for loop to iterate through the array starting at index 1, since 
	//we stored index 0 and will use that value to check the other elements
	for (int i = 1; i < arr.length; i++) {

		//if the element at index i is less than min, then replace min with A[i]
		if (arr.A[i] < min) {

			min = arr.A[i];
		};
	};

	//return min
	return min;

};












	
	int main() {

		struct Array arr = { {0,20,50,80,100}, 10,5 };

		//int i;
		//int v;
		//std::cin >> i;
		//std::cin >> v;

		//insert(&arr, i, v);
		//insert(&arr, 5, 525);
		append(&arr, 99);
		//std::cout << deleteElement(&arr, 3) << '\n' << '\n';
		append(&arr, 49);
		//std::cout << deleteElement(&arr, 2) << '\n' << '\n';
		append(&arr, 62);
		//std::cout << deleteElement(&arr, arr.length - 1) << '\n' << '\n';
		//display(arr);
		//improvedLinearArraySearchMoveToHead(&arr, 77);
		//display(arr);
		//deleteElement(&arr, 0);
		//std::cout << binaryArraySearchUsingLoop(arr, 100) << '\n' << '\n';

		//std::cout << binarySearchArrayUsingRecursion(arr.A,100,0,arr.length-1) << '\n' << '\n';
		display(arr);
		//setElement(&arr, 1, 444);
		display(arr);
		

		insertElement(&arr, 0, 94);
		deleteElement(&arr, 1);
		display(arr);
		std::cout << '\n' << '\n' << maxElement(arr);
		std::cout << '\n' << '\n' << minElement(arr);
		//deleteElement(&arr, 1);
		//display(arr);
		
		//std::cout << '\n' << '\n' << getElement(arr, 2) << '\n';
		//std::cout << '\n' << '\n' << linearArraySearch(arr, 21) << '\n';


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











