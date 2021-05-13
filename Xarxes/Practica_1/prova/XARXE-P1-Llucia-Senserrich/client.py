import argparse
import socket
import time
import os
import signal
import sys
DEBUG = True
NUM='0'*6
TCP_PORT=0
DISCONECTED=0
WAIT_REG=1
REGISTERED=2
ALIVE=3
STATE=DISCONECTED
def debug(text,error=False):
	if DEBUG:
		if error:
			print('ERROR: '+text)
		else:
			print('DEBUG: '+text)

class Config:
	def __init__(self,id,mac,server,udp_port,cfg_file='boot.cfg'):
		self.id=id
		self.mac=mac
		self.server=server
		self.udp_port=int(udp_port)
		self.tcp_port=None
		self.cfg_file=cfg_file
	@staticmethod
	def parseConfig(file,cfg='boot.cfg'):
		with open(file) as f:
			linesin = f.readlines()
			lines={}
			for l in linesin:
				tmp=l.replace('\n','').split(' ')
				lines[tmp[0].upper()]=tmp[1]
			return Config(lines['ID'],lines['MAC'],lines['SERVER'],lines['SRV-PORT'],cfg)	

class PDU:
	global NUM	
	types={
		'REGISTER_REQ': '\x10',
		'REGISTER_ACK': '\x11',
		'REGISTER_NACK':'\x12',
		'REGISTER_REJ': '\x13',
		'ERROR':        '\x19',
		'ALIVE_INF':    '\x20',
		'ALIVE_ACK':    '\x21',
		'ALIVE_NACK':   '\x22',
		'ALIVE_REJ':    '\x23',
		'PUT_FILE':     '\x30',
		'PUT_DATA':     '\x31',
		'PUT_ACK':      '\x32',
		'PUT_NACK':     '\x33',
		'PUT_REJ':      '\x34',
		'PUT_END':      '\x35',
		'GET_FILE':     '\x40',
		'GET_DATA':     '\x41',
		'GET_ACK':      '\x42',
		'GET_NACK':     '\x43',
		'GET_REJ':      '\x44',
		'GET_END':      '\x45'
	}
	@staticmethod
	def get_type(str,value=True):
		if value:
			return PDU.types[str]
		else :
			return PDU.types.keys()[PDU.types.values().index(str)]
	def __init__(self,type,id,mac,data,num=NUM):
		self.type=type
		self.id=id
		self.mac=mac
		self.data=data
		self.num=num
	def get_str(self,udp=True):
		global NUM
		l=TCP.DATA_SIZE
		if udp:
			l=UDP.DATA_SIZE
		return self.type+str(self.id)+'\0'+str(self.mac)+'\0'+str(NUM)+'\0'+self.data+'\0'*(l-len(self.data))
	def compare(pdu):
		self.num==pdu.num and self.mac==pdu.mac and self.id==pdu.id
	@staticmethod
	def from_conf(conf,type,data):
		return PDU(type,conf.id,conf.mac,data)
	@staticmethod
	def parse_str(str):
		data=[]
		st=''
		j=4
		data.append(chr(str[0]))
		for i in range(len(str)):
			if j==0:
				break
			if(chr(str[i])=='\0'):
				data.append(st)
				j-=1
				st=''
			else:
				st+=chr(str[i])
		return PDU(data[0],data[1],data[2],data[4],data[3])
class TCP:
	MSG_SIZE=178
	DATA_SIZE=150
	def __init__(self,config):
		self.config=config
	def connect(self):
		global TCP_PORT
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.server_address = (config.server, TCP_PORT)
		self.sock.connect(self.server_address)
	def send_file(self,filename):
		lines=None
		f =open(filename,'r')
		lines=f.readlines()
		f.close()
		p=PDU.from_conf(self.config,PDU.get_type('PUT_DATA'),'')
		
		for l in lines:
			p.data=l
			self.send(p)
		p.data=''
		p.type=PDU.get_type('PUT_END')
		self.send(p)
		self.close()
	def recive_file(self,filename):
		end=False
		f=open(filename,'w')
		while(not end):
			p=self.recive()
			if p is None:
				debug('error')
				exit(0)
			if p.type==PDU.get_type('GET_END'):
				end=True
			elif p.type==PDU.get_type('GET_DATA'):
				f.write(p.data)
		f.close()
		self.close()
	def send(self,pdu):
		self.sock.send(pdu.get_str(False).encode())
		debug('TCP message sent')
	def recive(self):
		r=self.sock.recv(TCP.MSG_SIZE)
		debug('TCP message recived')
		return PDU.parse_str(r)
	def close(self):
		self.sock.close()
class UDP:
	DATA_SIZE=50
	MSG_SIZE=78
	n=3
	t=1
	m=3
	p=7
	s=2
	q=2
	r=2
	u=3
	def __init__(self,config):
		self.config=config
	def connect(self):
		self.socket=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		debug('Connected to UDP server')
	def send(self,pdu):
		self.socket.sendto(pdu.get_str().encode(), (self.config.server,self.config.udp_port))
		debug('UDP message sent')
	def recive(self,timeout=None):
		if timeout!=None:
			self.socket.settimeout(timeout)
		try:
			data,addr=self.socket.recvfrom(self.config.udp_port)
		except:
			return None
		finally:
			if timeout!=None:
				self.socket.settimeout(None)
		debug('UDP message recived')
		if data==None:
			return None
		return PDU.parse_str(data)
	def close(self):
		self.socket.close()
		debug('UDP server closed')
	def send_alive(self):
		global STATE
		n=0
		while n<UDP.u :
			pdu=PDU.from_conf(self.config,PDU.get_type('ALIVE_INF'),'')
			self.send(pdu)
			pdu=self.recive(1)
			for _ in range(UDP.r):
				time.sleep(1)
			if pdu is None or pdu.type==PDU.get_type('ALIVE_REJ'):
				STATE=DISCONECTED
				return -1
			elif pdu.type!=PDU.get_type('ALIVE_ACK'):
				n+=1
			elif pdu.type==PDU.get_type('ALIVE_ACK') and STATE==WAIT_REG:
				STATE=ALIVE
			else:
				pass
	def reg_req(self):
		global STATE
		global NUM
		global TCP_PORT
		signal.signal(signal.SIGINT,die)
		p=PDU(PDU.get_type('REGISTER_REQ'),self.config.id,self.config.mac,"")
		q=0
		data=None
		n=0
		m=UDP.m
		t=UDP.t
		while data==None and q<UDP.q:
			while n<UDP.p and data==None:
				self.send(p)
				data=self.recive(t)
				if data is not None and str(data.type)==PDU.get_type('REGISTER_ACK'):
					STATE=WAIT_REG
					NUM=data.num
					TCP_PORT=int(data.data)
					return data
				if n>=UDP.n and t<UDP.t*UDP.m:
					t+=t
				else:
					n+=1
			q+=1
			for _ in range(UDP.s):
				time.sleep(1)
		STATE=DISCONECTED
	def start(self):
		global STATE
		global NUM
		global TCP_PORT
		data=None
		while True:
			if STATE==DISCONECTED:
				data=self.reg_req()
			if STATE in [WAIT_REG,REGISTERED,ALIVE]:
				self.send_alive()
class Comands:
	def __init__(self,config):
		self.config=config
		self.tcp=TCP(self.config)
	def listen(self):
		signal.signal(signal.SIGINT,die)
		a=-1
		while a==-1:
			command=input('Input the command: ')
			a=self.chose_act(command)
	def chose_act(self,cmd):
		if cmd=='get-cfg':
			self.get_cfg()
		elif cmd=='put-cfg':
			self.put_cfg()
		elif cmd=='quit':
			self.quit()
		return -1
	# sned a config file to the server
	def put_cfg(self):
		len=os.path.getsize(self.config.cfg_file)
		s=self.config.cfg_file+','+str(len)
		pdu=PDU.from_conf(self.config,PDU.get_type('PUT_FILE'),s)
		self.tcp.connect()
		self.tcp.send(pdu)
		self.tcp.send_file(config.cfg_file)
	# read config file from the server
	def get_cfg(self):
		s=self.config.cfg_file
		pdu=PDU.from_conf(self.config,PDU.get_type('GET_FILE'),s)
		self.tcp.connect()
		self.tcp.send(pdu)
		self.tcp.recive_file(config.cfg_file)
		pass
	def quit(self):
		os.kill(os.getppid(),signal.SIGTERM)
pid=0
udp=0
def child(conf):
	try:
		signal.signal(signal.SIGINT,die)
		c=Comands(conf)
		c.listen()
	except KeyboardInterrupt:
		debug("closed by ctr-c")
	exit(0)
	pass
def fatherdead(a,b):
	global udp
	udp.close()
	os.wait()
	exit(0)
def die(a,b):
	os.kill(os.getpid(),signal.SIGUSR2)
def father(u):
	try:
		signal.signal(signal.SIGUSR2,fatherdead)
		u.start()
	except KeyboardInterrupt:
		debug("closed by ctr-c")
	pass
def start_child(u,conf):
	global pid,udp
	udp=u
	pid=os.fork()
	if pid:
		father(u)
		os.wait()
	else:
		child(conf)
def init():
	global DEBUG
	parser = argparse.ArgumentParser()
	parser.add_argument('-c',default='client.cfg',type=str)
	parser.add_argument('-f',default='boot.cfg',type=str)
	parser.add_argument('-d', default = False, dest = 'DEBUG', help = 'Fer debug', action = 'store_true')
	args = parser.parse_args()
	DEBUG=args.DEBUG
	return Config.parseConfig(args.c,args.f)

if __name__=='__main__':
	config=init()
	u=UDP(config)
	u.connect()
	u.reg_req()
	start_child(u,config)
	