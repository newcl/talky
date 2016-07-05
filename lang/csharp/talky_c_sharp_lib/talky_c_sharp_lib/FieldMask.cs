using System;

namespace Talky
{
	public class FieldMark {
		public byte[] data;
		public int readIndex;
		public int writeIndex;

		public FieldMark(int bytes){
			data = new byte[bytes];
		}

		public void Mark(bool isMarked){
			if(writeIndex >= data.Length * 8){
				throw new Exception("overflow writeIndex=" + writeIndex + " data.length=" +data.Length );
			}

			int byteIndex = writeIndex / 8;
			int bitIndex = writeIndex % 8;
			data[byteIndex] |= (byte)(isMarked ? 1 << (7 - bitIndex) : 0);
			writeIndex ++;
		}

		public bool IsMarked(int index){
			int byteIndex = index / 8;
			int bitIndex = index % 8;
			return (data[byteIndex] & 1 << (7 - bitIndex)) != 0;
		}

		public bool ReadMark(){
			bool isMarked = IsMarked(readIndex++);
			return isMarked;
		}

		public byte[] GetData(){
			return data;
		}
	}	
}
