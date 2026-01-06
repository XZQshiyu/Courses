## 算法设计与分析 HW 1

### T1

> 给出一个转移系统 和断言 ，满足 在 中总为真，但 不是 的不变式

考虑$S=(C,\rightarrow,I)$ 存在 转移 $s_1 \rightarrow s_2$，但是 $s_1$在每一执行中都不可达。如 $S=(\{s_0,s_1,s_2\},\{s_1\rightarrow s_2\},\{s_0\})$，只需令 $P(s_0),P(s_1)$为 true，$P(s_2)$为false，在上述 S 的所有执行中，P在S中总为 true，但 S 中存在转移 $s_1 \rightarrow s_2$，则 $P(s_1)\rightarrow P(s_2)$ 不成立，所以 P 不是 S 的不变式。