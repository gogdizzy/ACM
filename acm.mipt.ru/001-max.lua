max = io.read( "*number" )
while true do
	now = io.read( "*number" )
	if not now then break end
	if now > max then max = now end
end
io.write( max )
