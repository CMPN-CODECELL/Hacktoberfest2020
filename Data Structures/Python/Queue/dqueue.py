# Python Program to demonstrate the FIFO principle using doeque

from collections import deque

q = deque() # Initializating Empty Queue

print(q) # Printing empty queue

# Adding items to the queue
q.append("Hey")
q.append("there!")
q.append("This")
q.append("is")
q.append("a")
q.append("Stack!")

print(q) # Printing queue with all elements

q.popleft() # Removing an element from the queue

print(q) # Printing queue after removing an element

q.append("What?!") # Adding another element to the queue

print(q) # Printing the new queue

# Removing all the elements from the queue
q.popleft()
q.popleft()
q.popleft()
q.popleft()
q.popleft()
q.popleft()

print(q) # Printing the empty queue
