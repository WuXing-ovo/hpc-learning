# Matrix Library

## Overview
A simple matrix library implemented in C with basic linear algebra operations.  
Includes creation, element access, initialization, and fundamental matrix operations.

## Features
- **Matrix Creation / Destruction** — Allocate and free matrices
- **Element Access** — Get and set individual matrix elements
- **Initialization** — Fill matrices with values, create identity matrices
- **Basic Operations**
  - Addition
  - Subtraction
  - Scalar multiplication
  - Transpose
  - Matrix multiplication
- **Error Handling** — Comprehensive error codes and validation

## Compilation
```bash
gcc matrix.c test.c -o test
./test
```

## File Structure
- `matrix.h` — Header file with function declarations
- `matrix.c` — Implementation
- `test.c` — Unit tests

## API Overview

### Core Functions
| Function | Description |
|----------|-------------|
| `create_matrix(rows, cols, mat)` | Create a matrix |
| `free_matrix(mat)` | Free matrix memory |
| `set(mat, i, j, value)` | Set element at (i, j) |
| `get(mat, i, j)` | Get element at (i, j) |

### Initialization
| Function | Description |
|----------|-------------|
| `fill(mat, num)` | Fill all elements with a value |
| `fill_0(mat)` | Fill with zeros |
| `fill_1(mat)` | Fill with ones |
| `identity_matrix(mat)` | Create identity matrix (square only) |

### Operations
| Function | Description |
|----------|-------------|
| `matrix_add(A, B, C)` | Compute C = A + B |
| `matrix_subtract(A, B, C)` | Compute C = A - B |
| `matrix_scalar_multiply(A, scalar, C)` | Compute C = scalar × A |
| `matrix_transpose(A, C)` | Compute C = A^T |
| `matrix_multiply(A, B, C)` | Compute C = A × B |

### Utility
| Function | Description |
|----------|-------------|
| `print_matrix(mat, precision)` | Print matrix to console |

## Error Codes
- `MATRIX_ERR_ALLOCATION` — Memory allocation failed
- `MATRIX_ERR_INVALID_MATRIX` — Matrix is NULL or not initialized
- `MATRIX_ERR_INVALID_ROW` — Row index out of bounds
- `MATRIX_ERR_INVALID_COL` — Column index out of bounds
- `MATRIX_ERR_NOT_SQUARED` — Operation requires square matrix
- `MATRIX_ERR_DIMENSION_MISMATCH` — Matrix dimensions incompatible

Error status is stored in global variable `matrix_errno`.

## Example Usage
```
// Create matrices
struct matrix A, B, C;
create_matrix(3, 3, &A);
create_matrix(3, 3, &B);
create_matrix(3, 3, &C);

// Initialize
fill_1(&A);
fill_0(&B);

// Perform operation
matrix_add(&A, &B, &C);

// Check result
print_matrix(&C, 2);

// Cleanup
free_matrix(&A);
free_matrix(&B);
free_matrix(&C);
```

## Testing
Run the test suite:
```bash
./test
```

All tests should pass with ✅ output.

## Notes
- Current implementation uses naive algorithms (not optimized)
- Future improvements: performance optimization, OpenMP parallelization
