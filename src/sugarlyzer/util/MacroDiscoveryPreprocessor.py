import pcpp
from pcpp import OutputDirective


class MacroDiscoveryPreprocessor(pcpp.Preprocessor):
    def __init__(self, *args, collected=None, **kwargs):
        if collected is None:
            collected = []
        self.__collected = collected
        super(MacroDiscoveryPreprocessor, self).__init__(*args, **kwargs)

    @property
    def collected(self):
        return [*[m for m in self.macros if m not in ['__DATE__', '__TIME__', '__PCPP__', '__FILE__']],
                *self.__collected]

    def on_unknown_macro_in_defined_expr(self, tok):
        self.__collected.append(tok.value)
        return None  # Pass through as expanded as possible

    def on_unknown_macro_in_expr(self, tok):
        self.__collected.append(tok.value)
        return None  # Pass through as expanded as possible