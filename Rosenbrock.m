function [fEval,fGrad,fHess] = Rosenbrock(x)
%%%fprintf('*** Rosebrock Function is Working ***\n');
%%% this function receives a 2x1 vector x and returns 1) a scalar quantity
%%% fEval; 2x1 vector fGrad; 2x2 matrix fHess

[DimPt,~] = size(x);

if DimPt ~= 2
    disp('Input dim should be 2.');
end

fEval = 100*(x(2)-x(1).^2).^2+(1-x(2)).^2;

if nargout >=2
    %%% complete this part
    fGrad = [(400*x(1).^3) - 400*x(1)*x(2); 200*(x(2)-x(1).^2)+ 2*x(2) - 2];
    %%% complete this part
    if nargout >=3
        %%% complete this part
        fHess = [1200*x(1).^2-400*x(2), -400*x(1); -400*x(1), 202];
        %%% complete this part
    end
end
