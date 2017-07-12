# ------------------------------------------
#  module : DP_matching
#
#  author : Takashi Higasa
#  date   : 2017/07/12
#
#  1. You make directory testset and trainingset
#  2. data is set in testset and trainingset
#  3. data is 2 Column
#
# -----------------------------------------


import numpy as np
import sys
import math
import os

args = sys.argv

test_datas = []
traing_datas = []

path_test = []
path_traing = []
sys.stdout = open('result.txt', 'w')

path_test = "./testset/"
path_traing = "./trainingset/"
test_datas = sorted(os.listdir(path_test))
traing_datas = sorted(os.listdir(path_traing))

result1 = []
result2 = []
result3 = []

a=0

for test_i in range(len(test_datas)):
   mini_data1=99999
   mini_data2=99999
   mini_data3=99999
   for traing_i in range(len(traing_datas)):
      x1 = []
      y1 = []
      x2 = []
      y2 = []
      cw1 = [0, 0, 0]
      cw2 = [0, 0, 0]
      cw3 = [0, 0, 0]
      i=0
      j=0
      g1=0
      g2=0
      g3=0
      bg=0
      for l in open(path_test + test_datas[test_i]).readlines():
         data1 = l[:-1].split('\t')
         x1.append(float(data1[0]))
         y1.append(float(data1[1]))
   
      for l in open(path_traing + traing_datas[traing_i]).readlines():
         data2 = l[:-1].split('\t')
         x2.append(float(data2[0]))
         y2.append(float(data2[1]))

      gl1= [[0 for k in range(len(x2))] for l in range(len(x1))]
      gl2= [[0 for k in range(len(y2))] for l in range(len(y1))]
      gl3= [[0 for k in range(len(y2))] for l in range(len(y1))]
      
      for i in range(len(x1)):
         for j in range(len(x2)):
            if i == 0 and j == 0 :
               g1 = math.sqrt(pow(x1[i]-x2[j],2))
               g2 = math.sqrt(pow(y1[i]-y2[j],2))
               g3 = math.sqrt(pow(x1[i]-x2[j],2)+(pow(y1[i]-y2[j],2)))
               
            elif i==0 and j != 0:
               g1 = math.sqrt(pow(x1[i]-x2[j],2))+gl1[i][j-1]
               g2 = math.sqrt(pow(y1[i]-y2[j],2))+gl2[i][j-1]
               g3 = math.sqrt(pow(x1[i]-x2[j],2)+(pow(y1[i]-y2[j],2)))+gl3[i][j-1]
               
            elif i!=0 and j == 0:
               g1 = math.sqrt(pow(x1[i]-x2[j],2))+gl1[i-1][j]
               g2 = math.sqrt(pow(y1[i]-y2[j],2))+gl2[i-1][j]
               g3 = math.sqrt(pow(x1[i]-x2[j],2)+(pow(y1[i]-y2[j],2)))+gl3[i-1][j]
               
            else :
               cw1[0]=math.sqrt(pow(x1[i]-x2[j],2))+gl1[i-1][j]
               cw1[1]=math.sqrt(pow(x1[i]-x2[j],2))+gl1[i][j-1]
               cw1[2]=2*(math.sqrt(pow(x1[i]-x2[j],2)))+gl1[i-1][j-1]
               g1 = min(cw1[0], cw1[1], cw1[2])

               cw2[0]=math.sqrt(pow(y1[i]-y2[j],2))+gl2[i-1][j]
               cw2[1]=math.sqrt(pow(y1[i]-y2[j],2))+gl2[i][j-1]
               cw2[2]=2*(math.sqrt(pow(x1[i]-x2[j],2)))+gl2[i-1][j-1]
               g2 = min(cw2[0], cw2[1], cw2[2])

               cw3[0]=math.sqrt(pow(x1[i]-x2[j],2)+(pow(y1[i]-y2[j],2)))+gl3[i][j-1]
               cw3[1]=math.sqrt(pow(x1[i]-x2[j],2)+(pow(y1[i]-y2[j],2)))+gl3[i-1][j]
               cw3[2]=2*(math.sqrt(pow(x1[i]-x2[j],2)+(pow(y1[i]-y2[j],2))))+gl3[i-1][j-1]
               g3 = min(cw3[0], cw3[1], cw3[2])

               
            gl1[i][j]=g1
            gl1[i][j]-gl1[i-1][j]

            gl2[i][j]=g2
            gl2[i][j]-gl2[i-1][j]

            gl3[i][j]=g3
            gl3[i][j]-gl3[i-1][j]
            
            #print gl[i][j]
      #print(gl[len(x1)-1][len(x2)-1])
      
      tmp1 = gl1[len(x1)-1][len(x2)-1]
      tmp2 = gl2[len(y1)-1][len(y2)-1]
      tmp3 = gl3[len(y1)-1][len(y2)-1]
      
      if tmp1 < mini_data1:
         mini_data1 = tmp1
         mini_training1 = traing_datas[traing_i]
         
      if tmp2 < mini_data2:
         mini_data2 = tmp2
         mini_training2 = traing_datas[traing_i]
         
      if tmp3 < mini_data3:
         mini_data3 = tmp3
         mini_training3 = traing_datas[traing_i]
         
   result1.append(mini_training1)
   result2.append(mini_training2)
   result3.append(mini_training3)

   print(test_datas[test_i]+ " | "+ result1[test_i] +" , " + result2[test_i] + " , " + result3[test_i])

