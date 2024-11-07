## Lecture 2

### Asymptotic Notation（渐进符号）

#### $O-notation$: upper bounds

##### def

![image-20230912142657468](./assets/image-20230912142657468.png)

找到一个函数g（n）能盖住f（n），图像上显示为，超过某一点后一直在f（x）上方

Example: 

$2n^2 = O(n^3) ~(c=1,n_0 = 2)$

![image-20230912143054798](./assets/image-20230912143054798.png)

#### $\Omega-notation$

##### def

![image-20230912143309172](./assets/image-20230912143309172.png)

找到一个函数g(n)，使得超过n0后，f(n)一直在g(n)图像之上，这样保证了一个f(n)的下界（不严格的）

Example: $\sqrt{n} = \Omega(lgn)$

#### $\Theta-notation$

![image-20230912143506390](./assets/image-20230912143506390.png)

找到一个函数g(n)使得f(n)的函数数量级和f(n)是一样的，只是有常数倍的区别

Example：

 $\frac{1}{2}n^2-2n = \Theta(n^2)$

#### theorem:

the leading constant and low order terms do not matter.

![image-20230912143624043](./assets/image-20230912143624043.png)

#### other asymptotic notations

##### $o-notation$ 

严格上界

![image-20230912211345864](./assets/image-20230912211345864.png)

$\omega-notation$

严格下界

![image-20230912211411817](./assets/image-20230912211411817.png)

#### A helpful analogy

![image-20230912143941281](./assets/image-20230912143941281.png)

##### Transitivity

渐进符号具有传递性

![image-20230912144120805](./assets/image-20230912144120805.png)

##### Reflexivity

渐进符号具有自反性

![image-20230912211556429](./assets/image-20230912211556429.png)

##### Symmetry & Transpose Symmetry

![image-20230912211912400](./assets/image-20230912211912400.png)

#### Non-completeness

也就是说，a和b的函数关系并不是只有三种，存在震荡的情况。

![image-20230912144226330](./assets/image-20230912144226330.png)

### Standard Notations and Common Functions

#### Floors and Ceilings

![image-20230912144424606](./assets/image-20230912144424606.png)

#### Modular Arithmetic

![image-20230912144512695](./assets/image-20230912144512695.png)

#### Exponentials

![image-20230912144537051](./assets/image-20230912144537051.png)

#### Logarithms

![image-20230912144624514](./assets/image-20230912144624514.png)

#### Factorials

![image-20230912145031715](./assets/image-20230912145031715.png)

#### Functional iteration

![image-20230912215433047](./assets/image-20230912215433047.png)

Example：$ if f(n) = 2n, then f^{(i)}(n) = 2^in$

the iterated logarithm function

![image-20230912215551105](./assets/image-20230912215551105.png)

#### Fibonacci Numbers

![image-20230912215612713](./assets/image-20230912215612713.png)

### Recurrences

to solve recurrences

![image-20230912215651848](./assets/image-20230912215651848.png)

核心来讲，就是一个公式 $ T(n) = a\times T(\frac{n}{b})+f(n)$

#### Substituion Method

![image-20230912215759343](./assets/image-20230912215759343.png)

- 只适用于猜答案
- 只有在确定上下界的时候发挥作用

![image-20230912220128201](./assets/image-20230912220128201.png)

![image-20230912220409517](./assets/image-20230912220409517.png)

![image-20230912220446541](./assets/image-20230912220446541.png)

#### Recursion-tree Method

![image-20230912220623799](./assets/image-20230912220623799.png)

#### The Master Method

![image-20230912220842922](./assets/image-20230912220842922.png)

compare f(n) with $n^{log_b^a}$

![image-20230912220958014](./assets/image-20230912220958014.png)

![image-20230912221022161](./assets/image-20230912221022161.png)

![image-20230912221048537](./assets/image-20230912221048537.png)

![image-20230912221238661](./assets/image-20230912221238661.png)

![image-20230912221244157](./assets/image-20230912221244157.png)

![image-20230912221310129](./assets/image-20230912221310129.png)