import enum


class State(enum.Enum):
    DISCONNECTED = 0xf0
    NOT_REGISTERED = 0xf1
    WAIT_ACK_REG = 0xf2
    WAIT_INFO = 0xf3
    WAIT_ACK_INFO = 0xf4
    REGISTERED = 0xf5
    SEND_ALIVE = 0xf6