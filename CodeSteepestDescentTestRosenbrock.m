%%% This code evaluates steepest descent method on Rosenbrock function.
%%% Please see Optimization Basics lecture slides for details.
%%% `RosenbrockGrid.mat' contains selected Rosenbrock function evaluations: used for visualization.
fprintf('*** Starting Steepest Descent Rosenbrock ***\n');
clear;
close all;

Param.NumIterBnd = 1000;
Param.GradNormRatio = 1e-7;
Param.LineSearch.Tau = 0.8;
Param.LineSearch.C = 0.2;
Param.LineSearch.InitAlpha = 100;

InitX = [1.8;1.8];

%%% loads pre-calcualted Rosenbrock function evaluations
load RosenbrockGrid.mat RosenbrockData;

%%% evaluate Rosenbrock at the initial search point InitX
[fInitX,fInitXGrad,fInitXHess] = Rosenbrock(InitX);

%%% minimize Rosenbrock using steepest descent
[OptX,EvalPlot,IntX] = SteepestDescent(InitX,'Rosenbrock',Param);
[fOptX,fOptXGrad] = Rosenbrock(OptX);


%%% visualize Rosenbrock function values and intermediate solutions along the optimization trajectory
figure(1);
subplot(1,2,1);
plot([1:Param.NumIterBnd],EvalPlot(1:Param.NumIterBnd));
xlabel('Iter num');
ylabel('f(x)');

subplot(1,2,2);
DOffset = 1000;
surf(RosenbrockData.Grid,RosenbrockData.Grid,RosenbrockData.RBOutMat,'EdgeColor','none');
hold on;
for i=1:Param.NumIterBnd
    plot3(IntX(2,i),IntX(1,i),DOffset,'.r','MarkerSize',20);
end
plot3(InitX(2),InitX(1),DOffset,'.y','MarkerSize',20);
plot3(OptX(2),OptX(1),DOffset,'.g','MarkerSize',20);
view(2);
hold off;

disp('done.');