from ast import parse
import inspect
import functools
import re
import textwrap
from typing import Callable, Union

class jsonserializer:
    @staticmethod
    def loads(s: str) -> dict:
        s = jsonserializer.prep_str(s)
        res = jsonserializer.parse_instance(s)
        return res

    @staticmethod
    def dumps(obj: object, /, *, indent: int = 0) -> str:
        if inspect.isclass(obj):
            obj = obj()            
        res = jsonserializer.serialize_instance(obj, 0, indent)
        return res

    def parse_dict(s: str) -> Union[dict, Callable]:
        # pattern = re.compile(r' ?{[\"\']<(\w+)>[\"\']:')#re.compile(r' ?{[\"\']<(\w+)>[\"\']:[\"\'](.+)[\"\']}$')
        # r = re.findall(pattern, s)

        i = s.index(':')

        if (s[i-8:i-2] == 'lambda'):#if (r[0][0] == 'lambda'):
            res = jsonserializer.parse_lambda(s[i+2:-2])
            return res
        elif(s[i-10:i-2] == 'function'):#elif(r[0][0] == 'function'):
            res = jsonserializer.parse_func(s[i+2:-2])[0]
            return res

        b1: int = 0
        b2: int = 0
        bf: int = 0
        bs: int = 0

        last: int = 1

        res: dict = {}

        key: object = None
        value: object = None

        i: int = 1
        l = len(s)

        while i < l:
            if (s[i] == '\"'):
                b1 += 1
            elif (s[i] == '\''):
                b2 += 2
            elif (not b1%2 and not b2%2):
                b1 = 0
                b2 = 0
                if s[i] == '{':
                    bf += 1
                elif s[i] == '}':
                    bf -= 1
                elif s[i] == '[':
                    bs += 1
                elif s[i] == ']':
                    bs -= 1

                if (not bf or bf == -1) and not bs:
                    if s[i] == ':':
                        key = jsonserializer.parse_instance(s[last:i])
                        last = i + 1
                    elif s[i] == ',' or (s[i] == '}' and bf == -1):
                        value = jsonserializer.parse_instance(s[last:i])
                        last = i + 1
                        res[key] = value
                        key = None
                        value = None
            i += 1
        return res

    def parse_list(s: str) -> list:
        b1: int = 0
        b2: int = 0
        bf: int = 0
        bs: int = 0

        l: int = len(s)
        i: int = 1

        last: int = 1

        res: list = []

        while i < l:
            if s[i] == '\"':
                b1 += 1
            elif s[i] == '\'':
                b2 += 1
            elif (not b1%2 and not b2%2):
                b1 = 0
                b2 = 0
                if s[i] == '{':
                    bf += 1
                elif s[i] == '}':
                    bf -= 1
                elif s[i] == '[':
                    bs += 1
                elif s[i] == ']':
                    bs -= 1
                    if bs == -1:
                        res.append(jsonserializer.parse_instance(s[last:i]))
                elif s[i] == ',':
                    if (not bf
                    and not bs):
                        res.append(jsonserializer.parse_instance(s[last:i]))
                        last = i + 1                    
            i += 1
        return res

    def parse_instance(s: str) -> object:
        if s[0] == '{':
            return jsonserializer.parse_dict(s)
        elif s[0] == '[':
            return jsonserializer.parse_list(s)
        elif s[0] == '\"' or s[0] == '\'':
            return s[1:-1]
        
        n = float(s)
        if float(int(n)) == float(n):
            return int(n)
        return n

    def prep_str(s: str) -> str:
        d = s
        b1: int = 0
        b2: int = 0
        l = len(d)
        i = 0
        while i < l:
            if d[i] == '\"':
                b1 += 1
            elif d[i] == '\'':
                b2 += 1
            elif (d[i] == ' ') or (d[i] == '\n') or (d[i] == '\t'):
                if (not b1 % 2
                and not b2 % 2):
                    d = d[:i] + d[i+1:]
                    i -= 1
                    l -= 1
            i += 1
        return d

    @staticmethod
    def isLambda(obj: object) -> bool:
        if inspect.isfunction(obj):
            if obj.__name__ == '<lambda>':
                return True
        return False

    @staticmethod
    def isFunction(obj: object) -> bool:
        return inspect.isfunction(obj)

    @staticmethod
    def isDictionary(obj: object) -> bool:
        res = isinstance(obj, dict)
        return res

    @staticmethod
    def isEnumerable(obj: object) -> bool:
        enumerable = (list, tuple, range, set, frozenset)
        res = isinstance(obj, enumerable)
        return res

    @staticmethod
    def isPrimitive(obj: object) -> bool:
        primitive = (int, float, str, bool, complex)
        res = isinstance(obj, primitive)
        return res

    @staticmethod
    def write_indent(depth: int, indent: int) -> str:
        if indent:
            return ('\n' + (' ' * depth * indent))
        return ""

    @staticmethod
    def serialize_enumerable(obj: list, depth: int = 0, indent: int = 0, /) -> str:
        res = "["
        for i in obj:
            res += jsonserializer.write_indent(depth + 1, indent)
            #if in quotes
            buf = jsonserializer.serialize_instance(i, depth + 1, indent)
            #if in quotes
            if isinstance(i, str):
                res += f'"{buf}"'
            else:
                res += buf
            res += ', '
        #remove last comma
        res = res[:-2]
        res += jsonserializer.write_indent(depth, indent)
        res += ']'
        return res

    @staticmethod
    def serialize_dict(obj: dict, depth: int = 0, class_obj: object = None, /, *, indent: int = 0) -> str:
        res = "{"
        for i in obj:
            res += jsonserializer.write_indent(depth, indent)
            #key
            buf = jsonserializer.serialize_instance(i, depth, indent)
            #if in quotes
            if (jsonserializer.isPrimitive(i)):
                res += f'"{buf}"'
            else:
                res += buf
            res += ':'                
            #space for butifulness
            res += ' '
            #value
            buf = jsonserializer.serialize_instance(obj[i], depth, indent)
            #if in quotes
            if(isinstance(obj[i], str)):
                res += f'"{buf}"'
            else:
                res += buf
            res += ', '

        if (class_obj is not None):
            method_list = [
                getattr(class_obj, attribute)
                for attribute in dir(class_obj) 
                if callable(getattr(class_obj, attribute)) and not attribute.startswith('__')
                ]

            if (method_list):
                for i in method_list:
                    if i.__name__ == '<lambda>':
                        res += jsonserializer.serialize_lambda(i, depth, indent)
                    else:
                        res += jsonserializer.serialize_function(i, depth, indent)
                    res += ', '

        #remove last comma
        res = res[:-2]
        res += jsonserializer.write_indent(depth - 1, indent) + '}'
        return res

    @staticmethod
    def serialize_function(obj: object, depth = 0, indent = 0, /) -> str:
        key = "<function>"
        name = obj.__name__
        value = inspect.getsource(obj)
        d = '{' + f'\"{key}\":\"{value}\"' + '}'
        res = f"{jsonserializer.write_indent(depth, indent)}\"{name}\": {d}"
        return res

    @staticmethod
    def serialize_lambda(obj: object, depth = 0, indent = 0, /) -> str:
        key = "<lambda>"
        obj = inspect.getsource(obj)
        name = obj.split('=')[0]
        value = obj[len(name) + 2:]
        value = functools.reduce(str.__add__, value)
        name = name.split()[0]
        if (value[-1] == '\n'):
            value = value[:-1]
        if (value[0] == ' '):
            value = value[1:]
        d = '{' + f'\"{key}\":\"{value}\"' + '}'
        res = f"{jsonserializer.write_indent(depth, indent)}\"{name}\": {d}"
        return res
            

    def serialize_instance(obj: object, depth: int = 0, indent: int = 0, /) -> str:
        res: str = ""
        if (jsonserializer.isPrimitive(obj)):
            res += f'{str(obj)}'
        elif (jsonserializer.isEnumerable(obj)):
            res += jsonserializer.serialize_enumerable(obj, depth, indent)
        elif (jsonserializer.isDictionary(obj)):
            res += jsonserializer.serialize_dict(obj, depth + 1, indent=indent)
        elif (jsonserializer.isLambda(obj)):
            res += jsonserializer.serialize_lambda(obj)
        elif (jsonserializer.isFunction(obj)):
            res += jsonserializer.serialize_function(obj, depth + 1, indent)
        else:
            vs = vars(obj)
            res += jsonserializer.serialize_dict(vs, depth + 1, obj, indent=indent)

        return res

    def parse_func(s: str) -> Callable:
        s = textwrap.dedent(s)
        pattern = re.compile(r'@\w+\n')
        decorators = re.findall(pattern, s)

        for i in range(len(decorators)):
            decorators[i] = re.sub(f'\n', '', decorators[i])

        s = re.sub(pattern, '', s)
        name = re.findall(r'^def (\w+)\(.*\).*:\s', s)
        name = name[0]
        exec(f"{s}\nglobal f\nf = {name}\n")
        res = f
        return res, decorators

    def parse_lambda(s: str) -> Callable:
        exec(f"global _l\n_l ={s}\n")
        res = _l
        return res