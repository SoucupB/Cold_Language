var element = 50
var ok = 0
var index = 2

var i = 2
var j = 0
var prime = 0

while(i <= element)
    ok = 0
    j = 2
    while(j * j <= i)
        if(i % j == 0)
            ok = 1
            j = i
        endif
        j = j + 1
    endw
    if(ok == 0)
        prime = i
    endif
    i = i + 1
endw