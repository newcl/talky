using System;

namespace Talky
{
	public class SerializationUtil
	{
		public SerializationUtil ()
		{
		}

		public const int MAX = 0X3FFFFFFF;

		public static int WriteVariableLength(MemoryEndianBinaryWriter writer, uint length){
			if(length < 0){
				throw new Exception("input shoule be positive " + length);
			}

			if(length > MAX){
				throw new Exception("overflow max="+MAX+" input="+length);
			}

			if(length <= 0x3F){
				byte[] data = new byte[]{(byte)(length)};
				writer.Write (data);
				return 1;
			}else if(length <= 0x3FFF){
				byte[] data = new byte[]{(byte)(1 << 6 | length >> 8), (byte)(length & 0xFF)};
				writer.Write (data);
				return 2;
			}else if(length <= 0x3FFFFF){
				byte[] data = new byte[]{(byte)(2 << 6 | length >> 16), (byte)((length >> 8) & 0xFF), (byte)(length & 0xFF)};
				writer.Write (data);
				return 3;
			}else if(length <= 0x3FFFFFFF){
				byte[] data = new byte[]{(byte)(3 << 6 | length >> 24), (byte)((length >> 16) & 0xFF), (byte)((length >> 8) & 0xFF), (byte)(length & 0xFF)};
				writer.Write (data);
				return 4;
			}else{
				throw new Exception("should not be here");
			}
		}

		public static UInt32 readVariableLength(MemoryEndianBinaryReader reader){
			byte highestByte = reader.ReadByte();
			int bytes = (highestByte >> 6) + 1;
			UInt32 value = (UInt32)(highestByte & 0x3F);
			for(int i=0; i < bytes-1; i++){
				byte theByte = reader.ReadByte ();
				value = (value << 8) | theByte;
			}
			return value;
		}
	}
}

