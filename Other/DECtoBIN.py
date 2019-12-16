# -*- coding: utf-8 -*-
"""
Created on Sat Jun  8 18:29:30 2019

@author: vaibhav
"""

z=[]
def store(x=0):
    
    z.append(x)
    

def decimalToBinary(number):
    if number > 1:

         decimalToBinary(number // 2)

    store(number % 2)
    print(number % 2)
 
number = int(input("Enter the decimal number you want to convert in binary: "))

decimalToBinary(number)
print("LENTH IS :" , len(z) )
j=0
for i in range(0,8-len(z)):
      z.insert(0,0)
      j=j+1
print("LENTH IS :" , len(z) )



