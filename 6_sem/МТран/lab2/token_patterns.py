COMMENT_patterns = [
    # comments  
    r"//.*",
]
COMMENT_pattern = '|'.join(COMMENT_patterns)


ID_patterns = [
    # id-tokens
    r'[_a-zA-Z]\w*',
]
ID_pattern = '|'.join(ID_patterns)


CONST_patterns = [
    # const numbers with 'u', 'l' or 'ul' postfixes and float const tokens
    r"\d+(?:ul|[ul]|(?:\.?\d+)?(?:e?\d+)?[fdm]?)?",
    
    # str-consts closed and not
    r"\".*?[^\\]\"|\".*",
]
CONST_pattern = '|'.join(CONST_patterns)


RESERVED_patterns = [
    # inc | dec
    r"\+\+|\-\-",

    # operator tokens
    r"[\+\-\*\/\^\%\|\=\!\<\>]=?",

    # tokens
    r"[\;\(\)\.\,\{\}]", 
]
RESERVED_pattern = '|'.join(RESERVED_patterns)

def all_patterns():
    return '|'.join([
                COMMENT_pattern,
                ID_pattern,
                CONST_pattern,
                RESERVED_pattern])
