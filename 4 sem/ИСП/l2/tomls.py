import pytomlpp as toml
import logging
import utility

def dumps(obj: object) -> str:
    logging.debug("tomls.dumps starts.")

    res = toml.dumps(utility.pack_instance(obj))
    utility.clear()

    logging.debug("tomls.dumps ends.")
    return res

def dump(file: str, obj: object) -> None: 
    logging.debug("tomls.dump starts.")

    with open(file, 'w') as f:
        f.seek(0)
        f.truncate()
        f.seek(0)

        res = dumps(obj)
        f.write(res)
    
    logging.debug("tomls.dump ends.")

def loads(s: str) -> object:
    logging.debug("tomls.loads starts.")

    res = utility.unpack_instance(toml.loads(s))

    logging.debug("tomls.loads ends.")
    return res

def load(file: str) -> object:
    logging.debug("tomls.load starts.")

    with open(file, 'r') as f:
        s = f.read()
        res = loads(s)

        logging.debug("tomls.load ends.")
        return res
