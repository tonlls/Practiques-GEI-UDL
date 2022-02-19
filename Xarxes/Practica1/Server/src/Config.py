class Config:
    def __init__(self, file, debug):
        self.file=file
        self.debug=debug
        self.__parse__(file)
    def __parse__(self,file):
        with open(file) as f:
            linesin = f.readlines()
            lines={}
            for l in linesin:
                tmp=l.replace('\n','').split(' ')
                lines[tmp[0].upper()]=tmp[1]
            self.id=lines['ID']
            self.udp_port=int(lines['UDP_PORT'])
            self.tcp_port=int(lines['TCP_PORT'])