/*algorithm:*/
int *ArrayDynamicAllocation(int array[], int size, int number) {
    int newSize = size * 2;
    int *newArray = new int[newSize];
    for(int i = 0; i < newSize; i++) {
        if (i >= size) {
            newArray[i] = (array[i - size])*2;
        } else {
            newArray[i] = array[i];
        }
    }
    if (number != 0) {
        return ArrayDynamicAllocation(newArray, newSize, (number - 1));
    } else {
        return newArray;
    }
}

/*test case:*/
int A[2] = {0,2};
int size = 2;
int number = 1;

/*
Iteration 1:
newSize = 2*2 = 4;
newArray = array with size 4
for (0 to 4-1)
  0 is less than 2:
    newArray[0] = A[0]
  1 is less than 2:
    newArray[1] = A[1]
  2 is 2:
    newArray[2] = A[2-2]*2 = A[0]*2
  3 is more than 2:
    newArray[3] = A[3-2]*2 = A[1]*2
delete []A
returns newArray
 
Output: {0,2,0,4}
 */