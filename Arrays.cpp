#include <iostream>

struct Array {

	int *A;
	int size;
	int length;
};


//Displays the elements within an array
//Displays only from 0 to length, not 0 to the full size 
void display(struct Array arr) {
	int i;

	std::cout << '\n' << '\n' << '\n';
	std::cout << "Elements are: " << '\n';
	for (i = 0; i < arr.length; i++) {
		std::cout << arr.A[i] << '\n';
	}

	std::cout << '\n' << '\n';

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
	else {
		std::cout << "Error: not enough room inside of the array. Cannot perform operation" << '\n';
	}
};







//Take the array by ADDRESS since it will modify the array
//This is pointing to the OBJECT arr, not a particular arr, just the WHOLE object
//Meaning we can modify its member variables 
void insertElement(struct Array *arr, int index, int value) {

	//Check to see if the size of the array is big enough for another element
	if (arr->length + 1 > arr->size) {
	
		std::cout << "Error: Array is not big enough" << '\n';

		return;
	};


	// we have to check if the index is valid, which is 0 to the length of the array
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


//Return the index at which the element is stored at
int getIndex(struct Array arr, int element) {

	//Use a for loop to iterate through the array's length
	for(int i = 0; i < arr.length; i++){
		
		//if the element is equal, return the index
		if (element == arr.A[i]) {
			return i;
		};
	
	}
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





//Find the sum of the full array
//Pass the array as a parameter
int sumOfElementsWithinArray(struct Array arr) {
	
	//Create a local variable total to represent a count for the total sum
	int total = 0;

	//create a for loop to iterate through each element within the array
	for (int i = 0; i < arr.length; i++) {
		
		//with each iteration, add the element with total, and store it within total
		total +=arr.A[i];
			
	};

	//return total
	return total;

};




//Find the sum of the full array and divide by the total number of elements
// which is length -1
//Pass the array as a parameter
float averageOfElementsWithinArray(struct Array arr) {

	//Create a local variable total to represent a count for the total sum
	int total = 0;

	//create a local variable average to represent the average value
	float average;

	//create a for loop to iterate through each element within the array
	for (int i = 0; i < arr.length; i++) {

		//with each iteration, add the element with total, and store it within total
		total += arr.A[i];

	};

	//since we are getting the average, we want the length, not length - 1 which gives us
	//the location of the last element within an array
	//Static cast the sum in order to have a float return value in average
	average = static_cast<float>(total) / arr.length;


	//return total
	return average;

};








//Recursively obtains the sum of the array
//This is done in O(n), because the activation records  that are called is in
//O(n), a regular for loop is prefered 
int sumOfElementsWithArrayRecursive(struct Array arr, int n) {
		
	//the index is only from 0 to n, so if it falls below 0 then return 0
	if (n < 0) {
		return 0;
	}
	else
		//recursively calls the function, this will keep doing n - 1 recurisvely
		//until it reaches n = 0, then it will add up A[n] and return the sum of the array
		return sumOfElementsWithArrayRecursive(arr, n - 1) + arr.A[n];
	
};




//Pass in the array as a parameter
void reverseArrayAuxilary(struct Array* arr) {
	
	//Create a new int array within the heap and have ArrayB point to it
	//We want the length of our new int array to be the same length as our
	//struct Array arr's length
	int* ArrayB = new int[arr->length];


	
	//We create a for loop with two indexes, i represents the index starting at our starting arrayA
	//We want to reverse the order so we start at the end of our array which is length - 1
	//our second index j represents the auxilary array which will hold the reversed values of our starting ArrayA
	//index j will start at 0, we want this loop to continue until it iterates through the whole array
	for (int i = arr->length - 1, j = 0; i >= 0; i--, j++) {
		
		//on each iteration, we want to store the element that is stored in ArrayA and place it into ArrayB
		ArrayB[j] = arr->A[i];

	
	};
	
	//Once we have iterated through the full array with the first loop, we then want to transfer 
	//the values from ArrayB, and place it into ArrayA from 0 to Length - 1, thus achieving the reverse
	for (int i = 0; i < arr->length; i++) {
	
		arr->A[i] = ArrayB[i];


	};
	


};






//pass in array pointer into parameter since we will be changing the value of the array
//This can be either int or void, its void if you dont want to return a value
//it can be int if you want to return 0 for successful or 1 for unsucessful, i will use int
int reverseArraySwap(struct Array *arr) {


	//We want to create two index points, one at the beginning of the array, and one at the end
	// then we want to swap each element until the two indexes cross, thats when we know we are finished
	for (int i = 0, j = arr->length - 1; i < j; i++, j--) {
	
		//We can use the swap element functions previously created to swap the elements by address
		//We must use pointers since we are changing the values and want this change to
		//be true even after the function ends
		swapElements(&arr->A[i], &arr->A[j]);
	

		//return 0 for success

		return 0;
	};

	//return 1 for unsuccessful
	return 1;
};



//Pass array into parameter
void shiftElementsToRight(struct Array* arr) {

	//Create a forloop taht iterates through the entire array, starting at 
	//the end of the array, until the beginning
	for (int i = arr->length - 1; i >= 0; i--) {
		
		//Since A[0] is our starting point, we cannot obtain the element from n-1
		//so when will input 0 
		if (i == 0) {
		
			arr->A[0] = 0;
		}
		else {

		//We want to copy the element from the previous index into the current index
		//to achieve a shift
			arr->A[i] = arr->A[i - 1];
		}
	
	};
};











//Pass array into parameter
void rotateElementsToRight(struct Array* arr) {

	//this temp array will store a single element
	//the reason for this temp array is, we need to store the element at the end of the array
	//since we are shiftting to the left, we cannot place the value of length - 1, directly 
	//into the first index, it will overide the values that are already inside of index 0
	//So we can create a temp array to hold that value
	int tempArray[1];


		//We want to create a for loop that will start at the end of the array and iterate to the beginning
		for (int i = arr->length - 1; i > 0; i--) {


			//Our first edge case is when the index is at the end of the array
			//which is actually the starting point, this is where we want to actually store
			//the value of A[0] in a temp array , since we are going to transfer the element from 
			//A[length - 1] to A[0], we want to save the value of A[0] first prior to doing so
			if (i == arr->length - 1) {


				//We will store the value of A[0] in a temp array 
				tempArray[0] = arr->A[0];
				//We can then insert the element of A[length - 1] into A[0]
				arr->A[0] = arr->A[i];
			}

			//when i is 1, this is where we want to place the element that we stored inside of the temp array
			//but prior to doing so, we have to transfer the value that is within A[i] to A[i+1] to shift it
			//after shifting it, we can then insert tempArray[0]
			else if (i == 1) {
				arr->A[i + 1] = arr->A[i];
				arr->A[i] = tempArray[0];
			}
			else {

				//Since we are shifting to the right in this case, all is left is to shift the value of A[i]
				//to the next one over A[i+1]
				arr->A[i + 1] = arr->A[i];
			}


		};	

};


//Pass the array and element into function
void insertElementIntoSortedArray(struct Array* arr, int element) {
	
	//have the index start at the end of the array, since its sorted, we are working backwards
	int i = arr->length - 1;

	//Check to see if we have space in order to insert a value
	if (arr->length == arr->size) {
		return;
	}
	//Create a while loop that continues to iterate until our element is greater than A[i]
		while (element < arr->A[i]) {
		
		//We want to shift the elements to the right after each iteration
			arr->A[i + 1] = arr->A[i];
			i--;
		};
		//Once our element is greater than A[I] we want to insert our element at that index
		arr->A[i + 1] = element;

		//then we want to increase the length of our array since we inserted an element
		arr->length++;


};


 





//data type is bool since we are returning true or false
//pass array as parameter
bool checkIfArrayIsSorted(struct Array arr) {

	//Create a for loop the starts from the beginning of the array A[0]
	//up until length - 2, the reason for length -2 and not the typical length -1
	//is because we are making a comparison, and we cannot compare length - 1
	//with anything  because length is not apart of our array
	for (int i = 0; i < arr.length - 2; i++) {
	
	//if the value of the number on the left is greater than the number on the right
	//then we know that the array is not sorted and can return false
		if (arr.A[i] > arr.A[i + 1]) {

			return false;
		}

	};

	//if we iterated throught the array and all of the numbers on the left are less
	//than the numbers on the right then we can return true
	return true;

};



//Create a function to swap negative and positive values
//We want to pass the pointer since we are changing the values within the array
void swapNegativeAndPositive(struct Array* arr) {


	//We want to create two indexes, i and j, i represents the beginning of the array,
	//and I will scan for any positive numbers, j will scan for any negative numbers
	int i = 0;
	int j = arr->length - 1;

	//this loop is true until i (positive scanner) is greater than j ( negative scanner)
	while (i < j) {

		//if the value at the beginning of the array is negative, continue iterating to
		// the end of the array, however if i(positive scanner) comes across a positive
		//number then exit out of the loop
		while (arr->A[i] < 0) {
			i++;
		}
		//once exited, a new while loop will be entered with j, which will do the same
		//starting at the end of the array and scanning for negative numbers, if it comes across
		//a negative number it exits the loop
		while (arr->A[j] >= 0) {
			j--;
		}

		//once both of these values have been found, swap the two and do this process again until i > j
		if (i < j) {
			swapElements(&arr->A[i], &arr->A[j]);
		}

	}


};



// Array1  - {2,4,6,8,10}
//Array 2 - {1,3,5,7,9}

//Array1 - Size 5 & Length 5
//Array2 - Size & Length is 5


//Array3 - {1,2,3,4,5,6,7,8,9,10}
//Array3 - Size & Length  is 10









//Goal is to sort two sorted arrays and place it into a third array
//Third array will be given back as a pointer (array3)
struct Array *mergeTwoSortedArrays(struct Array* arr, struct Array* arr2) {



	//Create a third array dynamically where Array1 + Array2 will be merged
	//The size of Array3 will be A length + B length
	struct Array* array3 = new struct Array[arr->length + arr2->length];


	//With the third array created, now we want to set 3 indexes
	//which will represent all three arrays, i,j and c respectively
	//and initialize all of them to 0

	int i = 0;		//Array1
	int j = 0;		//Array2
	int c = 0;		//Array3
				



	//We want to compare the elements of Array1 with Array2, and whichever
	//element is less, we want to store it inside of Array 3 and then move
	//the index + 1, we can go from 0 to length  which represents the last
	//value inside of the array



	while (i < arr->length   && j < arr2->length  ){
		
		//Create an if statement that compares the element at index i
		//with index j, and if the value is lower, place the element of i
		//inside of array3 at index c, which is for the third array
		if (arr->A[i] < arr2->A[j]) {
			
			array3->A[c] = arr->A[i];

			//go to the next element for both index i(array1), and index c(array3)
			i++;
			c++;
		}

		else if (arr2->A[j] < arr->A[i]) {

				array3->A[c] = arr2->A[j];

				j++;
				c++;

			}
		

	}
	//same logic is applied for when the element at j is lower than i
	
	// then we should be left with
	//a remainder of either i (array1) or j (array2) so all we do is copy 
	//those elements straight into array3



	for (; i < arr->length; i++) {
		
		array3->A[c] = arr->A[i];
		c++;
	};

	for (; j < arr->length; j++) {
	
		array3->A[c] = arr2->A[j];
	
	};

	array3->length = arr->length + arr2->length;
	array3->size = 10;


	//now we can return the pointer pointing to the new struct Array obj

	//This is returning an address, remember new returns an address within the heap
	return array3;
	
	};
 

//------------------------------------------------------------------------------//


//Union of two arrays, if the value is present, then do not place in array3
struct Array* unionTwoSortedArrays(struct Array* arr, struct Array* arr2) {



	//Create a third array dynamically where Array1 + Array2 will be merged
	//The size of Array3 will be A length + B length
	struct Array* array3 = new struct Array[arr->length + arr2->length];


	//With the third array created, now we want to set 3 indexes
	//which will represent all three arrays, i,j and c respectively
	//and initialize all of them to 0

	int i = 0;		//Array1
	int j = 0;		//Array2
	int c = 0;		//Array3




	//We want to compare the elements of Array1 with Array2, and whichever
	//element is less, we want to store it inside of Array 3 and then move
	//the index + 1, we can go from 0 to length  which represents the last
	//value inside of the array



	while (i < arr->length && j < arr2->length) {

		//Create an if statement that compares the element at index i
		//with index j, and if the value is lower, place the element of i
		//inside of array3 at index c, which is for the third array
		if (arr->A[i] < arr2->A[j]) {

			array3->A[c] = arr->A[i];

			//go to the next element for both index i(array1), and index c(array3)
			i++;
			c++;
		}

		else if (arr2->A[j] < arr->A[i]) {

			array3->A[c] = arr2->A[j];

			j++;
			c++;

		}
		else {

			//if they are equal to each other then just take one element from either arrays
			//and advance forward since we do not want duplicates

			array3->A[c] = arr->A[i];
			c++;
			j++;
			i++;
		}


	}
	//same logic is applied for when the element at j is lower than i

	// then we should be left with
	//a remainder of either i (array1) or j (array2) so all we do is copy 
	//those elements straight into array3



	for (; i < arr->length; i++) {

		array3->A[c] = arr->A[i];
		c++;
	};

	for (; j < arr->length; j++) {

		array3->A[c] = arr2->A[j];

	};

	array3->length = c;
	array3->size = 10;


	//now we can return the pointer pointing to the new struct Array obj

	//This is returning an address, remember new returns an address within the heap
	return array3;

};

//------------------------------------------------------------------------------//


//intersection only copies if they are equal
struct Array* intersectionTwoSortedArrays(struct Array* arr, struct Array* arr2) {



	//Create a third array dynamically where Array1 + Array2 will be merged
	//The size of Array3 will be A length + B length
	struct Array* array3 = new struct Array[arr->length + arr2->length];


	//With the third array created, now we want to set 3 indexes
	//which will represent all three arrays, i,j and c respectively
	//and initialize all of them to 0

	int i = 0;		//Array1
	int j = 0;		//Array2
	int c = 0;		//Array3




	//We want to compare the elements of Array1 with Array2, and whichever
	//element is less, we want to store it inside of Array 3 and then move
	//the index + 1, we can go from 0 to length  which represents the last
	//value inside of the array



	while (i < arr->length && j < arr2->length) {

		//Create an if statement that compares the element at index i
		//with index j, and if the value is lower, place the element of i
		//inside of array3 at index c, which is for the third array
		if (arr->A[i] < arr2->A[j]) {

			//Just move to the next element since they are not equal
			i++;
			
		}

		else if (arr2->A[j] < arr->A[i]) {

		//Just move to the next element since they are not equal
			j++;
			

		}
		else if (arr->A[i] = arr2->A[j]){

			array3->A[c] = arr->A[i];
			c++;
			j++;
			i++;
		}


	}
	//same logic is applied for when the element at j is lower than i

	// then we should be left with
	//a remainder of either i (array1) or j (array2) so all we do is copy 
	//those elements straight into array3




	array3->length = c;
	array3->size = 10;


	//now we can return the pointer pointing to the new struct Array obj

	//This is returning an address, remember new returns an address within the heap
	return array3;

};




//------------------------------------------------------------------------------//

//Union of two arrays, if the value is present, then do not place in array3
struct Array* differenceTwoSortedArrays(struct Array* arr, struct Array* arr2) {



	//Create a third array dynamically where Array1 + Array2 will be merged
	//The size of Array3 will be A length + B length
	struct Array* array3 = new struct Array[arr->length + arr2->length];


	//With the third array created, now we want to set 3 indexes
	//which will represent all three arrays, i,j and c respectively
	//and initialize all of them to 0

	int i = 0;		//Array1
	int j = 0;		//Array2
	int c = 0;		//Array3




	//We want to compare the elements of Array1 with Array2, and whichever
	//element is less, we want to store it inside of Array 3 and then move
	//the index + 1, we can go from 0 to length  which represents the last
	//value inside of the array



	while (i < arr->length && j < arr2->length) {

		//Create an if statement that compares the element at index i
		//with index j, and if the value is lower, place the element of i
		//inside of array3 at index c, which is for the third array
		if (arr->A[i] < arr2->A[j]) {

			array3->A[c] = arr->A[i];

			//go to the next element for both index i(array1), and index c(array3)
			i++;
			c++;
		}

		else if (arr2->A[j] < arr->A[i]) {

			//if array2 is less then move to the next index
			j++;

		}
		else {
			//if they are equal then move to the next index

			j++;
			i++;
		}


	}
	//same logic is applied for when the element at j is lower than i

	// then we should be left with
	//a remainder of either i (array1) or j (array2) so all we do is copy 
	//those elements straight into array3


	//Only copy the elements from array 1
	for (; i < arr->length; i++) {

		array3->A[c] = arr->A[i];
		c++;
	};



	array3->length = c;
	array3->size = 10;


	//now we can return the pointer pointing to the new struct Array obj

	//This is returning an address, remember new returns an address within the heap
	return array3;

};


























//------------------------------------------------------------------------------//

//------------
 struct Array *unionOfTwoUnsortedArrays(struct Array *arr, struct Array *arr2){
 
	 //First we want to create a third array inside of the heap
	 struct Array* array3 = new struct Array[arr->length + arr2->length];
	 array3->size = arr->length + arr2->length;
	 array3->length = 0;

	 //Create three index variables for Array1, Array2 and Array3
	 int i = 0;
	 int j = 0;
	 int c = 0;

	 //We want to insert Array1 elements inside of the third array

	 for (int i = 0; i < arr->length; i++) {
		
		 array3->A[c] = arr->A[i];
		 c++;
		 array3->length++;
	 
	 };
	 
	 //Now that we have Array1 inside of Array3, we now need to compare the elements in Array2
	 //With the elements already present in array3, if the value is present, dont insert,
	 //if it is not present then insert in array3

	 for (int j = 0; j < arr2->length; j++) {
		
		for (int c = 0; c < array3->length; c++){
			
			if( array3->A[c] == arr2->A[j]  ){
			}
			else {
				array3->A[array3->length] = arr2->A[j];
			}
		
		}
	 
	 };
	 
	 
	 return array3;
 
 };


 










	
	int main() {

		struct Array arr1;
		int choice;
		int value;
		int index;

		std::cout << "Enter the size of the array: ";
		std::cin >> arr1.size;
		arr1.length = 0;
		arr1.A = new int[arr1.size];
		
		std::cout << "Menu \n";
		std::cout << "1. Insert \n";
		std::cout << "2. Delete \n";
		std::cout << "3. Search \n";
		std::cout << "4. Sum \n";
		std::cout << "5. Display \n";
		std::cout << "6. Exit \n";

		std::cout << "enter your choice ";
		std::cin >> choice;

		//Create a switch case
		switch (choice) {
		case 1: std::cout << "Enter an index and value";
			std::cin >> index;
			std::cin >> value;
			insertElement(&arr1, index, value);
			break;


		}
		display(arr1);

		//struct Array arr = { {0,20,50,80,100}, 10,5 };
		//struct Array arr2 = { {10,30,60,90,99}, 10,5 };
		//struct Array arr3 = { {2,6,10,15,25}, 10,5 };
		//struct Array arr4 = { {3,6,7,15,20}, 10,5 };
		//int i;
		//int v;
		//std::cin >> i;
		//std::cin >> v;
		//insert(&arr, i, v);
		//insert(&arr, 5, 525);
		//append(&arr, 99);
		//std::cout << deleteElement(&arr, 3) << '\n' << '\n';
		//append(&arr, 49);
		//std::cout << deleteElement(&arr, 2) << '\n' << '\n';
		//append(&arr, 62);
		//std::cout << deleteElement(&arr, arr.length - 1) << '\n' << '\n';
		//display(arr);
		//improvedLinearArraySearchMoveToHead(&arr, 77);
		//display(arr);
		//deleteElement(&arr, 0);
		//std::cout << binaryArraySearchUsingLoop(arr, 100) << '\n' << '\n';
		//std::cout << binarySearchArrayUsingRecursion(arr.A,100,0,arr.length-1) << '\n' << '\n';
		//display(arr);
		//setElement(&arr, 1, 444);
		//display(arr);
		//insertElement(&arr, 0, 999);
		//deleteElement(&arr, 1);
		//display(arr);
		//reverseArraySwap(&arr);
		//reverseArrayAuxilary(&arr);
		//shiftElementsToRight(&arr);
		//rotateElementsToRight(&arr);
		//insertElementIntoSortedArray(&arr, 101);
		//swapNegativeAndPositive(&arr2);
		//insertElement(&arr2, 0, 4444);
		//insertElement(&arr2, 0, 4443);
		//insertElement(&arr2, 0, 4442);
		//insertElement(&arr2, 0, 4441);
		//insertElement(&arr2, 0, 4440);
		//insertElement(&arr2, 0, 4439);
		//display(arr2);
		//std::cout <<  checkIfArrayIsSorted(arr);
		//std::cout << '\n' << '\n' << maxElement(arr);
		//std::cout << '\n' << '\n' << minElement(arr);
		//std::cout << '\n' << '\n' << sumOfElementsWithinArray(arr);
		//std::cout << '\n' << '\n' << sumOfElementsWithArrayRecursive(arr, arr.length - 1);
		//std::cout << '\n' << '\n' << averageOfElementsWithinArray(arr);
		//std::cout << '\n' << '\n' << arr.length;
		//deleteElement(&arr, 1);
		//display(arr);
		//reverseArrayAuxilary(&arr);
		//std::cout << '\n' << '\n' << getElement(arr, 2) << '\n';
		//std::cout << '\n' << '\n' << linearArraySearch(arr, 21) << '\n';
		//display(arr);
		// 
		//display(arr2);
		// 
		// 
		//struct Array *arr3 = mergeTwoSortedArrays(&arr, &arr2);
		//struct Array* array3 = differenceTwoSortedArrays(&arr3, &arr4);
		//for (int i = 0; i < 10; i++) {
		//	std::cout << array3->A[i] << '\n';
		//}
		

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











