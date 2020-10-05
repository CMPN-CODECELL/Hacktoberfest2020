# Python Program to implement Bubble Sort

a = [] # Empty list initialization

n = int(input("Enter the number of elements: "))

print("Enter your numbers:")

for i in range(n):
    a.append(int(input()))

def bubbleSort(a):
    n = len(a)
    # Traverse through all the elements in the list
    for i in range(n):
        for j in range(0, n-i-1):
            if a[j] > a[j+1] :
                a[j], a[j+1] = a[j+1], a[j]

bubbleSort(a)

print ("Sorted array:")
for i in range(len(a)):
    print ("%d" %a[i])
