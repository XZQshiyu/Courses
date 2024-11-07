## 二项堆与斐波那契堆（Binomial Heaps and Fibonacci Heaps）

### 1.0 Overview

Mergeable Heap（可归并堆）

支持以下操作

- Make-heap（）：create and return a new heap containing no elements
- Insert()：Insert element x
- Minimum(H)：Return min element
- Extract-min（H）：Return and delete minimum element
- Union(H1,H2)：Create and return a new heap minimum element contains all the elements of heaps H1 and H2

一些其他操作

- 删除一个元素
- 将一个元素x降低为k

一些常见的堆的这些函数的渐进复杂度如下

![image-20231025181803234](./assets/image-20231025181803234.png)

### 1.1 Binomial Heaps

二项堆是二项树的集合，先对二项树进行介绍

#### Binomial Tree（二项树）

![image-20231025182329406](./assets/image-20231025182329406.png)

可以看出来，$B_0$有1个结点，$B_1$有两个结点，$B_2$有两个$B_1$构成，因此是4个结点...

![image-20231025182419619](./assets/image-20231025182419619.png)

对二项树$B_k$来说

- 结点总数是$2^k$
- 树的高度是k
- 根节点的度数（degree）是k，因为根节点连着从$B_0,B_1,...B_{k-1}$一共k棵树
- 删除根结点root可以得到$B_{k-1},...B_1,B_0$等k棵树
- ![image-20231025182813941](./assets/image-20231025182813941.png)

![image-20231025182850560](./assets/image-20231025182850560.png)

#### Binomial Heap：Overview

二项堆是一个二项树的序列，满足

- 每一棵树都是一个最小堆序
- 对于$B_k$只能有一棵或者没有

![image-20231025183225662](./assets/image-20231025183225662.png)

#### 实现方式（Implementation）

![image-20231025183334566](./assets/image-20231025183334566.png)

![image-20231025183423013](./assets/image-20231025183423013.png)

#### 二项堆的性质（Properties）

![image-20231025183655451](./assets/image-20231025183655451.png)

#### Union

![image-20231025183833906](./assets/image-20231025183833906.png)

![image-20231025184003032](./assets/image-20231025184003032.png)

##### Analysis of Union

![image-20231025184204059](./assets/image-20231025184204059.png)

#### Delete Min

![image-20231025184329214](./assets/image-20231025184329214.png)

![image-20231025184408157](./assets/image-20231025184408157.png)

#### Decrease Key

![image-20231025184457221](./assets/image-20231025184457221.png)

#### Delete

![image-20231025184530696](./assets/image-20231025184530696.png)

#### Insert

![image-20231025184553381](./assets/image-20231025184553381.png)

>二项堆最重要的两个操作就是delete-min和union
>
>insert就是建堆+union，delete就是将xdecrease到$-\infty$，而后delete-min



### 1.2 Fibonacci Heaps

#### Structure

![image-20231025185540633](./assets/image-20231025185540633.png)

#### Implementation

![image-20231025185730866](./assets/image-20231025185730866.png)

>每个结点有一个指向父节点和其中一个孩子节点的指针，然后该层是一个循环链表

#### Potential Function

![image-20231025190209076](./assets/image-20231025190209076.png)

##### Insert

![image-20231025190240513](./assets/image-20231025190240513.png)

##### Union

![image-20231025190304117](./assets/image-20231025190304117.png)

![image-20231025190346961](./assets/image-20231025190346961.png)

##### Delete Min

![image-20231025190536782](./assets/image-20231025190536782.png)

![image-20231025190625709](./assets/image-20231025190625709.png)

![image-20231025190708631](./assets/image-20231025190708631.png)

![image-20231025190821438](./assets/image-20231025190821438.png)

![image-20231025190757105](./assets/image-20231025190757105.png)

![image-20231025190845950](./assets/image-20231025190845950.png)

![image-20231025190902248](./assets/image-20231025190902248.png)

##### Delete Min Analysis

![image-20231025192051939](./assets/image-20231025192051939.png)

![image-20231025192247836](./assets/image-20231025192247836.png)

#### Decrease Key

![image-20231025192425303](./assets/image-20231025192425303.png)

![image-20231025192508618](./assets/image-20231025192508618.png)

![image-20231025192537600](./assets/image-20231025192537600.png)

![image-20231025192559805](./assets/image-20231025192559805.png)

![image-20231025192633522](./assets/image-20231025192633522.png)

![image-20231025192702142](./assets/image-20231025192702142.png)

![image-20231025192713386](./assets/image-20231025192713386.png)

##### Decrease Key Analysis

![image-20231025192757829](./assets/image-20231025192757829.png)

#### Delete

![image-20231025192824964](./assets/image-20231025192824964.png)

#### Bounding Max Degree

![image-20231025192859748](./assets/image-20231025192859748.png)

![image-20231025192959122](./assets/image-20231025192959122.png)



### 1.3 Data Structures for Disjoint Sets

#### Overview

![image-20231025193229110](./assets/image-20231025193229110.png)

#### Operations

![image-20231025193501312](./assets/image-20231025193501312.png)

##### Running time analysis

![image-20231025193657263](./assets/image-20231025193657263.png)

#### Link-List Representation

![image-20231025193834095](./assets/image-20231025193834095.png)

##### Example

![image-20231025193938563](./assets/image-20231025193938563.png)

##### Running time analysis

![image-20231025194122723](./assets/image-20231025194122723.png)

![image-20231025194201409](./assets/image-20231025194201409.png)