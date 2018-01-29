FreeIM: FreeIM.o FreeIM_Server.o Controller.o DataBase.o SQL.o TcpConnection.o TcpServer.o ThreadLoop.o View_Login.o View_Register.o View_P2PMes.o View_Close.o
	g++ -o FreeIM FreeIM.o FreeIM_Server.o Controller.o DataBase.o SQL.o TcpConnection.o TcpServer.o ThreadLoop.o View_Login.o View_Register.o View_P2PMes.o View_Close.o -lpthread -levent -ljsoncpp -L/usr/lib64/mysql -lmysqlclient
FreeIM.o: FreeIM.cpp FreeIM_Server.h DataBase.h
	g++ -o FreeIM.o -c FreeIM.cpp
FreeIM_Server.o: FreeIM_Server.cpp FreeIM_Server.h Controller.h View_All.h
	g++ -o FreeIM_Server.o -c FreeIM_Server.cpp
Controller.o: Controller.cpp Controller.h
	g++ -o Controller.o -c Controller.cpp
DataBase.o: DataBase.cpp DataBase.h
	g++ -o DataBase.o -c DataBase.cpp
SQL.o: SQL.cpp SQL.h 
	g++ -o SQL.o -c SQL.cpp
TcpConnection.o: TcpConnection.cpp TcpConnection.h ThreadLoop.h
	g++ -o TcpConnection.o -c TcpConnection.cpp
TcpServer.o: TcpServer.cpp TcpServer.h
	g++ -o TcpServer.o -c TcpServer.cpp
ThreadLoop.o: ThreadLoop.cpp ThreadLoop.h
	g++ -o ThreadLoop.o -c ThreadLoop.cpp
View_Login.o: View_Login.cpp View_Login.h TcpConnection.h DataBase.h ThreadLoop.h
	g++ -o View_Login.o -c View_Login.cpp
View_Register.o: View_Register.cpp View_Register.h TcpConnection.h DataBase.h ThreadLoop.h
	g++ -o View_Register.o -c View_Register.cpp
View_P2PMes.o: View_P2PMes.cpp View_P2PMes.h DataBase.h TcpConnection.h ThreadLoop.h
	g++ -o View_P2PMes.o -c View_P2PMes.cpp
View_Close.o: View_Close.cpp View_Close.h DataBase.h TcpConnection.h ThreadLoop.h
	g++ -o View_Close.o -c View_Close.cpp

clean:
	rm -rf FreeIM *.o
