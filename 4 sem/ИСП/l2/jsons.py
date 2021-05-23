import inspect
import types
from typing import Union
import logging
import utility

_primitive = (int, float, str, bool, complex, type(None))
_enumerable = (list, tuple, range, set, frozenset)
_functions_serialized = {}

def load(file: str) -> object:
    logging.debug("jsons.load starts.")

    with open(file, 'r') as f:
        s = f.read()
        res = loads(s)

        logging.debug("jsons.load ends.")
        return res


def loads(s: str) -> object:
    logging.debug("jsons.loads starts.")

    s = _prep_str(s)
    res = _parse_instance(s)

    logging.debug("jsons.loads ends.")
    return res


def dump(file: str, obj: object, indent: int = 0) -> None:
    logging.debug("jsons.dump starts.")

    with open(file, 'w') as f:
        f.seek(0)
        f.truncate()
        f.seek(0)

        res = dumps(obj, indent = indent)
        f.write(res)
    
    logging.debug("jsons.jsons.dump ends.")


def dumps(obj: object, /, *, indent: int = 0) -> str:
    logging.debug("jsons.dumps starts.")
       
    res = _serialize_instance(obj, 0, indent)
    utility.clear()

    logging.debug("jsons.dumps ends.")
    return res    


def _parse_dict(s: str) -> Union[dict, types.FunctionType, types.CodeType, types.ModuleType]:
    logging.debug("jsons.parse_dict starts.")

    if (s == "{}"):
        logging.debug("jsons.parse_dict ends.")
        return {}

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
                    key = _parse_instance(s[last:i])
                    last = i + 1
                elif s[i] == ',' or (s[i] == '}' and bf == -1):
                    value = _parse_instance(s[last:i])
                    last = i + 1
                    res[key] = value
                    key = None
                    value = None
        i += 1

    logging.debug("jsons.parse_dict ends.")
    return res

def _parse_list(s: str) -> list:
    logging.debug("jsons.parse_list starts.")

    if s == '[]':
        logging.debug("jsons.parse_list ends.")
        return []

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
                    res.append(_parse_instance(s[last:i]))
            elif s[i] == ',':
                if (not bf
                and not bs):
                    res.append(_parse_instance(s[last:i]))
                    last = i + 1                    
        i += 1

    logging.debug("jsons.parse_list ends.")
    return res


def _parse_instance(s: str) -> object:
    logging.debug("jsons.parse_instance starts.")

    try:
        if s[0] == '"':
            obj = s[1:-1]
        elif s[0].isdigit() or (s[0] == "-" and s[1].isdigit()):
            if '.' in s:
                obj = float(s)
            else:
                obj = int(s)
        elif s[0] == "{":
            obj = utility.unpack_instance(_parse_dict(s))
        elif s[0] == "[":
            obj = _parse_list(s)
        elif s[0] == "t" and s[:4] == "true":
            obj = True
        elif s[0] == "f" and s[:5] == "false":
            obj = False
        elif s[0] == "N" and s[:3] == "NaN":
            obj = False
        elif s[0] == "I" and s[:8] == "Infinity":
            obj = float("Infinity")
        elif s[0] == "-" and s[:9] == "-Infinity":
            obj = float("-Infinity")
        else:
            return None
    except IndexError:
        obj = None

    logging.debug("jsons.parse_instance ends.")
    return obj


def _serialize_instance(obj: object, depth: int = 0, indent: int = 0, /) -> str:
    logging.debug("jsons.serialize_instance starts.")

    res: str = ""
    if (_isPrimitive(obj)):
        if obj is True:
            res += "true"
        elif obj is False:
            res += "false"
        else:
            res += f'{str(obj)}'
    elif (_isEnumerable(obj)):
        res += _serialize_enumerable(obj, depth, indent)
    elif (isinstance(obj, bytes)):
        return str(list(bytearray(obj)))
    elif (_isDictionary(obj)):
        res += _serialize_dict(obj, depth + 1, indent)
    elif (_isFunction(obj)):
        res += _serialize_dict(utility.function_to_dict(obj), depth + 1, indent)
        global _functions_serialized
        _functions_serialized = {}
    elif (inspect.ismodule(obj)):
        res += _serialize_dict(utility.module_to_dict(obj), depth + 1, indent)
    elif (isinstance(obj, types.CodeType)):
        res += _serialize_dict(utility.code_to_dict(obj), depth + 1, indent)
    elif (inspect.isclass(obj)):
        res += _serialize_dict(utility.class_to_dict(obj), depth + 1, indent)
    elif (utility.is_class_instance(obj)):
        res += _serialize_dict(utility.instance_to_dict(obj), depth + 1, indent)
    else:
        res += "null"

    logging.debug("jsons.serialize_instance ends.")
    return res


def _serialize_enumerable(obj: list, depth: int = 0, indent: int = 0, /) -> str:
    logging.debug("jsons.serialize_enumerable starts.")

    if (not obj):
        logging.debug("jsons.serialize_enumerable ends.")
        return "[]"

    res = "["
    for i in obj:
        res += _write_indent(depth + 1, indent)
        #if in quotes
        buf = _serialize_instance(i, depth + 1, indent)
        #if in quotes
        if isinstance(i, str):
            res += f'"{buf}"'
        else:
            res += buf
        res += ', '
    #remove last comma
    res = res[:-2]
    res += _write_indent(depth, indent)
    res += ']'

    logging.debug("jsons.serialize_enumerable ends.")
    return res


def _serialize_dict(obj: dict, depth: int = 0, indent: int = 0) -> str:
    logging.debug("jsons.serialize_dict starts.")

    if (not obj):
        logging.debug("jsons.serialize_dict ends.")
        return r"{}"

    res = "{"
    for i in obj:
        res += _write_indent(depth, indent)
        #key
        buf = _serialize_instance(i, depth, indent)
        #if in quotes
        if (_isPrimitive(i)):
            res += f'"{buf}"'
        else:
            res += buf
        res += ':'                
        #space for butifulness
        res += ' '
        #value
        try:
            buf = _serialize_instance(obj[i], depth, indent)
        except TypeError:
            print(obj[i])
        try:
            buf = _serialize_instance(obj[i], depth, indent)
        except TypeError:
            pass
        #if in quotes
        if(isinstance(obj[i], str)):
            res += f'"{buf}"'
        else:
            res += buf
        res += ', '

    #remove last comma
    res = res[:-2]
    res += _write_indent(depth - 1, indent) + '}'
    logging.debug("jsons.serialize_dict ends.")
    return res


def _prep_str(s: str) -> str:
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


def _write_indent(depth: int, indent: int) -> str:
    if indent:
        return ('\n' + (' ' * depth * indent))
    return ""


def _isFunction(obj: object) -> bool:
    return isinstance(obj, types.FunctionType)


def _isDictionary(obj: object) -> bool:
    res = isinstance(obj, dict)
    return res


def _isEnumerable(obj: object) -> bool:
    res = isinstance(obj, _enumerable)
    return res


def _isPrimitive(obj: object) -> bool:
    res = isinstance(obj, _primitive)
    return res
