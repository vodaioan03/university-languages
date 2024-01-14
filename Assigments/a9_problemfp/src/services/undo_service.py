from ui.errors import *


class FunctionCall:
    def __init__(self, fun_name, *fun_params):
        self.__fun_name = fun_name
        self.__fun_params = fun_params

    def call(self):
        return self.__fun_name(*self.__fun_params)

    def __call__(self, *args, **kwargs):
        return self.call()


class Operation:
    def __init__(self, fundo: FunctionCall, fredo: FunctionCall):
        self.__fundo = fundo
        self.__fredo = fredo

    def undo(self):
        return self.__fundo()

    def redo(self):
        return self.__fredo()


class UndoError(Exception):
    pass


class UndoService:
    def __init__(self):
        self.__undo = []
        self.__redo = []

    def record(self, oper: Operation):
        self.__undo.append(oper)
        self.__redo = []

    def undo(self):
        if not self.__undo:
            raise ValidationException("No more undos!")

        o = self.__undo.pop()
        self.__redo.append(o)
        o.undo()

    def redo(self):
        if not self.__redo:
            raise ValidationException("No more redos!")

        o = self.__redo.pop()
        self.__undo.append(o)
        o.redo()