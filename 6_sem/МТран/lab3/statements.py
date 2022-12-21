from __future__ import annotations
from typing import Tuple, Callable, Iterator

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

    def exec(self):
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



class Value(Statement):
    def __init__(self,
                 var_name_or_const: str):

        operator = (lambda var_or_const: var_or_const)
        super().__init__(
            operator=operator,
            operands=(var_name_or_const,))


    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent)
        yield repr(self.operands[0])
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
        
        
class DeclareFunc(Statement):
    def __init__(self,
                 name: str,
                 return_type: TokenInfo,
                 args_info: MultipleValues | DeclareVar | Empty,
                 body: ComplexStatement,
                 header_namespace: TypeNamespace,
                 namespace: TypeNamespace,
                 #args_defaults: Tuple(None | TypeObject) = None,
                 ) -> None:
        
        operator = (lambda x: x)  # TODO
        #super.__init__(operands=(name, return_type, arg_names, arg_types, body, namespace, arg_defaults))
        super().__init__(
            operator=operator,
            operands=(name, return_type, args_info, body, header_namespace),
            namespace=namespace)

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent) 
        yield "declare func\n"
        yield from super().build_tree(indent + 1)
        yield repr(self.operands[1])
        yield "\n"
        yield from super().build_tree(indent + 1)
        yield repr(self.operands[0]) 
        yield "\n"
        for operand in self.operands[2:4]:
            yield from operand.build_tree(indent + 1)




class Set(Statement):
    def __init__(self,
                 var: Value,
                 value_to_set: Statement,
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


class Empty(Statement):
    def __init__(self) -> None:
        operator = (lambda: None)
        operands = ()
        super().__init__(
            operator=operator,
            operands=operands)

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield ""


class DeclareVar(Statement):
    def __init__(self,
                 var_name: str,
                 var_type: TokenInfo,
                 value: Statement,
                 namespace: TypeNamespace):
        
        operator = (lambda x: x)
        super().__init__(
            operator=operator,
            operands=(var_name, var_type, value),
            namespace=namespace)

    def build_tree(self, indent: int = 0) -> Iterator[str]:
        yield from super().build_tree(indent)
        yield "declare var\n"
        yield from super().build_tree(indent + 1)
        yield repr(self.operands[0])
        yield "\n"
        yield from super().build_tree(indent + 1)
        yield repr(self.operands[1])
        yield "\n"
        yield from self.operands[2].build_tree(indent + 1)


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
        yield from repr(self.operands[0])
        yield "\n"
        yield from self.operands[1].build_tree(indent + 1)


class DeclareVarDefineType(Statement):
    def __init__(self,
                 var_name: str,
                 var_value: Statement,
                 namespace: TypeNamespace):
        
        operator = (lambda: None)
        super().__init__(
            operator=operator,
            operands=(var_name, var_value),
            namespace=namespace
        )

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
