function [x_star, rosenbrock_eval, intermediate_sol] = NewtonMethod(x0, rrr, Param, rosenbrock_data)
%%%fprintf('*** Newton Method Function is Working ***\n');

%%% Param.NumIterBnd = 1000;         Number of iterations
%%% Param.GradNormRatio = 1e-7;      No idea
%%% Param.LineSearch.Tau = 0.95;     Tau value used in Line Search
%%% Param.LineSearch.C = 0.2;        C value used in Line Search 
%%% Param.LineSearch.InitAlpha = 1;  Alpha_Zero value in Line Search


x_star = x0;
rosenbrock_eval = zeros(Param.NumIterBnd,1);
intermediate_sol = zeros(2,Param.NumIterBnd);
%%%fprintf('Current solution is [%f,%f]\n',x_star(1),x_star(2));

t = 1;
sum=0
while t < (Param.NumIterBnd + 1)
    %%%fprintf('%fth iteration\n',t);
    [f_x, f_grad] = Rosenbrock(x_star);
    time=clock
    rosenbrock_eval(t) = f_x;
    intermediate_sol(1,t) = x_star(1);
    intermediate_sol(2,t) = x_star(2);
    alpha = LineSearch_N(Param.LineSearch, x_star);
    if f_x<0.01
        t
        break
    end
    det = (1200*x_star(1).^2-400*x_star(2))*202-400*400*x_star(1).^2;
    inverse_hessian = [202, 400*x_star(1); 400*x_star(1), 1200*x_star(1).^2-400*x_star(2)];
    inverse_hessian = (1/det)*inverse_hessian;
    
    x_star = x_star - alpha*inverse_hessian*f_grad;
    et=etime(clock,time)
    sum=sum+et
    t = t + 1;
end
sum/t
