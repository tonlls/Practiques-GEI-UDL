import enum


class PDU_Type(enum.Enum):
    REG_REQ=0xa0,
    REG_ACK = 0xa1,
    REG_NACK = 0xa2,
    REG_REJ = 0xa3,
    REG_INFO = 0xa4,
    INFO_ACK = 0xa5,
    INFO_NACK = 0xa6,
    INFO_REJ = 0xa7,
    DISCONNECTED = 0xf0,
    NOT_REGISTERED = 0xf1,
    WAIT_ACK_REG = 0xf2,
    WAIT_INFO = 0xf3,
    WAIT_ACK_INFO = 0xf4,
    REGISTERED = 0xf5,
    SEND_ALIVE  = 0xf6,
    ALIVE = 0xb0,
    ALIVE_NACK = 0xb1,
    ALIVE_REJ = 0xb2,
    SEND_DATA = 0xc0,
    DATA_ACK = 0xc1,
    DATA_NACK = 0xc2,
    DATA_REJ = 0xc3,
    SET_DATA = 0xc4,
    GET_DATA  = 0xc5

class TCP_PDU:
    TYPE_SIZE = 1
    FROM_ID_SIZE = 11
    TO_ID_SIZE = 11
    ELEMENT_SIZE = 8
    VLUE_SIZE = 16
    INFO_SIZE = 80
    @staticmethod
    def getFullSize():
        return TCP_PDU.TYPE_SIZE + TCP_PDU.FROM_ID_SIZE + TCP_PDU.TO_ID_SIZE + TCP_PDU.ELEMENT_SIZE + TCP_PDU.VLUE_SIZE + TCP_PDU.INFO_SIZE
    def __init__(self, type, from_id, to_id, element, vlue, info):
        self.type = type
        self.from_id = from_id
        self.to_id = to_id
        self.element = element
        self.vlue = vlue
        self.info = info
    def __str__(self):
        return "Type: {}, From: {}, To: {}, Element: {}, Vlue: {}, Info: {}".format(self.type, self.from_id, self.to_id, self.element, self.vlue, self.info)
    @classmethod
    def fromString(string:str):
        type = int(string[0:1], 16)
        from_id = string[1:12]
        to_id = string[12:23]
        element = string[23:31]
        vlue = string[31:47]
        info = string[47:]
        return TCP_PDU(type, from_id, to_id, element, vlue, info)

class UDP_PDU:
    TYPE_SIZE=1
    FROM_ID_SIZE=11
    TO_ID_SIZE=11
    DATA_SIZE=61
    @staticmethod
    def getFullSize():
        return UDP_PDU.TYPE_SIZE + UDP_PDU.FROM_ID_SIZE + UDP_PDU.TO_ID_SIZE + UDP_PDU.DATA_SIZE
    def __init__(self,type:PDU_Type, from_id:str, to_id:str, data:str):
        self.type=type
        self.from_id=from_id
        self.to_id=to_id
        self.data=data
    def __str__(self):
        return f"{self.type.name} {self.from_id} {self.to_id} {self.data}"
    @classmethod
    def fromString(string:str):
        type=PDU_Type(int(string[0:1],16))
        from_id=string[1:12]
        to_id=string[12:23]
        data=string[23:]
        return UDP_PDU(type,from_id,to_id,data)