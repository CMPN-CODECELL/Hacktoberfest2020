# Python Program to demonstrate the FIFO principle using doeque

from collections import deque

print("Queues utilize the FIFO (First In First Out) Principle")
print()

q = deque() # Initializating Empty Queue

print("Initial empty queue :", q) # Printing empty queue

# Adding items to the queue
q.append("Hey")
q.append("there!")
q.append("This")
q.append("is")
q.append("a")
q.append("Queue!")

print("After adding items into the queue:", q) # Printing queue with all elements

q.popleft() # Removing an element from the queue

print("After removing an item from the queue:", q)# Printing queue after removing an element

q.append("What?!") # Adding another element to the queue

print("After adding an extra item to the queue:", q) # Printing the new queue

# Removing all the elements from the queue
q.popleft()
q.popleft()
q.popleft()
q.popleft()
q.popleft()
q.popleft()

print("After removing all the items:", q) # Printing the empty queue

print("Trying to remove any more items will result in an error!")
