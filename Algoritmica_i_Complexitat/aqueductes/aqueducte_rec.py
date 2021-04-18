#!/usr/bin/python3
"""
this script calculates the price to build a pont or and an aqueducte,
the output is the cheapest price
"""
import sys
import math

def read_file(my_file):
    """
    this function reads the data file and returns a tuple with the data resume
    Args:
        my_file: a pointer to the open file to read
    Return:
        returns a tuple containing:
            the desired height
            the num of cols/points
            the alpha value
            the beta value
            the coordinates of the cols/points
    """
    rects=[]
    line=my_file.readline()
    num_cols,height,alpha,beta=list(map(int,line[:-1].split(' ')))
    for _ in range(num_cols):
        line=my_file.readline()
        rects.append(list(map(int,line[:-1].split(' '))))
    return num_cols,height,alpha,beta,rects


def calc_radius(rects):
    """
    this function calculates the radius of the circle between 2 arcs
    Args:
        rects: a list containing the columns coordinates
    Return:
        returns a list of all the calculated radius between the input cols
    """
    rad=[]
    for i in range(len(rects)-1):
        rad.append((rects[i+1][0]-rects[i][0])/2)
    return rad

def possible_pic(height,rad,cols,pic):
    """
    this function checks if a point is possible, checking its height
    Args:
        height: the desired height of the pont/aqueducte
        rad: the radius of the semicircle between the 2 columns
        cols: the columns points
        pic: the point to check
    Return:
        returns a boolean
    """
    mid=abs(((cols[1][0]-cols[0][0])/2)-pic[0])
    alt=abs((height-rad)-pic[1])
    dist=math.sqrt((mid**2)+(alt**2))
    return not(dist>rad and pic[1]>height-rad)

def its_posible_2pilars(f_input):
    """"
    this function checks if it's possible to build a "pont" between 2 pints using 2 cols
    Args:
        f_input: the input data extrated from the input file in a tuple containing:
            the desired height
            the num of cols/points
            the alpha value
            the beta value
            the coordinates of the cols/points
    Return:
        returns a boolean
    """
    _,height,_,_,rects=f_input
    rads=calc_radius([rects[0],rects[-1]])[0]
    return its_posible_2pilars_rec(height,rects[1:-1],rads,[rects[0],rects[-1]])

def its_posible_2pilars_rec(height,rects,rad,cols):
    """"
    tis function is used by the recursive algorithm
    Args:
        height: the desired height of the pont/aqueducte
        rects: the point to check
        rad: the radius of the semicircle between the 2 columns
        cols: the columns points
    Return:
        returns a boolean
    """
    if len(rects)==1:
        return not rects[0][1]>=height and  possible_pic(height,rad,cols,rects[0])
    return ((not rects[0][1]>=height
            and possible_pic(height,rad,cols,rects[0]))
            and its_posible_2pilars_rec(height,rects[1:],rad,cols))

def its_posible_multi_pilar(f_input):

    _,height,_,_,rects=f_input
    rads=calc_radius(rects)
    return its_posible_multi_pilar_rec(height,rects,rads,True)

def its_posible_multi_pilar_rec(height,rects,rads,first=False):
    if len(rects)==1:
        return rects[0][1]>height-rads[0]
    elif first:
        return rects[0][1]>height-rads[0] and its_posible_multi_pilar_rec(height,rects[1:],rads)
    return (rects[0][1]>height-max(rads[0],rads[1])
            and its_posible_multi_pilar_rec(height,rects[1:],rads[1:]))

def its_possible(f_input):
    """
    this function checks if in an input can be build
    Args:
        f_input: the input data extrated from the input file in a tuple containing:
            the desired height
            the num of cols/points
            the alpha value
            the beta value
            the coordinates of the cols/points
    Return:
        returns a boolean
    """
    return its_posible_2pilars(f_input) or its_posible_multi_pilar(f_input)

def calc_multi_pilar(f_input):
    """
    this function calculates the cost to build a milti pilar aqueducte
    Args:
        f_input: the input data extrated from the input file in a tuple containing:
            the desired height
            the num of cols/points
            the alpha value
            the beta value
            the coordinates of the cols/points
    Return:
        returns the cost
    """
    _,height,alpha,beta,rects=f_input
    height_list=[height-p[1] for p in rects]
    distance_list=[(rects[i+1][0]-rects[i][0])**2 for i in range(len(rects)-1)]
    return alpha*sum(height_list)+beta*sum(distance_list)

def calc_2pilar(f_input):
    """
    this function calculates the cost to build a pont of only 2 cols
    Args:
        f_input: the input data extrated from the input file in a tuple containing:
            the desired height
            the num of cols/points
            the alpha value
            the beta value
            the coordinates of the cols/points
    Return:
        returns the cost
    """
    _,height,alpha,beta,rects=f_input
    rects=[rects[0],rects[-1]]
    height_list=[height-p[1] for p in rects]
    distance_list=[(rects[i+1][0]-rects[i][0])**2 for i in range(len(rects)-1)]
    return alpha*sum(height_list)+beta*sum(distance_list)

def calc(f_input):
    """
    this function calculates the minimum cost
    Args:
        f_input: the input data extrated from the input file in a tuple containing:
            the desired height
            the num of cols/points
            the alpha value
            the beta value
            the coordinates of the cols/points
    Return:
        returns an int
    """
    if its_possible(f_input):
        prices=[calc_2pilar(f_input),calc_multi_pilar(f_input)]
        if 'impossible' in prices:
            prices.remove('impossible')
        if len(prices)==0:
            return 'impossible'
        return min(prices)
    return 'impossible'

if __name__ == '__main__':
    file=sys.stdin
    if len(sys.argv)>1:
        file=open(sys.argv[1],'r')
    params=read_file(file)
    file.close()
    print(calc(params))
