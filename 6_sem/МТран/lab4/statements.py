from __future__ import annotations
from typing import Tuple, Callable, Iterator

import semantics

from errors import SemanticError
from models import TokenInfo
from data_types import *

INDENT_SYMBOL = "|"
    

class Statement:
    def __init__(self,
                 operator: Callable[..., TypeObject],
                 operands: Tuple[Statement],
                 namespace: TypeNamespace = None) -> None:
        self.operator = operator
        self.operands = operands
        self.namespace = namespace

    def semantic_analyze(self) -> None:
        return

    def exec(self) -> None:
        self.operator(*self.operands)

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield INDENT_SYMBOL * indent


class ComplexStatement(Statement):
    def __init__(self,
                 body_statements: Tuple[Statement],
                 body_namespace: TypeNamespace,
                 namespace: TypeNamespace) -> None:
        
        def operator(self: Statement):
            for statement in self.operands:
                statement.exec()
        
        super().__init__(
            operator=operator,
            operands=(body_statements, body_namespace),
            namespace=namespace)
    

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent) 
        yield "{\n"
        for statement in self.operands[0]:
            yield from statement.build_tree(indent + 1)
        yield from super().build_tree(indent) 
        yield "}\n"

    def semantic_analyze(self) -> None:
        for operand in self.operands[0]:
            operand.semantic_analyze()



class Value(Statement):
    def __init__(self,
                 var_name_or_const_token: TokenInfo,
                 namespace: TypeNamespace):

        operator = (lambda var_or_const: var_or_const)
        super().__init__(
            operator=operator,
            operands=(var_name_or_const_token,),
            namespace=namespace)


    def define_type(self) -> TypeType:
        token, token_type, *_ = self.operands[0]

        if (token_type is TokenTypes.ID):
            return self.namespace.get_var(token).type

        return semantics.define_type_of_const(token)
        

    def semantic_analyze(self) -> None:
        return


    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent)
        yield str(self.operands[0])
        yield "\n"


class MultipleValues(Statement):
    def __init__(self,
                 values: Tuple[Value]):
        
        operator = (lambda: None)
        super().__init__(
            operator=operator,
            operands=values
        )

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent)
        yield "multiple values\n"
        for operand in self.operands:
            yield from operand.build_tree(indent + 1)

    def semantic_analyze(self) -> None:
        return
        
        
class DeclareFunc(Statement):
    def __init__(self,
                 name: TokenInfo,
                 return_type: TypeType,
                 args_info: MultipleValues | DeclareVar | Empty,
                 body: ComplexStatement,
                 header_namespace: TypeNamespace,
                 namespace: TypeNamespace,
                 #args_defaults: Tuple(None | TypeObject) = None,
                 ) -> None:
        
        operator = (lambda x: x)  # TODO
        super().__init__(
            operator=operator,
            operands=(name, return_type, args_info, body, header_namespace),
            namespace=namespace)

        # TODO: args for Func(...)
        namespace.declare(name, TypeFunction, Func(return_type)) 

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent) 
        yield "declare func\n"
        yield from super().build_tree(indent + 1)
        yield str(self.operands[1].__name__)
        yield "\n"
        yield from super().build_tree(indent + 1)
        yield str(self.operands[0]) 
        yield "\n"
        for operand in self.operands[2:4]:
            yield from operand.build_tree(indent + 1)

    def semantic_analyze(self) -> None:
        return

    def exec(self) -> None:
        return


class Set(Statement):
    def __init__(self,
                 var: Value,
                 value_to_set: Value | NumericOperation | Call,
                 namespace: TypeNamespace,):
        
        operator = (lambda x: x)  # TODO
        super().__init__(operator=operator,
                         operands=(var, value_to_set),
                         namespace=namespace)

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent)
        yield "=\n"
        for operand in self.operands:
            yield from operand.build_tree(indent + 1)


    def semantic_analyze(self) -> None:
        if (type(self.operands[0]) is MultipleValues):
            ...  # TODO
            return

        token_info = self.operands[0].operands[0]

        try:
            var = self.namespace.get_var(token_info.token)
        except semantics.SemanticError as e:
            print(f"Error on line {token_info.line[0]}:")
            print(f"{token_info.line[1]}")
            print(e, end="\n\n")
            return

        if (var.type is TypeDiscard):
            return

        value_for_set_type = self.operands[1].define_type()

        if (not semantics.are_types_compatible(var.type, value_for_set_type)):
            line = self.operands[0].operands[0].line

            print(f"Error on line {line[0]}:")
            print(f"{line[1]}")
            print(f"Cannot convert type \"{value_for_set_type.name}\" to \"{var.type.name}\".", end="\n\n")
            return


class NumericOperation(Statement):
    def __init__(self,
                 val_1: Statement,
                 val_2: Statement,
                 operation: str):
        
        operator = (lambda x: x)  # TODO
        super().__init__(operator=operator,
                         operands=(val_1, val_2, operation))

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent)
        yield self.operands[2] + "\n"
        for operand in self.operands[:2]:
            yield from operand.build_tree(indent + 1)

    def define_type(self) -> TypeType:
        return TypeNumeric


class Empty(Statement):
    def __init__(self) -> None:
        operator = (lambda: None)
        operands = ()
        super().__init__(
            operator=operator,
            operands=operands)

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield ""

    def semantic_analyze(self) -> None:
        return


class DeclareVar(Statement):
    def __init__(self,
                 var_name: TokenInfo,
                 var_type: TypeType,
                 namespace: TypeNamespace,
                 value: Value | NumericOperation | Call = None):

        operator = (lambda x: x)
        super().__init__(
            operator=operator,
            operands=(var_name, var_type, value),
            namespace=namespace)

        namespace.declare(var_name, var_type, value)


    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent)
        yield "declare var\n"
        yield from super().build_tree(indent + 1)
        yield str(self.operands[0]) + "\n"
        yield from super().build_tree(indent + 1)
        yield str(self.operands[1].__name__) +"\n"
        if (self.operands[2] is not None):
            yield from self.operands[2].build_tree(indent + 1)

    def exec(self) -> None:
        return

    def semantic_analyze(self) -> None:
        var_type = self.operands[1]
        value_type = self.operands[2]

        if (value_type is None):
            value_type = var_type
        else:
            value_type = value_type.define_type()
        
        if (not semantics.are_types_compatible(var_type, value_type)):
            line = self.operands[0].line

            print(f"Error on line {line[0]}")
            print(f"{line[1]}")
            print(f"Cannot convert type \"{value_type.name}\" to \"{var_type.name}\".", end="\n\n")

    def exec(self) -> None:
        return


class DecorateWithType(Statement):
    def __init__(self,
                 decorator_type: TokenInfo,
                 var_declaration: DeclareVar) -> None:

        operator = (lambda: None)
        super().__init__(
            operator=operator,
            operands=(decorator_type, var_declaration))

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent)
        yield "decorate with type\n"
        yield from super().build_tree(indent + 1)
        yield from str(self.operands[0])
        yield "\n"
        yield from self.operands[1].build_tree(indent + 1)


class DeclareVarDefineType(Statement):
    def __init__(self,
                 var_name: TokenInfo,
                 var_value: NumericOperation | Value | Call,
                 namespace: TypeNamespace):
        
        operator = (lambda: None)
        super().__init__(
            operator=operator,
            operands=(var_name, var_value),
            namespace=namespace
        )

        namespace.declare(var_name, var_value.define_type(), var_value)

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent)
        yield "define var define type\n"
        yield from super().build_tree(indent + 1)
        yield str(self.operands[0])
        yield "\n"
        for operand in self.operands[1:]:
            yield from operand.build_tree(indent + 1)


class Loop(Statement):
    def __init__(self,
                 loop_condition: Statement,
                 loop_body: ComplexStatement,
                 namespace: TypeNamespace,
                 loop_var_declaration: DeclareVar | Set = None,
                 loop_iteration_action: Statement = None,
                 loop_header_namespace: TypeNamespace = None):
        
        operator = (lambda: None)
        super().__init__(
            operator=operator,
            operands=(
                loop_condition,
                loop_body,
                namespace,
                loop_var_declaration,
                loop_iteration_action,
                loop_header_namespace)
        )

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent)
        yield "loop\n"
        yield from super().build_tree(indent + 1)
        yield "(\n"
        if (self.operands[3]):
            yield from self.operands[3].build_tree(indent + 1)
        yield from self.operands[0].build_tree(indent + 1)
        if (self.operands[4]):
            yield from self.operands[4].build_tree(indent + 1)
        yield from super().build_tree(indent + 1)
        yield ")\n"
        yield from self.operands[1].build_tree(indent + 1)


class Return(Statement):
    def __init__(self, statement: Statement, namespace: TypeNamespace) -> None:

        operator = lambda: None

        super().__init__(
            operator=operator,
            operands=(statement,),
            namespace=namespace)

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent)
        yield "return\n"
        yield from self.operands[0].build_tree(indent + 1)


class Call(Statement):
    def __init__(self, called: Value, args: MultipleValues, namespace: TypeNamespace):
        operator = lambda: None
        
        super().__init__(
            operator=operator,
            operands=(called, args),
            namespace=namespace
        )

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent)
        yield "call\n"
        for operand in self.operands:
            yield from operand.build_tree(indent + 1)

    def define_type(self) -> TypeType:
        name = self.operands[0].operands[0].token

        var = self.namespace.get_var(name)

        return var.value.return_type


class If(Statement):
    def __init__(self,
                 if_condition: Statement,
                 if_body: ComplexStatement | Statement,
                 namespace: TypeNamespace,
                 else_body: ComplexStatement = None) -> None:
        operator = lambda: None

        super().__init__(
            operator=operator,
            operands=(
                if_condition,
                if_body,
                else_body
            ),
            namespace=namespace
        )

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent)
        yield "if\n"
        yield from self.operands[0].build_tree(indent + 1)
        yield from self.operands[1].build_tree(indent + 1)
        if (self.operands[2]):
            yield from super().build_tree(indent)
            yield "else\n"
            yield from self.operands[2].build_tree(indent + 1)
