# Python Program to demonstrate the LIFO principle using stack

print("Stack utilizes the LIFO (Last In First Out) Principle")
print()

stack = [] # Initializating Empty Stack

print("Initializing empty stack :", stack) # Printing empty Stack

# Adding items to the Stack
stack.append("Hey")
stack.append("there!")
stack.append("This")
stack.append("is")
stack.append("a")
stack.append("Stack!")

print("After adding items into the stack:", stack) # Printing stack after adding items

stack.pop() # Removing an item from the Stack

print("After removing only one item from the stack:", stack) # Printing stack after removing an item

stack.append("Retry!") # Re-adding an item to the Stack

print("After re-adding an item to the stack:", stack) # Printing the new Stack

# Removing all the items from the Stack
stack.pop()
stack.pop()
stack.pop()
stack.pop()
stack.pop()
stack.pop()

print("After removing all the items from the stack", stack) # Printing empty Stack

print("Removing any more items will result in an error")
