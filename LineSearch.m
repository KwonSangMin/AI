function [Alpha] = LineSearch(arguments, x_input)
%%%fprintf('*** Line Search Function is Working ***\n');

%%% Param.LineSearch.Tau = 0.95;     Tau value used in Line Search
%%% Param.LineSearch.C = 0.2;        C value used in Line Search 
%%% Param.LineSearch.InitAlpha = 1;  Alpha_Zero value in Line Search
Tau = arguments.Tau
C = arguments.C
Alpha = arguments.InitAlpha

[f,f_gradient] = Rosenbrock(x_input)
[f_l, aa] = Rosenbrock(x_input - Alpha*f_gradient);
f_r = f - C*Alpha*transpose(f_gradient)*f_gradient;
check = f_l - f_r;

while check > 0
    Alpha = Tau * Alpha;
    
    [f_l, aa] = Rosenbrock(x_input - Alpha*f_gradient);
    f_r = f - C*Alpha*transpose(f_gradient)*f_gradient;
    check = f_l - f_r;
end
