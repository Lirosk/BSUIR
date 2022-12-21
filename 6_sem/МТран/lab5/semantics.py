import tokens

from data_types import *

# shit happens
def define_type_of_const(token: TokenInfo | str) -> TypeType:
    if (type(token) is TokenInfo):
        token = token.token
    
    token = token.lower()

    if (token == "true" or token == "false"):
        return TypeBool

    if (token.startswith("\"")):
        return TypeString

    if (token.startswith("\'")):
        return TypeChar

    if (token.endswith("m")):
        return TypeDecimal

    if (token.endswith("f")):
        return TypeFloat

    if (token.endswith("d") or token.find(".") != -1 or token.find("e") != -1):
        return TypeDouble

    if (token.endswith("ul")):
        return TypeULong

    if (token.endswith("l")):
        return TypeLong
    
    if (token.endswith("u")):
        return TypeUInt
    
    return TypeInt


def are_types_compatible(type1: TypeType, type2: TypeType):
    for _type in type1.compatible_with:
        if (issubclass(_type, type2) or issubclass(type2, _type)):
            return True

    return False


def get_type_from_token(type_token: TokenInfo | str) -> TypeType:
    if (type(type_token) is TokenInfo):
        type_token = type_token.token

    token = type_token.lower()

    return tokens.known[token].var_type


if __name__ == '__main__':
    print(are_types_compatible(TypeIntegral, TypeInt))
    print(are_types_compatible(TypeIntegral, TypeDouble))
    print(are_types_compatible(TypeDecimal, TypeDouble))   
    print(are_types_compatible(TypeIntegral, TypeBool))

    print(get_type_from_token(TokenInfo("int")))
    print(get_type_from_token(TokenInfo("float")))
    print(get_type_from_token("bool"))