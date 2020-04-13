var aa = 34564
var sum
while(aa != 0)
    if(aa % 10 != 4)
        sum = sum * 10
        sum = sum + aa % 10
    endif
    aa = aa / 10
endw

var tr = sum