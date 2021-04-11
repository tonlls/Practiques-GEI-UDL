def read_file(filename):
	lines=None
	rects=[]
	with f=open(filename,'r'):
		lines=f.readlines()
	n,h,a,b=lines[0].split(' ')
	for l in lines[1:]:
		rects.append(l.split(' ')
	return n,h,a,b,rects
