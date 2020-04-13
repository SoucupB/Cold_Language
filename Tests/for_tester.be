var sum
var n = 40
var g = 0
var ok = 0
var prime
for(i, 2, n, 1)
    ok = 0
    for(j, 2, i / 2, 1)
        if(i % j == 0)
            ok = 1
        endif
    endf
    if(ok == 0)
        prime = i
    endif
endf

var s = g
