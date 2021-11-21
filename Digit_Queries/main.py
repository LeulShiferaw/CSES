# find 21st digit = 1234567891011121314151 the answer is 1 the last digit
# Steps
# 1. remove everything before it that would be 123456789 so that you only have the group that contains the digit = 1011121314151
# 2. No remove evertyhing before then actual digits needed = 1
# 3. Just add on pow(10, d-1) the number of elements after the send step minus 1
# 4. from step 2 we have the digit we are looking for and from step 3 we have the actual number
# 5. Use the two to find the answer
import math

def reverse(n):
    res = 0
    while n != 0:
        res = res*10 + (n%10)
        n = n // 10
    return res

q = int(input(""))


for i in range(q):
    n = int(input(""))
    
    d = 1
    curr = 1
    while True:
        n -= d*curr*9
        
        if n < 0:
            n+=d*curr*9
            break
        
        d+=1
        curr *= 10
    
    x0 = n // d 
    n-=d*x0
    num = curr + x0 + (n!=0) -1

    if n == 0:
        print(num%10)
    else:
        num = reverse(num)
        for i in range(n-1):
            num = num // 10 
        print(num%10)