## Asymptotic Mark and Recursive Equation

### 1.1 渐进标记（Asymptotic Notation）

#### O-notation(upper bounds)


$$
We~write~f(n) = O(g(n))~if~there~exist~constants~c>0,n_0>0~\\
such~that~0 \leq f(n) \leq cg(n)~for~all~n > n_0
$$

- O(g(n))是一个f(n)的不严格上界
- 需要找到一个$c$和一个$n_0$

#### $\Omega-$notation(lower bounds)

$$
\Omega(g(n))=\{f(n):there ~exist ~constants~c>0,n_>0~such~that\\
0 \leq c\cdot g(n) \leq f(n)~ for ~all~n>n_0\}
$$

- $\Omega(g(n))$是一个不严格下界
- 同样需要找到一个c和一个$n_0$
- 例如：$\sqrt{n} = \Omega(lg~n)$

#### $\Theta$-notation(tight bounds)

$$
We~write~f(n)=\Theta(g(n)) ~if ~there ~exist~constants~c_1>0,c_2>0,n_0>0\\
such~that c_2g(n) \geq f(n) \geq c_1g(n) \geq 0~for~all~n>n_0
$$

$\Theta(g(n)) = O(g(n)) \cap \Omega(g(n))$

- 一个很好的界，把f(n)完全限制在了中间
- 需要$c_2,c_1$,n

![image-20231025001607575](./assets/image-20231025001607575.png)

#### Other Asymptotic Notations

![image-20231025001832164](./assets/image-20231025001832164.png)

#### A helpful Analogy

![image-20231025001853716](./assets/image-20231025001853716.png)

##### 传递性（Transitivity）

![image-20231025001924636](./assets/image-20231025001924636.png)

##### 自反性（Reflexivity）

![image-20231025001951621](./assets/image-20231025001951621.png)

##### Transpose Symmerty & Symmetry

![image-20231025002230999](./assets/image-20231025002230999.png)

##### Non-completeness

![image-20231025003011943](./assets/image-20231025003011943.png)

### 1.2 Standard Notations and Common Functions

#### Floors and Ceilings

![image-20231025004816989](./assets/image-20231025004816989.png)

![image-20231025005722262](./assets/image-20231025005722262.png)

![image-20231025011524626](./assets/image-20231025011524626.png)

斯特林近似公式

$n! = \sqrt{2\pi n}(\frac{n}{e})^n(1+\Theta(\frac{1}{n}))$

#### functional iteration

![image-20231025011909820](./assets/image-20231025011909820.png)

![image-20231025012020156](./assets/image-20231025012020156.png)

### 1.3 Recurrences

- substitution method: guess a bound and use mathemtical induction to prove the guess correct

- recursion-tree method: converts the recurrence into a tree and use techniques for bounding summations

- master method: provides bounds of the form

  $T(n) = a \cdot T(\frac{n}{b}) + f(n)$

#### 1.3.1 Substitution Method

![image-20231025092741120](./assets/image-20231025092741120.png)

example:

![image-20231025093214051](./assets/image-20231025093214051.png)

![image-20231025093221233](./assets/image-20231025093221233.png)

#### 1.3.2 Recursion-tree Method

A recursion-tree method can be unreliable.

The recursion tree method is good for genrating guesses for the substitution method.

example:

![image-20231025094313434](./assets/image-20231025094313434.png)

#### 1.3.3 The Master Method

![image-20231025094748245](./assets/image-20231025094748245.png)

##### three common cases

![image-20231025094844450](./assets/image-20231025094844450.png)

![image-20231025095005073](./assets/image-20231025095005073.png)

>In particular, for every constan $\epsilon > 0$ ，we have $n^{\epsilon} = \omega(lg n)$

注意：

- $a \geq 1, b > 1$

- 注意是否能比较

- a和b需要是常数

- 必须满足f(n)渐进为正

- ![image-20231025101808559](./assets/image-20231025101808559.png)

  一个特殊的例子

- ![image-20231025102140442](./assets/image-20231025102140442.png)

  ![image-20231025102149150](./assets/image-20231025102149150.png)





#### 主定理习题：

