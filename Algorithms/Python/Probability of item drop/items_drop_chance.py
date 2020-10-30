# This is a small script I've made for counting how many times you should fight
# an enemy, in any RPG game, in order to get a specific drop.

# If you enter the percentage of this specific item drop, this script will tell
# you how many times you should fight this enemy or event, in order to be almost
# sure you are going to get that item.

# For example, let assume in some game an enemy has a 1% chance of dropping an
# epic sword. You do really want that sword. Well, as it drop rate is 1/100 you
# are expected to get 1 sword for every 100 enemies you kill. But there is a
# chance you kill 100 enemies and you still don't get any sword. So this script
# tell you how many enemies you need to kill to get that epic sword!

# This program will ask the user for a value between 0 and 100 and then it will
# return:
#
# * The expected times
# * The nearly guaranteed 90% value
# * The nearly guaranteed 99% value

# NOTE: expected time refers to the total number of attemps a player can expect
# to get 1 drop.
# Nearly guaranteed value refers to how many times to have a that chance to get
# 1 item

# This scripts is based on the stadistical Bernoulli distribution


import math, sys

def enter_value(x = None):
    while True:
      try:
          if x == None:
              x = float(input("Enter the probability number: "))
          else:
              x = float(x)
          break
      except ValueError:
          print("Wrong value, please try again")
    return x

def values(percent):
    if percent == 0:
        return 0, 0, 0
    elif percent > 100:
        return 1, 1, 1
    prob = percent / 100
    expected = math.ceil(100 / percent)
    comp = 1 - prob
    n = 0; m = 1
    res = 1
    while res > 0.01:
        res = res * comp
        n = n+1
        if res > 0.1:
          m = m+1
    return expected, m, n

def bernoulli(x = None):
    p = enter_value(x)
    aux = values(p)
    print("The expected number of times are: {}\n The nearly guaranteed times"
    "to drop are:\n 90% of chances: {} \n 99% of chances: {}\n"\
    .format(aux[0], aux[1], aux[2]))

while True:
    h = input("Enter a percentage value or enter 'q' to exit\n")
    sys.exit(0) if h == 'q' else bernoulli(h)
