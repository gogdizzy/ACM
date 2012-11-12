function  readnum() 
	local x = io.read( "*number" )
	return x ~= -1 and x or nil
end

tbl1 = {}
while true do
	local now = readnum()
	if not now then break end
	tbl1[now] = 1
end

count = 0
while true do
	local now = readnum()
        if not now then break end
        if tbl1[now] == 1 then
		tbl1[now] = 2;
		count = count + 1;
	end
end

if count == 0 then
	io.write( "empty\n" )
else
	for k, v in pairs( tbl1 ) do
		if v == 2 then io.write( k, " " ) end
	end
end
