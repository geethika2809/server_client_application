CC=gcc
TARGET1=server
TARGET2=client
objs=server.o operation.o
objc=client.o
$(TARGET1):$(objs)
	$(CC) $(objs) -o $(TARGET1)
$(TARGET2):$(objc)
	$(CC) $(objc) -o $(TARGET2)
clean:
	rm -f $(TARGET1) $(TARGET2) $(objs) $(objc)

