import sys
def ex1(file):
	with open(file) as f:
		text=f.read()
	text=text.split('.')
	to_search=text[0].split()
	text=text[1].split()
	found={key:0 for key in to_search}
	for w in text:
		for sw in to_search:
			if sorted(w.capitalize())==sorted(sw.capitalize()):
				print(w+', ',end='')
				found[sw]+=1
	print()
	for k,v in found.items():
		print(k+' -> '+str(v))
def ex2(file):
	def is_wall(laberinth,x,y):
		
	def walk(laberinth,x,y,direction):
		if direction.capitalize()=='N':
			if(laberinth[])
	with open(file) as f:
		content=f.read().split('\n')
	laberinth=[list(r.replace('O',' ')) for r in  content[:10]]
	x=content[10]
	y=content[11]
	directions=content[12]
	
	for x in laberinth:
		print(x)


if sys.argv[1]=='ex1':
	ex1(sys.argv[2])
elif sys.argv[1]=='ex2':
	ex2(sys.argv[2])