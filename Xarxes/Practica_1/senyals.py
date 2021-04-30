import os
import signal

# def fill(pid):
	# signal.signal(signal.SIGUSR1,senyal)
	# while(True):
		# pass
# def senyal(a,b):
	# print('dead child')
	# exit(0)
# def pare(pid):
	# name1 = input("Enter name : ")
	# print(name1)
	# os.kill(pid,signal.SIGUSR1)
	
	
# pid=os.fork()
# if pid:
	# pare(pid)
	# os.wait()
	# print('dead pare')
# else:
	# fill(os.getppid())
file=open('boot.cfg','r')
li=file.readlines()
file.close()
f=open('boot_t.cfg','w')
for l in li:
	f.write(l)
f.close()