## changes to receive request from other client devices who has connected to same Wifi network..

# 1) Other devices cannot directly reach your WSL IP (like 172.x.x.x).
You MUST forward the port using Windows.

## Port Forward Windows → WSL
netsh interface portproxy add v4tov4 listenaddress=0.0.0.0 listenport=8080 connectaddress=<WSL_IP> connectport=8080


## Find WSL IP:
ip addr show eth0


# 2) Verify port forwarding exists
netsh interface portproxy show all


# 3) Windows Firewall may be blocking external devices
Allow incoming traffic:

netsh advfirewall firewall add rule name="WSL HTTP" dir=in action=allow protocol=TCP localport=8080


# 4)Test it from browser

http://<WINDOWS_LAN_IP>:8080

ex: http://192.168.1.5:8080


## example of Http response from server

const char* body = "Hello, World!";
std::string response =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "Content-Length: " + std::to_string(strlen(body)) + "\r\n"
    "Connection: close\r\n"
    "\r\n" +
    std::string(body);

send(client_socket, response.c_str(), response.size(), 0);
