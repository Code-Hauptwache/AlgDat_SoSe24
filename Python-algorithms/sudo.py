## Solve Every Sudoku Puzzle

## See http://norvig.com/sudoku.html

## Ported to Python 3.0 using python-modernize -w sudo.py 

## Throughout this program we have:
##   r is a row,    e.g. 'A'
##   c is a column, e.g. '3'
##   s is a square, e.g. 'A3'
##   d is a digit,  e.g. '9'
##   u is a unit,   e.g. ['A1','B1','C1','D1','E1','F1','G1','H1','I1']
##   g is a grid,   e.g. 81 non-blank chars, e.g. starting with '.18...7...
##   values is a dict of possible values, e.g. {'A1':'123489', 'A2':'8', ...}

from __future__ import print_function
from six.moves import zip
def cross(A, B):
    return [a+b for a in A for b in B]

rows = 'ABCDEFGHI'
cols = '123456789'
digits   = '123456789'
squares  = cross(rows, cols)
unitlist = ([cross(rows, c) for c in cols] +
            [cross(r, cols) for r in rows] +
            [cross(rs, cs) for rs in ('ABC','DEF','GHI') for cs in ('123','456','789')])
units = dict((s, [u for u in unitlist if s in u]) 
             for s in squares)
peers = dict((s, set(s2 for u in units[s] for s2 in u if s2 != s))
             for s in squares)
  
def search(values):
    "Using depth-first search and propagation, try all possible values."
    if values is False:
        return False ## Failed earlier
    if all(len(values[s]) == 1 for s in squares): 
        return values ## Solved!
    ## Chose the unfilled square s with the fewest possibilities
    _,s = min((len(values[s]), s) for s in squares if len(values[s]) > 1)
    return some(search(assign(values.copy(), s, d)) 
                for d in values[s])

def assign(values, s, d):
    "Eliminate all the other values (except d) from values[s] and propagate."
    if all(eliminate(values, s, d2) for d2 in values[s] if d2 != d):
        return values
    else:
        return False

def eliminate(values, s, d):
    "Eliminate d from values[s]; propagate when values or places <= 2."
    if d not in values[s]:
        return values ## Already eliminated
    values[s] = values[s].replace(d,'')
    if len(values[s]) == 0:
        return False ## Contradiction: removed last value
    elif len(values[s]) == 1:
        ## If there is only one value (d2) left in square, remove it from peers
        d2, = values[s]
        if not all(eliminate(values, s2, d2) for s2 in peers[s]):
            return False
    ## Now check the places where d appears in the units of s
    for u in units[s]:
        dplaces = [s for s in u if d in values[s]]
        if len(dplaces) == 0:
            return False
        elif len(dplaces) == 1:
            # d can only be in one place in unit; assign it there
            if not assign(values, dplaces[0], d):
                return False
    return values
                    
def parse_grid(grid):
    "Given a string of 81 digits (or .0-), return a dict of {cell:values}"
    grid = [c for c in grid if c in '0.-123456789']
    values = dict((s, digits) for s in squares) ## Each square can be any digit
    for s,d in zip(squares, grid):
        if d in digits and not assign(values, s, d):
            return False
    return values

def solve_file(filename, sep='\n', action=lambda x: x):
    "Parse a file into a sequence of 81-char descriptions and solve them."
    results = [action(search(parse_grid(grid)))
               for grid in open(filename).read().strip().split(sep)]
    print(("## Got %d out of %d" % (
          sum((r is not False) for r in results), len(results))))
    return results

def printboard(values):
    "Used for debugging."
    width = 1+max(len(values[s]) for s in squares)
    line = '\n' + '+'.join(['-'*(width*3)]*3)
    for r in rows:
        print((''.join(values[r+c].center(width)+(c in '36' and '|' or '')
                      for c in cols) + (r in 'CF' and line or '')))
   # print
    return values

def all(seq):
    for e in seq:
        if not e: return False
    return True

def some(seq):
    for e in seq:
        if e: return e
    return False

if __name__ == '__main__':
    solve_file("top95.txt", action=printboard)

## References used:
## http://www.scanraid.com/BasicStrategies.htm
## http://www.krazydad.com/blog/2005/09/29/an-index-of-sudoku-strategies/
## http://www2.warwick.ac.uk/fac/sci/moac/currentstudents/peter_cock/python/sudoku/
