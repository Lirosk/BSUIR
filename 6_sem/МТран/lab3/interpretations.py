from typing import List, Tuple, Any

import statements
import tokens

from models import NameTableStream, TokenInfo, TokenTypes
from data_types import TypeNamespace

class Interpretation:
    def interpret(nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        return None


class Value(Interpretation):
    def __init__(self, token_info: TokenInfo):
        self.token_info = token_info

    def interpret(self, nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        context.append(statements.Value(self.token_info))


class BinaryOperation(Interpretation):
    def __init__(self, operation: statements.Statement, *operation_args: Tuple[Any]):
        self.operation = operation
        self.operation_args = operation_args

    def interpret(self, nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        val_1 = context.pop()

        tokens.interpret_tokens_until(
            until_next=(lambda token_info: token_info.token in [";", ")"]), 
            nametable=nametable,
            context=context,
            namespace=namespace)

        val_2 = context.pop()
        
        if (self.operation is statements.Set):
            self.operation_args = (namespace, )
        context.append(self.operation(val_1, val_2, *self.operation_args))


class NumericOperation(BinaryOperation):
    def __init__(self, operation: str):
        super().__init__(statements.NumericOperation, operation)


class End(Interpretation):
    def interpret(nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        context.append(statements.Empty())


class DeclareVar(Interpretation):
    def __init__(self, var_type_token: TokenInfo):
        self.var_type_token = var_type_token

    def interpret(self, nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        var_name = nametable.next()

        next_token = nametable.peek().token
        match next_token:
            case "=":
                nametable.next()
                tokens.interpret_tokens_until(
                    until_next=(lambda token_info: token_info.token == ';'),
                    nametable=nametable,
                    context=context,
                    namespace=namespace
                )

                value_to_set = context.pop()

                context.append(
                    statements.DeclareVar(
                        var_name=var_name,
                        var_type=self.var_type_token,
                        value=value_to_set,
                        namespace=namespace))

                return
            case "(":
                # define func
                header_namespace = TypeNamespace(parent=namespace)

                # read params
                tokens.interpret_token(nametable.next(), nametable, context, header_namespace)
                args_multi_value = context.pop()

                # read body
                tokens.interpret_token(nametable.next(), nametable, context, header_namespace)
                body = context.pop()

                context.append(
                    statements.DeclareFunc(
                        name=var_name,
                        return_type=self.var_type_token,
                        args_info=args_multi_value,
                        body=body,
                        header_namespace=header_namespace,
                        namespace=namespace))

                return

        #case ";":
        value_to_set = statements.Value(TokenInfo())  # TODO

        context.append(
            statements.DeclareVar(
                var_name=var_name,
                var_type=self.var_type_token,
                value=value_to_set,
                namespace=namespace))


class DecorateWithType(Interpretation):
    def __init__(self, decorator: TokenInfo):
        self.decorator = decorator

    def interpret(self, nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        tokens.interpret_token(nametable.next(), nametable, context, namespace)
        var_declaration = context.pop()

        context.append(
            statements.DecorateWithType(
                decorator_type=self.decorator,
                var_declaration=var_declaration))


class DeclareVarDefineType:
    def interpret(nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        var_name = nametable.next().token

        # read "="
        nametable.next()

        tokens.interpret_tokens_until(
            until_next=(lambda token_info: token_info.token in [";", ","]),
            nametable=nametable,
            context=context,
            namespace=namespace,
        )

        value = context.pop()

        context.append(statements.DeclareVarDefineType(var_name, value, namespace))


class MultipleValueOrFuncCall(Interpretation):
    def interpret(nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        values = []

        tokens.interpret_tokens_until(
            until_next=(lambda token_info: token_info.token == ")"),
            nametable=nametable,
            context=values,
            namespace=namespace
        )

        # read ")"
        nametable.next()

        multiple_values = statements.MultipleValues(tuple(values))

        if (len(context) > 0):
            if type(context[-1]) is statements.Value:                    
                args = multiple_values
                called = context.pop()

                context.append(
                    statements.Call(
                        called=called,
                        args=args,
                        namespace=namespace
                    )
                )

                return

        context.append(multiple_values)


class ForLoop(Interpretation):
    def interpret(nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        loop_header_namespace = TypeNamespace(parent=namespace)

        nametable.next()
        tokens.interpret_tokens_until(
            until_next=(lambda token_info: token_info.token == ";"),
            nametable=nametable,
            context=context,
            namespace=loop_header_namespace
        )
        loop_var_declaration = context.pop()

        nametable.next()
        tokens.interpret_tokens_until(
            until_next=(lambda token_info: token_info.token == ";"),
            nametable=nametable,
            context=context,
            namespace=loop_header_namespace
        )
        loop_condition = context.pop()

        nametable.next()
        tokens.interpret_tokens_until(
            until_next=(lambda token_info: token_info.token == ")"),
            nametable=nametable,
            context=context,
            namespace=loop_header_namespace
        )
        loop_iteration_action = context.pop()

        nametable.next()

        if (nametable.peek().token == '{'):
            tokens.interpret_token(
                nametable.next(),
                nametable,
                context,
                loop_header_namespace)
        else:
            tokens.interpret_tokens_until(
                until_next=(lambda token_info: token_info.token == ';'),
                nametable=nametable,
                contetxt=context,
                namespace=loop_header_namespace
            )

        loop_body = context.pop()

        context.append(
            statements.Loop(
                loop_condition=loop_condition,
                loop_body=loop_body,
                namespace=namespace,
                loop_var_declaration=loop_var_declaration,
                loop_iteration_action=loop_iteration_action,
                loop_header_namespace=loop_header_namespace
            ))


class ComplexStatement(Interpretation):
    def interpret(nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        body_namespace = TypeNamespace(parent=namespace)

        body_statemets = []

        tokens.interpret_tokens_until(
            until_next=(lambda token_info: token_info.token == '}'),
            nametable=nametable,
            context=body_statemets,
            namespace=body_namespace
        )
        # read "}"
        nametable.next()

        context.append(
            statements.ComplexStatement(
                tuple(body_statemets),
                namespace,
                body_namespace
            )
        )


class Increment(Interpretation):
    def interpret(nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        var = context.pop()

        context.append(
            statements.Set(
                var=var,
                value_to_set=statements.NumericOperation(
                    val_1=var,
                    val_2=statements.Value(
                        TokenInfo("1", TokenTypes.CONST)
                    ),
                    operation="+",
                ),
                namespace=namespace
            )
        )

        # context.append(var)


class Decrement(Interpretation):
    def interpret(nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        var = context.pop()

        context.append(
            statements.Set(
                var=var,
                value_to_set=statements.NumericOperation(
                    val_1=var,
                    val_2=statements.Value(TokenInfo("1", type=TokenTypes.CONST)),
                    operation="-",
                ),
                namespace=namespace
            )
        )

        # context.append(var)


class WhileLoop(Interpretation):
    def interpret(nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:

        # read "("
        nametable.next()
        tokens.interpret_tokens_until(
            until_next=(lambda token_info: token_info.token == ")"),
            nametable=nametable,
            context=context,
            namespace=namespace
        )
        loop_condition = context.pop()

        # read ")"
        nametable.next()

        if (nametable.peek().token == '{'):
            tokens.interpret_token(
                nametable.next(),
                nametable,
                context,
                namespace)
        else:
            tokens.interpret_tokens_until(
                until_next=(lambda token_info: token_info.token == ';'),
                nametable=nametable,
                context=context,
                namespace=namespace
            )

        loop_body = context.pop()

        context.append(
            statements.Loop(
                loop_condition=loop_condition,
                loop_body=loop_body,
                namespace=namespace,
            ))


class Return(Interpretation):
    def interpret(nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        
        tokens.interpret_tokens_until(
            until_next=(lambda token_info: token_info.token == ";"),
            nametable=nametable,
            context=context,
            namespace=namespace
        )

        statement = context.pop()

        context.append(
            statements.Return(
                statement=statement,
                namespace=namespace)
        )


class If(Interpretation):
    def interpret(nametable: NameTableStream, context: List[statements.Statement], namespace: TypeNamespace) -> None:
        
        # read "("
        nametable.next()

        tokens.interpret_tokens_until(
            until_next=(lambda token_info: token_info.token == ")"),
            nametable=nametable,
            context=context,
            namespace=namespace
        )

        # read ")"
        nametable.next()

        condition = context.pop()

        if (nametable.peek().token == "{"):
            # interpret "{"
            tokens.interpret_token(
                nametable.next(),
                nametable,
                context,
                namespace
            )
        else:
            tokens.interpret_tokens_until(
                until_next=(lambda token_info: token_info.token == ";"),
                nametable=nametable,
                context=context,
                namespace=namespace
            )
            # read ";"
            nametable.next()

        if_body = context.pop()
        else_body = None

        peeked = nametable.peek()
        if (peeked and peeked.token == "else"):
            # read "else"
            nametable.next()

            match nametable.peek().token:
                case "{" | "if":
                    tokens.interpret_token(
                        nametable.next(),
                        nametable,
                        context,
                        namespace
                    )
                case _:
                    tokens.interpret_tokens_until(
                        until_next=(lambda token_info: token_info.token == ";"),
                        nametable=nametable,
                        context=context,
                        namespace=namespace
                    )
            
            else_body = context.pop()

        context.append(
            statements.If(
                if_condition=condition,
                if_body=if_body,
                else_body=else_body,
                namespace=namespace
            )
        )


class Error(Interpretation):
    def __init__(self, msg):
        self.msg = msg
    
    def interpret(self, *args):
        raise InterpretationError(self.msg + "\n")
        

class InterpretationError(Exception):
    def __init__(self, *args: object, _break = False) -> None:
        super().__init__(*args)
        self._break = _break