import socket

def run_server():
    s = socket.socket()
    print("Socket successfully created")
    val = "ok".encode('utf-8')
    port = 8881
    s.bind(('', port))
    print("socket binded to %s" % (port))
    s.listen(5)
    print("socket is listening")
    while True:
        try:
            c, addr = s.accept()
            print('Got connection from', addr)
            while True:
                data = c.recv(5012)
                if not data:
                    # Connection lost, break out of inner loop and reconnect
                    print("Connection lost, reconnecting...")
                    c.close()
                    break
                if data == b'info\r\n':
                    print(f"received: {info}")
                    print(f"sent: {val}")
                    c.send(val)
                if data == b'on':
                    print(f"received: {on}")
                    print(f"sent: {val}")
                    c.send(val)
                if data == b'off':
                    print(f"received: {off}")
                    print(f"sent: {val}")
                    c.send(val)
                if data == b'stay\r\n':
                    print(f"received: {stay}")
                    print(f"sent: {val}")
                    c.send(val)
                if data == b'temp?\r\n':
                    print(f"received: {temp}?")
                    print(f"sent: {val}")
                    c.send(val)
                if data == b'temp\r\n':
                    print(f"received: {temp}")
                    print(f"sent: {val}")
                    c.send(val)
                if data == b'state?\r\n':
                    print(f"received: {state}?")
                    print(f"sent: {val}")
                    c.send(val)
                if data == b'plate_temp?\r\n':
                    print(f"received: {plate_temp}?")
                    print(f"sent: {val}")
                    c.send(val)
                if data == b'plate_temp\r\n':
                    print(f"received: {plate_temp}")
                    print(f"sent: {val}")
                    c.send(val)
                else:
                    print(f"new data coming: {data}")  
        except KeyboardInterrupt:
            print("Program stopped by user.")
            break
        except Exception as e:
            print("Error occurred:", e)

    s.close()

if __name__ == "__main__":
    run_server()
