package main

import "net"
import "fmt"
import "time"
import "io/ioutil"
import "log"

var payload string;

func handle_conn(conn net.Conn) {
    defer conn.Close()
    conn.SetWriteDeadline(time.Now().Add(20 * time.Second))
    buf := make([]byte, 128)
    le, err := conn.Write([]byte(payload))
    if err != nil {
        return
    }
    fmt.Printf("Wrote %d bytes;", le)
    conn.SetReadDeadline(time.Now().Add(20 * time.Second))
    for {
        le, err = conn.Read(buf)
        if err != nil {
            fmt.Println(err)
            break
        }
        fmt.Printf("Len: %d. Read %s;", le, buf)
    }
    return
}

func main() {
    b, err := ioutil.ReadFile("arm.hex")
    if err != nil {
        log.Fatal(err)
    }
    payload = string(b)

    li, err := net.Listen("tcp", "0.0.0.0:31337")
    if err != nil {
        fmt.Println(err)
        return
    }
    for {
        conn, err := li.Accept()
        fmt.Println("[CONN] Accepted conn.")
        if err != nil {
            break
        }
        go handle_conn(conn)
    }
}

