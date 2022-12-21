from typing import List

import lexical_analyzer
import tokens

from statements import Statement, ComplexStatement
from models import NameTableStream, TokenTypes
from data_types import NamespaceGlobal, TypeNamespace


def build_statement(nametable: NameTableStream) -> Statement:
    global_namespace = NamespaceGlobal()
    body_namespace = TypeNamespace(parent=global_namespace)

    statements = []
    tokens.interpret_tokens_until(
        until_next = (lambda token_info: token_info.type == TokenTypes.EOF),
        nametable=nametable,
        context=statements,
        namespace=global_namespace,
    )
    
    statement = ComplexStatement(statements, body_namespace, global_namespace)
    for _ in statement.build_tree():
        print(_, end="")

    return statements


def main():
    name_table = NameTableStream(lexical_analyzer.main())
    statement = build_statement(name_table)

    return statement


if __name__ == '__main__':
    main()
