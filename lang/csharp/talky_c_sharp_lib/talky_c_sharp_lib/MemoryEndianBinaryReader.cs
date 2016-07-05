using System;
using MiscUtil;
using MiscUtil.Conversion;
using MiscUtil.IO;
using System.IO;

namespace Talky
{
	public class MemoryEndianBinaryReader : EndianBinaryReader
	{
		private MemoryStream memoryStream;
		public MemoryEndianBinaryReader (EndianBitConverter bitConverter, MemoryStream memoryStream) : base(bitConverter, memoryStream)
		{
			this.memoryStream = memoryStream;
		}

		public UInt16 GetUInt16(int offset) {
			return BitConverter.ToUInt16 (memoryStream.GetBuffer(), offset);
		}
	}	
}


