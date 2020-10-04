# Program to display the Fibonacci Series upto 'n'

n = int(input("Enter the value of n: ")) # Accepting value of 'n'

n1, n2 = 0, 1 # First two terms of the series
c = 0 # Counter variable

if n <= 0 :
    print("Invalid! Enter a positive number")
elif n == 1 :
    print("Fibonacci series upto",n,":",n1)
else :
    print("Fibonacci series :")
    while c < n :
        print(n1)
        n_sum = n1 + n2 # Temporary variable to store the sum of n1, n2
        n1 = n2
        n2 = n_sum
        c += 1
