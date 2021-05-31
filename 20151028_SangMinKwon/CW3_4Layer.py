#!/usr/bin/env python
# coding: utf-8

# In[19]:


import pandas as pd
import numpy as np
import matplotlib.pylab as plt

def sigmoid(x):
    return 1 / (1 + np.exp(-x))
def difsigmoid(x):
    return sigmoid(x)*(1-sigmoid(x))
def MSE(X1,W1,W2,W3,W4):
    Error=0
    for i in range(len(X1)):
        X=np.array(X1[i])
        z1=(W1.dot(X.T))
        o1=sigmoid(z1)
        z2=W2.dot(o1.T)
        o2=sigmoid(z2)
        z3=W3.dot(o2.T)
        o3=sigmoid(z3)
        
        z4=W4.dot(o3.T)
        o4=sigmoid(z4)
        #MSE
        Error+=pow(out[i]-o4,2)/2
    return Error
Header= ["in1","in2","out"]
dat=pd.read_table('Trn.txt',sep=' ',header=None,names=Header)
Train=dat[["in1","in2"]]
out=dat["out"]
Blue=dat[dat['out']==1]
Red=dat[dat['out']==0]
plt.xlim(-15,15)
plt.ylim(-15,15)
plt.plot(Red[["in1"]],Red[["in2"]],color='red')
plt.plot(Blue[["in1"]],Blue[["in2"]],color='blue')


# In[94]:


LearningRate=0.1
W1=np.random.randn(128,2)# out, in
W2=np.random.randn(128,128)
W3=np.random.randn(16,128)
W4=np.random.randn(1,16)
TrainArray=np.array(Train)
tole=0.001
index=0
minerror=1000000
RW1=[]
RW2=[]
RW3=[]
RW4=[]
initError=0

while index<=100000:
    initError=0
    
    index=index+1
    
    i=np.random.randint(0,len(TrainArray))
        #feed Forward
        
    X=np.array(TrainArray[i])
    z1=(W1.dot(X.T))
    o1=sigmoid(z1)
    z2=W2.dot(o1.T)
    o2=sigmoid(z2)
    z3=W3.dot(o2.T)
    o3=sigmoid(z3)
    z4=W4.dot(o3.T)
    o4=sigmoid(z4)
        #MSE
    e=(o4-out[i])#d
    P4=(out[i]-o4)*(o4*(1-o4)) # 항상 동일
    W4=W4+LearningRate*P4*o3
    P3=P4.dot(W4)*o3*(1-o3)
    for j in range(len(P3)):
        for k in range(len(o2)):
            W3[j][k]+=LearningRate*P3[j]*o2[k]
    tp=np.zeros((1,len(P3)))
    tp+=P3
    P2=tp.dot(W3)*o2*(1-o2)
    
    for j in range(len(P2)):
        for k in range(len(o1)):
            W2[j][k]+=LearningRate*P2[0][j]*o1[k]
    P1=P2.dot(W2)*o1*(1-o1)
    for j in range(len(P1)):
        for k in range(len(X)):
            W1[j][k]+=LearningRate*P1[0][j]*X[k]
    
RW1=W1
RW2=W2
RW3=W3
RW4=W4
# Perceptron => ActivationFunction(Wx+B)=OutPut => Backpropagation minimize E[OutPut-RealValue]


#출력은 0 or 1이니까 출력층은 1개의 노드면 충분하다.
#히든 레이어는 최소 2개의 출력값을 가져야 하므로 최소 2개 이상의 노드로 구성되어야한다.


# In[95]:



Header= ["in1","in2"]
Testdat=pd.read_table('Tst.txt',sep=' ',header=None,names=Header)
Test=Testdat[["in1","in2"]]
TestArray=np.array(Test)
Answer=[]
for i in range(0,len(TestArray)):
    
    X=np.array(TestArray[i])
    z1=(RW1.dot(X.T))
    o1=sigmoid(z1)
    z2=RW2.dot(o1.T)
    o2=sigmoid(z2)
    z3=RW3.dot(o2.T)
    o3=sigmoid(z3)
    z4=RW4.dot(o3.T)
    o4=sigmoid(z4)
    Answer.append(o4)

OUTPUT=pd.DataFrame(Answer)
OUTPUT=OUTPUT.rename({0:'out'},axis='columns')
result=pd.concat([Test,OUTPUT],axis=1)
Blue=result[result['out']>=0.5]
Red=result[result['out']<0.5]  
plt.xlim(-15,15)
plt.ylim(-15,15)
plt.plot(Red[["in1"]],Red[["in2"]],color='yellow')
plt.plot(Blue[["in1"]],Blue[["in2"]],color='darkblue')
Train=dat[["in1","in2"]]
out=dat["out"]
Blue=dat[dat['out']==1]
Red=dat[dat['out']==0]
plt.plot(Red[["in1"]],Red[["in2"]],color='red')
plt.plot(Blue[["in1"]],Blue[["in2"]],color='blue')


# In[96]:


Error=MSE(TrainArray,RW1,RW2,RW3,RW4)
Error


# In[ ]:




