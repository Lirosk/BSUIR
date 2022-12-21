from __future__ import annotations
from enum import Enum

from typing import Tuple


class TokenTypes(Enum):
    NULL = 0
    ID = 1
    CONST = 2
    RESERVED = 4
    EOF = 8

    def __str__(self):
        val = super().__str__()
        val = val[len(self.__class__.__name__) + 1:]
        return val



class TokenInfo:
    def __init__(self,
                 token: str = "",
                 type: TokenTypes = TokenTypes.NULL,
                 line: Tuple(int, str) = (0, "")):
        self.token = token
        self.type = type
        self.line = line

    def __eq__(self, token_info: TokenInfo):
        return self.token == token_info.token and self.type == token_info.type

    def __iter__(self):
        yield from (self. token, self.type)

    def __repr__(self):
        return repr(self.token)


class NameTableStream:
    def __init__(self, nametable: Tuple[TokenInfo]):
        self.nametable = nametable
        self.len = len(nametable)
        self.pos = 0

    def step(self) -> None:
        self.pos += 1

    def current(self) -> None:
        res = self.nametable[self.pos]
        return res 

    def peek(self) -> TokenInfo | None:
        if (self.pos >= self.len):
            return None
        
        res = self.nametable[self.pos]
        return res 

    def next(self) -> TokenInfo | None:
        if (self.pos >= self.len):
            return None
        
        res = self.nametable[self.pos]
        self.pos += 1
        return res 