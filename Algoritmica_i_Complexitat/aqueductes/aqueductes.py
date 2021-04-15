#!/usr/bin/python3
import sys
import Math
def read_file(f):
	rects=[]
	l=f.readline()
	n,h,a,b=map(int,l[:-1].split(' '))
	for _ in range(n):
		l=f.readline()
		rects.append(map(int,l[:-1].split(' ')))
	return n,h,a,b,rects

def posible_arc():
	pass
def calc_radius(rects):
	rad=[]
	for i in range(len(rects)-1):
		rad.append((rects[i+1][0]-rects[i][0])/2)
	return rad
def possible_pic(rad,cols,pic):
	mid=Math.abs((cols[1][0]-cols[0][0])/2)-pic[0])
	alt=Math.abs((h-rad)-pic[1])
	dist=Math.sqrt((mid**2)+(mid**2))
	return not(dist>rad and pic[1]>h-rad)
def its_posible_2pilars(input):
	n,h,a,b,rects=input
	rads=rects[0][0]
	for i in range(1,len(rects)):
		if rects[i][1]>=h and not possible_pic(rads[i-1],[rects[0],rects[-1]],rects[1:-2]):
			return False
	return True
# def rec(h,p1,p2):
	# if index==len(rects):
		# return 
	# return 
# def its_posible_r(input):
	
def its_posible_multi_pilar(input):
	n,h,a,b,rects=input
	rads=calc_radius(rects)
	hig=0
	for i in range(len(rects)):
		if i==0:
			hig=h-rads[0]
		elif i==len(rects)-1:
			hig=h-rads[-1]
		else:
			hig=h-max(rads[i],rads[i+1])
		if r[i][1]>=h-hig:
			return False
	return True
	
	
def its_possible(input):
	return its_posible_2pilars(input) or its_posible_multi_pilar(input)

def calc_multi_pilar(input):
	return 
def calc_2pilar(input):
	
def calc(input):
	n,h,a,b,rects=input
	

file=sys.stdin
if len(sys.argv)>1:
	file=open(sys.argv[1],'r')
input=read_file(file)
file.close()
if its_posible(input):
	calc(input)
else:
	pass
print(input)