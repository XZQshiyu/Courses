## HW1 

### Q1.

#### 1.

正确
$$
由f_i(n) = O(g(n)), 得\exists c>0, n_i > 0\\
当 n\geq n_i时，0 \leq f_i(n) \leq cg(n) \\
对 \forall i 均成立 \\
取 n_0 = max\{n_1,n_2,\cdots ,n_m\}\\
n \geq n_0 时，F_m(n) = \sum_{i=1}^{m} f_i(n) \leq cmg(n)\\
即 \exists C = cm, n_0 = max\{n_1, n_2,...,n_m\}使之成立，故正确
$$

#### 2.

错误
$$
f_i(n) = n,g(n) = n\log n\\
但F(n) = n^2 显然不满足题意
$$

#### 3.

正确
$$
对f_1(n) = n, g(n) = n^2\\
1与2之间存在无穷个实数a_1 <a_2<...<a_n<...<2\\
使f_i = n^{a_i} = o(n^{a_{i+1}})\\
$$

#### 4.

正确
$$
由题，\exists c与n_0使对 \forall n \geq n_0,有f(n)+g(n) \geq c h(n)\\
假设f(n) \notin \Omega(h(n))\\
那么对于\forall给定从c和n_0,存在一个足够大的n \geq n_0\\
使 f(n) < ch(n) f(n) + g(n) < ch(n) + g(n)\\
若f(n) + g(n) = \Omega(h(n)) 则只要f(n)\leq ch(n),f(n)+g(n)>ch(n)矛盾\\
所以，f(n)和g(n)中至少有一个属于 \Omega(f(n))
$$

#### 5.

错误
$$
构造反例:\\
f(n) = \begin{cases}
n^{\alpha} & n为奇数\\
n^{\beta} & n为偶数\\
\end{cases}\\
有f(n) = \Omega(n^{\alpha}),f(n) = O(n^{\beta})\\
但 f(n+1) = \Theta(f(n)),n为奇数时，有\\
c_1n^\alpha \leq (n+1)^\beta \leq c_2n^\alpha\\
则 c_1 \leq (\frac{(n+1)^\beta}{n^\alpha})\leq c_2\\
中间关于n的数列显然是发散的，故假设不成立\\
$$


### Q2.

#### （1）

$$
归纳假设， 对\forall n \\
当 m = 0 时， A(0, n) = n + 1显然终止\\
A(1,0) = A(0,1) = 2\\
m = 1时， A(1, n) = A(0, n+1) = n+2 显然终止\\
故对\forall n \in N, 有A(1,n) 可以终止 \\
假设m = k 时，对 \forall n, A(k, n)可以终止\\
则 m = k+1时，有\\
A(k+1,n) = A(k, A(k+1, n-1)) = A(k, A(k,A(k+1,n-2)))= \cdots\\
最终会到达A(k+1, 0) = A(k, 1)会终止，所以上述所有项都是有限的\\
所以A(k+1, n)也会终止\\
由归纳证明，A(m,n)的递归总能终止\\
$$



#### （2）

$$
对\forall n \in N, A(0,n) = n+1\\
当n_1 > n_2， A(0,n_1) = n_1 + 1 > n_2 + 1 = A(0,n_2)，对n显然单增\\
m = 1时，对\forall n, A(1,n_1) = A(0, n_1 + 1) = n_1 + 2 > n_2 + 2 =A(1, n_2) ，显然也是单增的\\
在m固定时,A(m,n)关于n单增是显然的，下证在n固定时对m单增\\
满足归纳假设的前提，我们假设\\
m = k时，对\forall n, A(k,n) > A(1,n) = n+2\\
有A(k,n) > n + 2,可以视n为一个变量\\
m = k+1时，A(k+1, n) = A(k, A(k+1, n-1)) >A(k+1, n-1) + 2 > \cdots\\
有 A(k+1, n) > A(k+1,0) +2n > n+2\\
可以先得到所有的A(m,n) > n+2\\
A(k+1, n) = A(k,A(k+1,n-1)),由A(k+1,n-1) > n-1 + 2 = n+1 及对n的单调性\\
有A(k+1,n) > A(k, n)，满足归纳假设条件\\
故A(m,n)对m也是单增的
$$



#### （3）

$$
不妨假设\alpha(x) = O(1),则存在正的常数c，s.t. \alpha(x) \leq c\\
A(n,n) \leq A(c,c)\\
取x = A(c+1,c+1)，\alpha(x) = c+1,与\alpha(x)\leq c矛盾\\
故\alpha(x)不能为O(1)，也即只能有一个下界\\
即 \alpha(x) = \omega(1)\\
要证明 \alpha(x) = O(lg^*x)，需要证明存在常数 c 和 n_0，使得对于所有的 x ≥ n_0，有 \alpha(x) ≤ c\cdot lg^*x\\

 A(n,n) 的值随 n 的增加而单调递增。因此，当 n > lg^*x 时，A(n,n) 必然大于 x\\
考虑 n_0 = lg^*x，对于x ≥ n_0，我们有：\\
A(\alpha(x),\alpha(x)) ≤ x\\
由于 A(\alpha(x),\alpha(x)) ≤ x，根据题目中定义的 \alpha(x)，我们知道 \alpha(x) 是使得 A(n,n) ≤ x 的最大自然数 n\\
因此，\alpha(x) ≤ \alpha(x)。这说明 \alpha(x) 是一个上界\\
实际在计算A(n,n)中，会迭代出A(m,n)项\\
下证A(m,n)与多重对数中x的增长速率关系，来证明A(n,n)的增长速率渐进小于lg^*x\\
m = k时， A(k,n) = n + 2 此时\alpha(x) = A(n,n)\leq x 中的n, 要 <lg^*x\\
在m = k + 1时，A(k+1,n) = A(k, A(k+1, n-1)) < 2^{A(k+1,n-1)} < x\\
因此有 \alpha(x) = (A(n,n) \leq x)中的n的增长速率慢于 lg^*x
$$



### Q3.

#### （1）

##### 1.

$$
f(n) = n^2 > n^{\log_2 3}\\
T(n) = \Theta(n^2)
$$

##### 2.

$$
f(n) = n^2, n^{\log_2 4} = n^2\\
T(n) = \Theta(n^2\lg n)
$$

##### 3.

$$
n^{log_21} = n^0 = 1,f(n) = \Omega(1),f(\frac{n}{2}) = 2^n < f(n) = 2^n\\
T(n) = \Theta(2^n)
$$

##### 4.

$$
T(n) = \Theta(n^nlgn)
$$

##### 5.

$$
T(n) = \Theta(n^2)
$$

##### 6.

$$
n^{log_2 2} = n,f(n) = nlgn \Theta(nlgn)\\ 
T(n) = \Theta(nlg^2n) 
$$

##### 7.

$$
f(n) = \frac{n}{\lg n}\\
无法使用主定理得到渐进阶，原因同3
$$

##### 8.

$$
T(n) = \Theta(n^{0.51})
$$

##### 9.

$$
T(n) = \Theta(n^{-1}lgn)
$$

##### 10.

$$
f(n) = n!，n^{log_4 16} = n^2,f(n) = \Omega(n^{2+\epsilon})\\
T(n) = \Theta(n!)
$$

##### 11.

$$
n^{log_2 \sqrt{2}} = n^{\frac{1}{2}} ,f(n) = O(n^{\frac{1}{2}-\epsilon})\\
T(n) = \Theta(n^{\frac{1}{2}})
$$



##### 12.

$$
T(n) = \Theta(n^{\log_2 3})
$$

##### 13.

$$
T(n) = \Theta(n)
$$

##### 14.

$$
T(n) = \Theta(n^2)
$$

##### 15.

$$
f(n) = \Omega(n^{log_4 3 +\epsilon})\\
T(n) = \Theta(nlgn)
$$

##### 16.

$$
T(n) = \Theta(nlgn)
$$

##### 17.

$$
f(n) = \Omega(n^{log_3 6 + \epsilon}),6f(\frac{n}{3}) = \frac{2}{3}*n^2(lgn - lg4) < n^2lgn\\
T(n) = \Theta(n^2lgn)
$$

##### 18.
$$
f(n) = \frac{n}{lgn}, n^{log_2 4} = n^2\\
T(n) = \Theta(n^2)
$$

##### 19.

$$
由于f(n)不是渐进正函数，所以不能使用主定理
$$

##### 20.

$$
T(n) = \Theta(n^2)
$$

##### 21.

$$
n^{log_2 4} = n^2, f(n) = O(n^{2-\epsilon})\\
T(n) = \Theta(n^2)
$$

##### 22.

$$
n^{log_2 1} = n^0 = 1, f(n) = \Omega(n^{0+\epsilon})\\
f(\frac{n}{2}) = \frac{n}{2} (2-cos\frac{n}{2}) < n(2-cosn)\\
T(n) = n(2-cosn)\\
$$

##### 23.

$$
不存在\epsilon使得f(n)= \Omega(n^{1+\epsilon})，故不能使用主定理
$$

##### 24.

$$
n^{\log_2 2} = n,不存在\epsilon，使得f(n) = \Omega(n^{1+\epsilon})\\
故不能使用主定理
$$

##### 25.

$$
n^{log_2 2} = n，且不存在\epsilon 使得f(n) = \Omega(n^{1+\epsilon})或f(n) = O(n^{1-\epsilon})，所以不能使用主定理
$$

#### （2）

##### 7.

$$
e_0 = 1, e_1 = -1\\
\vec{e}=(1,-1),\alpha = 1,cpow(e) = 0, cord(e) = 2\\
T(n) = \Theta(nlglgn)
$$

##### 23.

$$
\alpha = log_2 2 = 1\\
e_0 = 1, e_1 = 1, e_2 = 1\\
\vec{e} = (1,1,1), m = 2\\
e_0 = 1 = \alpha, cpow(e) = e_1 =1 > -1\\
T(n) = \Theta(n(lgn)^2 lglgn)
$$

##### 24.

$$
\vec{e} = (1,0,r), m = 2, e_0 = 1 = \alpha = log_2 2 = 1\\
e_0 = 1 = \alpha
T(n) = \Theta(nlgn(lglgn)^r)
$$

##### 25.

$$
\vec{e} = (1,-1,-1,s), \alpha = 1\\
当s = -1, cpow(e) = 0 > -1, cord(e) = 4, T(n) =\Theta(nlg^{(4)}n)\\
当s > -1, cpow(e) = s > -1, cord(e) = 3, T(n) = \Theta(n(lg^{(3)}n)^{s+1})\\
当s \leq -1，T(n) = \Theta(n^\alpha)
$$

### Q4.

#### (1)

算法1：
$$
输入n和f \in F_n'\\
计算m = [\frac{n}{f}]\\
则a = (m-1)\cdot f + 1\\
b = mf\\
输出<a,b>
$$
算法2:
$$
输入n和<a,b> \in S_n\\
f = \frac{b-a+1}{b+a}，输出f\\
$$
算法1和算法2可以构成双射，代入验证

#### (2)

正确性证明：
$$
由素数及唯一分解定理\\
n = 2^{k_0}p_1^{k_1}...p_n^{k_n}\\
奇因子q = n = p_1^{r_1}p_2^{r_2}...p_n^{r_n}, 0\leq r_i \leq k_i\\
r_i取值跑遍0到k_i共k_i+1种，S\times (k_i+1)\\
循环结束后,如果n\neq 1,则n为素数，\times 2
则此时结果即为|S_n|
$$

$$
m-1 \leq \lg n < m ,2^{m-1} \leq n < 2^m\\
当n为素数时，p^2 = n终止循环，由时间复杂度\Theta(2^{\frac{m}{2}})\\
由Bertrand公设，2^{m-1}与2^{m}之间存在素数p\\
故n = p时，取最坏情况
$$


#### (3)

##### （3.1）

不能断言这一算法的最坏时间复杂度是 $\Omega(2^{\alpha m})$

无法确定下界，上界为 $O(2^{\beta m})$

同样不能断言这一算法的平均时间负责度是 $\Theta(2^{\beta m})$

##### (3.2)

不会

