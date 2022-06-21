from z3 import *

x = Bool("!(defined __need___FILE) && !(defined _BITS_TYPESIZES_H) && (defined _IO_MTSAFE_IO)")
y = Bool("!(defined __need___FILE) && (defined _BITS_TYPESIZES_H)")
nf = Bool('nf')
bt = Bool('bt')
io = Bool('io')
s = Solver()
s.add(not nf and not bt and io, not nf and bt)
print(s.check())
print(s.model())
