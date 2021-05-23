import types
import inspect

_primitive = (int, float, str, bool, complex, type(None))
_enumerable = (list, tuple, range, set, frozenset)
_serialized = {}

##############################################################

def clear() -> None:
    global _serialized
    _serialized = {}

##############################################################

def pack_instance(obj: object) -> dict:
    if isinstance(obj, _primitive + _enumerable):
        return obj
    elif isinstance(obj, types.FunctionType):
        return function_to_dict(obj)
    elif isinstance(obj, types.ModuleType):
        return module_to_dict(obj)
    elif isinstance(obj, type):
        return class_to_dict(obj)
    elif is_class_instance(obj):
        return instance_to_dict(obj)
    return obj

def unpack_instance(obj: dict) -> object:
    if (isinstance(obj, dict)):
        if ("<code>" in obj):
            obj = code_from_dict(obj["<code>"])
        elif ("<class_instance>" in obj):
            obj = instance_from_dict(obj["<class_instance>"])
        elif ("<function>" in obj):
            obj = function_from_dict(obj["<function>"])
        elif ("<module>" in obj):
            obj = module_from_dict(obj["<module>"])
        elif ("<class>" in obj):
            obj = class_from_dict(obj["<class>"])
    return obj

##############################################################

def class_to_dict(obj: type) -> dict:
    _serialized[obj] = True
    _bases = ()

    for i in obj.__bases__:
        if i.__name__ != "object":
            _bases += class_to_dict(i),

    
    _dict = {}
    for k, v in dict(obj.__dict__).items():
        if isinstance(v, types.FunctionType):
            if v in _serialized:
                continue
        elif (isinstance(v, types.WrapperDescriptorType)):
            continue
        _dict[k] = pack_instance(v) 
    

    return\
        {
            "<class>":
            {
                "name": obj.__name__,
                "bases": _bases,
                "dict": _dict
            }
        }

def class_from_dict(obj: dict) -> type:
    return type(obj["name"], tuple(obj["bases"]), obj["dict"])

##############################################################

def instance_to_dict(obj: object) -> dict:
    return\
        {
            "<class_instance>":
                { 
                    "class": class_to_dict(obj.__class__),
                    "vars": obj.__dict__
                }
        }

def instance_from_dict(obj: dict) -> dict:
    def __init__(self):
            pass

    cls = obj["class"]
    temp = cls.__init__
    cls.__init__ = __init__
    res = cls()
    res.__dict__ = obj["vars"]
    res.__init__ = temp
    res.__class__.__init__ = temp
    return res

##############################################################
    
def function_to_dict(obj: types.FunctionType) -> dict:
    return\
        {
            "<function>" : 
                {
                    "__globals__": _get_globals(obj, obj.__code__), 
                    "__code__": code_to_dict(obj.__code__), 
                    "__name__": obj.__name__,
                    "__defaults__": obj.__defaults__,
                    "__closure__": obj.__closure__
                }
        }

def function_from_dict(obj: dict) -> types.FunctionType:
    res = types.FunctionType(
        globals = obj["__globals__"],
        code = obj["__code__"],
        name = obj["__name__"],
        closure = obj["__closure__"],
    )
    res.__defaults__ = obj['__defaults__']
    funcs = _collect_funcs(res, {})
    funcs.update({res.__name__: res})
    _set_funcs(res, {res.__name__: True}, funcs)
    res.__globals__.update(funcs)
    res.__globals__["__builtins__"] = __import__("builtins")

    return res

##############################################################

def module_to_dict(obj: types.ModuleType) -> dict:
    return {"<module>": obj.__name__}

def module_from_dict(obj: str) -> types.ModuleType:
    return __import__(obj)

##############################################################

def code_to_dict(obj: types.CodeType) -> dict:
    res = {
        "<code>": {
            "co_argcount": obj.co_argcount,
            "co_posonlyargcount": obj.co_posonlyargcount,
            "co_kwonlyargcount": obj.co_kwonlyargcount,
            "co_nlocals": obj.co_nlocals,
            "co_stacksize": obj.co_stacksize,
            "co_flags": obj.co_flags,
            "co_code": obj.co_code,
            "co_consts": obj.co_consts,
            "co_names": obj.co_names,
            "co_varnames": obj.co_varnames,
            "co_filename": obj.co_filename,
            "co_name": obj.co_name,
            "co_firstlineno": obj.co_firstlineno,
            "co_lnotab": obj.co_lnotab,
            "co_freevars": obj.co_freevars,
            "co_cellvars": obj.co_cellvars,
        }
    }

    return res

def code_from_dict(obj: dict) -> types.CodeType:
    res =  types.CodeType(
        obj["co_argcount"],
        obj["co_posonlyargcount"],
        obj["co_kwonlyargcount"],
        obj["co_nlocals"],
        obj["co_stacksize"],
        obj["co_flags"],
        bytes(bytearray(obj["co_code"])),
        tuple(obj["co_consts"]),
        tuple(obj["co_names"]),
        tuple(obj["co_varnames"]),
        obj["co_filename"],
        obj["co_name"],
        obj["co_firstlineno"],
        bytes(bytearray(obj["co_lnotab"])),
        tuple(obj["co_freevars"]),
        tuple(obj["co_cellvars"]),
    )

    return res

##############################################################

#snatched
def _get_globals(obj: types.FunctionType, obj_code: types.CodeType) -> dict:
    global _serialized
    _serialized[obj] = True
    _globals = {}
    for i in obj_code.co_names:
        try:
            if isinstance(obj.__globals__[i], types.FunctionType) or inspect.isclass(obj.__globals__[i]):
                if obj.__globals__[i] in _serialized:
                    continue
            _globals[i] = pack_instance(obj.__globals__[i])
        except KeyError:
            pass
    for i in obj_code.co_consts:
        if isinstance(i, types.CodeType):
            _globals.update(_get_globals(obj, i))
    return _globals


# snatched
def _collect_funcs(obj: types.FunctionType, visited: dict) -> dict:
    for i in obj.__globals__:
        attr = obj.__globals__[i]
        if isinstance(attr, types.FunctionType) and attr.__name__ not in visited:
            visited[attr.__name__] = attr
            visited = _collect_funcs(attr, visited)

    return visited


# snatched
def _set_funcs(obj: types.FunctionType, visited: dict, funcs: dict) -> dict:
    for i in obj.__globals__:
        attr = obj.__globals__[i]
        if isinstance(attr, types.FunctionType) and attr.__name__ not in visited:
            visited[attr.__name__] = True
            attr.__globals__.update(funcs)
            visited = _set_funcs(attr, visited, funcs)

    return visited

# snatched
def is_class_instance(obj):
    if not hasattr(obj, "__dict__"):
        return False
    if inspect.isroutine(obj):
        return False
    if inspect.isclass(obj):
        return False
    else:
        return True