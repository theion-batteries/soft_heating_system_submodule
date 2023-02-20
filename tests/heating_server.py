import socket

def run_server():
    s = socket.socket()
    print("Socket successfully created")
    ok = "ok".encode('utf-8')
    temp_sulfur = "120".encode('utf-8')
    temp_plate = "100".encode('utf-8')
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
                elif data == b'info\r\n':
                    print(f"received: info")
                    print(f"sent: {ok}")
                    c.send(ok)
                elif data == b'on\r\n':
                    print(f"received: on")
                    print(f"sent: {ok}")
                    c.send(ok)
                elif data == b'off\r\n':
                    print(f"received: off")
                    print(f"sent: {ok}")
                    c.send(ok)
                elif data == b'stay\r\n':
                    print(f"received: stay")
                    print(f"sent: {ok}")
                    c.send(ok)
                elif data == b'temp?\r\n':
                    print(f"received: {temp}?")
                    print(f"sent: {temp_sulfur}")
                    c.send(temp_sulfur)
                elif data == b'state?\r\n':
                    print(f"received: state?")
                    print(f"sent: {ok}")
                    c.send(ok)
                elif data == b'plate_temp?\r\n':
                    print(f"received: plate_temp?")
                    print(f"sent: {temp_plate}")
                    c.send(temp_plate)
                ## treat all cases =      
                elif b'plate_temp=' in data:         
                    print(f"received: {data}")
                    print(f"sent: ok")
                    c.send(b'ok') 
                ## treat all cases =      
                elif b'temp=' in data:         
                    print(f"received: {data}")
                    print(f"sent: ok")
                    c.send(b'ok') 
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
