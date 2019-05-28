#include <iostream>
using namespace std;


/** Merges two sorted array segments theArray[first..mid] and
 *  theArray[mid+1..last] into one sorted array.
 * @pre first <= mid <= last. The subarrays theArray[first..mid]
 * and theArray[mid+1..last] are each sorted in increasing order.
 * @post theArray[first..last] is sorted.
 * @param theArray  The given array.
 * @param first  The beginning of the first segment in theArray.
 * @param mid  The end of the first segement in theArray.  mid + 1
 *        marks the beginning of the second segment.
 * @param last  The last element in the second segment in theArray.
 * @note This function merges the two subarrays into a temporary
 * array and copies the result into the original array theArray. */
void merge(int theArray[], int first, int mid, int last, int N_ITEMS )
{
    int tempArray[N_ITEMS];    // temporary array

    // initialize the local indexes to indicate the subarrays
    int first1 = first;       // beginning of first subarray
    int last1  = mid;         // end of first subarray
    int first2 = mid + 1;     // beginning of second subarray
    int last2  = last;        // end of second subarray

    // while both subarrays are not empty, copy the
    // smaller item into the temporary array
    int index = first1;    // next available location in
    // tempArray
    for (; (first1 <= last1) && (first2 <= last2); ++index)
    {
        if (theArray[first1] < theArray[first2])
        {
            tempArray[index] = theArray[first1];
            ++first1;
        }
        else
        {
            tempArray[index] = theArray[first2];
            ++first2;
        }
    }

    // finish off the nonempty subarray

    // finish off the first subarray, if necessary
    for (; first1 <= last1; ++first1, ++index)
    {
        tempArray[index] = theArray[first1];
    }

    // finish off the second subarray, if necessary
    for (; first2 <= last2; ++first2, ++index)
    {
        tempArray[index] = theArray[first2];
    }

    // copy the result back into the original array
    for (index = first; index <= last; ++index)
        theArray[index] = tempArray[index];
}

/** Sorts the items in an array into ascending order.
 * @pre theArray[first..last] is an array.
 * @post theArray[first..last] is sorted in ascending order.
 * @param theArray  The given array.
 * @param first  The first element to consider in theArray.
 * @param last  The last element to consider in theArray. */
void mergeSort(int theArray[], int first, int last, int n)
{
    if (first < last)
    {
        int mid = (first + last)/2;    // index of midpoint

        // sort left half theArray[first..mid]
        mergeSort( theArray, first, mid, n );

        // sort right half theArray[mid+1..last]
        mergeSort( theArray, mid + 1, last, n );
        // merge the two halves
        merge( theArray, first, mid, last, n );
    }
}

int main()
{
	int m;
	cin >> m;
	while (m != 0)
	{	
		int a[m];
		for (int i = 0; i < m; i++)
			cin >> a[i];

		mergeSort(a, 0, m - 1, m);
		for (int i = 0; i < m; i++)
		{
			if (i == m - 1)
				printf("%d",a[i]) ;
			else
				printf("%d ", a[i]);
		}
			
		printf("\n");
		cin >> m;
	}
	return 0;
}
