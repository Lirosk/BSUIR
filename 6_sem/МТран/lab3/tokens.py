from __future__ import annotations
from typing import Callable, List

import data_types
import interpretations
import statements

from models import TokenInfo, TokenTypes, NameTableStream


reserved_data_types = {
    r"var"   : interpretations.DeclareVarDefineType,
    r"float" : interpretations.DeclareVar(data_types.TypeFloat),
    r"double": interpretations.DeclareVar(data_types.TypeDouble),
    r"int"   : interpretations.DeclareVar(data_types.TypeInt),
    r"uint"  : interpretations.DeclareVar(data_types.TypeUint),
    r"long"  : interpretations.DeclareVar(data_types.TypeLong),
    r"ulong" : interpretations.DeclareVar(data_types.TypeUlong),
    r"byte"  : interpretations.DeclareVar(data_types.TypeByte),
    r"sbyte" : interpretations.DeclareVar(data_types.TypeSbyte),
    r"void"  : interpretations.DeclareVar(data_types.TypeNull),
    r"const" : interpretations.DecorateWithType(data_types.TypeConst),
}

reserved_ids = {
    r"true" : interpretations.Value(TokenInfo("true", type=TokenTypes.ID)),
    r"false": interpretations.Value(TokenInfo("false", type=TokenTypes.ID)),
    r"_"    : interpretations.Value(TokenInfo("_", type=TokenTypes.ID)),
    r"null" : interpretations.Value(TokenInfo("null", type=TokenTypes.ID)),
}

reserved = {
    r";" : interpretations.End,
    r"//": interpretations.Interpretation,
    r"{" : interpretations.ComplexStatement,
    r"}" : interpretations.Error("Redundant \"}\"."),
    r")" : interpretations.Error("Redundant \")\"."),
    r"(" : interpretations.MultipleValueOrFuncCall,
    r"," : interpretations.Interpretation,
    r"." : interpretations.Interpretation,
    r"return" : interpretations.Return,
    r"while": interpretations.WhileLoop,
    r"if": interpretations.If,
    r"else": interpretations.Interpretation,
    r"for": interpretations.ForLoop,
}

un_operators = {
    r"++": interpretations.Increment,
    r"--": interpretations.Decrement,
}

bin_operators = {
    r"=" : interpretations.BinaryOperation(statements.Set),

    r"+" : interpretations.NumericOperation(r"+"),
    r"-" : interpretations.NumericOperation(r"-"),
    r"/" : interpretations.NumericOperation(r"/"),
    r"*" : interpretations.NumericOperation(r"*"),
    r"^" : interpretations.NumericOperation(r"^"),
    r"|" : interpretations.NumericOperation(r"|"),
    r"&" : interpretations.NumericOperation(r"&"),
    r"%" : interpretations.NumericOperation(r"%"), 
    r"<<": interpretations.NumericOperation(r"<<"), 
    r">>": interpretations.NumericOperation(r">>"), 

    r"!=": interpretations.NumericOperation(r"!="),
    r"==": interpretations.NumericOperation(r"=="),
    r">=": interpretations.NumericOperation(r">="),
    r"<=": interpretations.NumericOperation(r"<="),
    r">" : interpretations.NumericOperation(r">"),
    r"<" : interpretations.NumericOperation(r"<"),
}

known = \
      reserved_data_types \
    | reserved_ids \
    | reserved \
    | un_operators \
    | bin_operators


def interpret_token(token_info: TokenInfo,
                    nametable: NameTableStream,
                    context: List[statements.Statement],
                    namespace: data_types.TypeNamespace) -> None:

    if (token_info.type in (TokenTypes.NULL, TokenTypes.EOF)):
        return

    if (token_info.token not in known and token_info.type in (TokenTypes.CONST, TokenTypes.ID)):
        interpretations.Value(token_info).interpret(nametable, context, namespace)
        return

    known[token_info.token].interpret(nametable, context, namespace)


def interpret_tokens_until(until_next: Callable[[TokenInfo], bool],
                           nametable: NameTableStream,
                           context: List[statements.Statement],
                           namespace: data_types.TypeNamespace):
    if (until_next(nametable.peek())):
        return

    while (token_info := nametable.next()):
        try:
            interpret_token(token_info, nametable, context, namespace)

            if (next_token_info:=nametable.peek()):
                if (until_next(next_token_info)):
                    break

                if (next_token_info.type is TokenTypes.EOF):
                    raise interpretations.InterpretationError("Expected end of expression.", _break=True)

            else:
                raise interpretations.InterpretationError("Expected end of expression.")
       
        except interpretations.InterpretationError as e:
            print(f"Error on line {token_info.line[0]}:")
            print(f"{token_info.line[1]}")
            print(e, end="\n\n")

            if (e._break):
                break
