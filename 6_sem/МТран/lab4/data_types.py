from __future__ import annotations
from typing import Dict, Tuple


from models import TokenInfo, TokenTypes
from errors import SemanticError


class TypeNamespace:
    def __init__(self,
                 defined_vars: Dict[str, Variable] = None,
                 parent: TypeNamespace = None) -> None:
        self.declared_vars = defined_vars or {}
        self.parent = parent

    def declare(self, token_info: TokenInfo, type: TypeType, value: TypeObject = None):
        name, token_type, *_ = token_info

        if (token_type is TokenTypes.ID):
            if (name not in self.declared_vars):
                self.declared_vars[name] = Variable(type, value)
                return

        # TODO: throw semantic exception
        print("Error: declare var with const name")

    def get_var(self, var_name: str | TokenInfo):
        if (type(var_name) is TokenInfo):
            var_name = var_name.token

        # no var in local namespace
        if (var_name in self.declared_vars):
            return self.declared_vars[var_name]
        
        # search in outer namespace
        if (self.parent):
            return self.parent.get_var(var_name)
        
        # TODO no var declared
        raise SemanticError(f"Error: no var declared with name \"{var_name}\"")


class TypeObject:
    name = "object"
    default = None
    compatible_with: Tuple[TypeObject] = ()


class TypeType(TypeObject):
    name = "type"


class TypeConst:
    ...


class TypeString(TypeObject):
    name = "string"


class TypeFunction(TypeObject):
    ...


class TypeDiscard(TypeObject):
    name = "discard"


class TypeNull(TypeObject):
    name = "null"


class TypeNumeric(TypeObject):
    name = "numeric"
    default = 0


class TypeFloatingPoint(TypeNumeric):
    ...



class TypeDecimal(TypeFloatingPoint):
    name = "decimal"


class TypeFloat(TypeFloatingPoint):
    name = "float"


class TypeDouble(TypeFloatingPoint):
    name = "double"


class TypeIntegral(TypeNumeric):
    ...


class TypeChar(TypeIntegral):
    name = "char"


class TypeInt(TypeIntegral):
    name = "int"


class TypeUInt(TypeIntegral):
    name = "uint"


class TypeLong(TypeIntegral):
    name = "long"


class TypeULong(TypeIntegral):
    name = "ulong"


class TypeByte(TypeIntegral):
    name = "byte"


class TypeSbyte(TypeIntegral):
    name = "sbyte"


class TypeBool(TypeObject):
    name = "bool"


TypeObject.compatible_with = (TypeObject, )
TypeType.compatible_with = (TypeType, )
TypeString.compatible_with = (TypeString, )
TypeFloatingPoint.compatible_with = (TypeFloatingPoint, )
TypeIntegral.compatible_with = (TypeIntegral, )
TypeBool.compatible_with = (TypeBool, )


class Variable:
    def __init__(self, type: TypeType, value: TypeObject = None):
        self.type = type
        self.value = value or type.default


class Func(Variable):
    def __init__(self, return_type: TypeType, *args ):
        self.return_type = return_type
        self.args = args


class NamespaceGlobal(TypeNamespace):
    __default_globals = {
        "_": Variable(TypeDiscard),
        "null": Variable(TypeNull),
        "true": Variable(TypeBool, value=1),
        "false": Variable(TypeBool, value=0),
    }

    __obj = TypeNamespace(defined_vars=__default_globals)

    def __new__(cls):
        return cls.__obj
