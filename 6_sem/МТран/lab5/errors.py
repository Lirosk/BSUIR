class InterpretationError(Exception):
    def __init__(self, *args: object, _break = False) -> None:
        super().__init__(*args)
        self._break = _break


class SemanticError(Exception):
    ...