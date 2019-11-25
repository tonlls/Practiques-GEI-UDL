
import random
import sys
import re

text = ""
with open(sys.argv[1]) as file:
    text = file.read()

text = [x for x in text if x != '.']
spaces = [x for x,y in enumerate(text) if y == ' ']

position = random.randint(0, len(spaces)-1)
end = start = spaces[position]+1
while text[end].isalpha():
    end += 1

word = text[start:end]
print(''.join(word) + '.')

alt_word = ''.join(random.sample(word,len(word)))
alt_word = ''.join([(lambda x :  x if random.randint(0,1) else x.swapcase())(x) for x in alt_word])

for i in range(start, end):
    text[i] = alt_word[i-start]

print(''.join(text) + '.')
