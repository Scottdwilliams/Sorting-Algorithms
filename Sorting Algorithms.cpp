#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>


using namespace std;

vector<int> bubbleSort(vector<int> v);
vector<int> insertionSort(vector<int> v);
vector<int> merge(vector<int> left, vector<int> right);
vector<int> mergeSort(vector<int> v);
void heapify(vector<int> &v, int s, int i);
vector<int> heapSort(vector<int> v);
int partition(vector<int> &v, int low, int high);
vector<int> quickSort(vector<int> &v, int low, int high);
void printVector(vector<int> v);
void createVector(vector<int> &v, int n);
void validateInt(int &x);

int main()
{

    //for keeping track of execution time
    clock_t start;
    double finish;

    int vectorSize;                 //user input for elements in the vector to sort
    vector<int> originalVector;

    cout << "\n\t\tThe Sorting Hat 3000\n\n" << endl;
    cout << "This program compares sorting methods by filling a vector with random integers and sorting it." << endl;
    cout << "\nFirst, you must designate how large the vector to be sorted should be." << endl;
    cout << "Please input an integer: ";
    cin >> vectorSize;
    validateInt(vectorSize);
    cout << "\nTerrific! Assembling a new vector with " << vectorSize << " random numbers in it." << endl;

    createVector(originalVector, vectorSize);   //create unsorted vector of random numbers

    //print original vector if <= 15 elements
    if (originalVector.size() <= 15)
    {
        cout << "\n\nThe original, unsorted vector: \t\t";
        printVector(originalVector);
    }
    else
    {
        cout << "\n\nThe unsorted vector is too large to show (anything with more than 15 elements).";
    }

    //start the clock
    start = clock();

    //create new vector and run bubble sort
    vector<int> bubbleVector = bubbleSort(originalVector);
    finish = (clock() - start) / (double) CLOCKS_PER_SEC;   //calculate execution time
    cout << "\n\nThe bubble sorted vector took " << finish << " seconds.";
    printVector(bubbleVector);

    //restart the clock
    start = clock();

    //create new vector and run insertion sort
    vector<int> insertionVector = insertionSort(originalVector);
    finish = (clock() - start) / (double) CLOCKS_PER_SEC;   //calculate execution time
    cout << "\nThe insertion sorted vector took " << finish << " seconds.";
    printVector(insertionVector);

    //restart the clock
    start = clock();

    //create new vector and run merge sort
    vector<int> mergeVector = mergeSort(originalVector);
    finish = (clock() - start) / (double) CLOCKS_PER_SEC;   //calculate execution time
    cout << "\nThe merge sorted vector took " << finish << " seconds.\t";
    printVector(mergeVector);

    //restart the clock
    start = clock();

    //create new vector and run heap sort
    vector<int> heapVector = heapSort(originalVector);
    finish = (clock() - start) / (double) CLOCKS_PER_SEC;   //calculate execution time
    cout << "\nThe heap sorted vector took " << finish << " seconds.\t";
    printVector(heapVector);

    //restart the clock
    start = clock();

    //create new vector and run quick sort
    vector<int> quickVector = quickSort(originalVector, 0, originalVector.size() - 1);
    finish = (clock() - start) / (double) CLOCKS_PER_SEC;   //calculate execution time
    cout << "\nThe quick sorted vector took " << finish << " seconds.\t";
    printVector(quickVector);

    return 0;
}

//Bubble Sort
vector<int> bubbleSort(vector<int> v)
{

    unsigned int i, j;
    for (i = 0; i < v.size() - 1; i++)
    {
        for (j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j] > v[j+1]) {swap(v[j],v[j+1]);}
        }
    }

    return v;
}

//Insertion Sort
vector<int> insertionSort(vector<int> v)
{
    int i, j, key;

    for (i = 1; i < v.size(); i++)
    {
        key = v[i];
        j = i - 1;

        //move any element before v[i] (that is greater than key) one position forward
        while (j >= 0 && v[j] > key)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }

    return v;
}

//merge function for merge sort
vector<int> merge(vector<int> left, vector<int> right)
{

    vector<int> result; //create temp vector to merge into

    while (left.size() > 0 || right.size() > 0)
    {
        if (left.size() > 0 && right.size() > 0)
        {
            //compare first elements and put lowest into <result>, erase what was used
            if (left.front() <= right.front())
            {
                result.push_back(left.front());
                left.erase(left.begin());
            }
            else
            {
                result.push_back(right.front());
                right.erase(right.begin());
            }
        }

        //if any elements are remaining in <left>, throw them into <result>
        else if (left.size() > 0)
        {
            for (int i = 0; i < left.size(); i++)
            {
                result.push_back(left[i]);
            }
            break;
        }

        //if any elements are remaining in <right>, throw them into <result>
        else if (right.size() > 0)
        {
            for (int i = 0; i < right.size(); i++)
            {
                result.push_back(right[i]);
            }
            break;
        }
    }
    return result;
}

//merge sort
vector<int> mergeSort(vector<int> v)
{
    if (v.size() <= 1)
    {
        return v;
    }

    vector<int> left, right, result;
    int middle = (v.size() + 1) / 2;

    for (int i = 0; i < middle; i++)
    {
        left.push_back(v[i]);
    }

    for (int i = middle; i < v.size(); i++)
    {
        right.push_back(v[i]);
    }

    left = mergeSort(left);
    right = mergeSort(right);
    result = merge(left,right);

    return result;
}

//heapify function for heap sort
//s = size of vector to heapify, i = index
void heapify(vector<int> &v, int s, int i)
{
    int largest = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;

    if (left < s && v[left] > v[largest])
    {
        largest = left;
    }

    if (right < s && v[right] > v[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(v[i], v[largest]);
        heapify(v, s, largest);
    }
}

//heap sort
vector<int> heapSort(vector<int> v)
{
    //build the heap
    int s = v.size();
    for (int i = (s / 2) - 1; i >= 0; i--)
    {
        heapify(v, s, i);
    }

    //sort the heap
    for (int i = s - 1; i >= 0; i--)
    {
        swap(v[0], v[i]);
        heapify(v, i, 0);
    }

    return v;
}

//partition for quick sort
int partition(vector<int> &v, int low, int high)
{
    int pivot = v[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (v[j] <= pivot)
        {
            i++;
            swap(v[i],v[j]);
        }
    }
    swap(v[i + 1], v[high]);
    return (i + 1);
}

//quick sort
vector<int> quickSort(vector<int> &v, int low, int high)
{
    if (low < high)
    {
        int partitionIndex = partition(v, low, high);

        //sort elements before and after partition
        quickSort(v, low, partitionIndex - 1);
        quickSort(v, partitionIndex + 1, high);
    }

    return v;
}

//standard swap function
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//function to print vector
void printVector(vector<int> v)
{
    if (v.size() >= 16) {return;}    //don't print if more than 15 elements

    cout << "\t{";
    for (int i = 0; i < v.size() - 1; i++)
    {
        cout << v[i] << ", ";
    }
    cout << v[v.size() - 1] << "}";
}

//creates a vector of size n with random integers between 1 and 100
void createVector(vector<int> &v, int n)
{
    srand (time(NULL)); //seed random numbers to time
    int temp;

    for (unsigned int i = 0; i < n; i++)
    {
        temp = rand() % 100 + 1;
        v.push_back(temp);
    }
}

//validates input to ensure a number
void validateInt(int &x)
{
    if (cin.fail()){
        cin.clear();
        cin.clear();
        cin.ignore();
        cout << "\nSorry, that's not a number. Please enter an integer: ";
        cin >> x;
        validateInt(x);
    }

    return;
}
