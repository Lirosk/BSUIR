from data_types import *


class M(type):
    def __new__(cls, *args, **kwargs):
        _type = super().__new__(cls, *args, **kwargs)
        _type.self = args[0]
        return _type
