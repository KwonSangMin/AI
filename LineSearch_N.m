function [Alpha] = LineSearch_N(arguments, x_input)
%%%fprintf('*** Line Search Function is Working ***\n');

%%% Param.LineSearch.Tau = 0.95;     Tau value used in Line Search
%%% Param.LineSearch.C = 0.2;        C value used in Line Search 
%%% Param.LineSearch.InitAlpha = 1;  Alpha_Zero value in Line Search
Tau = arguments.Tau;
C = arguments.C;
Alpha = arguments.InitAlpha;
x_star=x_input;
det = (1200*x_star(1).^2-400*x_star(2))*202-400*400*x_star(1).^2;
inverse_hessian = [202, 400*x_star(1); 400*x_star(1), 1200*x_star(1).^2-400*x_star(2)];
inverse_hessian = (1/det)*inverse_hessian;
[f,f_gradient,fHess] = Rosenbrock(x_input);
[f_l, aa] = Rosenbrock(x_input - Alpha*inverse_hessian*f_gradient);
f_r = f - C*Alpha*transpose(f_gradient)*inverse_hessian*f_gradient;
check = f_l - f_r;

while check > 0
    Alpha = Tau * Alpha;
    
    [f_l, aa] = Rosenbrock(x_input - Alpha*inverse_hessian*f_gradient);
    f_r = f - C*Alpha*transpose(f_gradient)*inverse_hessian*f_gradient;
    check = f_l - f_r;
end