import yaml
import logging
from typing import Union
import utility

def dumps(obj: object, protocol: Union[int, None] = None) -> str:
    logging.debug("yamls.dumps starts.")

    res = yaml.dumps(utility.pack_instance(obj), protocol)
    utility.clear()

    logging.debug("yamls.dumps ends.")
    return res

def dump(file: str, obj: object, protocol: Union[int, None] = None) -> None: 
    logging.debug("yamls.dump starts.")

    with open(file, 'w') as f:
        f.seek(0)
        f.truncate()
        f.seek(0)

        res = dumps(obj, protocol)
        f.write(res)
    
    logging.debug("yamls.dump ends.")

def loads(s: str) -> object:
    logging.debug("yamls.loads starts.")

    res = utility.unpack_instance(yaml.loads(s))

    logging.debug("yamls.loads ends.")
    return res

def load(file: str) -> object:
    logging.debug("yamls.load starts.")

    with open(file, 'r') as f:
        s = f.read()
        res = loads(s)

        logging.debug("yamls.load ends.")
        return res
