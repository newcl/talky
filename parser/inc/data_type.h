#ifndef __data_type_h__
#define __data_type_h__

enum DataType
{
    DT_INT64,	///< 8 bytes
    DT_UINT64,	///< 8 bytes.
    DT_DOUBLE,	///< 8 bytes.
    DT_FLOAT,	///< 4 bytes
    DT_INT32,	///< 4 bytes
    DT_UINT32,	///< 4 bytes
    DT_INT16,	///< 2 bytes
    DT_UINT16,	///< 2 bytes
    DT_INT8,	///< 1 bytes
    DT_UINT8,	///< 1 bytes
    DT_BOOL,	///< 1 bytes
    DT_ENUM,	///< 1 bytes
    DT_STRING,	///< len * 1 bytes.
    DT_UNKNOWN
};

#endif