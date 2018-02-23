figure
imshow('cartoon.png')
[x, y] = getpts
maxx = max(x)
maxy = max(y)
x = (x - 1.1179e+03)/max(maxy,maxx)
y =-(y- 1.2127e+03)/max(maxy,maxx)