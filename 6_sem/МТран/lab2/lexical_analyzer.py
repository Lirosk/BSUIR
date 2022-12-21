import re

from typing import List, Tuple
from sys import argv
from collections import namedtuple
from genericpath import exists

import token_patterns
import tokens


TokenInfo = namedtuple("TokenInfo", ["token", "type"], defaults=["", tokens.Types.NULL])


class LexicalErrorChecker():
    def __init__(self, name_table: List[TokenInfo]):
        self.name_table = name_table
        self.last_token_info: TokenInfo = TokenInfo()
    
    def __is_lexical_error(self, token_info: TokenInfo) -> Tuple[bool, str]:
        _type = token_info.type
        _token: str = token_info.token

        _last_type = self.last_token_info.type
        _last_token = self.last_token_info.token

        incompatible_token_types = [tokens.Types.ID, tokens.Types.CONST]

        if (_type == tokens.Types.ID):
            if (_token not in tokens.data_types and _token not in tokens.reserved_funtions):

                name_table = self.name_table

                if (len(self.name_table) > 1):
                    if (self.name_table[-1] == token_info):
                        name_table = name_table[:-1]

                    if (_last_token not in tokens.data_types):
                        if (token_info not in name_table and token_info.token not in tokens.reserved_ids):
                            return (True, f"Undefined {_type}-token \"{_token}\".")
            
        if (_type in incompatible_token_types and _last_type in incompatible_token_types):
            if (_token not in tokens.data_types and _last_token not in tokens.data_types):
                return (True, f"No operator between {_last_type}-token \"{_last_token}\" and {_type}-token \"{_token}\".")

        if (_type == tokens.Types.CONST):
            if ((_token.startswith("\"") and not _token.endswith("\"")) or \
                (_token.startswith("\'") and not _token.endswith("\'"))):
                return (True, f"End of string constant \"{_token}\" expected.")

        if (_type == tokens.Types.RESERVED):
            if (_token in tokens.bin_operators):
                if (_last_type != tokens.Types.ID and _last_type != tokens.Types.CONST and _last_token != ')'):
                    return (True, f"Missed operand for binary operator \"{_token}\".")
            if (_last_token in tokens.bin_operators and _token != '('):
                return (True, f"Missed operand for binary operator \"{_last_token}\".")

        return (False, "")

    def is_lexical_error(self, token_info: TokenInfo) -> Tuple[bool, str]:
        res = self.__is_lexical_error(token_info)
        self.last_token_info = token_info
        return res 


def identify_type_of_token(token: str) -> tokens.Types:
    if (token in tokens.reserved):
        return tokens.Types.RESERVED

    if re.match(token_patterns.ID_pattern, token):
        return tokens.Types.ID

    if re.match(token_patterns.CONST_pattern, token):
        return tokens.Types.CONST

    if re.match(token_patterns.RESERVED_pattern, token):
        return tokens.Types.RESERVED


def get_name_table(sample_filename: str) -> List[TokenInfo]:
    pattern = re.compile(token_patterns.all_patterns(), re.IGNORECASE)
    
    name_table: List[TokenInfo] = []

    try:
        line_num = 0
        error_checker = LexicalErrorChecker(name_table)

        with open(sample_filename, "r", encoding="UTF-8") as sample:
            while ((line := sample.readline())):
                line = line.strip()
                line_num += 1

                tokens: List[str] = re.findall(pattern, line)

                for token in tokens:
                    if token.startswith(r"//"):
                        continue

                    token = token.strip()

                    type = identify_type_of_token(token)
                    token_info = TokenInfo(token, type)

                    name_table.append(token_info)

                    is_error, message = error_checker.is_lexical_error(token_info)

                    if is_error:
                        print(f"Error on line {line_num}:")
                        print(line)
                        print(message, end='\n\n')
        
    except Exception as e:
        e.with_traceback()

    return name_table

if __name__ == '__main__':
    _, *args = argv

    if len(args) != 1:
        file = ".\sample\Program.cs"
        if not exists(".\sample\Program.cs"):
            print("Specify file for analyze as parameter.")
            exit(-1)

        args = (file,)

    name_table = get_name_table(*args)
    print("-" * 36)
    print(f"| {'Token':<18}| {'Type':<12} |")
    print("-" * 36)
    for token in name_table:
        print(f"| {token.token:<18}| {token.type:<12} |")
        print("-"*36)
