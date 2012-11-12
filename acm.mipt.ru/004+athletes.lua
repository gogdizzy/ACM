mass = {}
strength = {}
n = io.read( "*number" );

for i = 1,n do
    mass[i], strength[i] = io.read( "*number", "*number" );
end

function  qsort( l, r )
    if l >= r then return end
    local  i, j = l, r;
    local  m0, s0 = mass[i], strength[i];
    while i < j do
        while i < j and s0 < strength[j] do j = j - 1; end
        if i ~= j then mass[i], strength[i] = mass[j], strength[j] end
        while i < j and s0 > strength[i] do i = i + 1; end
        if i ~= j then mass[j], strength[j] = mass[i], strength[i] end
    end
    mass[i], strength[i] = m0, s0;
    qsort( l, i - 1 );
    qsort( i + 1, r );
end

qsort( 1, n );

function  dp( n )
    if n <= 0 then return 0; end

    local  total = {}
    local  count = {}
    local  bestpos = 1;

    total[1], count[1] = mass[1], 1;

    for i = 2, n do
	if strength[i] >= total[bestpos] then
		total[i] = mass[i] + total[bestpos];
		count[i] = count[bestpos] + 1;
		bestpos = i;
	end
    end
    return  count[bestpos];
end

io.write( dp( n ) );
