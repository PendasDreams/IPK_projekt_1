build:	
	gcc server.c -o server
	gcc ipkcp.c -o ipkcp
clean:
	rm server ipkcp