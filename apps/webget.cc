#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  // cerr << "Function called: get_URL(" << host << ", " << path << ")\n";
  // cerr << "Warning: get_URL() has not been implemented yet.\n";

  Address dest_addr(host, "80");  // port 80 for http service
  TCPSocket tcp_sock;  tcp_sock.connect(dest_addr);  // telnet cs144.keithw.org http
  std::vector<std::string> bufs = {  // string_view is a pointer to a position in the char array
    "GET " + path + " HTTP/1.1\r\n",
    "Host: " + host + "\r\n",
    "Connection: close\r\n",
    "\r\n"  // an empty line to terminate the http request
  };
  tcp_sock.write(bufs);

  std::string reply_line;
  while (true) {
    tcp_sock.read(reply_line);
    if (reply_line.size())
      std::cout << reply_line;
    else
      break;
  }
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
