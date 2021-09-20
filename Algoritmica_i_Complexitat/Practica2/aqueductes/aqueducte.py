#!/usr/bin/python3
import sys
import math

sys.setrecursionlimit(777777777)

class Pillar:
    def __init__(self,x,y,height,alpha,id):
        self.x=x
        self.y=y
        self.h=height
        self.alpha=alpha
        self.id=id

    def get_cost(self):
        """
        this functions returns the cost to build a single pillar
        """
        return self.h*self.alpha

class Bridge:
    def __init__(self, height,points,alpha,beta):
        self.height=height
        self.points=points
        self.pillars=[Pillar(points[i][0],points[i][1],height-points[i][1],alpha,i) for i in range(len(points))]
        self.alpha=alpha
        self.beta=beta
        self.len=len(self.pillars)
    def its_possible(self,start_i,end_i):
        """
        this function checks if in an input can be build
        Args:
                start_i: strating index
                end_i: ending index
        Return:
                returns a boolean
        """
        start=self.pillars[start_i]
        end=self.pillars[end_i]
        rad=(end.x-start.x)/2
        if not(start.y<=self.height-rad and end.y<=self.height-rad):
            return False
        others=range(start_i+1,end_i)
        for p in others:
            if not self.possible_pic(start_i,end_i,p):
                return False
        return True

    def possible_pic(self,start_i,end_i,pic_i):
        """
        this function checks if a point is possible, checking its height
        Args:
                start_i: index of the starting point
                end_i: index of the ending point
                pic_i: index of the pic to check
        Return:
                returns a boolean
        """
        start=self.pillars[start_i]
        end=self.pillars[end_i]
        pic=self.pillars[pic_i]
        rad=(end.x-start.x)/2
        mid=(start.x+rad)
        alt=(self.height-rad)
        x_dif=(mid-pic.x)
        y_dif=(alt-pic.y)
        dist=math.sqrt((x_dif**2)+(y_dif**2))
        return pic.y<=alt or (pic.y>alt and dist<=rad)

    def get_partial_cost(self,start,end,between=False):
        """
        gets the cost from a starting pillar to another
        Args:
            start: starting pillar
            end: ending pillar
            between: when true onl6y returned the bride and the last pillar cost
        Return:
            returns a float
        """
        if not between:
            return (((end.x-start.x)**2)*self.beta)+start.get_cost()+end.get_cost()
        return (((end.x-start.x)**2)*self.beta)+end.get_cost()



class Calculator:
    @staticmethod
    def run(bridge,str,it):
        """
        calculates the minimum cost to build the bridge withe the specified algothm
        Args:
            str: algorithm name aka ['greedy'|'backtracking'|'dynamic']
            it: a boolean to specify if the algorithm you want to use is iterative
        Return:
            the minimum cost with the input algorithm
        """
        if str=='greedy':
            return Calculator.greedy(bridge,it)
        elif str=='backtracking':
            return Calculator.backtracking(bridge,it)
        return Calculator.dynamic(bridge,it)

    @staticmethod
    def dynamic(bridge,it):
        """
        Calculates the minimum cost to build a bride using dynamic programming
        Args:
            bridge: Bridge class input from user or file
            it: iterative or recursive?
        """
        try:
            if it:
                return Calculator.__dynamic_it__(bridge)
            return Calculator.__dynamic__(bridge)
        except:
            return "impossible"

    @staticmethod
    def __dynamic__(bridge,i=0,memo={}):
        """
        Calculates the minimum cost to build a bride using dynamic programming
        actually the useful function
        """
        res=[]
        if i>=len(bridge.pillars)-1:
            return 0
        start=bridge.pillars[i]
        for p in range(i+1,bridge.len):
            if bridge.its_possible(i,p):
                if (str(i)+'-'+str(p) not in memo):
                    memo[str(i)+'-'+str(p)]=bridge.get_partial_cost(start,bridge.pillars[p],i!=0)+Calculator.__dynamic__(bridge,p,memo)
                res.append(memo[str(i)+'-'+str(p)])
        if i==0 and len(res)==0:
            raise Exception("Impossible")
        elif len(res)==0:
            return -1
        return min(res)

    @staticmethod
    def __dynamic_it__(bridge):
        """
        Calculates the minimum cost to build a bride using dynamic programming
        actually the useful function
        """
        return 'unimplemented'

    @staticmethod
    def backtracking(bridge,it):
        """
        Calculates the minimum cost to build a bride using backtracking
        Args:
            bridge: Bridge class input from user or file
            it: iterative or recursive?
        """
        try:
            if it:
                return Calculator.__backtracking_it__(bridge)
            return Calculator.__backtracking__(bridge)
        except:
            return "impossible"
    @staticmethod
    def __backtracking__(bridge,i=0):
        """
        Calculates the minimum cost to build a bride using backtracking
        actually the useful function
        """
        res=[]
        if i>=len(bridge.pillars)-1:
            return 0
        start=bridge.pillars[i]
        for p in range(i+1,len(bridge.pillars)):
            if bridge.its_possible(i,p):
                c=Calculator.__backtracking__(bridge,p)
                if c!=-1:
                    res.append(bridge.get_partial_cost(start,bridge.pillars[p],i!=0)+c)
        if i==0 and len(res)==0:
            raise Exception("Impossible")
        elif len(res)==0:
            return -1
        return min(res)
    def __backtracking_it__(bridge):
        """
        Calculates the minimum cost to build a bride using backtracking
        actually the useful function
        """
        return 'unimplemented'

    @staticmethod
    def greedy(bridge,it):
        """
        Calculates the minimum cost to build a bride using greedy
        Args:
            bridge: Bridge class input from user or file
            it: iterative or recursive?
        """
        try:
            if it:
                return Calculator.__greedy_it__(bridge)
            return Calculator.__greedy__(bridge)
        except:
            return "impossible"

    @staticmethod
    def __greedy__(bridge,i=0):
        """
        Calculates the minimum cost to build a bride using greedy
        actually the useful function
        """
        cost={}
        if i==len(bridge.pillars)-1:
            return 0
        for b in bridge.pillars[i+1:]:
            if bridge.its_possible(i,b.id):
                cost[b.id]=bridge.get_partial_cost(bridge.pillars[i],b,i!=0)
        if len(cost)==0:
            raise Exception("Impossible")
        k=min(cost,key=cost.get)
        return cost[k]+Calculator.__greedy__(bridge,k)

    def __greedy_it__(bridge):
        """
        Calculates the minimum cost to build a bride using backtracking
        actually the useful function
        """
        res=0
        i=0
        while i!=len(bridge.pillars)-1:
            cost={}
            for b in bridge.pillars[i+1:]:
                if bridge.its_possible(i,b.id):
                    cost[b.id]=bridge.get_partial_cost(bridge.pillars[i],b)
            if len(cost)==0:
                raise Exception("Impossible")
            k=min(cost,key=cost.get)
            res+=cost[k]
            i=k
        return res



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

if __name__ == '__main__':
    file=sys.stdin
    if len(sys.argv)>1:
        file=open(sys.argv[1],'r')
    params=read_file(file)
    file.close()
    b=Bridge(params[1],params[4],params[2],params[3])
    print(Calculator.dynamic(b,False))