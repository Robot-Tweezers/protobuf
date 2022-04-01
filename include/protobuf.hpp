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
    private:
        /**
         * @brief Writes a Protobuf message over UART 
         * 
         * @param uart          Uart bus to use for transfer
         * @param fields        message description (provided in protobuf generated header)
         * @param data_struct   data structure to write, (must correspond to fields description)
         * @return true         Successful message encoding and transfer
         * @return false        Unsuccessful transfer
         */
        static bool UartWrite(HardwareSerial *uart, const pb_msgdesc_t *fields, const void *data_struct);

        /**
         * @brief Read a Protobuf message over UART
         * 
         * @param uart          Uart bus to use for transfer
         * @param fields        message description (provided in protobuf generated header)
         * @param data_struct   data structure to read, (must correspond to fields description)
         * @return true         Successful message decoding and transfer
         * @return false        Unsuccessful transfer
         */
        static bool UartRead(HardwareSerial *uart, const pb_msgdesc_t *fields, void *data_struct);

    public:
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