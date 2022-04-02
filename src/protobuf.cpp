#include <protobuf.hpp>

size_t RobotTweezers::Protobuf::Encode(pb_byte_t *buffer, const pb_msgdesc_t *fields, const void *data_struct)
{
    // Create output stream from buffer
    pb_ostream_t ostream = pb_ostream_from_buffer(buffer, MAX_MESSAGE_SIZE);
    return (pb_encode(&ostream, fields, data_struct) == true) ? ostream.bytes_written : 0;
}

bool RobotTweezers::Protobuf::Decode(pb_byte_t *buffer, size_t size, const pb_msgdesc_t *fields, void *data_struct)
{
    // Create input stream from buffer
    pb_istream_t istream = pb_istream_from_buffer(buffer, size);
    return pb_decode(&istream, fields, data_struct);
}

size_t RobotTweezers::Protobuf::UartWriteBuffer(HardwareSerial *uart, const pb_byte_t *buffer, const size_t size)
{
    return uart->write(buffer, size);
}

#ifdef ESP32
    size_t RobotTweezers::Protobuf::WifiWriteBuffer(WiFiClient *wifi, const pb_byte_t *buffer, const size_t size)
    {
        return wifi->write(buffer, size);
    }
#endif

size_t RobotTweezers::Protobuf::UartReadBuffer(HardwareSerial *uart, pb_byte_t *buffer)
{
    size_t size = uart->available();
    return uart->readBytes(buffer, size);
}

#ifdef ESP32
    size_t RobotTweezers::Protobuf::WifiReadBuffer(WiFiClient *wifi, pb_byte_t *buffer)
    {
        size_t size = wifi->available();
        return wifi->readBytes(buffer, size);
    }
#endif

size_t RobotTweezers::Protobuf::UartWrite(HardwareSerial *uart, const OrientationMsg *orientation_msg)
{
    pb_byte_t buffer[MAX_MESSAGE_SIZE];
    size_t size;
    
    // Encode stream
    size = Encode(buffer, OrientationMsg_fields, (const void *)orientation_msg);
    return UartWriteBuffer(uart, buffer, size);
}

#ifdef ESP32
    size_t RobotTweezers::Protobuf::WifiWrite(WiFiClient *wifi, const OrientationMsg *orientation_msg)
    {
        pb_byte_t buffer[MAX_MESSAGE_SIZE];
        size_t size;
        
        // Encode stream
        size = Encode(buffer, OrientationMsg_fields, (const void *)orientation_msg);
        return WifiWriteBuffer(wifi, buffer, size);
    }
#endif

bool RobotTweezers::Protobuf::UartRead(HardwareSerial *uart, OrientationMsg *orientation_msg)
{
    pb_byte_t buffer[MAX_MESSAGE_SIZE];
    size_t size;
    
    size = UartReadBuffer(uart, buffer);
    return (size > 0) ? Decode(buffer, size, OrientationMsg_fields, (void *)orientation_msg) : false;
}

#ifdef ESP32
    bool RobotTweezers::Protobuf::WifiRead(WiFiClient *wifi, OrientationMsg *orientation_msg)
    {
        pb_byte_t buffer[MAX_MESSAGE_SIZE];
        size_t size;
        
        size = WifiReadBuffer(wifi, buffer);
        return (size > 0) ? Decode(buffer, size, OrientationMsg_fields, (void *)orientation_msg) : false;
    }
#endif

size_t RobotTweezers::Protobuf::UartWrite(HardwareSerial *uart, const UartConnection *connection_msg)
{
    pb_byte_t buffer[MAX_MESSAGE_SIZE];
    size_t size;
    
    // Encode stream
    size = Encode(buffer, UartConnection_fields, (const void *)connection_msg);
    return UartWriteBuffer(uart, buffer, size);
}

bool RobotTweezers::Protobuf::UartRead(HardwareSerial *uart, UartConnection *connection_msg)
{
    pb_byte_t buffer[MAX_MESSAGE_SIZE];
    size_t size;
    
    size = UartReadBuffer(uart, buffer);
    return (size > 0) ? Decode(buffer, size, UartConnection_fields, (void *)connection_msg) : false;
}
