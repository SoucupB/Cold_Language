var element = 24
var ok = 0
var index = 2

while(index * index <= element)
    if(element % index == 0)
        ok = 1
        index = element
    endif
    index = index + 1
endw

var zr = ok