# Python Program to demonstrate the LIFO principle using stack

stack = [] # Initializating Empty Stack

print(stack) # Printing empty Stack

# Adding items to the Stack
stack.append("Hey")
stack.append("there!")
stack.append("This")
stack.append("is")
stack.append("a")
stack.append("Stack!")

print(stack) # Printing stack after adding items

stack.pop() # Removing an item from the Stack

print(stack) # Printing stack after removing an item

stack.append("Retry!") # Re-adding an item to the Stack

print(stack) # Printing the new Stack

# Removing all the items from the Stack
stack.pop()
stack.pop()
stack.pop()
stack.pop()
stack.pop()
stack.pop()

print(stack) # Printing empty Stack
