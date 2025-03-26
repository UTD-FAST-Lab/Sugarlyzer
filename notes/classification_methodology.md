# How Varbugs Reports are Classified

Varbugs reports are classified using a basic TRUE/FALSE, in addition to a set of modifiers that indicate extra information about the report.

The varbugs dataset can be found [here](https://vbdb.bitbucket.io/database.html).
## TRUE/FALSE

Indicates whether the bug described by the report can ever happen at the indicated line under the indicated configuration.

TRUE means that there does exist some circumstance under which the human classifier believes that the described bug may occur.

FALSE means that the bug will never occur.

## MODIFIERS

- NEW: Only valid for alarms classified as "true." Indicates that the bug may occur but was not in the original VBDb dataset.

- UNDER: Only valid for true positive bugs. Indicates that the bug was true but that the configuration given by the tool is underconstrained (e.g., the bug requires A /\ B to occur, but the given condition uses only A). Formally, the configuration is underconstrained if there exists a configuration that meets the constraints emitted by Sugarlyzer but that does not trigger the bug.

- OVER: Only valid for true positive bugs. Indicates that the bug was true but that the configuration is overconstrained (e.g., the bug requires A to occur, but the given condition gives A /\ B). Formally, the configuration is overconstrained if there exists a configuration that triggers the bug but does not conform to the constraints emitted by Sugarlyzer.

- EXACT: **This should never be added explicitly; rather, the absence of OVER and UNDER implies EXACT.** Only valid for true positive bugs. Indicates that the bug was true, and that Sugarlyzer ascribed the exact set of configurations that produce the bug.

## VALID CLASSIFICATIONS

The following classifications are valid:

- FALSE
- TRUE
- TRUE_OVER
- TRUE_UNDER
- TRUE_OVER_UNDER
- TRUE_NEW
- TRUE_NEW_OVER
- TRUE_NEW_UNDER
- TRUE_NEW_OVER_UNDER

**Note that the absence of an OVER and/or UNDER modifier implies that the configuration was an exact match.**

## EXAMPLES

### Scenario 1

Problem: The static analyzer emits a warning about a dead store under any configuration. The varbugs dataset does not include this bug, but it is indeed a dead store.

Solution: The alarm should be classified as "TRUE_NEW"

### Scenario 2

Problem: The static analyzer correctly identifies a warning that exists in the varbugs dataset, but in the dataset, the bug only occurs under condition A, while Sugarlyzer claims it occurs under any configuration.

Solution: The alarm should be classified as "TRUE_UNDER"

### Scenario 3

Problem: The static analyzer emits a warning that matches a warning in the varbugs dataset. However, Sugarlyzer ascribes the configuration A /\ B, while the bug only needs A to trigger.

Solution: The alarm should be classified as "TRUE_OVER"

### Scenario 4

Problem: The static analyzer emits a warning that matches a bug in the varbugs dataset. However, the dataset indicates that the bug is predicated on A, and the analyzer says the bug is predicated on B /\ C.

Solution: The alarm should be classified as "TRUE_OVER_UNDER"

### Scenario 5

Problem: The analyzer emits a true positive that is not in the varbugs dataset. However, Sugarlyzer ascribes the configuration A \/ B, and the bug requires A to trigger.

Solution: The alarm should be classified as "TRUE_NEW_UNDER"


