from collections import deque

q = deque()

print(q)

q.append("Hey")
q.append("there!")
q.append("This")
q.append("is")
q.append("a")
q.append("Stack!")

print(q)

q.popleft()

print(q)

q.append("What?!")

print(q)

q.popleft()
q.popleft()
q.popleft()
q.popleft()
q.popleft()
q.popleft()

print(q)
