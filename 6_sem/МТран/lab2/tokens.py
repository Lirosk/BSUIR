class Types:
    NULL = ""
    ID = "ID"
    CONST = "CONST"
    RESERVED = "RESERVED"


reserved_funtions = [
    
]

# ... for interpreter pattern
data_types = {
    r"var": ...,
    r"float": ...,
    r"double": ...,
    r"int": ...,
    r"long": ...,
    r"const": ...,
    r"unsigned": ...,
    r"byte": ...,
    r"sbyte": ...,
    r"uint" : ...,
    r"ulong" : ...,
}

reserved_ids = {
    r"_" : ...,
}

reserved = {
    r";" : ...,
    r"//": ...,
    r"{" : ...,
    r"}" : ...,
    r")" : ...,
    r"(" : ...,
    r"{" : ...,
    r"}" : ...,
    r"\'": ...,
    r"\"": ...,
    r"," : ...,
    r"." : ...,
    r"return" : ...,
    r"while": ...,
    r"if": ...,
    r"else": ...,
    r"for": ...,
}

un_ops = {
    r"++": ...,
    r"--": ...,
}

bin_operators = {
    r">" : ...,
    r"<" : ...,
    r"+" : ...,
    r"-" : ...,
    r"/" : ...,
    r"*" : ...,
    r"^" : ...,
    r"|" : ...,
    r"&" : ...,

    r"=" : ...,
    r">=": ...,
    r"<=": ...,
    r"+=": ...,
    r"-=": ...,
    r"/=": ...,
    r"*=": ...,
    r"^=": ...,
    r"|=": ...,
    r"&=": ...,
}