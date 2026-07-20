# Simple TCP socket example

## Build

```bash
gcc server.c -o server
gcc client.c -o client
```

## Run

Terminal 1:

```bash
./server
```

Terminal 2:

```bash
./client "Xin chao server"
```

The client sends one message and the server replies once.
