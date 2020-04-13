var fiboone = 1
var fibotwo = 1
var nthfibo = fiboone + fibotwo
var n = 10
var bb = 1
while(bb <= n)
    nthfibo = fiboone + fibotwo
    fiboone = fibotwo
    fibotwo = nthfibo
    bb = bb + 1
endw

var zr = nthfibo