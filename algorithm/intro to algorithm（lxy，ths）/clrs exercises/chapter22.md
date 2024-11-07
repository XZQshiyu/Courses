# chapter 22 基本的图算法

## 22.1

### 22.1-1

#### Question：

![image-20240114174744411](./assets/image-20240114174744411.png)

#### Answer：

设顶点数为 $V$，边的个数为 $E$

出度：$\sum_{v \in V} (out\_degree(v)) = O(|V|+|E|)$

入度：$\sum_{v \in V} (in\_degree(v)) = O(|V|+|E|)$

### 22.1-2

#### Question：

![image-20240115115617642](./assets/image-20240115115617642.png)

#### Answer：

![IMG_1227(20240115-124920)](./assets/IMG_1227(20240115-124920).PNG)

### 22.1-3

#### Question：

![image-20240115124724457](./assets/image-20240115124724457.png)

#### Answer：

邻接表：

```c++
let Adj'[1...|V|] be a new adjacency list of the transposed G^T
for each vertex u in G.V
    for each v in Adj[u]
        Insert(Adj'[v],u)
```

时间复杂度为 $O(|E| + |V|)$

邻接矩阵：

做一个矩阵转置操作

时间复杂度为 $O(|V|^2)$

### 22.1-4

#### Question：

![image-20240115125351128](./assets/image-20240115125351128.png)

#### Answer：

### 22.1-6

### 22.2 广度优先搜索

#### 22.2.6



![image-20240115224530915](./assets/image-20240115224530915.png)

![image-20240115224536954](./assets/image-20240115224536954.png)

![image-20240115224602675](./assets/image-20240115224602675.png)

这题的意思是说，对于一个图的任意一颗生成树和某个确定的源点s，并不是通过从s的BFS得到一棵相应的生成树

#### 22.2.7

![image-20240115224916475](./assets/image-20240115224916475.png)

问题抽象成 一个n个顶点，r条边的图，找到一种二染色方案

![image-20240115225555210](./assets/image-20240115225555210.png)

>本质上是以一个顶点为起点跑一次BFS，得到一棵BFS生成树，对奇数层次染一种颜色，偶数层染另一个颜色，然后对每一条边进行检查

#### 22.2.8

![image-20240115230837520](./assets/image-20240115230837520.png)

从树上任意点u开始(BFS)遍历图，得到距离u最远的结点v,然后从v点开始BFS遍历图，得到距离v最远的结点w， 则v、w之间的距离就是树的直径。

![image-20240115230821852](./assets/image-20240115230821852.png)

#### 22.2.9

![image-20240115231849918](./assets/image-20240115231849918.png)

![image-20240115231842555](./assets/image-20240115231842555.png)
