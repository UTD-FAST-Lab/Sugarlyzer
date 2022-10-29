import logging

import pcpp
from pcpp import OutputDirective, Action

logger = logging.getLogger(__name__)


class MacroDiscoveryPreprocessor(pcpp.Preprocessor):

    def on_include_not_found(self, is_malformed, is_system_include, curdir, includepath):
        """Called when a #include wasn't found.

        Raise OutputDirective to pass through or remove, else return
        a suitable path. Remember that Preprocessor.add_path() lets you add search paths.

        The default calls ``self.on_error()`` with a suitable error message about the
        include file not found if ``is_malformed`` is False, else a suitable error
        message about a malformed #include, and in both cases raises OutputDirective
        (pass through).
        """
        try:
            if is_malformed:
                self.on_error(self.lastdirective.source, self.lastdirective.lineno,
                                  "Malformed #include statement: %s" % includepath)
            else:
                self.on_error(self.lastdirective.source, self.lastdirective.lineno,
                              "Include file '%s' not found" % includepath)
        except AttributeError as ae:
            logger.exception("Exception encountered while trying to raise error.")
        finally:
            raise OutputDirective(Action.IgnoreAndPassThrough)

    def on_directive_handle(self, directive, toks, ifpassthru, precedingtoks):
        if directive.value == 'define':
            self.defined.extend([t.value for t in toks])

    def __init__(self, *args, collected=None, **kwargs):
        if collected is None:
            collected = []
        self.defined = []
        self.__collected = collected
        super(MacroDiscoveryPreprocessor, self).__init__(*args, **kwargs)

    @property
    def collected(self):
        return [*[m for m in self.macros if m not in ['__DATE__', '__TIME__', '__PCPP__', '__FILE__', *self.defined]],
                *self.__collected]

    def on_unknown_macro_in_defined_expr(self, tok):
        self.__collected.append(tok.value)
        return None  # Pass through as expanded as possible

    def on_unknown_macro_in_expr(self, tok):
        self.__collected.append(tok.value)
        return None  # Pass through as expanded as possible
