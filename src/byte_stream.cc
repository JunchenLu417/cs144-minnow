#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

bool Writer::is_closed() const
{
  return writer_closed;
}

void Writer::push( string data )
{
  if (available_capacity()) {
    if (data.size() > available_capacity())
      data.resize(available_capacity());
    bytes_pushed_cnt += data.size();
    bs_buf += data;
  }
}

void Writer::close()
{
  writer_closed = true;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - reader().bytes_buffered();
}

uint64_t Writer::bytes_pushed() const
{
  return bytes_pushed_cnt;
}

bool Reader::is_finished() const
{
  return writer_closed && !bytes_buffered();
}

uint64_t Reader::bytes_popped() const
{
  return bytes_popped_cnt;
}

string_view Reader::peek() const
{
  return bs_buf;
}

void Reader::pop( uint64_t len )
{
  bs_buf.erase(0, min(len, bytes_buffered()));
  bytes_popped_cnt += min(len, bytes_buffered());
}

uint64_t Reader::bytes_buffered() const
{
  return bytes_pushed_cnt - bytes_popped_cnt;
}
