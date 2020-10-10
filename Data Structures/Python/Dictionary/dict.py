# Program to demonstrate the basics of Python dictionaries

x = {} # Creating an empty dictionary

x = { "one" : 1, "two" : 2, "three" : 3 } # Creating a dictionary with 3 key-value pairs

print(x['two']) # Displaying an element throught the dictionary key

print(x.keys()) # Retrieving a list of all the keys present in the dictionary

print(x.values()) # Retrieving a list of all the values present in the dictionary

x["four"] = 4 # Adding an entry in the dictionary
print(x)

x["one"] = "uno" # Modifying an entry in the dictionary
print(x)

del x["four"] # Deleting an entry from the dictionary
print(x)

print(len(x)) # To display the number of entries in the dictionary

y = x.copy() # Copying the dictionary into another variable
print(y)

x.clear() # Removing all the entires from the dictionary
print(x)

# Looping over keys
for key in x.keys():
    print(key)

# Looping over values
for value in x.values():
    print(value)

# using the if statement to get the values
if "one" in x:
    print(x['one'])

if "two" not in x:
    print("Two not found")

if "three" in x:
    del x['three']
