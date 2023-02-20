import re

from typing import List, Tuple
from sys import argv
from genericpath import exists


import token_patterns
import tokens

from models import TokenInfo, TokenTypes


class LexicalErrorChecker():
    def __init__(self, name_table: List[TokenInfo]):
        self.name_table = name_table
        self.last_token_info: TokenInfo = TokenInfo()
    
    def __is_lexical_error(self, token_info: TokenInfo) -> Tuple[bool, str]:
        _type = token_info.type
        _token: str = token_info.token

        _last_type = self.last_token_info.type
        _last_token = self.last_token_info.token

        incompatible_token_types = [TokenTypes.ID, TokenTypes.CONST]

        if (_type == TokenTypes.ID):
            if (_token not in tokens.reserved_data_types):

                name_table = self.name_table

                if (len(self.name_table) > 1):
                    if (self.name_table[-1] == token_info):
                        name_table = name_table[:-1]

                    if (_last_token not in tokens.reserved_data_types):
                        if (token_info not in name_table and token_info.token not in tokens.reserved_ids):
                            return (True, f"Undefined {_type}-token \"{_token}\".")
            
        if (_type in incompatible_token_types and _last_type in incompatible_token_types):
            if (_token not in tokens.reserved_data_types and _last_token not in tokens.reserved_data_types):
                return (True, f"No operator between {_last_type}-token \"{_last_token}\" and {_type}-token \"{_token}\".")

        if (_type == TokenTypes.CONST):
            if ((_token.startswith("\"") and not _token.endswith("\"")) or \
                (_token.startswith("\'") and not _token.endswith("\'"))):
                return (True, f"End of string constant \"{_token}\" expected.")

        if (_type == TokenTypes.RESERVED):
            if (_token in tokens.bin_operators):
                if (_last_type != TokenTypes.ID and _last_type != TokenTypes.CONST and _last_token != ')'):
                    return (True, f"Missed operand for binary operator \"{_token}\".")
            if (_last_token in tokens.bin_operators and _token != '('):
                return (True, f"Missed operand for binary operator \"{_last_token}\".")

        return (False, "")

    def is_lexical_error(self, token_info: TokenInfo) -> Tuple[bool, str]:
        res = self.__is_lexical_error(token_info)
        self.last_token_info = token_info
        return res 


def identify_type_of_token(token: str) -> TokenTypes:
    if (token in tokens.reserved):
        return TokenTypes.RESERVED

    if re.match(token_patterns.ID_pattern, token):
        return TokenTypes.ID

    if re.match(token_patterns.CONST_pattern, token):
        return TokenTypes.CONST

    if re.match(token_patterns.RESERVED_pattern, token):
        return TokenTypes.RESERVED


def get_name_table(sample_filename: str) -> List[TokenInfo]:
    def check_error(token_info):
        is_error, message = error_checker.is_lexical_error(token_info)

        if is_error:
            print(f"Error on line {line_num}:")
            print(line)
            print(message, end='\n\n')

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
                    token_info = TokenInfo(token, type, (line_num, line))
                    name_table.append(token_info)

                    # "a *= b" to "a = a * b"
                    if (token.endswith("=") and len(token) > 1 and token not in ["!=", "==", ">=", "<="]):
                        name_table.pop()
                        var_token = name_table[-1]
                        name_table.append(TokenInfo(token[-1], type, (line_num, line)))
                        check_error(token_info)
                        name_table.append(var_token)
                        check_error(token_info)
                        name_table.append(TokenInfo(token[:-1], type, (line_num, line)))

                    check_error(token_info)                    
        
    except Exception as e:
        e.with_traceback()

    name_table.append(TokenInfo(type=TokenTypes.EOF, line=(line_num, line)))

    return name_table

def main() -> Tuple[TokenInfo]:
    _, *args = argv

    if len(args) != 1:
        file = ".\sample\Program.cs"
        if not exists(".\sample\Program.cs"):
            print("Specify file for analyze as parameter.")
            exit(-1)

        args = (file,)

    name_table = get_name_table(*args)
    return tuple(name_table)


if __name__ == '__main__':
    name_table = main()

    print("-" * 36)
    print(f"| {'Token':<18}| {'Type':<12} |")
    print("-" * 36)
    for token in name_table:
        print(f"| {token.token:<18}| {token.type:<12} |")
        print("-"*36)
