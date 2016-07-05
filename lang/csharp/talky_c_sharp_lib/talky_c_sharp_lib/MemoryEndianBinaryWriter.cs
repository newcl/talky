using System;
using MiscUtil;
using MiscUtil.IO;
using MiscUtil.Conversion;

using System.IO;

namespace Talky
{
	public class MemoryEndianBinaryWriter : EndianBinaryWriter
	{
		MemoryStream memoryStream;

		public MemoryEndianBinaryWriter (EndianBitConverter converter, MemoryStream stream) : base(converter, stream)
		{
			this.memoryStream = stream;
		}

		public void WriteByte(Byte value) {
			base.Write (value);
		}

		public void WriteSByte(SByte value) {
			base.Write (value);
		}

		public void WriteUInt16(UInt16 value) {
			base.Write (value);
		}

		public void WriteInt16(Int16 value) {
			base.Write (value);
		}

		public void WriteUInt32(UInt32 value) {
			base.Write (value);
		}

		public void WriteInt32(Int32 value) {
			base.Write (value);
		}

		public void WriteUInt64(UInt64 value) {
			base.Write (value);
		}

		public void WriteInt64(Int64 value) {
			base.Write (value);
		}

		public void WriteChar(Char value) {
			base.Write (value);
		}

		public void WriteDouble(Double value) {
			base.Write (value);
		}

		public void WriteSingle(Single value) {
			base.Write (value);
		}

		public void WriteBoolean(bool value) {
			base.Write (value);
		}

		public void WriteUTF(string value) {
			base.Write (value);
		}
	}

}


