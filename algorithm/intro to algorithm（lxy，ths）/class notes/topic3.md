## Topic 3  Comparsion Based Sorting Algorithms

### Basic Concepts

#### Stability

![image-20230921145409796](./assets/image-20230921145409796.png)

#### Time Complexity

Usually measured by the number  of data comparisons and the number of data movements in the algorithm execution.

#### In-place Sorting 

**Only a constant** of elements are **stored outside the input array**.

### Simple Sorting Algorithms

#### Insertion Sort

```c
insertion-sort(A)
{
    for j =2 to A.length do
        key = A[j]
        i = j-1
        while i >0 and A[i] > key do
            A[i + 1] = A[i]
            i = i-1
        A[i+1] = key
}
```

![image-20230921150726286](./assets/image-20230921150726286.png)

#### Selection Sort

Select and remove the smallest element from unsorted set

```
selection-sort(A)
{
	for i = 1 to A.length - 1 do
		k = i
		for j = i+1 to A.length do
			if A[j] < A[k] then
				k = j
		if k != i then
			A[i] <-> A[k]
}
```

![image-20230921151211874](./assets/image-20230921151211874.png)

Stable sorting: How to revise the selection sorting to make it stable?

#### Bubble Sort

From the back to the front, if some elements are smaller than their predecessor, then swap them.

![image-20230921151552621](./assets/image-20230921151552621.png)

![image-20230921151628880](./assets/image-20230921151628880.png)

### Efficient Sorting Algorithms

#### Shellsort

![image-20230921152228486](./assets/image-20230921152228486.png)

![image-20230921152235162](./assets/image-20230921152235162.png)



#### Heapsort

#### Quicksort

### Summary