## PageRank算法

### 基本理念：

- 链接投票机制：一个网页被越多其他网页链接，它就越重要
- **权威传递**：来自重要网页的链接比普通网页的链接更有价值
- **民主投票**：每个网页平等地将其重要性分配给它链接的所有网页

### 计算公式：

#### 1. 基础公式

对于网页 $i$，其 PageRank 值 $PR(i)$ 的计算公式：

$PR(i)= \sum_{j \in B_i} \frac{PR(j)}{L(j)}$

其中：

- $B_i$：所有指向网页 $i$ 的网页集合（反向链接）
- $L(j)$：网页 $j$ 的出链数量
- $\frac{PR(j)}{L(j)}$：网页 $j$ 分配给每个出链的 PageRank 值

##### 2. 加入阻尼因子（Damping Factor）

实际应用中的完整公式：

$PR(i)= \frac{1-d}{N} + d \sum_{j \in B_i} \frac{PR(j)}{L(j)}PR(i)$

其中：

- $d$：阻尼因子（通常取 0.85）
- $N$：网页总数
- $\frac{1-d}{N}$：随机跳转概率的贡献

##### 3. 矩阵形式

PageRank 可以表示为矩阵运算：

$PR=d \cdot \mathbf{M} \cdot \mathbf{PR} + \frac{1-d}{N} \mathbf{e}$

其中：

- $\mathbf{PR}$：PageRank 向量
- $\mathbf{M}$：转移概率矩阵
- $\mathbf{e}$：全 1 向量