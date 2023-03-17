build:	
	g++ server.cpp -o server
	g++ ipkcp.cpp -o ipkcpc 

clean:
	rm server ipkcp