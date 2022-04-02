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

void RobotTweezers::Protobuf::UartWriteBuffer(HardwareSerial *uart, const pb_byte_t *buffer, const size_t size)
{
    // Write size of message as first byte, then write buffer
    uart->write(size);
    for (size_t i = 0; i < size; i++)
    {
        uart->write(buffer[i]);
    }
}

size_t RobotTweezers::Protobuf::UartReadBuffer(HardwareSerial *uart, pb_byte_t *buffer)
{
    size_t size = 0;

    if (uart->available() > 0)
    {
        // Read first byte, should indicate message size
        size = uart->read();
        for (size_t i = 0; i < size; i++)
        {
            // Read message into buffer
            buffer[i] = uart->read();
        }
    }

    return size;
}

bool RobotTweezers::Protobuf::UartWrite(HardwareSerial *uart, const OrientationMsg *orientation_msg)
{
    pb_byte_t buffer[MAX_MESSAGE_SIZE];
    size_t size;
    bool status = false;
    
    // Encode stream
    size = Encode(buffer, OrientationMsg_fields, (const void *)orientation_msg);

    if (size > 0)
    {
        status = true;
        UartWriteBuffer(uart, buffer, size);
    }

    return status;
}

bool RobotTweezers::Protobuf::UartRead(HardwareSerial *uart, OrientationMsg *orientation_msg)
{
    pb_byte_t buffer[MAX_MESSAGE_SIZE];
    size_t size;
    bool status = false;
    
    size = UartReadBuffer(uart, buffer);
    
    if (size > 0)
    {
        status = Decode(buffer, size, OrientationMsg_fields, (void *)orientation_msg);
    }

    return status;
}

bool RobotTweezers::Protobuf::UartWrite(HardwareSerial *uart, const UartConnection *connection_msg)
{
    pb_byte_t buffer[MAX_MESSAGE_SIZE];
    size_t size;
    bool status = false;
    
    // Encode stream
    size = Encode(buffer, UartConnection_fields, (const void *)connection_msg);

    if (size > 0)
    {
        status = true;
        UartWriteBuffer(uart, buffer, size);
    }

    return status;
}

bool RobotTweezers::Protobuf::UartRead(HardwareSerial *uart, UartConnection *connection_msg)
{
    pb_byte_t buffer[MAX_MESSAGE_SIZE];
    size_t size;
    bool status = false;
    
    size = UartReadBuffer(uart, buffer);
    
    if (size > 0)
    {
        status = Decode(buffer, size, UartConnection_fields, (void *)connection_msg);
    }

    return status;
}
