import scala.collections.mutable.*

case class Data(b: byte[], cnt: Int) {
    byte[] buf = b
    Int count = cnt
}

case class AddDest(s: Socket)

class DestinationListener {
    val socket = ServerSocket(port)
    val proxy = myProxy
    DestinationListener(myProxy: Proxy, port: Int)

    def listen = {
        Socket s = socket.accept()
        // new client connected to proxy
        proxy ! AddDest(s)
    }
}


class Destination extends Actor{
    val socket = mySocket
    Destination(mySocket: Socket)

    def receive = {
        case d: Data =>
            va ostream = socket.getOutputStream()
            ostream.write(buf, 0 , cnt)
    }
}

class Proxy extends Actor {
    // destinations
    val dstList = List()
    val srcIP = "localhost"
    val srcPort = 8081
    val destListenPort = 8082

    def receive = {
        case AddDest(s)  =>
            dstList.add(Destination(s))

        case d: Data =>
            for (dst <- dstList)
                dst ! d
}

class Source extends Actor {
    val socket = Socket(port)
    val proxy = myProxy
    var active = true

    Source(myProxy: Proxy, port: Int)

    def read = {
        Socket s = socket.connect()
        // new client connected to proxy
        proxy ! Data()

        val len = 2000
        byte[] buf = new byte[len]

        while (active) {
            val istream = socket.getInputStream();
            val count = istream.read(buf)

            if (count == -1) return
            if (count > 0) {
                proxy ! Data(buf, count)
            }
       }
    }
}

