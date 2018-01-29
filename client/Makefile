FreeIM: FreeIM.o FreeIM_Client.o TcpClient.o TcpConnection.o 
	g++ -o FreeIM FreeIM.o FreeIM_Client.o TcpClient.o TcpConnection.o -lpthread -levent -ljsoncpp
FreeIM.o: FreeIM.cpp FreeIM_Client.h
	g++ -o FreeIM.o -c FreeIM.cpp
FreeIM_Client.o: FreeIM_Client.cpp FreeIM_Client.h TcpClient.h TcpConnection.h
	g++ -o FreeIM_Client.o -c FreeIM_Client.cpp
TcpClient.o: TcpClient.cpp TcpClient.h TcpConnection.h
	g++ -o TcpClient.o -c TcpClient.cpp
TcpConnection.o: TcpConnection.cpp TcpConnection.h
	g++ -o TcpConnection.o -c TcpConnection.cpp

clean:
	rm -rf FreeIM *.o
