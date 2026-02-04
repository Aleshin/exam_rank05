# BSQ - Biggest Square Task (Exam Rank 05)

## Overview
This folder contains the complete and reconstructed specification for the **bsq** task from the 42 School's Exam Rank 05.

## Task Summary
Write a program that finds the **largest square** on a 2D map that:
- Fits entirely within the map boundaries
- Contains only "empty" cells (avoiding obstacles)
- Is filled with a "full" character in the output

## Files in This Folder

### 1. **subject.txt** (PRIMARY SPECIFICATION)
The complete and official task specification including:
- Objective and usage
- Input/output format
- Algorithm requirements
- Validation rules (very strict)
- Examples
- Edge cases

**Read this first** for comprehensive understanding.

### 2. **algorithm_notes.txt** (IMPLEMENTATION GUIDE)
Technical details for implementation:
- Dynamic programming approach
- Pseudocode for key functions
- Header parsing implementation
- Map validation logic
- Memory handling patterns
- Common mistakes to avoid
- Testing approach

**Reference this** when starting to implement.

### 3. **SUMMARY.txt** (QUICK REFERENCE)
Quick checklist and summary including:
- Critical requirements
- Validation checklist
- Common mistakes
- Quick examples
- File reference guide

**Use this** as a quick reference during implementation.

## Key Points (Must Know)

### Validation is STRICT
Your program must validate:
- ✓ Exactly 4 header values
- ✓ Row count > 0
- ✓ Characters are distinct (all three different)
- ✓ Characters are printable (ASCII 32-126)
- ✓ All rows same length
- ✓ Row count matches header
- ✓ Only valid characters in map
- ✓ All rows end with newline

If ANY validation fails: output `map error\n` to **stderr** and continue.

### Tie-Breaking (Important!)
If multiple squares of same maximum size exist:
1. Choose the one **closest to top** (smallest row)
2. If tied, choose the **leftmost** (smallest column)

### Output
- **Success**: Modified map to stdout (with filled square)
- **Error**: `map error\n` to stderr
- Each output followed by newline

### Input Support
- File argument: `./bsq mapfile.txt`
- Stdin: `cat mapfile.txt | ./bsq` or `./bsq < mapfile.txt`
- Multiple files: `./bsq map1.txt map2.txt map3.txt`

## Where to Find Test Cases

The workspace includes test maps in:
- `bsq0/bsq_test_maps/` - Valid and invalid test maps
- `bsq0/bsq_edge_tests/` - Edge cases
- `bsq3/test*.txt` - Various test cases with error examples

## Common Implementation Path

1. Parse header with fscanf
2. Validate header (especially character distinctness)
3. Read map lines with getline
4. Validate map against header
5. Find largest square using DP (O(n*m))
6. Output result or error
7. Free all memory

## Critical Code Points

```c
// CHARACTER DISTINCTNESS CHECK (DO NOT MISS)
if (empty == obstacle || empty == full || obstacle == full)
    return ERROR;

// ERROR OUTPUT (NOT printf!)
fprintf(stderr, "map error\n");

// OUTPUT NEWLINES
printf("\n");

// MEMORY FROM getline (MUST FREE)
free(line);
```

## References
This specification was reconstructed from:
- Multiple student implementations (bsq3, bsq0, bsq8, BSQ1, BSQ2, etc.)
- Official 42 exam specifications
- Actual test maps and edge cases

It is **COMPLETE and ACCURATE** for the bsq task.
