from __future__ import annotations
from typing import Dict


class TypeNamespace:
    def __init__(self,
                 defined_vars: Dict[str, TypeObject] = None,
                 parent: TypeNamespace = None) -> None:
        self.defined_vars = defined_vars or {}
        self.parent = parent


class TypeObject:
    default = None


class TypeConst:
    ...


class TypeFunction(TypeObject):
    ...


class TypeDiscard(TypeObject):
    ...


class TypeNull(TypeObject):
    ...


class TypeNumeric(TypeObject):
    default = 0


class TypeFloat(TypeNumeric):
    ...


class TypeDouble(TypeNumeric):
    ...


class TypeInt(TypeNumeric):
    ...


class TypeUint(TypeNumeric):
    ...


class TypeLong(TypeNumeric):
    ...


class TypeUlong(TypeNumeric):
    ...


class TypeByte(TypeNumeric):
    ...


class TypeSbyte(TypeNumeric):
    ...


class NamespaceGlobal(TypeNamespace):
    __default_globals = {
        "_": TypeDiscard(),
        "null": TypeNull(),
    }

    __obj = TypeNamespace(defined_vars=__default_globals)

    def __new__(cls):
        return cls.__obj
