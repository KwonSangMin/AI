function [x_star, rosenbrock_eval, intermediate_sol] = SteepestDescent(x0, rrr, Param)
%%%fprintf('*** Steepest Descent Function is Working ***\n');

%%% Param.NumIterBnd = 1000;         Number of iterations
%%% Param.GradNormRatio = 1e-7;      No idea
%%% Param.LineSearch.Tau = 0.95;     Tau value used in Line Search
%%% Param.LineSearch.C = 0.2;        C value used in Line Search 
%%% Param.LineSearch.InitAlpha = 1;  Alpha_Zero value in Line Search


x_star = x0;
rosenbrock_eval = zeros(Param.NumIterBnd,1);
intermediate_sol = zeros(2,Param.NumIterBnd);

%%%fprintf('The first soltion is [%f,%f]\n',x_star(1),x_star(2));

min = [1.0;1.0];


t = 1;

while t < (Param.NumIterBnd + 1)
    %%%fprintf('%fth iteration\n',t);
    alpha = LineSearch(Param.LineSearch, x_star);
    %%%fprintf('Current Alpha is: %f\n',alpha);
    [f_x, f_grad] = Rosenbrock(x_star);
    if f_x<0.01
        t
        break
    end
    rosenbrock_eval(t) = f_x;
    intermediate_sol(1,t) = x_star(1);
    intermediate_sol(2,t) = x_star(2);
    
    x_star = x_star - alpha*f_grad;
    t = t + 1;
end

