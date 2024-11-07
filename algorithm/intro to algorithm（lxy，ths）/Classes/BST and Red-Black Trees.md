## BST and Red-Black Trees(二叉搜索树和红黑树)

### 1.0 Overview

#### Binary Trees

![image-20231025195545230](./assets/image-20231025195545230.png)

data structures can support **dynamic set operations**

- Search
- Minimum
- Maximum
- Predecessor
- Successor
- Insert
- Delete

### 1.1 Binary Search Trees

#### BST Representation

![image-20231025201340022](./assets/image-20231025201340022.png)

#### Binary Search Tree Property

![image-20231025201504923](./assets/image-20231025201504923.png)

#### Inorder Traversal

![image-20231025201557949](./assets/image-20231025201557949.png)

##### Correctness of Inorder-Walk

![image-20231025201652884](./assets/image-20231025201652884.png)

#### Preorder Traversal

![image-20231025202307707](./assets/image-20231025202307707.png)

#### Postorder Traversal

![image-20231025202619292](./assets/image-20231025202619292.png)

#### Querying a Binary Search Tree

![image-20231025205620068](./assets/image-20231025205620068.png)

#### Tree Search

![image-20231025205713090](./assets/image-20231025205713090.png)

#### Iterative Tree Search

![image-20231025205741797](./assets/image-20231025205741797.png)

```
IterativeTreeSearch(x, k)
while x != NIL and k != key[x] do
	if k < key[x] then
		x <- left[x]
	else
		x <- right[x]
return x
```

#### Finding Min & Max

![image-20231025205908754](./assets/image-20231025205908754.png)

#### Predecessor and Successor

![image-20231025210226794](./assets/image-20231025210226794.png)

![image-20231025212501216](./assets/image-20231025212501216.png)

#### Insertion and Deletion

![image-20231025212740191](./assets/image-20231025212740191.png)

##### BST insertion 

```
TreeInsert(T,z)
y <- NIL
x <- root[T]
while x != NIL do
	y <- x
	if key[z] < key[x] then
		x <- left[x]
	else
		x <- right[x]
p[z] <- y
if y = NIL then
	root[T] <- z
else if key[z] < key[y]
then
	left[y] <- z
else 
	right[y] <- z
```

![image-20231025213124023](./assets/image-20231025213124023.png)

##### Sorting using BSTs

![image-20231025213359539](./assets/image-20231025213359539.png)

##### BST Deletion

![image-20231025213434021](./assets/image-20231025213434021.png)

```
TreeDelete(T,z)
if left[z] = NIL or right[z] = NIL then
	y <- z
else
	y <- TreeSuccessor[z]
if left[y] != NIL then
	x <- left[y]
else 
	x <- right[y]
if x != NIL then
	p[x] <- p[y]
if p[y] = NIL then
	root[T] <- x
else if y <- left[p[i]] then
	left[p[y]] <- x
else
	right[p[y]] <- x
if y != z then
	key[z] <- key[y]
return y
```

##### Correctness of TreeDelete

![image-20231025220544863](./assets/image-20231025220544863.png)

### 1.2 Red-Black Trees

#### Overview

![image-20231025220614474](./assets/image-20231025220614474.png)

Red-Black Tree

- Binary search tree + 1 bit per node: the attribute color, which is either red or black
- All other attributes of BSTs are inherited: key, left, right, and p
- All empty trees(leaves) are colored black
  - We use a single sentinel, nil, for all the leaves of red-black tree T, with color[nil] = black
  - The root's parent is also nil[T]

![image-20231025220830420](./assets/image-20231025220830420.png)

#### Red-Black Properties

![image-20231025220929256](./assets/image-20231025220929256.png)

##### Height of a Red-Black Tree

![image-20231025221036747](./assets/image-20231025221036747.png)

![image-20231025221527206](./assets/image-20231025221527206.png)

![image-20231025221736418](./assets/image-20231025221736418.png)

![image-20231025221817905](./assets/image-20231025221817905.png)

可以得到一个结论:

>$h \leq 2lg(n+1)$

##### RB Trees: Worst-Case Time

![image-20231025232909785](./assets/image-20231025232909785.png)

#### Rotation

![image-20231025232938800](./assets/image-20231025232938800.png)

#### Insertion

![image-20231025233045691](./assets/image-20231025233045691.png)

Case1:

![image-20231025233216692](./assets/image-20231025233216692.png)

Case2:

![image-20231025233258520](./assets/image-20231025233258520.png)

Case3:

![image-20231025233359576](./assets/image-20231025233359576.png)

#### Delete

##### Ordinary BST Delete

![image-20231025233624913](./assets/image-20231025233624913.png)

##### Bottom-up Deletion

![image-20231025233735685](./assets/image-20231025233735685.png)
![image-20231025234042289](./assets/image-20231025234042289.png)

Case1:
![image-20231025234153589](./assets/image-20231025234153589.png)

Case2:

![image-20231025234357558](./assets/image-20231025234357558.png)

Case3:

![image-20231025234711229](./assets/image-20231025234711229.png)

Case4:

![image-20231025234802521](./assets/image-20231025234802521.png)

### 1.3 Augmenting Data Structures

#### Overview

![image-20231025235128269](./assets/image-20231025235128269.png)

#### Dynamic Order Statistics

![image-20231025235229666](./assets/image-20231025235229666.png)

![image-20231025235257218](./assets/image-20231025235257218.png)
