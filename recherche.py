import os

tab = "/Users/yboughan/.brew/bin:/Users/yboughan/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki".split(':')
rech = "wc"


for i in tab:
    arr = os.listdir(i)
    if(rech in arr):
        print(i)