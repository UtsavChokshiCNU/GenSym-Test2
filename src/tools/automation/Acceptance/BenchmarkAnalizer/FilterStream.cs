using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BenchmarkAnalizer
{
    class FilterStream : System.IO.Stream
    {
        private readonly System.IO.Stream s;
        private readonly byte ff = 0x0C;
        private readonly byte esc = 0x1B;
        private readonly byte sp = 0x20;

        public FilterStream(System.IO.Stream s) 
        {
            this.s = s;
        }
        public override bool CanRead
        {
            get { return s.CanRead; }
        }
        public override bool CanSeek
        {
            get { return s.CanSeek; }
        }
        public override bool CanWrite
        {
            get { return s.CanWrite; }
        }
        public override long Length
        {
            get { return s.Length; }
        }
        public override long Position
        {
            get { return s.Position; }
            set { s.Position = value; }
        }
        public override void Close()
        {
            s.Close();
        }
        public override void Flush()
        {
            s.Flush();
        }
        public override long Seek(long offset, System.IO.SeekOrigin origin)
        {
            return s.Seek(offset, origin);
        }
        public override void SetLength(long value)
        {
            s.SetLength(value);
        }
        public override int Read(byte[] buffer, int offset, int count)
        {
            int ret = s.Read(buffer, offset, count);
            for (int i = 0; i < buffer.Length; i++ )
            {
                buffer[i] = replace(buffer[i]);
            }
            return ret;
        }
        public override int ReadByte()
        {
            return (int)replace((byte)s.ReadByte());
        }
        private byte replace(byte b)
        {
            return ((b == ff) || (b == esc)) ? sp : b;
        }
        public override void Write(byte[] buffer, int offset, int count)
        {
            s.Write(buffer, offset, count);
        }
        public override void WriteByte(byte value)
        {
            s.WriteByte(value);
        }

    }
}
