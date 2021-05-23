from typing import Union
import logging
import dill as pickle

def dumps(obj: object, protocol: Union[int, None] = None) -> str:
    logging.debug("pickes.dumps starts.")

    res = pickle.dumps(obj, protocol)

    logging.debug("pickles.dumps ends.")
    return res

def dump(file: str, obj: object, protocol: Union[int, None] = None) -> None: 
    logging.debug("pickles.dump starts.")

    with open(file, 'w') as f:
        f.seek(0)
        f.truncate()
        f.seek(0)

        res = dumps(obj, protocol)
        f.write(res)
    
    logging.debug("pickles.dump ends.")

def loads(s: str) -> object:
    logging.debug("pickles.loads starts.")

    res = pickle.loads(s)

    logging.debug("pickles.loads ends.")
    return res

def load(file: str) -> object:
    logging.debug("pickle.load starts.")

    with open(file, 'r') as f:
        s = f.read()
        res = loads(s)

        logging.debug("pickle.load ends.")
        return res
        