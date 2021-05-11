# Optimization Algorithms

## Descriptions
This is the Matlab implementation of **Steepest Descent** and **Newton Method** Optimization Algorithms.
It is a CourseWork3 of CSE46301: Machine Learning, Fall 2019.
As an example of loss function, we have used Rosenbrock function.
Evaluation of the Rosenbrock Function, it's Gradient and it's Hessian at a specific point is implemented in [Rosenbrock](https://github.com/kanybekasanbekov/Optimization-Algorithms/blob/master/Rosenbrock.m). 
The initial search point **x** is **[2.0,2.0]**. The Global Minimum of Rosenbrock function is **x** = **[1.0,1.0]**.
<p align="center">
    <img src="./asset/rosenbrock.png" width="400"/>
</p>

## Steepest Descent
*Steepest Descent* is an Iterative Descent Algorithm, used to find Global Minimum of a twice differentiable convex function *f(x)*. It descents in the direction of the largest directional derivative. That's a *Gradient of Rosenbrock function* in this case.
* The *Stopping Condition* is the fixed number of iterations, 1000 iterations in this case.
* The *Step Size* is calculated by using [LineSearch](https://github.com/kanybekasanbekov/Optimization-Algorithms/blob/master/LineSearch.m) algorithm.  

After 1000 iterations, *Steepest Descent* reaches **[1.78,1.334]**.
However *Steepest Descent* converges to **[1.0,1.0]** approximately in 10000 iterations.
In the image below you can see intermediate values obtained by *Steepest Descent*.
Thus, *Steepest Descent* requires a lot of steps to converge and moves forward to Global Minimum just for a little at each step.
To test "Steepest Descent" run [CodeSteepestDescentTestRosenbrock](https://github.com/kanybekasanbekov/Optimization-Algorithms/blob/master/CodeNewtonMethodTestRosenbrock.m) which calls [SteepestDescent](https://github.com/kanybekasanbekov/Optimization-Algorithms/blob/master/SteepestDescent.m) function.
<p align="center">
    <img src="./asset/steepest.png" width="800"/>
</p>  

* *Yellow point* stands for initial value of **x**
* *Red point* stands for intermediate value of **x**
* *Green point* stands for final value of **x**

## Newton Method
*Newton Method* is an Iterative Method for finding Global Minimum of a twice differentiable convex function *f(x)*.
At each iteration it approximates *f(x)* using Second Order Taylor Series approximation *m(x)*.
Then it sets derivative of *m(x)* to 0, thus we obtain new value for **x**  
* The *Stopping Condition* is the fixed number of iterations, 1000 iterations in this example.  

*Newton Method* in this example converges in 3 iterations.
In the image below you can see intermediate values obtained by *Newton Method*.
Thus, *Newton Method* requires just a few steps to converge.
To test "Newton Method" run [CodeNewtonMethodTestRosenbrock](https://github.com/kanybekasanbekov/Optimization-Algorithms/blob/master/CodeNewtonMethodTestRosenbrock.m) which calls [NewtonMethod](https://github.com/kanybekasanbekov/Optimization-Algorithms/blob/master/NewtonMethod.m) function.
<p align="center">
    <img src="./asset/newton.png" width="800"/>
</p>  

* *Yellow point* stands for initial value of **x**
* *Red point* stands for intermediate value of **x**
* *Green point* stands for final value of **x**
