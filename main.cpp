#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>



using namespace std::chrono;


//----------Random Number Generator--------------------
int* randomNumberGenerator(int arraySize, int newSort[]){
    //Planting random seed
    srand((unsigned)time(NULL));
    //Creating array of random number
    //Establishing
    int random;
    bool inserted;
    bool isDuplicate;

    for(int i = 0; i < arraySize; i++){

        inserted = false;
        //Checking for duplicates
        while(!inserted){

            //Random number between 1 and 20,000
            random = (rand()%20000)+1;
            isDuplicate = false;

            for(int x = 0; x < i; x++){
                //Checking if the randomly generated number is currently in the array
                //If it is in array set bool to True.
                if(random == newSort[x]){

                    isDuplicate = true;
                }
            }
            //Not duplicate, add random number to the array.
            if(!isDuplicate){

                newSort[i] = random;
                std::cout<< newSort[i]<<std::endl;
                //Now inserted move on
                inserted = true;
            }
        }
    }

    return newSort;
}
//------------------Print Array-----------------------

void printArray(int arraySize, int* newSort){

    for(int i = 0; i< arraySize; i++){

        std::cout<<newSort[i]<<std::endl;
    }
}


//--------------Insertion Sort-------------------
void insertionSort(int arraySize, int newSort[]){
    //creating temp variable
    int j, hold;


    for(int i = 0; i< arraySize; i++){

        j = i;

        while(j>0 && newSort[j]< newSort[j-1]){

            hold = newSort[j];
            newSort[j] = newSort[j-1];
            newSort[j-1] = hold;
            j--;
        }
    }
}
//-------------Merge Sort-------------------------------
void merge(int newSort[], int low, int high, int middle){

    int p1, p2, p3;
    //Creating two temporary sub arrays to hold smaller portions.
    int temp1 = middle - low + 1;
    int temp2 = high - middle;

    //Creating temporary arrays to be used as sub arrays
    int left[temp1], right[temp2];

    //For loops to copy the data to the temporary arrays
    for(p1 = 0; p1 < temp1; p1++){

        left[p1] = newSort[low + p1];
    }
    for(p2 = 0; p2 < temp2; p2++){

        right[p2] = newSort[middle + 1 + p2];
    }

    //--------------Merging---------------
    //Initial indexes
    p1 = 0;
    p2 = 0;
    p3 = low;
    //Merge temp arrays into original array
    while(p1 < temp1 && p2 < temp2){

        if(left[p1]<= right[p2]){

            newSort[p3] = left[p1];
            p1++;

        }
        else{

            newSort[p3] = right[p2];
            p2++;

        }
        p3++;
    }
    //Copying remaining elements of sub arrays
    while(p1 < temp1){

        newSort[p3] = left[p1];
        p1++;
        p3++;

    }
    while(p2 < temp2){

        newSort[p3] = right[p2];
        p2++;
        p3++;

    }
}

//Actual merge sort
void mergeSort(int newSort[], int low, int high){

    int middle;
    if(low < high){

        //Finding middle of array
        //Avoids overflow
        middle = (low + high)/2;
        //Sorting separate halves
        mergeSort(newSort, low, middle);
        mergeSort(newSort, middle + 1, high);
        //Merge
        merge(newSort, low, high, middle);

    }

    return;
}

//--------------Heap Sort-----------------------

void swapHeap(int* newSort, int i, int j){

    if(i == j){

        return;
    }

    int temp;
    temp = newSort[i];
    newSort[i] = newSort[j];
    newSort[j] = temp;
}

void organize(int* newSort, int heapS, int node){

    int i, j;
    //Largest as root
    j = node;

    while(i != j){

        i = j;

        if(((2*i + 1) < heapS) && newSort[j] < newSort[2*i + 1]) {

            j = 2*i + 1;

        }

        if(((2*i + 2) < heapS) && newSort[j] < newSort[2*i + 2]) {

            j = 2*i + 2;

        }


        swapHeap(newSort, i, j);

    }
}

//Constructing a heap
void createHeap(int arraySize, int* newSort){

    for(int i = arraySize - 1; i >= 0; --i){

        organize(newSort, arraySize, i);

    }
}

void heapSort(int arraySize, int* newSort){

    createHeap(arraySize, newSort);

    //Grab an element from the heap
    for(int i = arraySize - 1; i > 0; --i){

        //Move current root to end
        swapHeap(newSort, i, 0);
        //call organize
        organize(newSort, i, 0);

    }
}

//------------ Quick Sort----------------
// The partition function
int partition(int* newSort, int i, int j)
{
    //Last element as pivot or furthest to the right
    int pivot = newSort[j];

    while ( i < j )
    {
        while ( newSort[i] < pivot )
            //Increase index or move to the right
            i++;

        while ( newSort[j] > pivot )
            //Decrease index or move to the left.
            j--;

        if ( newSort[i] == newSort[j] )
            //Increase index
            i++;
        else if ( i < j )
        {
            //Swap
            int tmp = newSort[i];
            newSort[i] = newSort[j];
            newSort[j] = tmp;
        }
    }

    return j;
}

// The quicksort recursive function
void quickSort(int* newSort, int i, int j)
{
    if ( i < j )
    {
        //n is the partitioning index
        int n = partition(newSort, i, j);
        //Before index
        quickSort(newSort, i, n-1);
        //After index
        quickSort(newSort, n+1, j);
    }
}


int main()
{
    //To be used for finding the execution time.
    auto t_start = std::chrono::high_resolution_clock::now();
    auto t_end = std::chrono::high_resolution_clock::now();

    //Taking in size of List
    int size;
    std::cout<< "Please enter size of list: "<<std::endl;
    std::cin>> size;


    int sortThis[size], sortMergeArray[size],sortHeapArray[size],sortQuickArray[size];


    std::cout<<"Unsorted"<<std::endl;

    //Copying into different arrays for easier access with sorting algorithms
    //Wanted to make sure that the first sort was random and not influenced by another sorting algorithm.
    randomNumberGenerator(size, sortThis);
    std::copy(sortThis, sortThis + size, sortMergeArray);
    std::copy(sortThis, sortThis + size, sortHeapArray);
    std::copy(sortThis, sortThis + size, sortQuickArray);



    std::cout<<"------------------------------------------"<<std::endl;

    //------------------------------------------------------------------------

    std::cout<<"Insertion Sort" <<std::endl;
    //Unsorted
    t_start = std::chrono::high_resolution_clock::now();
    insertionSort(size, sortThis);
    t_end = std::chrono::high_resolution_clock::now();


    //printArray(size, sortThis);

    std::cout << std::fixed<<"Unsorted: "
              << "Wall clock time passed: "
              << std::chrono::duration<float, std::milli>(t_end-t_start).count()
              << " ms/n"<<std::endl;

    t_start =  std::chrono::high_resolution_clock::now();
    insertionSort(size, sortThis);
    t_end = std::chrono::high_resolution_clock::now();

    std::cout << std::fixed<<"Sorted: "
              << "Wall clock time passed: "
              << std::chrono::duration<float, std::milli>(t_end-t_start).count()
              << " ms/n"<<std::endl;

    std::cout<<"------------------------------------------"<<std::endl;

    //--------------------------------------------------------------------------

    std::cout<<"Merge Sort"<<std::endl;

    t_start = std::chrono::high_resolution_clock::now();
    mergeSort(sortMergeArray, 0, size - 1);
    t_end = std::chrono::high_resolution_clock::now();

    //printArray(size, sortMergeArray);

    std::cout << std::fixed<<"Unsorted: "
              << "Wall clock time passed: "
              << std::chrono::duration<float, std::milli>(t_end-t_start).count()
              << " ms/n"<<std::endl;

    t_start = std::chrono::high_resolution_clock::now();
    mergeSort(sortMergeArray, 0, size - 1);
    t_end = std::chrono::high_resolution_clock::now();

    std::cout << std::fixed<<"Sorted: "
              << "Wall clock time passed: "
              << std::chrono::duration<float, std::milli>(t_end-t_start).count()
              << " ms/n"<<std::endl;

    std::cout<<"------------------------------------------"<<std::endl;

    //---------------------------------------------------------------------

    std::cout<<"Heap Sort"<<std::endl;

    t_start = std::chrono::high_resolution_clock::now();
    heapSort(size, sortHeapArray);
    t_end = std::chrono::high_resolution_clock::now();

    //printArray(size, sortHeapArray);

    std::cout << std::fixed<< "Unsorted: "
              << "Wall clock time passed: "
              << std::chrono::duration<float, std::milli>(t_end-t_start).count()
              << " ms/n"<<std::endl;

    t_start = std::chrono::high_resolution_clock::now();
    heapSort(size, sortHeapArray);
    t_end = std::chrono::high_resolution_clock::now();

    std::cout << std::fixed<<"Sorted: "
              << "Wall clock time passed: "
              << std::chrono::duration<float, std::milli>(t_end-t_start).count()
              << " ms/n"<<std::endl;

    std::cout<<"------------------------------------------"<<std::endl;

    //----------------------------------------------------------------------

    std::cout<<"Quick Sort"<<std::endl;

    t_start = std::chrono::high_resolution_clock::now();
    quickSort(sortQuickArray, 0, (size-1));
    t_end = std::chrono::high_resolution_clock::now();

    //printArray(size, sortQuickArray);

     std::cout << std::fixed<<"Unsorted: "
              << "Wall clock time passed: "
              << std::chrono::duration<float, std::milli>(t_end-t_start).count()
              << " ms/n"<<std::endl;

    t_start = std::chrono::high_resolution_clock::now();
    quickSort(sortQuickArray, 0, size);
    t_end = std::chrono::high_resolution_clock::now();

    std::cout << std::fixed<<"Sorted: "
              << "Wall clock time passed: "
              << std::chrono::duration<float, std::milli>(t_end-t_start).count()
              << " ms/n"<<std::endl;
    std::cout<<"------------------------------------------"<<std::endl;

    //------------------------------------------------------------------------

    return 0;
}
