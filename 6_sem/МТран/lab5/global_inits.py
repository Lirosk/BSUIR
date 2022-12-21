from data_types import *
from statements import *
from models import TokenInfo, TokenTypes

def main():
    define_WriteLine()

def define_WriteLine():
    header_namespace = TypeNamespace(parent=NamespaceGlobal())
    body_namespace = TypeNamespace(parent=header_namespace)

    obj_arg_token = TokenInfo("obj", TokenTypes.ID)

    declare_arg = DeclareVar(
        var_name=obj_arg_token,
        var_type=TypeObject,
        namespace=header_namespace)

    args_info = MultipleValues((declare_arg, ))

    body_namespace=header_namespace
    body_statements = (
        Print(
            operands= (Value(obj_arg_token,body_namespace),),
            namespace=header_namespace.parent
        ),
    )

    body = ComplexStatement(
        body_statements=body_statements,
        body_namespace=body_namespace,
        namespace=header_namespace)

    DeclareFunc(
        name=TokenInfo("WriteLine", TokenTypes.ID),
        return_type=TypeVoid,
        args_info=args_info,
        body=body,
        header_namespace=header_namespace,
        namespace=NamespaceGlobal()
    )

