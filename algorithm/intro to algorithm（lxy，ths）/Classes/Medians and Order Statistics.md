## Medians and Order Statistics

### 1.0 Selection Problem

![image-20231025103502010](./assets/image-20231025103502010.png)

选择一个序列中第i位的元素

### 1.1 Minimum and Maximum

#### Minimum

To determine the minimum a set of n elements, a lower bound of comparisons is n-1

```
MINIMUM(A)
min = A[1]
for i = 2 to A.length do
	if min > A[i] then
		min = A[i]
return min
```

#### Simultaneous Minimum and Maximum

![image-20231025104010182](./assets/image-20231025104010182.png)

$3 \lfloor n/2 \rfloor$ comparisons algorithm

```
MAX_MIN(A)
if A[1] > A[2] then min = A[2], max = A[1]
				else min = A[1], max = A[2]
for i = 2 to [n/2] do 
	if A[2i-1] > A[2i]
		then if A[2i] < min then min = A[2i]
			 if A[2i - 1] > max then max = A[2i-1]
	else if A[2i-1] < min then min = A[2i-1]
		if A[2i] > max then max = A[2i]
if n != 2[n/2] then if A[n] < min then min = A[n]
					if A[n] > max then max = A[n]
return (min, max)
	
```

![image-20231025160640007](./assets/image-20231025160640007.png)



### 1.2 Selection in Expected Linear Time

A divided-and-conquer algorithm for selection problem: RANDOMIZED-SELECT

![image-20231025161006262](./assets/image-20231025161006262.png)

```
Randomized-select(A,p,r,i)
if p == r then
	return A[p]
q = Randomized-partition(A, p, r)
k = q-p+1
if i == k then
	return A[q] // the pivot value is the answer
if i < k then
	return Randomized-select(A,p, q-1, i)
else 
	return Randomized-select(a,q + 1, r, i - k)
```

![image-20231025161555708](./assets/image-20231025161555708.png)

Analysis

![image-20231025161909916](./assets/image-20231025161909916.png)



### 1.3 Selection in Worst-case Linear Time

The algorithm SELECT finds the desired element by recursively partitioning the input array.

![image-20231025162847726](./assets/image-20231025162847726.png)

![image-20231025163416138](./assets/image-20231025163416138.png)

Analysis

![image-20231025164157932](./assets/image-20231025164157932.png)

![image-20231025164203528](./assets/image-20231025164203528.png)

![image-20231025164209465](./assets/image-20231025164209465.png)

![image-20231025164216225](./assets/image-20231025164216225.png)