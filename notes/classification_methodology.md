# How Varbugs Reports are Classified

Varbugs reports are classified using a basic TRUE/FALSE, in addition to a set of modifiers that indicate extra information about the report.

## TRUE/FALSE

Indicates whether the bug described by the report can ever happen at the indicated line under the indicated configuration.
TRUE means that there does exist some circumstance under which the human classifier believes that the described bug may occur.
FALSE means that the bug will never occur.

## MODIFIERS
- NEW: Only valid for alarms classified as "true." Indicates that the bug may occur but was not in the original VBDb dataset
- UNDER: Only valid for true positive bugs that were included in VBDb. Indicates that the bug was true but that the configuration given by the tool is underconstrained (e.g., the bug requires A /\ B to occur, but the given condition uses only A).
- OVER: Only valid for false positive bugs that were included in VBDb. Indicates that the bug was true but that the configuration is overconstrained (e.g., the bug requires A to occur, but the given condition gives A /\ B.)
