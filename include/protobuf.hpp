#ifndef _PROTOBUF_HPP_
#define _PROTOBUF_HPP_

#include <Arduino.h>

#include <pb_encode.h>
#include <pb_decode.h>

#include <orientation_msg.pb.h>
#include <uart_connection.pb.h>

#define MAX_MESSAGE_SIZE 64U
#define PROTOBUF_INTERFACE_BAUDRATE 921600U

#define TEENSY_ID 0x80
#define ESP32_ID 0xA0

namespace RobotTweezers
{
    /**
     * @brief Provides static methods for the protobuf interface
     * 
     */
    class Protobuf
    {
    public:
        /**
         * @brief Encodes a Protobuf message into a byte buffer
         * 
         * @param buffer        Byte array containing encoded message 
         * @param fields        Fields corresponding to the message being encoded (see generated header)
         * @param data_struct   Data structure to encode
         * @return size_t       Byte count of encoded byte buffer
         */
        static size_t Encode(pb_byte_t *buffer, const pb_msgdesc_t *fields, const void *data_struct);

        /**
         * @brief Decodes a byte buffer into a Protobuf message
         * 
         * @param buffer        Encoded byte buffer
         * @param size          Size of byte buffer
         * @param fields        Fields corresponding to the message type to decode to (see generated header)
         * @param data_struct   Returned data structure
         * @return true         Successful decoding 
         * @return false        Unsuccessful decoding
         */
        static bool Decode(pb_byte_t *buffer, size_t size, const pb_msgdesc_t *fields, void *data_struct);
        
        /**
         * @brief Writes a Protobuf message byte buffer over UART 
         * 
         * @param uart      Uart bus to use for transfer
         * @param buffer    Buffer to write over uart
         * @param size      Size of the buffer
         */
        static void UartWriteBuffer(HardwareSerial *uart, const pb_byte_t *buffer, const size_t size);

        /**
         * @brief Read a Protobuf message byte buffer over UART
         * 
         * @param uart      Uart bus to use for transfer
         * @param buffer    Buffer pointer to data read from uart
         * @return size_t   Size of the returned data, zero on failure
         */
        static size_t UartReadBuffer(HardwareSerial *uart, pb_byte_t *buffer);

        /**
         * @brief Write an orientation message over UART
         * 
         * @param uart              Uart bus to use for transfer
         * @param orientation_msg   Struct containing orientation information
         * @return true             Successful encoding and transfer
         * @return false            Unsuccessful transfer 
         */
        static bool UartWrite(HardwareSerial *uart, const OrientationMsg *orientation_msg);

        /**
         * @brief Read an orientation message over UART
         * 
         * @param uart              Uart bus to use for transfer
         * @param orientation_msg   Orientation struct to populate 
         * @return true             Successful decoding and transfer
         * @return false            Unsuccessful transfer 
         */
        static bool UartRead(HardwareSerial *uart, OrientationMsg *orientation_msg);

        /**
         * @brief Write an UartConnection message over UART
         * 
         * @param uart              Uart bus to use for transfer
         * @param connection_msg    Struct containing connection information
         * @return true             Successful encoding and transfer
         * @return false            Unsuccessful transfer 
         */
        static bool UartWrite(HardwareSerial *uart, const UartConnection *connection_msg);

        /**
         * @brief Read an UartConnection message over UART
         * 
         * @param uart              Uart bus to use for transfer
         * @param connection_msg    UartConnection struct to populate 
         * @return true             Successful decoding and transfer
         * @return false            Unsuccessful transfer 
         */
        static bool UartRead(HardwareSerial *uart, UartConnection *connection_msg);
    };
}

#endif // _PROTOBUF_HPP_