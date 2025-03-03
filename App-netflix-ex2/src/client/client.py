import socket
import sys
import signal

def signal_handler(sig, frame):
    sys.exit(0)

def main():
    if len(sys.argv) != 3:
        return

    server_ip = sys.argv[1]
    port = int(sys.argv[2])

    # Register the signal handler for SIGINT
    signal.signal(signal.SIGINT, signal_handler)

    # Create a TCP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        try:
            # Connect to the server
            client_socket.connect((server_ip, port))

            while True:
                # Get user input
                command = input()

                # Send command to the server
                client_socket.sendall(command.encode())

                # Receive response from the server
                response = client_socket.recv(1024).decode()
                print(response, end='')

        except Exception:
            pass

if __name__ == "__main__":
    main()